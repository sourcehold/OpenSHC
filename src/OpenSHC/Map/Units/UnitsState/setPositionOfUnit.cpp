#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E900
        void UnitsState::setPositionOfUnit(int unitID, uint x, uint y, undefined4 height)
        {
            if (x >= 400 || y >= 400) {
                return;
            }
            /* the 400x400 map of placeable tiles at 0x021AEC98 */
            if (*(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                return;
            }
            this->units[unitID].currentIndexInPathPlan = 0;
            this->units[unitID].tunnelerFinishedDigging = 0;
            this->units[unitID].field105_0xe8 = 0;
            this->units[unitID].movementRelated = 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            this->units[unitID].microXPosition = (short)x * 8 + 4;
            this->units[unitID].microYPosition = (short)y * 8 + 4;
            this->units[unitID].terrainOrClimbHeight = (short)height;
            this->units[unitID].mimicCurrentXPosition = (short)x;
            this->units[unitID].x = (short)x;
            this->units[unitID].mimicCurrentYPosition = (short)y;
            this->units[unitID].y = (short)y;
            this->units[unitID].tile
                = (short)x + DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
        }

    }
}
}
