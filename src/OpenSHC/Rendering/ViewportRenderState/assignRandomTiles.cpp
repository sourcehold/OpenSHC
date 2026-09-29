#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5B80
    void ViewportRenderState::assignRandomTiles()
    {
        for (int i = 0; i < 45; i++) {
            if (this->landscapeAnimationRandomTileArray[i] == 0) {
                int randomHighBits = MACRO_CALL(OpenSHC::OS_Func::_rand)() << 0xf;
                uint randomLowBits = MACRO_CALL(OpenSHC::OS_Func::_rand)();
                int randomTile = (int)(randomLowBits | randomHighBits) % 80400;
                if ((DAT_TileMapState::instance.LogicLayer[randomTile] & 1) != 0
                    && (DAT_TileMapState::instance.MiscDisplayLayer[randomTile] & 0x3c0) == 0
                    && (DAT_TileMapState::instance.Logic2Layer[randomTile] & 8) == 0) {
                    this->landscapeAnimationRandomTileArray[i] = randomTile;
                    this->landscapeSeaWhiteCapsAnimationFrames[i] = 0;
                }
            } else if (8 <= this->landscapeSeaWhiteCapsAnimationFrames[i]) {
                this->landscapeAnimationRandomTileArray[i] = 0;
            }
        }
    }

}
}
