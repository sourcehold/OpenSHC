#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            using WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x00466160
            void MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton()
            {
                BOOLEnum notDamaged = FALSE;
                if (!MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                        DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.menuSelectedBuildingID)) {
                    notDamaged = TRUE;
                }
                int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
                // No repairs with an enemy within 30 (15 in a multiplayer game). Set before the call: written inline in
                // the call it moves the registers.
                int requiredDistance;
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    requiredDistance = 15;
                } else {
                    requiredDistance = 30;
                }
                BOOLEnum const enemyTooClose
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                        DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, requiredDistance);
                if (enemyTooClose || notDamaged) {
                    return;
                }
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.menuSelectedBuildingID);
                // Cost against stock in this order, as the original compares them.
                if (DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost
                    > DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[Game::Resources::RT_WOOD]) {
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_WOOD);
                    return;
                }
                if (DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost
                    > DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[Game::Resources::RT_STONE]) {
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_STONE);
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_BuildingsState::instance.menuSelectedBuildingID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_REPAIR_TOWER);
            }

        }
    }
}
}
