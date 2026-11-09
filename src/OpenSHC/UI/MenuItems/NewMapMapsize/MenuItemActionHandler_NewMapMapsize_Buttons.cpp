#include "../NewMapMapsize.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/MapLockState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042F940
        void NewMapMapsize::MenuItemActionHandler_NewMapMapsize_Buttons(int button, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            // buttons 1 to 4 make a new map of that size
            int mapSize = OpenSHC::Map::MC_MAP_SIZE_400;
            if (button <= 0) {
                return;
            }
            if (button > 4) {
                if (button == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                }
                return;
            }
            if (button == 1) {
                mapSize = OpenSHC::Map::MC_MAP_SIZE_160;
            } else if (button == 2) {
                mapSize = OpenSHC::Map::MC_MAP_SIZE_200;
            } else if (button == 3) {
                mapSize = OpenSHC::Map::MC_MAP_SIZE_300;
            }
            DAT_TileMapState::instance.mapSize = mapSize;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                mapSize);
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
                DAT_PathFindingState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap,
                DAT_PathFindingState::ptr)(1);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
                DAT_BuildingsState::ptr)();
            DAT_TileMapState::instance.forceUpdateMacroLayerFlag = 1;
            DAT_TileMapState::instance.field_0x55487c = 200;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processGameTick, DAT_GameState::ptr)();
            for (int section = 0; section < 40; ++section) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(
                    section);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize,
                DAT_MinimapViewState::ptr)(0, 100);
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                DAT_ViewportRenderState::ptr)();
            DAT_GameCore::instance.descriptionUseStringTable = 0;
            DAT_GameCore::instance.U3_mapLockedState = OpenSHC::Map::MLS_EDITABLE;
            DAT_GameCore::instance.temporaryTextBufferOfSize1000[0] = '\0';
            // both arms are the same; the original still compares U2_mapType_singleOrMulti here
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
            }
            DAT_GameCore::instance.mapLoadedForEditor = 1;
        }

    }
}
}
