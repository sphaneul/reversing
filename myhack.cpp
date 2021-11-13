#include<tchar.h>
#include<Windows.h>

#pragma comment(lib,"urlmon.lib")

#define DEF_URL L"http://www.naver.com/index.html"
#define DEF_FILE_NAME L"C:\\index.html"

HMODULE g_hMod = NULL;

DWORD WINAPI ThreadProc(LPVOID IParam) {
	TCHAR szPath[_MAX_PATH] = { 0, };
	memset(szPath, 0, _MAX_PATH);

	if (!GetModuleFileName(g_hMod, szPath, MAX_PATH))
		return FALSE;
	TCHAR* p = _tcsrchr(szPath, '\\');
	if (!p)
		return FALSE;
	_tcscpy_s(p + 1, _MAX_PATH, DEF_FILE_NAME);
	URLDownloadToFile(NULL, DEF_URL, DEF_FILE_NAME, 0, NULL);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID IpvReserved) {
	
	HANDLE hThread = NULL;
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"myhack.dll Injection!!!");
		hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		CloseHandle(hThread);
		break;
	}
	return TRUE;
}