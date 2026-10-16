#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CBD0
        void TroopValueState::redeployArchersToDefensivePositions()
        {
            int _index;
            int _tile;
            if (!this->attackInfo.unitsSentToKeepFlag && 0 < this->attackInfo.unitIDIndex_0x2bd4c
                && (_index = 0, 0 < this->attackInfo.unitIDIndex_0x2c520)) {
                do {
                    int _unitID = (int)this->attackInfo.unitIDArray_0x2c070[_index];
                    if (((!_unitID)
                            || (DAT_UnitsState::instance.units[_unitID].uid
                                != this->attackInfo.uidArray_0x2c200[_index]))
                        && (_tile = this->attackInfo.tileArray_0x2bd50[_index],
                            (DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) != 0)) {
                        short _y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                        short _unitID2
                            = this->attackInfo.unitIDArray_0x2b57c[this->attackInfo.unitIDIndex_0x2bd4c + -1];
                        int _unitIDInt = (int)_unitID2;
                        int _xOff = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                        this->attackInfo.unitIDIndex_0x2bd4c = this->attackInfo.unitIDIndex_0x2bd4c + -1;
                        this->attackInfo.uidArray_0x2c200[_index] = DAT_UnitsState::instance.units[_unitIDInt].uid;
                        this->attackInfo.unitIDArray_0x2c070[_index] = _unitID2;
                        DAT_UnitsState::instance.units[_unitIDInt].state.generic
                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                            _unitIDInt, (uint)(_tile - _xOff), (uint)(_y), 0);
                    }
                    _index = _index + 1;
                } while (_index < this->attackInfo.unitIDIndex_0x2c520);
            }
        }

    }
}
}
