#include "../UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053BB90
        void UnitsState::teleportUnitToUnitXAndY(int unitID)
        {
            int _tileY = DAT_ViewportRenderState::instance
                             .tileTranslationMatrix_YComponent[DAT_UnitsState::instance.units[unitID].tile];
            int _tileX = DAT_UnitsState::instance.units[unitID].tile
                - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile;
            if (_tileY == DAT_UnitsState::instance.units[unitID].y
                && _tileX == DAT_UnitsState::instance.units[unitID].x) {
                return;
            }
            this->units[unitID].microXPosition = _tileX * 8 + 4;
            this->units[unitID].microYPosition = _tileY * 8 + 4;
            this->units[unitID].mimicCurrentXPosition = _tileX;
            this->units[unitID].x = _tileX;
            this->units[unitID].mimicCurrentYPosition = _tileY;
            this->units[unitID].y = _tileY;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
        }

    }
}
}
