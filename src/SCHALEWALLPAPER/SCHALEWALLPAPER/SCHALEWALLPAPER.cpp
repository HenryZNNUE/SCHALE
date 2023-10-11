#include <Windows.h>
#include <stdio.h>
#include <string>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowExW(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0)
	{
		HWND hWorkerw = FindWindowExW(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);
		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{
	HWND hwd = ::GetDesktopWindow();
	HDC hdc = ::GetDC(hwd);

	LPCWSTR lpParameter = L" C:\\SCHALE\\SCHALE.mp4 -noborder -x 2560 -y 1440 -loop 0";
	STARTUPINFOW si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	std::wstring s1 = L" C:\\SCHALE\\SCHALE.mp4 -noborder -x ";
	std::wstring s2 = std::to_wstring(GetDeviceCaps(hdc, DESKTOPHORZRES));
	std::wstring s3 = L" -y ";
	std::wstring s4 = std::to_wstring(GetDeviceCaps(hdc, DESKTOPVERTRES));
	std::wstring s5 = L" -loop 0";

	std::wstring C;
	LPCWSTR S;
	C = s1 + s2 + s3 + s4 + s5;
	S = C.c_str();

	if (CreateProcessW(L"C:\\SCHALE\\ffplay.exe", (LPWSTR)S, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi))
	{
		Sleep(2000);
		HWND hProgman = FindWindowW(L"Progman", 0);
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);
		HWND hFfplay = FindWindowW(L"SDL_app", 0);
		SetParent(hFfplay, hProgman);
		EnumWindows(EnumWindowsProc, 0);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}