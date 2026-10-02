#include "../EditorMapTypeQuickChange.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Map::MapType2;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004ABEB0
        void EditorMapTypeQuickChange::MenuItemActionHandler_EditorMapTypeQuickChange_Main(int param_1, ...)
        {
            BOOLEnum BVar1;
            int _y10;
            switch (param_1) {
            case 0:
            case 1:
            case 2:
                DAT_GameCore::instance.U3_mapLockedState = param_1;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                BVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::mapHasCertainEvent, DAT_MapPropertiesState::ptr)();
                if (BVar1 == FALSE) {
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = param_1 - OpenSHC::Map::MT_JUST_BUILD;
                /*
                  param1 - 3
                 */                }
                break;
            case 10:
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 0;
                return;
            case 0xb:
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 1;
                return;
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::resetAreaBasedOnLogicalLayer, DAT_TileMapState::ptr)();
                if (param_1 == 0x14) {
                    DAT_TileMapState::instance.mapSize = 0xa0;
                } else if (param_1 == 0x15) {
                    DAT_TileMapState::instance.mapSize = 200;
                } else if (param_1 == 0x16) {
                    DAT_TileMapState::instance.mapSize = 300;
                } else {
                    DAT_TileMapState::instance.mapSize = 400;
                    if (param_1 != 0x17) {
                        DAT_TileMapState::instance.mapSize = param_1;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
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
                DAT_TileMapState::instance.field68_0x55487c = 200;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::processGameTick, DAT_GameState::ptr)();
                _y10 = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlifeGrid, DAT_WildlifeState::ptr)(
                        _y10);
                    _y10 = _y10 + 1;
                } while (_y10 < 0x28);
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateWildlife, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateSection1034Info, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Map::WildlifeState_Func::updateNofFpoints, DAT_WildlifeState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                    DAT_ViewportRenderState::ptr)();
            }
        }

    }
}
}
