#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00457960
    void GameStateStructures::updatePrimaryBuildingPlayerDataReferences(uint buildingID)
    {
        int const playerID = DAT_BuildingsState::instance.buildings[buildingID].owner;
        // the primary building entries follow each other, starting at the keep
        for (int entryIndex = 0; entryIndex < 20; ++entryIndex) {
            if (this->playerDataArray[playerID].buildingEntryInfos[entryIndex].id == buildingID) {
                this->playerDataArray[playerID].buildingEntryInfos[entryIndex].id = 0;
                break;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_STOCKPILE) {
            this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_STOCKPILE].id
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_STOCKPILE);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_GRANARY) {
            this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_GRANARY].id
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_GRANARY);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_ARMORY) {
            this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_ARMORY].id
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_ARMORY);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_BARRACKS) {
            this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_BARRACKS].id
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_BARRACKS);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_MERCENARYPOST) {
            this->playerDataArray[playerID].buildingEntryInfos[Player::Enums::BEIE_MERCENARYPOST].id
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_MERCENARYPOST);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
    }

}
}
