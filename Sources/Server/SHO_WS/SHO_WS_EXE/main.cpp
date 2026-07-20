#include <cstdio>
#include <filesystem>
#include <string>
#include <tuple>
#include <unordered_map>

#include <crtdbg.h>

#include <Windows.h>

#include <SHO_WS_DLL.H>

BOOL WINAPI CloseHandler(_In_ DWORD dwCtrlType);

HWND MakeDummyWindow(HINSTANCE instance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class ConsoleAPI: public EXE_WS_API
{
public:
	ConsoleAPI(wchar_t const *const logFileName);
	~ConsoleAPI() noexcept;

	void __stdcall SetUserCNT(int iUserCNT) override;

	void __stdcall WriteLOG(char *szString) override;
	void __stdcall SetListItemINT(void *pListItem, int iSubStrIDX, int iValue) override;
	void __stdcall SetListItemSTR(void *pListItem, int iSubStrIDX, char *szStr) override;

	void *__stdcall AddChannelITEM(
		void *pOwner,
		short nChannelNO,
		char *szChannelName,
		char *szServerIP,
		int iPortNO) override;

	void __stdcall DelChannelITEM(void *pListItem) override;

	void *__stdcall AddUserITEM(
		void *pUser,
		char *szAccount,
		char *szCharName,
		char *szIP) override;
	void __stdcall DelUserITEM(void *pListItem) override;

private:
	FILE *logFile;
	std::unordered_map<void*, std::string> channels;
	std::unordered_map<void*, std::tuple<std::string, std::string, std::string>> users;
};

struct Settings
{
	Settings(std::string const& fileName);

	std::string dataDir, dbIp, dbName, dbUser, dbPass, logDbUser, logDbPass;
	std::string worldName, loginServerIP;
	short loginServerPort, gameServerPort, clientPort;
	int languageType;
	bool blockCreateChar;
};

bool quit = false;

int wmain(int argc, wchar_t *argv[])
{
	SetConsoleCtrlHandler(CloseHandler, TRUE);

	HINSTANCE applicationInstance = GetModuleHandle(nullptr);
	SetConsoleCP(51949);

	if(GetFileAttributesA("SHO_WS.ini") == INVALID_FILE_ATTRIBUTES)
	{
		fputs("SHO_WS.ini not found.", stderr);
		return EXIT_FAILURE;
	}

	std::filesystem::path iniPath = std::filesystem::current_path() / "SHO_WS.ini";
	Settings settings(iniPath.generic_u8string().c_str());

	ConsoleAPI api(L"SHO_WS.log");

	HWND window = MakeDummyWindow(applicationInstance);
	if(!window)
	{
		fputs("Error creating dummy window.", stderr);
		return EXIT_FAILURE;
	}

	bool started = WS_Init(
		applicationInstance,
		settings.dataDir.data(),
		settings.languageType,
		&api);

	if(!started)
	{
		fputs("Error initializing world server.", stderr);
		return EXIT_FAILURE;
	}

	started = WS_ConnectDB(
		settings.dbIp.data(),
		settings.dbName.data(),
		settings.dbUser.data(),
		settings.dbPass.data(),
		settings.logDbUser.data(),
		settings.logDbPass.data());

	if(!started)
	{
		fputs("Error connecting to database.", stderr);
		WS_Free();
		return EXIT_FAILURE;
	}

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);
	//_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);

	//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	//_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	//_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	/*_CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF
		//| _CRTDBG_CHECK_ALWAYS_DF
		| _CRTDBG_CHECK_CRT_DF
		| _CRTDBG_DELAY_FREE_MEM_DF
		//| _CRTDBG_LEAK_CHECK_DF
		| _CRTDBG_CHECK_EVERY_1024_DF);*/

	char const *ip = "127.0.0.1";
	started = WS_Start(
		window,
		settings.worldName.data(),
		settings.loginServerIP.data(),
		settings.loginServerPort,
		const_cast<char *>(ip),
		19999,
		settings.gameServerPort,
		settings.clientPort,
		settings.blockCreateChar);

	if(!started)
	{
		fputs("Error starting world server.", stderr);
		WS_Shutdown();
		WS_Free();

		return EXIT_FAILURE;
	}

	WS_StartCLI_SOCKET();

	MSG message;
	HACCEL accelTable = nullptr;
	while(GetMessage(&message, nullptr, 0, 0) && !quit)
	{
		if (!TranslateAccelerator(message.hwnd, accelTable, &message))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	WS_ShutdownCLI_SOCKET();
	WS_Shutdown();
	WS_Free();

	_CrtDumpMemoryLeaks();

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

ConsoleAPI::ConsoleAPI(wchar_t const *const logFileName)
	: logFile(nullptr)
	, channels()
	, users()
{
	logFile = _wfopen(logFileName, L"a");
	if(!logFile)
		throw std::runtime_error("Error opening log file!");
}

ConsoleAPI::~ConsoleAPI() noexcept
{
	fflush(logFile);
	fclose(logFile);
}

void ConsoleAPI::WriteLOG(char *szString)
{
	printf(szString);
	fprintf(logFile, szString);
}

void ConsoleAPI::SetUserCNT(int userCount)
{
	printf("User count: %d\n", userCount);
}

void ConsoleAPI::SetListItemINT(
	void */*pListItem*/,
	int /*iSubStrIDX*/,
	int /*iValue*/)
{
}

void ConsoleAPI::SetListItemSTR(
	void */*pListItem*/,
	int /*iSubStrIDX*/,
	char */*szStr*/)
{
}

void *ConsoleAPI::AddChannelITEM(
	void *pOwner,
	short nChannelNO,
	char *szChannelName,
	char *szServerIP,
	int iPortNO)
{
	printf(
		"Connected to game server: index: %d name: %s, IP: %s, port: %d\n",
		nChannelNO,
		szChannelName,
		szServerIP,
		iPortNO);

	channels[pOwner] = szServerIP;

	return pOwner;
}

void ConsoleAPI::DelChannelITEM(void *pListItem)
{
	auto const it = channels.find(pListItem);

	if(it == channels.end())
	{
		puts("Unknown game server disconnect.");
		return;
	}

	printf("Disconnected from game server: %s\n", it->second.c_str());
	channels.erase(it);
}

void *ConsoleAPI::AddUserITEM(
	void *pUser,
	char *szAccount,
	char *szCharName,
	char *szIP)
{
	printf(
		"User connected: account name: %s, char name: %s, IP: %s\n",
		szAccount,
		szCharName,
		szIP);

	users[pUser] = std::make_tuple(
		std::string(szAccount),
		std::string(szCharName),
		std::string(szIP));

	return pUser;
}

void ConsoleAPI::DelUserITEM(void *pListItem)
{
	auto const it = users.find(pListItem);

	if(it == users.end())
	{
		puts("Unknown user disconnect.");
		return;
	}

	auto const &tup = it->second;

	printf(
		"User disconnected: account name: %s, char name: %s, IP: %s\n",
		std::get<0>(tup).c_str(),
		std::get<1>(tup).c_str(),
		std::get<2>(tup).c_str());

	users.erase(it);
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
	wcex.lpszClassName = "SHO_WS_CONSOLE";
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	HWND ret = CreateWindow(
		"SHO_WS_CONSOLE",
		"SHO_WS_CONSOLE",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		instance,
		nullptr);

	if(!ret)
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
	switch(message)
	{
	case WM_DESTROY:
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Settings::Settings(std::string const &fileName)
{
	char buf[256];
	memset(buf, 0, 256);

	DWORD end = GetPrivateProfileStringA(
		"FormDataDIR",
		"EditDataDIR",
		"C:\\SHO\\srvData",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dataDir = buf;

	languageType = GetPrivateProfileIntA(
		"FormDataDIR",
		"selIdx_ComboBoxLANG",
		1,
		fileName.c_str());

	gameServerPort = GetPrivateProfileIntA(
		"FormWSCFG",
		"EditZoneListenPORT",
		19005,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditLoginServerIP",
		"127.0.0.1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	loginServerIP = buf;

	loginServerPort = GetPrivateProfileIntA(
		"FormWSCFG",
		"EditLoginServerPORT",
		19000,
		fileName.c_str());

	clientPort = GetPrivateProfileIntA(
		"FormWSCFG",
		"EditUserListenPORT",
		29100,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditWorldNAME",
		"1World 1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	worldName = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditDBServerIP",
		"127.0.0.1",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbIp = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditDBTableName",
		"SHO",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbName = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditDBAccount",
		"sa",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbUser = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditDBPW",
		"password",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	dbPass = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditLogAccount",
		"sa",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	logDbUser = buf;

	end = GetPrivateProfileStringA(
		"FormWSCFG",
		"EditLogPW",
		"password",
		buf,
		256,
		fileName.c_str());

	buf[++end] = 0;

	logDbPass = buf;

	blockCreateChar = GetPrivateProfileIntA(
		"FormWSCFG",
		"CheckBoxCreateChar",
		0,
		fileName.c_str());
}
