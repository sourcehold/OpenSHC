#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004314E0
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(MappersEnum command, ...)
        {
            switch (command) {
            case OpenSHC::Commands::M_MAPPER_EXIT:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_UNUSED_OLD_TITLE_MENU, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_REBUILD:
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                return;
            case OpenSHC::Commands::M_MAPPER_TO_MAP_EDIT:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_TOMAIN:
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = OpenSHC::UI::Enums::BMTT_CASTLE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_AREA:
                // the next brush size; rocks only come in odd sizes
                ++DAT_TileMapState::instance.editorActiveBrush;
                if (DAT_TileMapState::instance.editorActiveBrush > 7) {
                    DAT_TileMapState::instance.editorActiveBrush = 1;
                }
                if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5) {
                    if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                        DAT_TileMapState::instance.editorActiveBrush = 3;
                    } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                        DAT_TileMapState::instance.editorActiveBrush = 5;
                    } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                        DAT_TileMapState::instance.editorActiveBrush = 7;
                    }
                }
                DAT_TileMapState::instance.unknownBrushRelated = DAT_TileMapState::instance.editorActiveBrush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            case OpenSHC::Commands::M_MAPPER_AFFECT_TYPE:
                ++DAT_TileMapState::instance.editorAffectType;
                if (DAT_TileMapState::instance.editorAffectType > 1) {
                    DAT_TileMapState::instance.editorAffectType = 0;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_MIN:
                DAT_TileMapState::instance.mapperMax = FALSE;
                DAT_TileMapState::instance.currentMapperCommand = command;
                return;
            case OpenSHC::Commands::M_MAPPER_MAX:
                DAT_TileMapState::instance.mapperMax = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = command;
                return;
            // each rock steps the brush up to the next odd size; one shared round-up for the five loses the match
            case OpenSHC::Commands::M_MAPPER_BIGROCK1:
                DAT_TileMapState::instance.editorRockType = 1;
                DAT_TileMapState::instance.rockOrientation = 0;
                DAT_TileMapState::instance.currentMapperCommand = command;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK2:
                DAT_TileMapState::instance.editorRockType = 2;
                DAT_TileMapState::instance.rockOrientation = 2;
                DAT_TileMapState::instance.currentMapperCommand = command;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK3:
                DAT_TileMapState::instance.editorRockType = 3;
                DAT_TileMapState::instance.rockOrientation = 4;
                DAT_TileMapState::instance.currentMapperCommand = command;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK4:
                DAT_TileMapState::instance.editorRockType = 4;
                DAT_TileMapState::instance.rockOrientation = 6;
                DAT_TileMapState::instance.currentMapperCommand = command;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK5:
                DAT_TileMapState::instance.editorRockType = 5;
                DAT_TileMapState::instance.rockOrientation = 0;
                DAT_TileMapState::instance.currentMapperCommand = command;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_SNAP_TO:
                // the snap mode steps 0 -> 1 -> 2 -> 0
                if (DAT_TileMapState::instance.editorSnapToMode == 0) {
                    DAT_TileMapState::instance.editorSnapToMode = 1;
                } else if (DAT_TileMapState::instance.editorSnapToMode == 1) {
                    DAT_TileMapState::instance.editorSnapToMode = 2;
                } else {
                    DAT_TileMapState::instance.editorSnapToMode = 0;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_MAP_SIZE:
                // a map without a size yet gets the default one
                if (DAT_TileMapState::instance.mapSize == 0) {
                    DAT_TileMapState::instance.mapSize = OpenSHC::Map::MC_MAP_SIZE_400;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMapSize, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize,
                    DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize,
                    DAT_ViewportRenderState::ptr)();
                return;
            case OpenSHC::Commands::M_MAPPER_MP_KEEP1:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP2:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP3:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP4:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP5:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP6:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP7:
            case OpenSHC::Commands::M_MAPPER_MP_KEEP8:
                // players 1 to 8
                DAT_GameSynchronyState::instance.editorPlacementPlayerID
                    = command - OpenSHC::Commands::M_MAPPER_MP_KEEP1 + 1;
                if (DAT_GameCore::instance.mapU2MiddleBytes[2] != 0) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_KEEP3;
                } else if (DAT_GameCore::instance.mapU2MiddleBytes[1] != 0) {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_KEEP2;
                } else {
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_KEEP1;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_AREA_BACK:
                // the previous brush size; rocks only come in odd sizes
                --DAT_TileMapState::instance.editorActiveBrush;
                if (DAT_TileMapState::instance.editorActiveBrush < 1) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5) {
                    if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                        DAT_TileMapState::instance.editorActiveBrush = 1;
                    } else if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                        DAT_TileMapState::instance.editorActiveBrush = 3;
                    } else if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                        DAT_TileMapState::instance.editorActiveBrush = 5;
                    }
                }
                DAT_TileMapState::instance.unknownBrushRelated = DAT_TileMapState::instance.editorActiveBrush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            case OpenSHC::Commands::M_MAPPER_TEST:
                // the test button does nothing here
                return;
            default:
                DAT_GameSynchronyState::instance.editorPlacementPlayerID = 1;
                DAT_TileMapState::instance.currentMapperCommand = command;
                return;
            }
        }

    }
}
}
