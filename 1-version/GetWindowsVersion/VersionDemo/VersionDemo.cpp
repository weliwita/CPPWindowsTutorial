// VersionDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// need to disable warning above windows 8.1
#pragma warning (disable : 4996)

int _tmain(int argc, _TCHAR* argv[])
{
	OSVERSIONINFOEX osv = { sizeof(osv) };

	GetVersionEx((OSVERSIONINFO*)&osv);
	printf("Version: %d.%d\n", osv.dwMajorVersion, osv.dwMinorVersion);

	return 0;
}

