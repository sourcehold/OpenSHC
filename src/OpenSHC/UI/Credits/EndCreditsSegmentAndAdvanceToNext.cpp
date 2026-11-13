#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_00ed2bd8.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/INT_00eb1230.hpp"
#include "OpenSHC/Globals/INT_00eb9ac0.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::DE::SHCDE::eMusicIDs;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA200
        void EndCreditsSegmentAndAdvanceToNext()
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
            }
            DWORD_00eb9ac4::instance = 0;
            INT_00eb1230::instance = 0;
            INT_00eb9ac0::instance = 0;
            DAT_00ed2bd8::instance = 0;
            for (int i = 0; i < 24; i++) {
                DAT_ARRAY_00ec0348::instance[i].type = 0;
            }
            for (DAT_UnknownBinkIndex::instance += 1; DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance;
                DAT_UnknownBinkIndex::instance += 1) {
                if (DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType == 39) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                        (eMusicIDs)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream);
                }
                if (DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType == 31) {
                    break;
                }
            }
        }

    }
}
}
