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
        void SFXState::loadWavSounds(char* param_1)
        {
            // Might have arrived in a different format, maybe it was void, or an char(param_1)[270][8][1000] and they
            // casted it to perform arithmetic?
            char* soundNames = param_1;
            int soundStructure2Index = 0;
            while (soundStructure2Index < 270) {
                this->DAT_SoundStructures2[soundStructure2Index].soundID = 0;
                this->DAT_SoundStructures2[soundStructure2Index].field1_0x4 = 0;
                this->DAT_SoundStructures2[soundStructure2Index].variationCount = 0;
                this->DAT_SoundStructures2[soundStructure2Index].variationCounter = 0;

                char* variation = soundNames;
                for (int i = 0; i < 8; ++i) {
                    if (!strcmp(variation, s_Null_wav_005a4cf8))
                        break;

                    ++this->DAT_SoundStructures2[soundStructure2Index].field1_0x4;
                    variation += sizeof(char[1000]);
                }

                variation = soundNames;
                for (int i = 0; i < 8; ++i) {
                    if (!strcmp(variation, s_Null_wav_005a4cf8))
                        break;

                    int soundID = MACRO_CALL_MEMBER(
                        MSS::SoundSystem_Func::loadSoundFileAndGetIndex, DAT_SoundSystemState::ptr)(variation);

                    if (soundID < 0)
                        break;

                    ++this->DAT_SoundStructures2[soundStructure2Index].variationCount;

                    if (this->DAT_SoundStructures2[soundStructure2Index].soundID == 0)
                        this->DAT_SoundStructures2[soundStructure2Index].soundID = soundID;

                    this->DAT_SoundStructures[soundID].pointerToFilename = variation;

                    variation += sizeof(char[1000]);
                }
                soundNames += sizeof(char[8][1000]);

                ++soundStructure2Index;
                int loadingBar = soundStructure2Index * 80;

                IO::Graphics::GmID currentGmId
                    = (IO::Graphics::GmID)(loadingBar / 270 + DAT_LoadingBarProgress::instance);

                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawLoadingBarUnk,
                    DAT_TextureRenderCoreObject::ptr)(currentGmId, DAT_LoadingBarProgress::instance + 180);
            }
        }

    }
}
}
