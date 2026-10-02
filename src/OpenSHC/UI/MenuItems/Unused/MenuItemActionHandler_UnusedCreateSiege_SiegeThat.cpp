#include "../Unused.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/MenuItems/MapEditorLandscaping.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95f68.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"
#include "OpenSHC/Globals/INT_00b960ec.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Map::MapLockState;
        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004437E0
        void Unused::MenuItemActionHandler_UnusedCreateSiege_SiegeThat(int param_1, ...)
        {
            int iVar1;
            switch (param_1) {
            case 2:
                DAT_MenuTextInputState::instance.field42_0x9c = 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveMap, DAT_MenuTextInputState::ptr)(
                    OpenSHC::UI::Enums::MMT_LOAD_MAP);
                INT_00b960ec::instance = 1;
                return;
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
            case 0x1e:
            case 0x1f:
            case 0x20:
            case 0x21:
            case 0x22:
                break;
            case 4:
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_MAPS, "mission22.map");
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                DAT_GameCore::instance.section1095 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[0xf] = 1500;
                DAT_GameState::instance.playerDataArray[iVar1].startResources[4] = 1000;
                DAT_GameState::instance.playerDataArray[iVar1].pitchDitchTileCount = 0;
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                DAT_GameState::instance.playerDataArray[iVar1].moatTileCount = 0;
                DAT_GameCore::instance.mapU4Int1 = 1;
                INT_00b960ec::instance = 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
            case 6:
                INT_00b95f68::instance = 1;
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SIEGE_THAT;
                DAT_GameCore::instance.missionNumber1to20 = 0x1b;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameCore::instance.missionNumber1to20 = 0x1f;
                MACRO_CALL(OpenSHC::UI::MenuItems::MapEditorLandscaping_Func::
                        MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)(OpenSHC::Commands::M_MAPPER_TOMAIN);
                INT_00b960ec::instance = 1;
                return;
            case 5:
                if (INT_00b95f68::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                }
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x2b;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_QUIT_DIALOG);
                return;
            case 0x23:
                if (INT_00b960ec::instance != 0) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                        DAT_MapPropertiesState::ptr)();
                    DAT_MenuTextInputState::instance.field42_0x9c = 1;
                    DAT_MenuTextInputState::instance.field44_0xa4 = 0;
                    DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_EDITABLE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveMap, DAT_MenuTextInputState::ptr)(
                        OpenSHC::UI::Enums::MMT_SAVE_MAP);
                    INT_00b960e4::instance = 1;
                }
                break;
            case 0x24:
                if (INT_00b960ec::instance != 0) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                        DAT_MapPropertiesState::ptr)();
                    DAT_MenuTextInputState::instance.field42_0x9c = 1;
                    DAT_MenuTextInputState::instance.field44_0xa4 = 0;
                    DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_PLAYABLE;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::activateLoadOrSaveMapUI, DAT_MenuTextInputState::ptr)(10);
                    INT_00b960e4::instance = 1;
                }
                break;
            default:
                break;
            }
        }

    }
}
}
