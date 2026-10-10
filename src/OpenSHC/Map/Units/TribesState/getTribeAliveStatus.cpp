#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        /*
          @return 0 if all alive, 1 if majority alive, 50 if fewer alive than dead, 100 if all dead decompilerscript:
          committed: 2025-01-30 21:57:43.216000   decompilerscript: committed: 2026-05-02 18:15:17.059000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00524BF0
        int TribesState::getTribeAliveStatus(int tribeID)
        {
            int _unit;
            int _size = (int)this->tribes[tribeID].size;
            int _index = 0;
            int _other = 0;
            int _alive = 0;
            if (0 < _size) {
                do {
                    _unit = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, _index);
                    _index = _index + 1;
                    if ((DAT_UnitsState::instance.units[_unit].logicalState == Map::Units::ULS_NORMAL)
                        && (DAT_UnitsState::instance.units[_unit].dying == 0)) {
                        if (DAT_UnitsState::instance.units[_unit].tunnelerFinishedDigging == 2) {
                            _alive = _alive + 1;
                        } else {
                            _other = _other + 1;
                        }
                    }
                } while (_index < _size);
                if (_alive != 0) {
                    if (_alive <= _other) {
                        return (int)(50);
                    }
                    return (uint)(_other != 0);
                }
            }
            return 100;
        }

    }
}
}
