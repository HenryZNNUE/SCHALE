#include <Windows.h>
#include <time.h>
#include "resource.h"

#pragma comment(lib,"Winmm.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void SCHALE()
{
	time_t t = time(NULL);
	tm* t_tm = localtime(&t);
	time_t tt = mktime(t_tm);
	int y = t_tm->tm_year + 1900;
	int m = t_tm->tm_mon + 1;
	int d = t_tm->tm_mday;
	int h = t_tm->tm_hour;
	int min = t_tm->tm_min;
	int sec = t_tm->tm_sec;

	if (h >= 5 && h < 11)
	{
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_SYNC);
	}

	if (h >= 11 && h < 18)
	{
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_SYNC);
	}

	if (h >= 18 || h < 5)
	{
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_SYNC);
	}

	MessageBox(NULL, L"Welcome to S.C.H.A.L.E System", L"S.C.H.A.L.E", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

int main()
{
	Sleep(3000);
	SCHALE();
}