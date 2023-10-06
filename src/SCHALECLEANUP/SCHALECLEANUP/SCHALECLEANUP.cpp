#include <Windows.h>
#include "resource.h"

#pragma comment(lib,"Winmm.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void SCHALECLEANUP()
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_SYNC);

	if (MessageBox(NULL, L"'OK'=RUN     'CANCEL'=EXIT", L"S.C.H.A.L.E Clean Up", MB_OKCANCEL | MB_ICONQUESTION | MB_SYSTEMMODAL) == IDOK)
	{
		system("del /f /s /q C:\\Windows\\SoftwareDistribution\\Download");
	}
}

int main()
{
	SCHALECLEANUP();
}