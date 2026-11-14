#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"
#include "OpenSHC/Map/LogicHelpers/MiscDisplay.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E5B80
    void ViewportRenderState::assignRandomTiles()
    {
        for (int i = 0; i < countof(this->landscapeAnimationRandomTileArray); ++i) {
            if (this->landscapeAnimationRandomTileArray[i] == 0) {
                int randomTile = (MACRO_CALL(OpenSHC::OS_Func::_rand)() << 15 | MACRO_CALL(OpenSHC::OS_Func::_rand)())
                    % Map::MC_MAP_TILES_COUNT;
                if ((DAT_TileMapState::instance.LogicLayer[randomTile] & Map::LogicHelpers::L_SEA) != 0
                    && (DAT_TileMapState::instance.MiscDisplayLayer[randomTile] & Map::LogicHelpers::MD_SEA_EDGES) == 0
                    && (DAT_TileMapState::instance.Logic2Layer[randomTile] & Map::LogicHelpers::L2_PLATEAU_HIGH) == 0) {
                    this->landscapeAnimationRandomTileArray[i] = randomTile;
                    this->landscapeSeaWhiteCapsAnimationFrames[i] = 0;
                }
            } else if (Enums::VC_SEA_WHITE_CAP_FRAME_COUNT <= this->landscapeSeaWhiteCapsAnimationFrames[i]) {
                this->landscapeAnimationRandomTileArray[i] = 0;
            }
        }
    }

}
}
