#pragma once

#include "Log.h"

namespace ShuangLong
{
    class ProcessUtilTest sealed
    {
    private:
        ProcessUtilTest();
        Log* mpLog = nullptr;

    public:
        ~ProcessUtilTest();

        static ProcessUtilTest *mpInstance;
        static void Entry();

        void ProcessUtilTest_EnumProcess();
        void ProcessUtilTest_CreateSnapshot();
        void ProcessUtilTest_GetPerformanceInfo();
    };
}
