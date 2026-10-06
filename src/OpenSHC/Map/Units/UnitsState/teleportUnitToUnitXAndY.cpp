#include "OpenSHC/Map/Units/UnitsState.func.hpp"

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
            DAT_UnitsState::instance.units[unitID].microXPosition = (short)(_tileX * 8 + 4);
            DAT_UnitsState::instance.units[unitID].microYPosition = (short)(_tileY * 8 + 4);
            DAT_UnitsState::instance.units[unitID].mimicCurrentXPosition = (short)_tileX;
            DAT_UnitsState::instance.units[unitID].x = (short)_tileX;
            DAT_UnitsState::instance.units[unitID].mimicCurrentYPosition = (short)_tileY;
            DAT_UnitsState::instance.units[unitID].y = (short)_tileY;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
        }

    }
}
}
