#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E900
        void UnitsState::setPositionOfUnit(int unitID, int x, int y, undefined4 height)
        {
            if (x < 0 || x > MC_MAP_XY_LIMIT_INCLUSIVE || y < 0 || y > MC_MAP_XY_LIMIT_INCLUSIVE) {
                return;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x] == 0) {
                return;
            }
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].tunnelerFinishedDigging = 0;
            this->units[unitID].field_0xe8 = FALSE;
            this->units[unitID].movementRelated = 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            this->units[unitID].microXPosition = x * 8 + 4;
            this->units[unitID].microYPosition = y * 8 + 4;
            this->units[unitID].terrainOrClimbHeight = height;
            this->units[unitID].mimicCurrentXPosition = x;
            this->units[unitID].x = x;
            this->units[unitID].mimicCurrentYPosition = y;
            this->units[unitID].y = y;
            this->units[unitID].tile = this->units[unitID].x
                + DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].y].addXgetTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
        }

    }
}
}
