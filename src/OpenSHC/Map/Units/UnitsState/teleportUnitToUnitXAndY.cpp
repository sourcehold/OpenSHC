#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053BB90
        void UnitsState::teleportUnitToUnitXAndY(int unitID)
        {
            int _tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[this->units[unitID].tile];
            int _tileX
                = this->units[unitID].tile - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile;
            if (_tileY == this->units[unitID].y && _tileX == this->units[unitID].x) {
                return;
            }
            this->units[unitID].microXPosition = (short)(_tileX * 8 + 4);
            this->units[unitID].microYPosition = (short)(_tileY * 8 + 4);
            this->units[unitID].mimicCurrentXPosition = (short)_tileX;
            this->units[unitID].x = (short)_tileX;
            this->units[unitID].mimicCurrentYPosition = (short)_tileY;
            this->units[unitID].y = (short)_tileY;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
        }

    }
}
}
