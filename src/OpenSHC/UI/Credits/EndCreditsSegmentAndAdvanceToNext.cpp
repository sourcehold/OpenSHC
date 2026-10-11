#include "../Credits.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

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
#include "OpenSHC/Globals/INT_00ec0828.hpp"

namespace OpenSHC {
namespace UI {

    using Audio::MSS::enums::SHC_SoundStream;

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA200
    void Credits::EndCreditsSegmentAndAdvanceToNext()
    {
        CreditsRelatedStructure* pCVar1;
        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            Audio::MSS::enums::SND_STR_SFX_1Unk);
        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
        DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            Audio::MSS::enums::SND_STR_SPEECH_1);
        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
            Audio::MSS::enums::SND_STR_SPEECH_2);
        if (INT_00ed27a4::instance != 2) {
            MACRO_CALL_MEMBER(
                Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
            MACRO_CALL_MEMBER(
                Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(1);
        }
        DWORD_00eb9ac4::instance = 0;
        INT_00eb1230::instance = 0;
        INT_00eb9ac0::instance = 0;
        DAT_00ed2bd8::instance = 0;
        pCVar1 = DAT_ARRAY_00ec0348::instance;
        do {
            pCVar1->isValid = 0;
            pCVar1 = pCVar1 + 1;
        } while ((int)pCVar1 < (int)&INT_00ec0828::instance);
        DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance + 1;
        if (DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance) {
            do {
                if (DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType == 0x27) {
                    MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(
                        Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                        (DE::SHCDE::eMusicIDs)(DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance]
                                .soundStream));
                }
            } while ((DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType != 0x1f)
                && (DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance + 1,
                    DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance));
        }
        return;
    }

}
}
