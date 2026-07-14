#include "../SFXState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x00449DC0
        void SFXState::playSFXAtLocation(int xPosition, int yPosition, eSFX sfxOffsetInArray)
        {
            int variationCount = this->DAT_SoundStructures2[sfxOffsetInArray].variationCount;
            if (variationCount <= 0) {
                return;
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

            // An AI analysis suggests that this code is a screen transform. So the logic pre-filters sound outside this
            // window and binds the actual computation to this. Somewhere in the code also needs to be the reason
            // sound from the other map edge is played. Zoomed out the sound also happens mostly in the upper left.
            // Although, this could be computation order.
            // The required opcodes here are only produced when either ">> 1", or if both are unsigned and "/ 2". The
            // negatives used suggest an int, but it really depends on what the tile center values contain. Apparently,
            // division by ">>" creates a different rounding behavior (to lower) compared to "/" (to 0).
            int horizontalScreenPos = x - y;
            int verticalScreenPos = (x + y) >> 1;
            if (-45 > horizontalScreenPos || horizontalScreenPos > 45 || -36 > verticalScreenPos
                || verticalScreenPos > 36) {
                return;
            }
            int samplePan = horizontalScreenPos * 2 + 62;
            if (samplePan < 0) {
                samplePan = 0;
            } else if (127 < samplePan) {
                samplePan = 127;
            }
            // Without source compares it is unclear if the actual functions are the same, but the structure now is.
            int _computedVolume = (int)(float)sqrt((double)(x * x + y * y));
            _computedVolume = _computedVolume * 2;
            if (70 < _computedVolume) {
                _computedVolume = 70;
            }
            int const _soundStructureID = this->DAT_SoundStructures2[sfxOffsetInArray].soundID
                + this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter++;
            if (this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter >= variationCount) {
                this->DAT_SoundStructures2[sfxOffsetInArray].variationCounter = 0;
            }
            this->DAT_SoundStructures[_soundStructureID].scheduledPlayCounter++;
            this->DAT_SoundStructures[_soundStructureID].volumePercentage
                = ((100 - _computedVolume) * this->DAT_SoundStructures[_soundStructureID].baseVolumePercentageUnk)
                / 100;
            this->DAT_SoundStructures[_soundStructureID].samplePan = samplePan;
            ++this->DAT_SFXCounter1;
            if (this->DAT_SFXCounter1 > this->highestSFXCounter) {
                this->highestSFXCounter = this->DAT_SFXCounter1;
            }
        }

    }
}
}
