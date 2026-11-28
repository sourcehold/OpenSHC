#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FA70
        void TroopValueState::recomputeTotalTroopValueOfTroopsNearKeep()
        {
            for (int player = 0;
                player < countof(DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep);
                ++player) {
                DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[player] = 0;
            }
            for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                Unit* const unit = &DAT_UnitsState::instance.units[unitID];
                if (unit->logicalState == Map::Units::ULS_INVISIBLE || unit->dying
                    || !unit->isSelectable_OR_matchTime) {
                    continue;
                }
                UnitTypeShort const troopType = unit->unitType;
                if (troopType == Map::Units::UT_E_ENGINEER || troopType == Map::Units::UT_TUNNELER
                    || troopType == Map::Units::UT_E_LADDER) {
                    continue;
                }
                int const playerID = unit->owner;
                MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_GameState::instance.playerDataArray[playerID]
                                                          .buildingEntryInfos[Game::Player::Enums::BEIE_CAMPGROUND]
                                                          .xEntry,
                    DAT_GameState::instance.playerDataArray[playerID]
                        .buildingEntryInfos[Game::Player::Enums::BEIE_CAMPGROUND]
                        .yEntry,
                    unit->x, unit->y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 40) {
                    int const troopValue = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getValueOfTroopType,
                        this)((Map::Units::UnitType)unit->unitType);
                    DAT_TroopValueState::instance.attackInfo.playerTotalTroopValueOfTroopsNearKeep[playerID]
                        += troopValue;
                }
            }
        }

    }
}
}
