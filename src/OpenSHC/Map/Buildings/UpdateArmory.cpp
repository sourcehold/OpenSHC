#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00412730
    void Buildings::UpdateArmory()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int resourceGiven = 0;
        int sprite = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        if (DAT_TileMapState::instance.currentMapperCommand == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someResourceNumber = 0;
        }

        // Hand out one unit of each starting weapon while the armory has room
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) == 0
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[owner].someCountdown01 == 0) {
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BOW] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_BOW, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_BOW] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BOW] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_BOW] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CROSSBOW] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_CROSSBOW, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_CROSSBOW]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CROSSBOW]
                    -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_CROSSBOW] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_SPEAR] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_SPEAR, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_SPEAR]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_SPEAR] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_SPEAR] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_PIKE] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_PIKE, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_PIKE] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_PIKE] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_PIKE] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MACE] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_MACE, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_MACE] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MACE] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_MACE] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_SWORD] > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_SWORD, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_SWORD]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_SWORD] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_SWORD] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_LEATHERARMOR]
                    > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_LEATHERARMOR, owner, 1)) {
                DAT_GameState::instance.playerDataArray[owner]
                    .currentResources[OpenSHC::Game::Resources::RT_LEATHERARMOR] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_LEATHERARMOR]
                    -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_LEATHERARMOR] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_IRONARMOR]
                    > 0
                && MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, DAT_BuildingsState::ptr)(
                    DAT_CurrentBuildingID::instance, OpenSHC::Game::Resources::RT_IRONARMOR, owner, 1)) {
                // The original sets the iron armour count to 1 instead of adding 1
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_IRONARMOR]
                    = 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_IRONARMOR]
                    -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_IRONARMOR] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (resourceGiven != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(owner);
            }
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
            < 10) {
            DAT_GameState::instance.playerDataArray[owner].isArmouryAlmostFilledUp = 0;
        }
        if (DAT_GameState::instance.mapAndTime
                    .playerTeams[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                == DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
            || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                    == -1
                && DAT_GameSynchronyState::instance
                        .currentAIArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                    != 0)) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown -= 1;
            } else if (DAT_BuildingsState::instance.isFirstTickInLoop != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        int bows = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_BOW];
        int crossbows = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                            .resources[OpenSHC::Game::Resources::RT_CROSSBOW];
        int spears = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                         .resources[OpenSHC::Game::Resources::RT_SPEAR];
        int pikes = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .resources[OpenSHC::Game::Resources::RT_PIKE];
        int maces = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .resources[OpenSHC::Game::Resources::RT_MACE];
        int swords = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                         .resources[OpenSHC::Game::Resources::RT_SWORD];
        int leatherArmour = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                .resources[OpenSHC::Game::Resources::RT_LEATHERARMOR];
        int ironArmour = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                             .resources[OpenSHC::Game::Resources::RT_IRONARMOR];

        // The armory animates its flag in extraOverlayImage8, since overlayImageID holds a weapon pile
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive == 0) {
            return;
        }

        // Each of the 4 pile slots shows the most plentiful weapon left, up to 16 of it
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        for (int slot = 0; slot < 4; ++slot) {
            int weaponType = 0;
            int amount = 0;
            if (bows > 0) {
                weaponType = 1;
                amount = bows;
            }
            if (crossbows > amount) {
                weaponType = 2;
                amount = crossbows;
            }
            if (spears > amount) {
                weaponType = 3;
                amount = spears;
            }
            if (pikes > amount) {
                weaponType = 4;
                amount = pikes;
            }
            if (maces > amount) {
                weaponType = 5;
                amount = maces;
            }
            if (swords > amount) {
                weaponType = 6;
                amount = swords;
            }
            if (ironArmour > amount) {
                weaponType = 7;
                amount = ironArmour;
            }
            if (leatherArmour > amount) {
                weaponType = 8;
                amount = leatherArmour;
            }
            if (weaponType <= 0) {
                return;
            }
            if (amount > 16) {
                amount = 16;
            }
            if (weaponType == 1) {
                bows -= amount;
                sprite = amount + 32;
            } else if (weaponType == 2) {
                crossbows -= amount;
                sprite = amount + 48;
            } else if (weaponType == 3) {
                spears -= amount;
                sprite = amount + 64;
            } else if (weaponType == 4) {
                pikes -= amount;
                sprite = amount + 80;
            } else if (weaponType == 5) {
                maces -= amount;
                sprite = amount + 96;
            } else if (weaponType == 6) {
                swords -= amount;
                sprite = amount + 112;
            } else if (weaponType == 7) {
                ironArmour -= amount;
                sprite = amount;
            } else if (weaponType == 8) {
                leatherArmour -= amount;
                sprite = amount + 128;
            }
            if (slot == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = sprite;
            } else if (slot == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage3 = sprite;
            } else if (slot == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = sprite;
            } else if (slot == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = sprite;
            }
        }
    }

}
}
