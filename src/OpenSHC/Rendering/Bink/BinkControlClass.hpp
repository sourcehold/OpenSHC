/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/BinkControlClass.hpp'
*/

#pragma once

#include "OpenSHC/Audio/mss/HDIGDRIVER.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStreamInt.hpp"
#include "OpenSHC/Rendering/Bink/HBINK.hpp"
#include "OpenSHC/Rendering/Bink/UnsortedBinkFlagInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::mss::HDIGDRIVER;
        using OpenSHC::Audio::mss::_enums::SHC_SoundStreamInt;
        using OpenSHC::Rendering::Bink::HBINK;
        using OpenSHC::Rendering::Bink::UnsortedBinkFlagInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000060
        class BinkControlClass {
        public:
            dword unknownParam04[2]; // 0x00000000 length: 8
            int xPos[2]; // 0x00000008 length: 8
            int yPos[2]; // 0x00000010 length: 8
            BOOLEnum frameReadyToDisplay[2]; // 0x00000018 length: 8
            dword unknownParam03[2]; // 0x00000020 length: 8
            dword unknownParam07[2]; // 0x00000028 length: 8
            dword unknown01_zero[2]; // 0x00000030 length: 8
            dword unknown02_zero[2]; // 0x00000038 length: 8
            SHC_SoundStreamInt soundStreamIndex[2]; // 0x00000040 length: 8
            dword startTime[2]; // 0x00000048 length: 8
            HBINK binkObjPtrArray[2]; // 0x00000050 length: 8
            UnsortedBinkFlagInt mapGameSurfaceType; // 0x00000058 length: 4
            UnsortedBinkFlagInt screenMenuSurfaceType_0x5c; // 0x0000005C length: 4

        private:
            BinkControlClass(BinkControlClass const&);
            void operator=(BinkControlClass const&);

            BinkControlClass();
            ~BinkControlClass();

        public:
            void zeroBinkPtrAndLoadBinkSoundSystem(HDIGDRIVER drvrPtr);

            void stopBinkPlayback(int binkObjIndex);

            void setBinkSndStreamAndStartTime(int binkObjIndex, SHC_SoundStreamInt soundStreamIndexUnk);

            void stopAllBinkPlayback();

            void playBINK(
                int binkObjIndex, char* binkFileName, DWORD param_3, DWORD param_4, int xPos, int yPos, DWORD param_7);

            void copyBinkToVideoBuffer(dword param_1);

            void processBinkFrames();

            void stopAllBinkPlaybackThunk();
        };

        static_assert_cpp98_obj(sizeof(BinkControlClass) == 96, BinkControlClass);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(BinkControlClass, false, Address::SHC_3BB0A8C1_0x02157518) pDAT_BinkControlClass;

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
