#include "../SFXState.func.hpp"

#include "OpenSHC/Audio/mss/SoundSystem.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449B30
        void SFXState::loadWavSounds(char(param_1)[270][8][1000])
        {
            for (int soundStructure2Index = 0; soundStructure2Index < 270; ++soundStructure2Index) {
                this->DAT_SoundStructures2[soundStructure2Index].soundID = 0;
                this->DAT_SoundStructures2[soundStructure2Index].field1_0x4 = 0;
                this->DAT_SoundStructures2[soundStructure2Index].variationCount = 0;
                this->DAT_SoundStructures2[soundStructure2Index].variationCounter = 0;

                for (int unknownIndex = 0; unknownIndex < 8; ++unknownIndex) {
                    if (!strcmp(param_1[soundStructure2Index][unknownIndex], s_Null_wav_005a4cf8)) {
                        break;
                    }
                    ++this->DAT_SoundStructures2[soundStructure2Index].field1_0x4;
                }
                for (int unknownIndex = 0; unknownIndex < 8; ++unknownIndex) {
                    if (!strcmp(param_1[soundStructure2Index][unknownIndex], s_Null_wav_005a4cf8)) {
                        break;
                    }
                    int const _soundStructureID = MACRO_CALL_MEMBER(MSS::SoundSystem_Func::meth_0x479c20,
                        DAT_SoundSystemState::ptr)(param_1[soundStructure2Index][unknownIndex]);
                    if (_soundStructureID < 0) {
                        break;
                    }
                    ++this->DAT_SoundStructures2[soundStructure2Index].variationCount;
                    if (this->DAT_SoundStructures2[soundStructure2Index].soundID == 0) {
                        this->DAT_SoundStructures2[soundStructure2Index].soundID = _soundStructureID;
                    }
                    this->DAT_SoundStructures[_soundStructureID].pointerToFilename
                        = param_1[soundStructure2Index][unknownIndex];
                }
                IO::Graphics::GmID const currentGmId
                    = (IO::Graphics::GmID)(DAT_LoadingBarProgress::instance + ((soundStructure2Index + 1) * 80 / 270));
                int const barLengthUnk = DAT_LoadingBarProgress::instance + 180;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawLoadingBarUnk,
                    DAT_TextureRenderCoreObject::ptr)(currentGmId, barLengthUnk);
            };
        }

    }
}
}
