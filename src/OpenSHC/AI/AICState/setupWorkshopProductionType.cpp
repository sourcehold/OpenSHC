#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Resources::ResourceTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBE30
    void AICState::setupWorkshopProductionType(int playerID, int buildingID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_NULL) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_BLACKSMITH) {
            int setting = this->aics[aicIndex].blacksmithSetting;
            if (setting == -999) {
                int itemType = MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::chooseProductionItemType, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, Map::Buildings::BT_BLACKSMITH);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)itemType;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)itemType;
                return;
            }
            if (setting == Game::Resources::RT_SWORD) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_SWORD;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_SWORD;
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_MACE;
            DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_MACE;
            return;
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_POLETURNER) {
            int setting = this->aics[aicIndex].poleturnerSetting;
            if (setting == -999) {
                int itemType = MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::chooseProductionItemType, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, Map::Buildings::BT_POLETURNER);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)itemType;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)itemType;
                return;
            }
            if (setting == Game::Resources::RT_SPEAR) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_SPEAR;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_SPEAR;
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_PIKE;
            DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_PIKE;
            return;
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == Map::Buildings::BT_FLETCHER) {
            int setting = this->aics[aicIndex].fletcherSetting;
            if (setting == -999) {
                int itemType = MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::chooseProductionItemType, DAT_BuildingsState::ptr)(
                    DAT_BuildingsState::instance.buildings[buildingID].owner, Map::Buildings::BT_FLETCHER);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)itemType;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)itemType;
                return;
            }
            if (setting == Game::Resources::RT_BOW) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_BOW;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_BOW;
                return;
            }
            DAT_BuildingsState::instance.buildings[buildingID].producedItemType = Game::Resources::RT_CROSSBOW;
            DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = Game::Resources::RT_CROSSBOW;
        }
    }
}
}
