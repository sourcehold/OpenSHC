#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3F70
    void AICState::aiAssignMoatDiggers(int playerID)
    {
        int _unitID;
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        Map::Units::UnitTypeShort _unitType;
        if (((_aiType != AITA_NULL) && (0 < DAT_GameState::instance.playerDataArray[playerID].totalTroopsType0))
            && (_unitID = 1, 1 < (int)DAT_UnitsState::instance.maxUnitCount)) {
            Map::Units::Unit* _ptrUnit = &DAT_UnitsState::instance.units[1];
            do {
                if ((((((_ptrUnit->logicalState != Map::Units::ULS_INVISIBLE) && (_ptrUnit->owner == playerID))
                          && ((_ptrUnit->isSelectable_OR_matchTime != 0
                              && ((_ptrUnit->aiUnitBehaviourType == 0 && (_ptrUnit->dying == 0))))))
                         && (_unitType = _ptrUnit->unitType, _unitType != Map::Units::UT_LORD))
                        && ((((_unitType != Map::Units::UT_E_ENGINEER && (_unitType != Map::Units::UT_TUNNELER))
                                 && (_unitType != Map::Units::UT_S_CATAPULT))
                            && ((
                                _unitType != Map::Units::UT_S_TREBUCHET && (_unitType != Map::Units::UT_S_MANGONEL))))))
                    && ((
                        (_unitType != Map::Units::UT_S_TOWER
                            && ((_unitType != Map::Units::UT_S_BATTERINGRAM && (_unitType != Map::Units::UT_S_SHIELD))))
                        && ((_unitType != Map::Units::UT_S_BALLISTA && (_unitType != Map::Units::UT_S_FBALLISTA)))))) {
                    if (((((int)this->aics[_aiType - 1].DefDiggingUnitMax == 0)
                             || (_unitType == Map::Units::UT_E_ARCHER))
                            || (_unitType == Map::Units::UT_E_XBOW))
                        || (_ptrUnit->someUnitStat4 == 0)) {
                        MACRO_CALL_MEMBER(AICState_Func::assignUnitToATribe, this)(_unitID);
                    } else {
                        MACRO_CALL_MEMBER(AICState_Func::aiAddUnitToMoatDiggerTribe, this)(_unitID);
                    }
                }
                _unitID = _unitID + 1;
                _ptrUnit = _ptrUnit + 1;
            } while (_unitID < (int)DAT_UnitsState::instance.maxUnitCount);
        }
    }
}
}
