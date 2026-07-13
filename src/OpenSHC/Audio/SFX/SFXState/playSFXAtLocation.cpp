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
            // TODO: Currently looks unlikely, that they used two alternatives. But maybe the issue is somewhere else?
            int _x = xPosition - DAT_ViewportRenderState::instance.viewportState.tileCenterX;
            int _y = yPosition - DAT_ViewportRenderState::instance.viewportState.tileCenterY;
            int _x2 = _x;
            int _y2 = _y;
            if (DAT_TileMapState::instance.SEC_MapOrientation == 2) {
                _x2 = _y;
                _y2 = -_x;
            } else if (DAT_TileMapState::instance.SEC_MapOrientation == 4) {
                _x2 = -_x;
                _y2 = -_y;
            } else if (DAT_TileMapState::instance.SEC_MapOrientation == 6) {
                _x2 = -_y;
                _y2 = _x;
            }

            int diff = _x2 - _y2;
            // TODO: The required opcodes here are only produced when either ">> 1", or if both are unsigned and "/ 2".
            // The negatives used suggest an int, but it really depends on what the tile center values contain.
            int avg = (_x2 + _y2) >> 1;
            if (-45 > diff || diff > 45 || -36 > avg || avg > 36) {
                return;
            }
            int samplePan = diff * 2 + 62;
            if (samplePan < 0) {
                samplePan = 0;
            } else if (127 < samplePan) {
                samplePan = 127;
            }
            // Without source compares it is unclear if the actually functions are the same, but the structure now is.
            int _computedVolume = (int)(float)sqrt((double)(_x2 * _x2 + _y2 * _y2));
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
