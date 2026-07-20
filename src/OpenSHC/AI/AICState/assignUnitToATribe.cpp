#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2660
    void AICState::assignUnitToATribe(int unitID)
    {
        short* _unitTypeIndex;
        int _isOfType;
        int _tribeID;
        int _playerID = (int)DAT_UnitsState::instance.units[unitID].owner;
        if (DAT_GameState::instance.playerDataArray[_playerID].aiType != AITA_NULL) {
            int iVar1;
            if ((DAT_GameState::instance.playerDataArray[_playerID].aivCurrentPauseIndex == 1) &&
                (0 < DAT_GameState::instance.playerDataArray[_playerID].aivPauses[1])) {
                iVar1 = 1;
            }
            else {
                iVar1 = 0;
            }
            _unitTypeIndex = (short*)MACRO_CALL(Global_Func::GetUnitTypeIndexForUnitID)(unitID, iVar1);
            int _tribeSize = DAT_GameState::instance.playerDataArray[_playerID].aivUnitLocationSlotLocationCount[(int)_unitTypeIndex];
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 1;
            if (_tribeSize < 1) {
                _isOfType = MACRO_CALL_MEMBER(AICState_Func::unitIDIsRangedOrArmored, this)(unitID);
                if (_isOfType != 0) {
                    _tribeID = MACRO_CALL_MEMBER(AICState_Func::createTribeForUnitType, this)(_playerID, 0);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, _tribeID);
                    return;
                }
                _tribeID = MACRO_CALL_MEMBER(AICState_Func::createTribeForUnitType, this)(_playerID, 1);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, _tribeID);
                return;
            }
            _tribeID = MACRO_CALL_MEMBER(AICState_Func::smallestTribeOfUnitType, this)(_playerID, _unitTypeIndex);
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(unitID, _tribeID);
        }
    }
}
}
