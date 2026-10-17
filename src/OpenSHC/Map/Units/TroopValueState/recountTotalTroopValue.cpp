#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F9C0
        void TroopValueState::recountTotalTroopValue()
        {
            int* piVar1;
            int _troopTypeValue;
            Unit* pUVar2;
            int iVar2;
            int _playerID;
            UnitTypeShort _troopType;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[0] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[1] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[2] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[3] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[4] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[5] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[6] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[7] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[8] = 0;
            DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray[9] = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                pUVar2 = &DAT_UnitsState::instance.units[1];
                iVar2 = DAT_UnitsState::instance.maxUnitCount - 1;
                do {
                    if (pUVar2->logicalState != Map::Units::ULS_INVISIBLE && !pUVar2->dying
                        && pUVar2->isSelectable_OR_matchTime
                        && (_troopType = pUVar2->unitType,
                            _troopType != Map::Units::UT_E_ENGINEER && (_troopType != Map::Units::UT_TUNNELER))
                        && _troopType != Map::Units::UT_E_LADDER) {
                        _troopTypeValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                            this)((Map::Units::UnitType)(short)_troopType);
                        _playerID = pUVar2->owner;
                        piVar1 = DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueArray + _playerID;
                        *piVar1 = *piVar1 + _troopTypeValue;
                    }
                    pUVar2 = pUVar2 + 1;
                    iVar2 = iVar2 + -1;
                } while (iVar2);
            }
        }

    }
}
}
