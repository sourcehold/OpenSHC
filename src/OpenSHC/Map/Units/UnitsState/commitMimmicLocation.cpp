#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E9F0
        void UnitsState::commitMimmicLocation(int unitID)
        {
            this->units[unitID].movementRelated = 8;
            this->units[unitID].field105_0xe8 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            this->units[unitID].y = this->units[unitID].mimicCurrentYPosition;
            this->units[unitID].microXPosition = this->units[unitID].mimicCurrentXPosition * 8 + 4;
            this->units[unitID].x = this->units[unitID].mimicCurrentXPosition;
            this->units[unitID].microYPosition = this->units[unitID].mimicCurrentYPosition * 8 + 4;
            this->units[unitID].tile = this->units[unitID].mimicCurrentXPosition
                + DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].mimicCurrentYPosition]
                      .addXgetTile;
            this->units[unitID].terrainOrClimbHeight = DAT_TileMapState::instance.HeightLayer[this->units[unitID].tile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recomputeUnitStandingHeight, this)(unitID);
        }

    }
}
}
