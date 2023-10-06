#include <Windows.h>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void SCHALECLEANUP()
{
	if (MessageBox(NULL, L"'OK'=RUN     'CANCEL'=EXIT", L"S.C.H.A.L.E Clean Up", MB_OKCANCEL | MB_ICONQUESTION | MB_SYSTEMMODAL) == IDOK)
	{
		system("del /f /s /q C:\\Windows\\SoftwareDistribution\\Download");
	}
}

int main()
{
	SCHALECLEANUP();
}