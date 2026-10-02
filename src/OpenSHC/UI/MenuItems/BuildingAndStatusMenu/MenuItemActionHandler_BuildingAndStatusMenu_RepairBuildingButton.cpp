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

        using OpenSHC::Audio::SFX::ResourceLackSFX;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00466160
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton()
        {
            BOOLEnum _buildingDamaged;
            _buildingDamaged
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.menuSelectedBuildingID);
            int _buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
            BOOLEnum _enemyTooClose = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(
                (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].owner,
                (uint)((
                    short)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .x),
                (uint)((
                    short)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .y),
                (int)((-(uint)(DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                          & 0xfffffff1)
                    + 0x1e));
            if ((_enemyTooClose == FALSE) && (_buildingDamaged != FALSE)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                    DAT_BuildingsState::ptr)(DAT_BuildingsState::instance.menuSelectedBuildingID);
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[2]
                    < DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_WOOD);
                }
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[4]
                    < DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                    = DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                    = DAT_BuildingsState::instance.buildings[_buildingID].uid;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    = DAT_BuildingsState::instance.menuSelectedBuildingID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_REPAIR_TOWER);
            }
        }

    }
}
}
