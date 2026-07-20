#include <cstdio>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <Windows.h>

#include <SHO_LS_DLL.H>

BOOL WINAPI CloseHandler(_In_ DWORD dwCtrlType);

HWND MakeDummyWindow(HINSTANCE instance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class ConsoleAPI: public EXE_LS_API
{
public:
	ConsoleAPI(wchar_t const *const logFileName);
	~ConsoleAPI() noexcept;

	void __stdcall WriteLOG(char *szString) override;
	void __stdcall SetListItemINT(
		void *pListItem,
		int iSubStrIDX,
		int iValue) override;
	void __stdcall SetListItemSTR(
		void *pListItem,
		int iSubStrIDX,
		char *szStr) override;

	void *__stdcall AddConnectorITEM(void *pOwner, char *szIP) override;
	void __stdcall DelConnectorITEM(void *pListItem) override;

	void *__stdcall AddWorldITEM(
		void *pOwner,
		char *szWorld,
		char *szIP,
		int iPort,
		unsigned int dwRight) override;

	void __stdcall DelWorldITEM(void *pListItem) override;

	void *__stdcall AddBlockITEM(
		void *pOwner,
		char *szIP,
		unsigned int dwEndTime) override;

	void __stdcall DelBlockITEM(void *pListItem) override;

	void __stdcall SetStatusBarTEXT(unsigned int iItemIDX, char *szText) override;

private:
	FILE *logFile;
	std::unordered_map<void*, std::string> connections, blocks, worldServers;
};

struct Settings
{
	Settings(std::string const& fileName);

	std::string ip, monitorPassword, dbName, dbUser, dbPassword;
	short port, clientPort;
	unsigned int loginRight;
	int maxUsers;
	bool showOnlyWorldServer;
};

bool quit = false;

int wmain(int argc, wchar_t *argv[])
{
	SetConsoleCtrlHandler(CloseHandler, TRUE);

	HINSTANCE applicationInstance = GetModuleHandle(nullptr);
	SetConsoleCP(51949);

	if(GetFileAttributesA("SHO_LS.ini") == INVALID_FILE_ATTRIBUTES)
	{
		fputs("SHO_LS.ini not found.", stderr);
		return EXIT_FAILURE;
	}

	std::filesystem::path iniPath = std::filesystem::current_path() / "SHO_LS.ini";
	Settings settings(iniPath.generic_u8string().c_str());

	ConsoleAPI api(L"SHO_LS.log");

	HWND window = MakeDummyWindow(applicationInstance);
	if(!window)
	{
		fputs("Error creating dummy window.", stderr);
		return EXIT_FAILURE;
	}

	bool started = LS_Init(applicationInstance, &api);

	if(!started)
	{
		fputs("Error initializing login server.", stderr);
		return EXIT_FAILURE;
	}

	char const *ip = "127.0.0.1";
	started = LS_StartServerSOCKET(
		window,
		settings.ip.data(),
		settings.dbName,
		settings.dbUser,
		settings.dbPassword,
		settings.port,
		settings.loginRight,
		const_cast<char *>(ip),
		20000,
		settings.showOnlyWorldServer);

	if(!started)
	{
		fputs("Error starting loging server socket.", stderr);
		LS_Free();
		return EXIT_FAILURE;
	}

	BYTE md5[32];
	memcpy(
		&md5,
		settings.monitorPassword.c_str(),
		settings.monitorPassword.size());

	started = LS_StartClientSOCKET(settings.clientPort, settings.maxUsers, md5);

	if(!started)
	{
		fputs("Error starting client socket.", stderr);
		LS_Shutdown();
		LS_Free();

		return EXIT_FAILURE;
	}

	MSG message;
	HACCEL accelTable = nullptr;
	while(GetMessage(&message, nullptr, 0, 0) && !quit)
	{
		if(!TranslateAccelerator(message.hwnd, accelTable, &message))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	LS_CloseClientSOCKET();
	LS_Shutdown();
	LS_Free();

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
	, connections()
	, blocks()
	, worldServers()
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

void *ConsoleAPI::AddConnectorITEM(void *pOwner, char *szIP)
{
	printf("Connected: %s\n", szIP);
	connections[pOwner] = szIP;

	return pOwner;
}

void ConsoleAPI::DelConnectorITEM(void *pListItem)
{
	auto const it = connections.find(pListItem);

	if(it == connections.end())
	{
		puts("Unknown disconnect.");
		return;
	}

	printf("Disconnected: %s\n", it->second.c_str());
	connections.erase(it);
}

void *ConsoleAPI::AddWorldITEM(
	void *pOwner,
	char *szWorld,
	char *szIP,
	int iPort,
	unsigned int dwRight)
{
	printf(
		"Connected to world server: name: %s, IP: %s, port: %d, long right: %d\n",
		szWorld,
		szIP,
		iPort,
		dwRight);

	worldServers[pOwner] = szWorld;

	return pOwner;
}

void ConsoleAPI::DelWorldITEM(void *pListItem)
{
	auto const it = worldServers.find(pListItem);

	if(it == worldServers.end())
	{
		puts("Unknown world server disconnect.");
		return;
	}

	printf("World server disconnected: %s\n", it->second.c_str());
	worldServers.erase(it);
}

void *ConsoleAPI::AddBlockITEM(
	void *pOwner,
	char *szIP,
	unsigned int dwEndTime)
{
	printf("Add block: IP: %s, end time: %d", szIP, dwEndTime);
	blocks[pOwner] = szIP;

	return pOwner;
}

void ConsoleAPI::DelBlockITEM(void *pListItem)
{
	auto const it = blocks.find(pListItem);

	if(it == blocks.end())
	{
		puts("Unknown unblock.");
		return;
	}

	printf("Block removed: %s\n", it->second.c_str());
	blocks.erase(it);
}

void ConsoleAPI::SetStatusBarTEXT(unsigned int /*iItemIDX*/, char */*szText*/)
{
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
	wcex.lpszClassName = "SHO_LS_CONSOLE";
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	HWND ret = CreateWindow(
		"SHO_LS_CONSOLE",
		"SHO_LS_CONSOLE",
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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch(message)
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

Settings::Settings(std::string const &fileName)
{
	char buf[128];
	memset(buf, 0, 128);
	DWORD end = GetPrivateProfileStringA(
		"FormLSCFG",
		"EditDBIP",
		"127.0.0.1",
		buf,
		128,
		fileName.c_str());

	buf[++end] = 0;
	ip = buf;

	clientPort = GetPrivateProfileIntA(
		"FormLSCFG",
		"EditClientPort",
		29000,
		fileName.c_str());

	port = GetPrivateProfileIntA(
		"FormLSCFG",
		"EditServerPort",
		19000,
		fileName.c_str());

	loginRight = GetPrivateProfileIntA(
		"FormLSCFG",
		"EditLoginRight",
		1,
		fileName.c_str());

	maxUsers = GetPrivateProfileIntA(
		"FormLSCFG",
		"EditLimitUserCNT",
		1500,
		fileName.c_str());

	showOnlyWorldServer = GetPrivateProfileIntA(
		"FormLSCFG",
		"CheckBoxWS",
		0,
		fileName.c_str());

	end = GetPrivateProfileStringA(
		"FormLSCFG",
		"EditPW",
		"4cfec6ac15c56014472852bec92321cb", // p@ssword1
		buf,
		32,
		fileName.c_str());

	buf[++end] = 0;
	monitorPassword = buf;

	end = GetPrivateProfileStringA(
		"FormLSCFG",
		"EditLoginAccountDBName",
		"SEVEN_ORA",
		buf,
		128,
		fileName.c_str());

	buf[++end] = 0;
	dbName = buf;

	end = GetPrivateProfileStringA(
		"FormLSCFG",
		"EditLoginAccountDBUser",
		"sa",
		buf,
		128,
		fileName.c_str());

	buf[++end] = 0;
	dbUser = buf;

	end = GetPrivateProfileStringA(
		"FormLSCFG",
		"EditLoginAccountDBPassword",
		"p@ssword1",
		buf,
		128,
		fileName.c_str());

	buf[++end] = 0;
	dbPassword = buf;
}
