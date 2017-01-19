#include "stdafx.h"
#include "GenericUtilsTest.h"
#include "TimeUtil.h"
#include "CodeLocation.h"
#include "StringUtil.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

ShuangLong::ILog *g_pLog = nullptr;
void GenericUtilsTestEntry(ShuangLong::ILog *pLog)
{
	g_pLog = pLog;
	std::cout << "-------------------------------- Generic Utils Testing --------------------------------" << std::endl;

	//TimeUtilTest();// 时间相关测试
	//DirectoryUtilTest();// 文件目录相关操作测试
	StringUtilTest();
}

void TimeUtilTest()
{
	std::cout << std::endl << "---------------------------------- Time Utils Testing ----------------------------------" << std::endl;
	long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
	std::cout << "frequency: " << frequency << std::endl;
	long long curWinTime = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	std::cout << "curWinTime: " << curWinTime << std::endl;
	g_pLog->Console(SL_CODELOCATION, "PerformanceCounter: %llu", curWinTime);
	g_pLog->Console(SL_CODELOCATION, "Current Full Time String: %s", ShuangLong::Utils::TimeUtil::GetFullTimeString().c_str());

	time_t timeTest;
	tm tmStruct;
	time(&timeTest);
	timeTest += 28800;
	gmtime_s(&tmStruct, &timeTest);
	g_pLog->Console(SL_CODELOCATION, "gmtimes %04d-%02d-%02d %02d:%02d:%02d", tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);

	tm gmTime;
	tm loTime;
	gmtime_s(&gmTime, &timeTest);
	time_t gmt = mktime(&gmTime);
	localtime_s(&loTime, &timeTest);
	time_t lot = mktime(&loTime);
	double diff = difftime(gmt, lot);
	g_pLog->Console(SL_CODELOCATION, "diff = %lf", diff);

	_tzset();

	int dayLight;
	_get_daylight(&dayLight);

	long timeZone;
	int errorCode = _get_timezone(&timeZone);

	char timeZoneName[64];
	size_t t;
	_get_tzname(&t, timeZoneName, sizeof(timeZoneName), 0);

	g_pLog->Console(SL_CODELOCATION, "dayLight=%d timeZone=%ld[%d] zoneName=%s", dayLight, timeZone, errorCode, timeZoneName);

	DWORD tickCount = GetTickCount();
	clock_t clock = ::clock();
	LONGLONG counter = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	Sleep(1000);
	DWORD tickCount2 = GetTickCount();
	clock_t clock2 = ::clock();
	LONGLONG counter2 = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	g_pLog->Console("tickCount = %lu     clock = %ld     counter = %llu", tickCount2 - tickCount, clock2 - clock, (counter2 - counter)*1000/frequency);
}

void DirectoryUtilTest()
{
	std::cout << std::endl << "---------------------------------- Directory Testing ----------------------------------" << std::endl;
	char curDirBuffer[512];
	GetCurrentDirectoryA(512, curDirBuffer);
	g_pLog->Console("Current Directory: %s", curDirBuffer);

	char fullPathBuffer[512];
	char *pFilePart = nullptr;
	GetFullPathNameA("Log.h", 512, fullPathBuffer, &pFilePart);
	g_pLog->Console("Full Path: %s", fullPathBuffer);
	g_pLog->Console("File Name : %s", pFilePart);

	DWORD fileAttributes = GetFileAttributesA("Log.h");
	g_pLog->Console("File Attribut : %d", fileAttributes);

	WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
	BOOL success = GetFileAttributesExA("Log.h", GetFileExInfoStandard, &fileAttributeData);
	if (success == 0)
	{
		g_pLog->Console(SL_CODELOCATION, "Get file attributes faild %d", GetLastError());
	}
	else
	{
		g_pLog->Console("FileAttributes=%d      FileSizeHigh=%d      FileSizeLow=%d",
			fileAttributeData.dwFileAttributes, fileAttributeData.nFileSizeHigh, fileAttributeData.nFileSizeLow);

		unsigned long long ulongTime = fileAttributeData.ftCreationTime.dwHighDateTime;
		ulongTime = ulongTime << 32 | fileAttributeData.ftCreationTime.dwLowDateTime;
		g_pLog->Console("CreationTime: 0x%X  0x%X    ulong: %llu",
			fileAttributeData.ftCreationTime.dwHighDateTime, fileAttributeData.ftCreationTime.dwLowDateTime, ulongTime);

		SYSTEMTIME sysTime;
		FILETIME localFileTime;
		FileTimeToLocalFileTime(&fileAttributeData.ftCreationTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		FileTimeToLocalFileTime(&fileAttributeData.ftLastWriteTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		FileTimeToLocalFileTime(&fileAttributeData.ftLastAccessTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		ULARGE_INTEGER largeTime;
		largeTime.HighPart = fileAttributeData.ftCreationTime.dwHighDateTime;
		largeTime.LowPart = fileAttributeData.ftCreationTime.dwLowDateTime;
		g_pLog->Console("LargeTime: %I64u", largeTime.QuadPart);
		g_pLog->Console("LargeTime: %llu", largeTime.QuadPart);
	}
}

void StringUtilTest()
{
	std::string test = "\t sdfsdf  sdfsdf  \t";
	std::cout << "BEGIN" << test << "END" << std::endl;
	std::cout << "BEGIN:" << ShuangLong::Utils::StringUtil::Trim(test) << "END" << std::endl;

	std::wstring wtest = L"\t sdfsdf  sdfsdf  \t";
	std::wcout << "BEGIN" << wtest << "END" << std::endl;
	std::wcout << "BEGIN:" << ShuangLong::Utils::StringUtil::WTrim(wtest) << "END" << std::endl;

	std::vector<std::string> nameVector;
	std::string nameString = "shuanglong,airu,yaru,longlong";
	unsigned int count = ShuangLong::Utils::StringUtil::Split(nameVector, nameString, ',');
	g_pLog->Console(SL_CODELOCATION, "count=%u", count);
	for (int i=0;i<count;i++)
	{
		g_pLog->Console("name[%d] = %s", i, nameVector[i].c_str());
	}

	std::vector<std::string>::iterator it;
	int index = 0;
	for (it = nameVector.begin(); it != nameVector.end(); it++)
	{
		g_pLog->Console("name[%d] = %s", index++, it->c_str());
	}
}
