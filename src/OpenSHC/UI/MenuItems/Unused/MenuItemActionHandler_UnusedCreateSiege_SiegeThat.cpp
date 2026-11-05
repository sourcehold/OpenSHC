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
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004437E0
        void Unused::MenuItemActionHandler_UnusedCreateSiege_SiegeThat(int button, ...)
        {
            switch (button) {
            case 5:
                if (INT_00b95f68::instance) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 43;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_QUIT_DIALOG);
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                break;
            case 4:
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    // "mission22.map"
                    OpenSHC::IO::FRT_MAPS, STR_Mission22Map);
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
                // the slot is read at each store: with a local, ecx for the call below is loaded before them
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[OpenSHC::Game::Resources::RT_GOLD] = 1500;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[OpenSHC::Game::Resources::RT_STONE] = 1000;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .pitchDitchTileCount = 0;
                DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .moatTileCount = 0;
                DAT_GameCore::instance.mapU4Int1 = 1;
                INT_00b960ec::instance = TRUE;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
                // case 4 goes on into case 6
            case 6:
                INT_00b95f68::instance = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SIEGE_THAT;
                DAT_GameCore::instance.missionNumber1to20 = 27;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameCore::instance.missionNumber1to20 = 31;
                MACRO_CALL(OpenSHC::UI::MenuItems::MapEditorLandscaping_Func::
                        MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)(OpenSHC::Commands::M_MAPPER_TOMAIN);
                INT_00b960ec::instance = TRUE;
                break;
            case 2:
                DAT_MenuTextInputState::instance.field_0x9c = 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveMap, DAT_MenuTextInputState::ptr)(
                    OpenSHC::UI::Enums::MMT_LOAD_MAP);
                INT_00b960ec::instance = TRUE;
                break;
            case 35:
                if (INT_00b960ec::instance) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                        DAT_MapPropertiesState::ptr)();
                    DAT_MenuTextInputState::instance.field_0x9c = 1;
                    DAT_MenuTextInputState::instance.field_0xa4 = 0;
                    DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_EDITABLE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveMap, DAT_MenuTextInputState::ptr)(
                        OpenSHC::UI::Enums::MMT_SAVE_MAP);
                    INT_00b960e4::instance = TRUE;
                }
                break;
            case 36:
                if (INT_00b960ec::instance) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
                    MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                        DAT_MapPropertiesState::ptr)();
                    DAT_MenuTextInputState::instance.field_0x9c = 1;
                    DAT_MenuTextInputState::instance.field_0xa4 = 0;
                    DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_PLAYABLE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateLoadOrSaveMapUI,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_SAVE_MAP);
                    INT_00b960e4::instance = TRUE;
                }
                break;
            }
        }

    }
}
}
