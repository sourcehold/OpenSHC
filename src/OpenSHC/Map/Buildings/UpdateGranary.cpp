#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00415110
    void Buildings::UpdateGranary()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int totalFood = 0;
        int bread = 0;
        int cheese = 0;
        int meat = 0;
        int apples = 0;
        int sprite = 1;
        int resourceGiven = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);

        // Hand out one unit of each starting food while the granary has room
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) == 0
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
            && DAT_GameState::instance.playerDataArray[owner].someCountdown01 == 0) {
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BREAD] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_BREAD]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_BREAD] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_BREAD] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CHEESE] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_CHEESE]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_CHEESE] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_CHEESE] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MEAT] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_MEAT] += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_MEAT] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_MEAT] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_APPLE] > 0
                && (int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                       DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
                    < 250) {
                DAT_GameState::instance.playerDataArray[owner].currentResources[OpenSHC::Game::Resources::RT_APPLE]
                    += 1;
                DAT_GameState::instance.playerDataArray[owner].startResources[OpenSHC::Game::Resources::RT_APPLE] -= 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_APPLE] += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
                resourceGiven = 1;
            }
            if (resourceGiven != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, DAT_BuildingsState::ptr)(owner);
            }
        }
        if ((int)MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance)
            < 230) {
            DAT_GameState::instance.playerDataArray[owner].granaryIsAlmostFilledUp = 0;
        }
        if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
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
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage4 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 0;
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[0] == 0) {
            bread = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                        .resources[OpenSHC::Game::Resources::RT_BREAD];
            if (bread != 0) {
                totalFood += bread;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[1] == 0) {
            cheese = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                         .resources[OpenSHC::Game::Resources::RT_CHEESE];
            if (cheese != 0) {
                totalFood += cheese;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[2] == 0) {
            meat = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_MEAT];
            if (meat != 0) {
                totalFood += meat;
            }
        }
        if (DAT_GameState::instance.playerDataArray[owner].isFoodTypeBanned[3] == 0) {
            apples = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                         .resources[OpenSHC::Game::Resources::RT_APPLE];
            if (apples != 0) {
                totalFood += apples;
            }
        }
        DAT_GameState::instance.playerDataArray[owner].breadCount += bread;
        DAT_GameState::instance.playerDataArray[owner].cheeseCount += cheese;
        DAT_GameState::instance.playerDataArray[owner].meatCount += meat;
        DAT_GameState::instance.playerDataArray[owner].appleCount += apples;
        DAT_GameState::instance.playerDataArray[owner].totalFood += totalFood;

        bread = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                    .resources[OpenSHC::Game::Resources::RT_BREAD];
        cheese = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                     .resources[OpenSHC::Game::Resources::RT_CHEESE];
        meat = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                   .resources[OpenSHC::Game::Resources::RT_MEAT];
        apples = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                     .resources[OpenSHC::Game::Resources::RT_APPLE];
        int const storedFood = apples + meat + cheese + bread;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (storedFood <= 0
            || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive == 0) {
            return;
        }

        // Each of the 16 pile slots shows the most plentiful food left, up to a per-type pile size
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        for (int slot = 0; slot < 16; ++slot) {
            int foodType = 0;
            int amount = 0;
            if (bread > 0) {
                foodType = 1;
                amount = bread;
            }
            if (cheese > amount) {
                foodType = 2;
                amount = cheese;
            }
            if (meat > amount) {
                foodType = 3;
                amount = meat;
            }
            if (apples > amount) {
                foodType = 4;
                amount = apples;
            }
            if (foodType <= 0) {
                return;
            }
            if (foodType == 1) {
                if (amount > 32) {
                    amount = 32;
                }
            } else if (foodType == 2) {
                if (amount > 16) {
                    amount = 16;
                }
            } else if (foodType == 3) {
                if (amount > 16) {
                    amount = 16;
                }
            } else if (foodType == 4) {
                if (amount > 8) {
                    amount = 8;
                }
            }
            if (foodType == 1) {
                bread -= amount;
                sprite = amount;
            } else if (foodType == 2) {
                cheese -= amount;
                sprite = amount + 160;
            } else if (foodType == 3) {
                meat -= amount;
                sprite = amount + 176;
            } else if (foodType == 4) {
                apples -= amount;
                sprite = amount + 152;
            }
            if (slot == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = sprite;
            } else if (slot == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = sprite;
            } else if (slot == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = sprite;
            } else if (slot == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = sprite;
            } else if (slot == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = sprite;
            } else if (slot == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = sprite;
            } else if (slot == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage3 = sprite;
            } else if (slot == 7) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage4 = sprite;
            } else if (slot == 8) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = sprite;
            } else if (slot == 9) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = sprite;
            } else if (slot == 10) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = sprite;
            } else if (slot == 11) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = sprite;
            } else if (slot == 12) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = sprite;
            } else if (slot == 13) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = sprite;
            } else if (slot == 14) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = sprite;
            } else if (slot == 15) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = sprite;
            }
        }
    }

}
}
