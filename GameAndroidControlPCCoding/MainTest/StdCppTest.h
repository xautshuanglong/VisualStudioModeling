#pragma once

#include "Log.h"

namespace Shuanglong::Test
{
    class StdCppTest sealed
    {
    private:
        StdCppTest();
        StdCppTest(const char* name);
        Log*                    mpLog;
        const char             *mpName;
        static StdCppTest      *mpInstance;

        class SingleHelpper
        {
        public:
            SingleHelpper() {}
            ~SingleHelpper()
            {
                if (mpInstance != nullptr)
                {
                    delete mpInstance;
                    mpInstance = nullptr;
                }
            }
        };
        static SingleHelpper    mHelpper;

    public:
        ~StdCppTest();
        static void Entry();

    private:
        void SharedPointerTypedefTest();
        void SharedPointerHelperFunc();
    };
}

