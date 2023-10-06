#include <Windows.h>
#include <string>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

BOOL CALLBACK EnumWinProc(_In_ HWND hwnd, _In_ LPARAM lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);

	if (hDefView != 0)
	{
		HWND hWorkerW = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerW, SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void SCHALEWALLPAPER()
{
	std::string p1 = "C:\\SCHALE\\ffplay.exe C:\\SCHALE\\SCHALE.mp4 -noborder -x ";
	std::string p2 = std::to_string(GetSystemMetrics(SM_CXSCREEN));
	std::string p3 = " -y ";
	std::string p4 = std::to_string(GetSystemMetrics(SM_CYSCREEN));
	std::string p5 = " -loop 0";

	std::string COMMAND;
	const char* SCHALECOMMAND = NULL;

	COMMAND = p1 + p2 + p3 + p4 + p5;
	SCHALECOMMAND = COMMAND.c_str();

	if (system(SCHALECOMMAND))
	{
		Sleep(200);

		HWND hProgman = FindWindow(L"Progman", 0);
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);
		HWND hffplay = FindWindow(L"SDL_app", 0);
		SetParent(hffplay, hProgman);
		EnumWindows(EnumWinProc, 0);
	}
}

int main()
{
	SCHALEWALLPAPER();
}