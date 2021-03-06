#include "stdafx.h"

#include <iostream>

#define VLD_FORCE_ENABLE
#include <vld/vld.h>
#include <google/protobuf/stubs/common.h>

#include "Log.h"
#include <Utils/CodeLocation.h>
//-------------- GenericUtils --------------
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
#include "DirectoryUtilTest.h"
#include "TestClassTest.h"
#include "UpPrivilegeTest.h"
#include "VersionUtilTest.h"
#include "ProcessUtilTest.h"
#include "ThumbnailTest.h"
#include "StdCppTest.h"
#include "StdStlTest.h"
#include "UnhandlerExceptionTest.h"
#include "WaitMultiEventTest.h"
#include "JsonTest.h"
#include "TinyXml2Test.h"
#include "MD5Test.h"
#include "WindowsInfoLookerTest.h"
#include "CryptogramTest.h"
#include "MySQLConnectionTest.h"
#include "MultiThreadTest.h"
#include "RandomNumberTest.h"
//------------ LibCurl -------------
#include "LibcurlHttpTest.h"
//------------ ProtoBuf -------------
#include "UserInfoTest.h"
//------------ TcpUdpCommunication -------------
#include "TcpSocketServerTest.h"
#include "UdpSocketServerTest.h"

BOOL ConsoleEventHandler(DWORD dwCtrlType);

int main(int argc, char** argv)
{
    BOOL retValue = SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, TRUE);
    std::cout << "====================================== Main Testing ======================================" << std::endl;
    Shuanglong::Log *pLog = Shuanglong::Log::GetInstance();
    pLog->Console(SL_CODE_LOCATION, "LogTest tid=%u", GetCurrentThreadId());

    //---------------------- Json Testing ----------------------
    Shuanglong::Test::JsonTest::Entry();
    Shuanglong::Test::JsonTest::Exit();

    //---------------------- TinyXml2 Testing ----------------------
    Shuanglong::Test::TinyXml2Test::Entry();
    Shuanglong::Test::TinyXml2Test::Exit();

    //---------------------- MD5 Testing ----------------------
    Shuanglong::Test::MD5Test::Entry();
    Shuanglong::Test::MD5Test::Exit();

    //--------------------- GenericUtils Testing ---------------------
    //Shuanglong::TestClassTest::Entry();
    //Shuanglong::Test::StringUtilTest::Entry();
    //Shuanglong::Test::TimeUtilTest::Entry();
    Shuanglong::Test::DirectoryUtilTest::Entry();
    Shuanglong::Test::DirectoryUtilTest::Exit();
    //Shuanglong::Test::UpPrivilegeTest::Entry();
    //Shuanglong::Test::VersionUtilTest::Entry();
    //Shuanglong::Test::ProcessUtilTest::Entry();
    //Shuanglong::Test::ThumbnailTest::Entry();
    Shuanglong::Test::StdCppTest::Entry();
    Shuanglong::Test::StdStlTest::Entry();
    //Shuanglong::Test::UnhandlerExceptionTest::GetInstance();
    //Shuanglong::Test::WaitMultiEventTest::GetInstance()->Entry();
    //Shuanglong::Test::WaitMultiEventTest::GetInstance()->Exit();
    Shuanglong::Test::CryptogramTest::Entry();
    Shuanglong::Test::CryptogramTest::Exit();
    Shuanglong::Test::MySQLConnectionTest::Entry();
    Shuanglong::Test::MySQLConnectionTest::Exit();

    Shuanglong::Test::WindowsInfoLookerTest::GetInstance()->Entry();

    //Shell_NotifyIcon
    //FindFirstFile
    //FindFirstFile

    //--------------------- LibCurl Testing --------------------
    Shuanglong::Test::LibcurlHttpTest::GetInstance()->Entry();
    Shuanglong::Test::LibcurlHttpTest::GetInstance()->Exit();

    //--------------------- Protobuf Testing --------------------
    Shuanglong::Test::UserInfoTest::GetInstance()->Entry();
    Shuanglong::Test::UserInfoTest::GetInstance()->Exit();

    //--------------------- TcpUdpCommunication Testing ---------------------
    Shuanglong::Test::TcpSocketServerTest::Entry();
    Shuanglong::Test::UdpSocketServerTest::Entry();

    //------------------------ Multiple Thread Testing ------------------------
    Shuanglong::Test::MultiThreadTest::GetInstance()->Entry();

    //------------------------ Random Number Testing ------------------------
    Shuanglong::Test::RandomNumberTest::GetInstance()->Entry();
    Shuanglong::Test::RandomNumberTest::GetInstance()->Exit();

    //Shuanglong::Utils::SingletonUtil<Shuanglong::Test::RandomNumberTest>::GetInstance()->Entry();
    //Shuanglong::Utils::SingletonUtil<Shuanglong::Test::RandomNumberTest>::GetInstance()->Exit();

    std::cout << "Press any key to exit !" << std::endl;
    getchar();

    Shuanglong::Test::TcpSocketServerTest::Exit();
    Shuanglong::Test::UdpSocketServerTest::Exit();

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleEventHandler, FALSE);

    google::protobuf::ShutdownProtobufLibrary(); // VLD ��⵽ ProtoBuf �ڴ�й©�����䣺repeated ���� add_foo --> clear_foo��
    return 0;
}

BOOL ConsoleEventHandler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT:
        printf_s("Control + C\n");
        Shuanglong::Test::UdpSocketServerTest::Exit();
        break;
    case CTRL_BREAK_EVENT:
        printf_s("Control + Break\n");
        break;
    case CTRL_CLOSE_EVENT:
        printf_s("Close\n");
        Shuanglong::Test::UdpSocketServerTest::Exit();
        break;
    case CTRL_LOGOFF_EVENT:
        printf_s("User is logging off\n");
        break;
    case CTRL_SHUTDOWN_EVENT:
        printf_s("The system is shutting down\n");
        break;
    default:
        break;
    }

    return FALSE;
}

