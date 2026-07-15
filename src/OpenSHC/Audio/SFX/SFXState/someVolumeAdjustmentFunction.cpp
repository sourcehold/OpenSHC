#include "../SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449F10
        void SFXState::someVolumeAdjustmentFunction(int xPosition, int yPosition, int sfxOffsetInArray)
        {
            int variationCount = this->DAT_SoundStructures2[sfxOffsetInArray].variationCount;
            if (variationCount <= 0) {
                return;
            }

            int const _soundStructureID = this->DAT_SoundStructures2[sfxOffsetInArray].soundID
                + this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter++;
            if (this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter >= variationCount) {
                this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter = 0;
            }

            int x = xPosition - DAT_ViewportRenderState::instance.viewportState.tileCenterX;
            int y = yPosition - DAT_ViewportRenderState::instance.viewportState.tileCenterY;
            if (DAT_TileMapState::instance.SEC_MapOrientation == 2) {
                int t = -x;
                x = y;
                y = t;
            } else if (DAT_TileMapState::instance.SEC_MapOrientation == 4) {
                x = -x;
                y = -y;
            } else if (DAT_TileMapState::instance.SEC_MapOrientation == 6) {
                int t = x;
                x = -y;
                y = t;
            }

            int samplePan = (x - y) * 2 + 62;
            if (samplePan < 0) {
                samplePan = 0;
            } else if (127 < samplePan) {
                samplePan = 127;
            }

            this->DAT_SoundStructures[_soundStructureID].scheduledPlayCounter++;
            this->DAT_SoundStructures[_soundStructureID].volumePercentage
                = this->DAT_SoundStructures[_soundStructureID].baseVolumePercentageUnk;
            this->DAT_SoundStructures[_soundStructureID].samplePan = samplePan;
            ++this->DAT_SFXCounter1;
            if (this->DAT_SFXCounter1 > this->highestSFXCounter) {
                this->highestSFXCounter = this->DAT_SFXCounter1;
            }
        }

    }
}
}
