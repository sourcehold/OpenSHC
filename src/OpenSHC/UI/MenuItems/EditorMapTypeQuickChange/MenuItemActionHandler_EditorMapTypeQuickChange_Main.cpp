#include "../EditorMapTypeQuickChange.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABEB0
        void EditorMapTypeQuickChange::MenuItemActionHandler_EditorMapTypeQuickChange_Main(int param_1, ...)
        {
            switch (param_1) {
            case 0:
            case 1:
            case 2:
                DAT_GameCore::instance.U3_mapLockedState = param_1;
                return;
            case 3:
            case 4:
            case 5:
            case 6:
                // buttons 3 to 6 are the map types siege, invasion, economic and just build
                if (!MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::mapHasCertainEvent, DAT_MapPropertiesState::ptr)()) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = param_1 - 3;
                }
                return;
            case 10:
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 0;
                return;
            case 11:
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 1;
                return;
            case 20:
            case 21:
            case 22:
            case 23: {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::resetAreaBasedOnLogicalLayer, DAT_TileMapState::ptr)();
                int mapSize;
                if (param_1 == 20) {
                    mapSize = 160;
                } else if (param_1 == 21) { // the original compares the ids in turn, not a table
                    mapSize = 200;
                } else if (param_1 == 22) {
                    mapSize = 300;
                } else if (param_1 == 23) {
                    mapSize = 400;
                } else {
                    mapSize = param_1;
                }
                DAT_TileMapState::instance.mapSize = mapSize;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                    mapSize);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::resetAreaBasedOnLogicalLayer, DAT_TileMapState::ptr)();
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
                for (int row = 0; row < 40; ++row) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(
                        row);
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                    DAT_ViewportRenderState::ptr)();
                return;
            }
            }
        }

    }
}
}
