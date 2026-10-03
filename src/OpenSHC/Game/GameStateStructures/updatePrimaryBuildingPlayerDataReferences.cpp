#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457960
    void GameStateStructures::updatePrimaryBuildingPlayerDataReferences(uint buildingID)
    {
        int playerID = DAT_BuildingsState::instance.buildings[buildingID].owner;
        /*
          the primary building entries follow each other, starting at the keep
         */
        for (int entryIndex = 0; entryIndex < 20; entryIndex++) {
            if ((&this->playerDataArray[playerID].keep)[entryIndex].id == buildingID) {
                (&this->playerDataArray[playerID].keep)[entryIndex].id = 0;
                break;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_STOCKPILE) {
            this->playerDataArray[playerID].stockpile.id = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_STOCKPILE);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_GRANARY) {
            this->playerDataArray[playerID].granary.id = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_GRANARY);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_ARMORY) {
            this->playerDataArray[playerID].armory.id = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_ARMORY);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_BARRACKS) {
            this->playerDataArray[playerID].barracks.id = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_BARRACKS);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_MERCENARYPOST) {
            this->playerDataArray[playerID].mercenaryPost.id = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_MERCENARYPOST);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
    }
}
}
