#include "../Credits.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

    /*
      WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004DA180
    void Credits::StopCreditsPlaybackAndSounds()
    {
        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            OpenSHC::Audio::MSS::enums::SND_STR_SFX_1Unk);
        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
        if (INT_00ed27a4::instance != 2) {
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(1);
            DAT_UnknownBinkIndex::instance = DAT_UnknownBinkCount::instance;
        }
        DAT_UnknownBinkIndex::instance = DAT_UnknownBinkCount::instance;
    }

}
}
