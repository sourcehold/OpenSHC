#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525790
        void TribesState::removeSelectedUnitsFromTheirCurrentTribes(int playerID)
        {
            uint uVar1;
            Unit* _pUnit;
            int _unitTribeID;
            int _tribeID;
            uint _unitID;
            bool _unitRemovedFromTribeByID[1250];
            Tribe* _pTribe;
            uVar1 = MSVC_SecurityCookie::instance ^ (uint)_unitRemovedFromTribeByID;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                1250, '\0', (void*)((int)(_unitRemovedFromTribeByID)));
            _unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_pUnit->logicalState == Map::Units::ULS_NORMAL && !_pUnit->dying
                        && _pUnit->ifSelectedThenPlayerID == playerID
                        && (_unitTribeID = (int)_pUnit->tribeID, 0 < _unitTribeID)) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromThisTribeIfInTribe, this)(
                            _unitID, _unitTribeID);
                        _unitRemovedFromTribeByID[_unitTribeID] = true;
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 0x248;
                } while ((int)_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
            _tribeID = 1;
            _pTribe = &this->tribes[1];
            do {
                /*
                  tribeState
                 */
                if (_pTribe->tribeState == 2) {
                    if (_pTribe->selectionTargetUnitID == -1) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setTargetUnitForTribe, this)(_tribeID);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(_tribeID);
                }
                _tribeID = _tribeID + 1;
                _pTribe = _pTribe + 1;
            } while (_tribeID < 1250);
            ;
        }

    }
}
}
