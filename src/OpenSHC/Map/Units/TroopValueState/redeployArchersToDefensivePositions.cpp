#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
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
            if (!DAT_TroopValueState::instance.attackInfo.unitsSentToKeepFlag
                && 0 < DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c
                && (_index = 0, 0 < DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520)) {
                do {
                    int const _unitID = (int)DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070[_index];
                    if (((!_unitID)
                            || (DAT_UnitsState::instance.units[_unitID].uid
                                != DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200[_index]))
                        && (_tile = DAT_TroopValueState::instance.attackInfo.tileArray_0x2bd50[_index],
                            (DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000100U) != 0)) {
                        int const _y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
                        DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c
                            = DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c + -1;
                        int _unitID2
                            = DAT_TroopValueState::instance.attackInfo
                                  .unitIDArray_0x2b57c[DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c];
                        int const _xOff = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                        DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200[_index]
                            = DAT_UnitsState::instance.units[_unitID2].uid;
                        DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070[_index] = (short)_unitID2;
                        DAT_UnitsState::instance.units[_unitID2].state.generic
                            = Map::Units::States::US_MOVE_TO_DESTINATION;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                            _unitID2, (uint)(_tile - _xOff), (uint)(_y), 0);
                    }
                    _index = _index + 1;
                } while (_index < DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520);
            }
        }

    }
}
}
