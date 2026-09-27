#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053D900
        void UnitsState::exitLadder(int unitID)
        {
            int _previousTile = this->units[unitID].field42_0x60;
            this->units[unitID].vanish = 0;
            this->units[unitID].usingTeleport = 0;
            this->units[unitID].field203_0x35c = 0;
            this->units[unitID].field43_0x64 = 0;
            this->units[unitID].movementRelated = 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingTileIDs, this)(
                unitID, _previousTile);
            this->units[unitID].field42_0x60 = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            this->units[unitID].y = this->units[unitID].mimicCurrentYPosition;
            this->units[unitID].x = this->units[unitID].mimicCurrentXPosition;
            this->units[unitID].microYPosition = this->units[unitID].mimicCurrentYPosition * 8 + 4;
            this->units[unitID].tile = this->units[unitID].mimicCurrentXPosition
                + DAT_ViewportRenderState::instance.translationMatrix[this->units[unitID].mimicCurrentYPosition]
                      .addXgetTile;
            this->units[unitID].microXPosition = this->units[unitID].mimicCurrentXPosition * 8 + 4;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
        }

    }
}
}
