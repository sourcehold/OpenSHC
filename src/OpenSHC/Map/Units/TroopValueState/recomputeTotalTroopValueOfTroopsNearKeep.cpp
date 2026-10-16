#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FA70
        void TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep()
        {
            int* piVar1;
            UnitTypeShort UVar2;
            int _troopValue;
            int iVar3;
            Unit* ptrUnit;
            short _playerID;
            iVar3 = 1;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[0] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[1] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[2] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[3] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[4] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[5] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[6] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[7] = 0;
            this->attackInfo.playerTotalTroopValueOfTroopsNearKeep[8] = 0;
            this->attackInfo.padding_0x25b50[0] /* 0x25B50: start of padding_0x25b50 in the header */ = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                ptrUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if ((((ptrUnit->logicalState != Map::Units::ULS_INVISIBLE) && (!ptrUnit->dying))
                            && (ptrUnit->isSelectable_OR_matchTime))
                        && (((UVar2 = ptrUnit->unitType,
                                 UVar2 != Map::Units::UT_E_ENGINEER && (UVar2 != Map::Units::UT_TUNNELER))
                            && (UVar2 != Map::Units::UT_E_LADDER)))) {
                        _playerID = ptrUnit->owner;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(
                            DAT_GameState::instance.playerDataArray[_playerID].campground.xEntry,
                            DAT_GameState::instance.playerDataArray[_playerID].campground.yEntry,
                            (int)((int)(ptrUnit->x)), (int)((int)(ptrUnit->y)));
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < 40) {
                            _troopValue
                                = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                                    this)((Map::Units::UnitType)(short)ptrUnit->unitType);
                            piVar1 = this->attackInfo.playerTotalTroopValueOfTroopsNearKeep + _playerID;
                            *piVar1 = *piVar1 + _troopValue;
                        }
                    }
                    iVar3 = iVar3 + 1;
                    ptrUnit = ptrUnit + 0x248;
                } while (iVar3 < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
