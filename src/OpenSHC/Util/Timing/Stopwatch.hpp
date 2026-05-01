/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Util/Timing/Stopwatch.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Util {
    namespace Timing {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000010
        class Stopwatch {
        public:
            dword duration_0x0; // 0x00000000 length: 4
            BOOLEnum running_0x4; // 0x00000004 length: 4
            dword startTime_0x8; // 0x00000008 length: 4
            dword stopTime_0xc; // 0x0000000C length: 4

        private:
            Stopwatch(Stopwatch const&);
            void operator=(Stopwatch const&);

            Stopwatch();
            ~Stopwatch();

        public:
            // Constructor
            Stopwatch* Cosntructor_Stopwatch();

            void start();

            void stop();
        };

        static_assert_cpp98_obj(sizeof(Stopwatch) == 16, Stopwatch);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(Stopwatch, false, Address::SHC_3BB0A8C1_0x0165271C) pDAT_Stopwatch;

    } // namespace Timing
} // namespace Util
} // namespace OpenSHC
