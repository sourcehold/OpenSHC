/**
  path: 'OpenSHC/Rendering/Bink/BinkControlClass.func.hpp'
*/

#include "OpenSHC/Audio/mss/HDIGDRIVER.hpp"
#include "OpenSHC/Audio/mss/_enums/SHC_SoundStreamInt.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace Rendering {
    namespace Bink {
        namespace BinkControlClass_Func {

            using OpenSHC::Audio::mss::HDIGDRIVER;
            using OpenSHC::Audio::mss::_enums::SHC_SoundStreamInt;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(HDIGDRIVER), false, Address::SHC_3BB0A8C1_0x00408E10,
                &BinkControlClass::zeroBinkPtrAndLoadBinkSoundSystem)
            zeroBinkPtrAndLoadBinkSoundSystem;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(int), false, Address::SHC_3BB0A8C1_0x00408E30,
                &BinkControlClass::stopBinkPlayback)
            stopBinkPlayback;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(int, SHC_SoundStreamInt), false,
                Address::SHC_3BB0A8C1_0x00408E70, &BinkControlClass::setBinkSndStreamAndStartTime)
            setBinkSndStreamAndStartTime;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(), false, Address::SHC_3BB0A8C1_0x00408EB0,
                &BinkControlClass::stopAllBinkPlayback)
            stopAllBinkPlayback;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(int, char*, DWORD, DWORD, int, int, DWORD), false,
                Address::SHC_3BB0A8C1_0x00408ED0, &BinkControlClass::playBINK)
            playBINK;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(dword), false, Address::SHC_3BB0A8C1_0x00408FC0,
                &BinkControlClass::copyBinkToVideoBuffer)
            copyBinkToVideoBuffer;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(), false, Address::SHC_3BB0A8C1_0x00409200,
                &BinkControlClass::processBinkFrames)
            processBinkFrames;

            MACRO_FUNCTION_RESOLVER(void (BinkControlClass::*)(), false, Address::SHC_3BB0A8C1_0x004092B0,
                &BinkControlClass::stopAllBinkPlaybackThunk)
            stopAllBinkPlaybackThunk;

        } // namespace BinkControlClass_Func
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
