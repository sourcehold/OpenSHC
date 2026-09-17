#include "../SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044BCA0
        void SFXState::loadSFX(int param_1)
        {
            if (!DAT_TextureRenderCoreObject::instance.unknownSfxAndGmRelatedFlag) {
                MACRO_CALL_MEMBER(SFXState_Func::loadWavSounds, this)(
                    (char*)DAT_SpeechDefinedData::instance.WavFileGroups[0]);
                MACRO_CALL_MEMBER(SFXState_Func::readVolumeFileAndSetupSoundVolumes, this)();
            } else {
                MACRO_CALL_MEMBER(SFXState_Func::loadWavSounds, this)(
                    (char*)(DAT_SpeechDefinedData::instance.WavFileGroups[1]));
                MACRO_CALL_MEMBER(SFXState_Func::readVolumeFileAndSetupSoundVolumes, this)();
            }
        }

    }
}
}
