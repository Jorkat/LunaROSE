#include <cstdio>
#include <filesystem>
#include <string>
#include <tuple>
#include <unordered_map>

#include <Windows.h>

#include <SHO_GS_DLL.H>

#include <DbgHelp.h>
#include <ctime>
#include <exception>
#include <stdexcept>

#pragma comment(lib, "Dbghelp.lib")

BOOL WINAPI CloseHandler(_In_ DWORD dwCtrlType);

HWND MakeDummyWindow(HINSTANCE instance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class ConsoleAPI : public EXE_GS_API
{
public:
	ConsoleAPI(wchar_t const* const logFileName);
	~ConsoleAPI() noexcept;

	void __stdcall SetUserCNT(int iUserCNT) override;

	void __stdcall WriteLOG(char* szString) override;
	void __stdcall SetListItemINT(void* pListItem, int iSubStrIDX, int iValue) override;
	void __stdcall SetListItemSTR(void* pListItem, int iSubStrIDX, char* szStr) override;

	void* __stdcall	AddZoneITEM(void* pOwner, short nZoneNO, char* szZoneName) override;
	void __stdcall DelZoneITEM(void* pListItem) override;

private:
	FILE* logFile;
	std::unordered_map<void*, std::string> zones;
};

struct Settings
{
	Settings(std::string const& fileName);

	std::string dataDir, dbIp, dbName, dbUser, dbPass;
	std::string logDbUser, logDbPass, mallDbUser, mallDbPass;
	std::string worldServerIP, channelName, clientIp;
	short worldServerPort, clientPort;
	int languageType, channelIndex, busyCount, fullCount, userLimit;
};

bool quit = false;

static void WriteCrashText(
	const char* crashLogName,
	EXCEPTION_POINTERS* exceptionInfo)
{
	FILE* crashLog = nullptr;

	if (fopen_s(&crashLog, crashLogName, "a") != 0 || !crashLog)
		return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	fprintf(
		crashLog,
		"\n============================================================\n"
		"GameServer crash: %04u-%02u-%02u %02u:%02u:%02u\n",
		time.wYear,
		time.wMonth,
		time.wDay,
		time.wHour,
		time.wMinute,
		time.wSecond);

	if (exceptionInfo && exceptionInfo->ExceptionRecord)
	{
		const EXCEPTION_RECORD* record = exceptionInfo->ExceptionRecord;

		fprintf(
			crashLog,
			"Exception code   : 0x%08lX\n"
			"Exception address: 0x%p\n"
			"Thread ID        : %lu\n",
			record->ExceptionCode,
			record->ExceptionAddress,
			GetCurrentThreadId());

		switch (record->ExceptionCode)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			fprintf(crashLog, "Reason           : Access violation\n");

			if (record->NumberParameters >= 2)
			{
				const char* operation = "unknown operation";

				if (record->ExceptionInformation[0] == 0)
					operation = "reading";
				else if (record->ExceptionInformation[0] == 1)
					operation = "writing";
				else if (record->ExceptionInformation[0] == 8)
					operation = "executing";

				fprintf(
					crashLog,
					"Memory operation : %s address 0x%p\n",
					operation,
					reinterpret_cast<void*>(
						record->ExceptionInformation[1]));
			}
			break;

		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			fprintf(crashLog, "Reason           : Integer divide by zero\n");
			break;

		case EXCEPTION_STACK_OVERFLOW:
			fprintf(crashLog, "Reason           : Stack overflow\n");
			break;

		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			fprintf(crashLog, "Reason           : Array bounds exceeded\n");
			break;

		case EXCEPTION_ILLEGAL_INSTRUCTION:
			fprintf(crashLog, "Reason           : Illegal instruction\n");
			break;

		default:
			fprintf(crashLog, "Reason           : Unknown/unhandled exception\n");
			break;
		}
	}
	else
	{
		fprintf(crashLog, "No EXCEPTION_POINTERS information available.\n");
	}

	fflush(crashLog);
	fclose(crashLog);
}

static void WriteMiniDump(
	const char* dumpFileName,
	EXCEPTION_POINTERS* exceptionInfo)
{
	HANDLE dumpFile = CreateFileA(
		dumpFileName,
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (dumpFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION dumpInfo{};
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ExceptionPointers = exceptionInfo;
	dumpInfo.ClientPointers = FALSE;

	const MINIDUMP_TYPE dumpType = static_cast<MINIDUMP_TYPE>(
		MiniDumpWithDataSegs |
		MiniDumpWithHandleData |
		MiniDumpWithThreadInfo |
		MiniDumpWithIndirectlyReferencedMemory);

	const BOOL dumpCreated = MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		dumpFile,
		dumpType,
		exceptionInfo ? &dumpInfo : nullptr,
		nullptr,
		nullptr);

	if (!dumpCreated)
	{
		const DWORD errorCode = GetLastError();

		char errorMessage[256]{};
		sprintf_s(
			errorMessage,
			"MiniDumpWriteDump failed. Windows error: %lu\n",
			errorCode);

		OutputDebugStringA(errorMessage);
	}

	FlushFileBuffers(dumpFile);
	CloseHandle(dumpFile);
}

static LONG WINAPI GameServerCrashHandler(
	EXCEPTION_POINTERS* exceptionInfo)
{
	SYSTEMTIME time{};
	GetLocalTime(&time);

	char crashLogName[MAX_PATH]{};
	char dumpFileName[MAX_PATH]{};

	sprintf_s(
		crashLogName,
		"SHO_GS_CRASH_%04u-%02u-%02u_%02u-%02u-%02u.log",
		time.wYear,
		time.wMonth,
		time.wDay,
		time.wHour,
		time.wMinute,
		time.wSecond);

	sprintf_s(
		dumpFileName,
		"SHO_GS_CRASH_%04u-%02u-%02u_%02u-%02u-%02u.dmp",
		time.wYear,
		time.wMonth,
		time.wDay,
		time.wHour,
		time.wMinute,
		time.wSecond);

	WriteCrashText(crashLogName, exceptionInfo);
	WriteMiniDump(dumpFileName, exceptionInfo);

	return EXCEPTION_EXECUTE_HANDLER;
}

static void TerminateHandler()
{
	FILE* crashLog = nullptr;

	if (fopen_s(&crashLog, "SHO_GS_TERMINATE.log", "a") == 0 && crashLog)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		fprintf(
			crashLog,
			"\nstd::terminate called: %04u-%02u-%02u %02u:%02u:%02u\n",
			time.wYear,
			time.wMonth,
			time.wDay,
			time.wHour,
			time.wMinute,
			time.wSecond);

		fflush(crashLog);
		fclose(crashLog);
	}

	RaiseException(
		0xE0000001,
		EXCEPTION_NONCONTINUABLE,
		0,
		nullptr);

	abort();
}

int wmain(int argc, wchar_t* argv[])
{
	SetUnhandledExceptionFilter(GameServerCrashHandler);
	std::set_terminate(TerminateHandler);

	SetConsoleCtrlHandler(CloseHandler, TRUE);

	HINSTANCE applicationInstance = GetModuleHandle(nullptr);
	SetConsoleCP(51949);

	if (GetFileAttributesA("SHO_GS.ini") == INVALID_FILE_ATTRIBUTES)
	{
		fputs("SHO_GS.ini not found.", stderr);
		return EXIT_FAILURE;
	}

	std::filesystem::path iniPath = std::filesystem::current_path() / "SHO_GS.ini";
	Settings settings(iniPath.generic_u8string().c_str());

	ConsoleAPI api(L"SHO_GS.log");

	HWND window = MakeDummyWindow(applicationInstance);
	if (!window)
	{
		fputs("Error creating dummy window.", stderr);
		return EXIT_FAILURE;
	}

	bool started = GS_Init(
		applicationInstance,
		settings.dataDir.data(),
		settings.languageType,
		&api);

	if (!started)
	{
		fputs("Error initializing game server.", stderr);
		return EXIT_FAILURE;
	}

	char const* ip = "127.0.0.1";
	started = GS_ConnectSERVER(
		settings.dbIp.data(),
		settings.dbName.data(),
		settings.dbUser.data(),
		settings.dbPass.data(),
		settings.logDbUser.data(),
		settings.logDbPass.data(),
		settings.mallDbUser.data(),
		settings.mallDbPass.data(),
		settings.worldServerIP.data(),
		settings.worldServerPort,
		const_cast<char*>(ip),
		19998);

	if (!started)
	{
		fputs("Error connecting to database.", stderr);
		GS_Free();
		return EXIT_FAILURE;
	}

	started = GS_Start(
		window,
		settings.channelName.data(),
		settings.clientIp.data(),
		settings.clientPort,
		settings.channelIndex,
		settings.busyCount,
		settings.fullCount);

	if (!started)
	{
		fputs("Error starting game server.", stderr);
		GS_Shutdown();
		GS_Free();

		return EXIT_FAILURE;
	}

	GS_SetUserLIMIT(settings.userLimit);

	MSG message;
	HACCEL accelTable = nullptr;
	while (GetMessage(&message, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(message.hwnd, accelTable, &message))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	GS_Shutdown();
	GS_Free();

	return EXIT_SUCCESS;
}

BOOL WINAPI CloseHandler(_In_ DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_C_EVENT || dwCtrlType == CTRL_CLOSE_EVENT)
	{
		quit = true;
		return TRUE;
	}

	return FALSE;
}

ConsoleAPI::ConsoleAPI(wchar_t const* const logFileName)
	: logFile(nullptr)
	, zones()
{
	logFile = _wfopen(logFileName, L"a");
	if (!logFile)
		throw std::runtime_error("Error opening log file!");
}

ConsoleAPI::~ConsoleAPI() noexcept
{
	fflush(logFile);
	fclose(logFile);
}

void ConsoleAPI::WriteLOG(char* szString)
{
	if (!szString)
		return;

	printf("%s", szString);
	fprintf(logFile, "%s", szString);

	fflush(stdout);
	fflush(logFile);
}

void ConsoleAPI::SetUserCNT(int userCount)
{
	printf("User count: %d\n", userCount);
}

void ConsoleAPI::SetListItemINT(
	void*/*pListItem*/,
	int /*iSubStrIDX*/,
	int /*iValue*/)
{
}

void ConsoleAPI::SetListItemSTR(
	void*/*pListItem*/,
	int /*iSubStrIDX*/,
	char*/*szStr*/)
{
}

void* ConsoleAPI::AddZoneITEM(
	void* pOwner,
	short nZoneNO,
	char* szZoneName)
{
	printf("Added zone: index: %d, name: %s\n", nZoneNO, szZoneName);
	zones[pOwner] = szZoneName;

	return pOwner;
}

void ConsoleAPI::DelZoneITEM(void* pListItem)
{
	auto const it = zones.find(pListItem);

	if (it == zones.end())
	{
		puts("Unknown zone disconnect.");
		return;
	}

	printf("Zone disconnected: %s\n", it->second.c_str());
	zones.erase(it);
}

HWND MakeDummyWindow(HINSTANCE instance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = 0;
	wcex.hCursor = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = "SHO_GS_CONSOLE";
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	HWND ret = CreateWindow(
		"SHO_GS_CONSOLE",
		"SHO_GS_CONSOLE",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		instance,
		nullptr);

	if (!ret)
		return nullptr;

	ShowWindow(ret, 0);
	UpdateWindow(ret);

	return ret;
}

//
// 함수: WndProc(HWND, unsigned, WORD, LONG)
//
// 목적: 주 창의 메시지를 처리합니다.
//
// WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
// WM_PAINT	- 주 창을 그립니다.
// WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴의 선택 영역을 구문 분석합니다.
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Settings::Settings(std::string const& fileName)
{
	char buf[256];
	memset(buf, 0, 256);

	DWORD end = GetPrivateProfileStringA(
		"FormDataDir",
		"EditDataDir",
		"C:\\SHO\\srvData",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dataDir = buf;

	languageType = GetPrivateProfileIntA(
		"FormDataDir",
		"selIdx_ComboBoxLANG",
		1,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditDBIP",
		"127.0.0.1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbIp = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditDBName",
		"SHO",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbName = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditDBUser",
		"sa",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbUser = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditDBPassword",
		"password",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbPass = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditLogUser",
		"sa",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	logDbUser = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditLogPassword",
		"password",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	logDbPass = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditMallUser",
		"sa",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	mallDbUser = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditMallPW",
		"password",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	mallDbPass = buf;

	end = GetPrivateProfileStringA(
		"FormDBCFG",
		"EditWorldServerIP",
		"127.0.0.1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	worldServerIP = buf;

	worldServerPort = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditLoginWorldPORT",
		19005,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormGSCFG",
		"EditWorldName",
		"Channel 1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	channelName = buf;

	channelIndex = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditChannelNO",
		1,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormGSCFG",
		"EditClientIP",
		"127.0.0.1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	clientIp = buf;

	clientPort = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditClientPORT",
		29200,
		fileName.c_str());

	busyCount = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditLowAGE",
		100,
		fileName.c_str());

	fullCount = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditHighAGE",
		750,
		fileName.c_str());

	userLimit = GetPrivateProfileIntA(
		"FormDBCFG",
		"EditMaxUSER",
		1500,
		fileName.c_str());
}