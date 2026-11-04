#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
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

        using OpenSHC::Commands::MappersEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004314E0
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(MappersEnum param_1, ...)
        {
            switch (param_1) {
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
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_AREA: {
                int brush = DAT_TileMapState::instance.editorActiveBrush + 1;
                DAT_TileMapState::instance.editorActiveBrush = brush;
                if (brush > 7) {
                    brush = 1;
                    DAT_TileMapState::instance.editorActiveBrush = brush;
                }
                if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5) {
                    if (brush == 2) {
                        brush = 3;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    } else if (brush == 4) {
                        brush = 5;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    } else if (brush == 6) {
                        brush = 7;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    }
                }
                DAT_TileMapState::instance.unknownBrushRelated = brush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            }
            case OpenSHC::Commands::M_MAPPER_AFFECT_TYPE:
                if (++DAT_TileMapState::instance.editorAffectType > 1) {
                    DAT_TileMapState::instance.editorAffectType = 0;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_MIN:
                DAT_TileMapState::instance.mapperMax = FALSE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case OpenSHC::Commands::M_MAPPER_MAX:
                DAT_TileMapState::instance.mapperMax = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            // each rock steps the brush up to the next odd size: the original repeats the tail in every case
            case OpenSHC::Commands::M_MAPPER_BIGROCK1:
                DAT_TileMapState::instance.editorRockType = 1;
                DAT_TileMapState::instance.rockOrientation = 0;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK2:
                DAT_TileMapState::instance.editorRockType = 2;
                DAT_TileMapState::instance.rockOrientation = 2;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK3:
                DAT_TileMapState::instance.editorRockType = 3;
                DAT_TileMapState::instance.rockOrientation = 4;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK4:
                DAT_TileMapState::instance.editorRockType = 4;
                DAT_TileMapState::instance.rockOrientation = 6;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_BIGROCK5:
                DAT_TileMapState::instance.editorRockType = 5;
                DAT_TileMapState::instance.rockOrientation = 0;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                    return;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                return;
            case OpenSHC::Commands::M_MAPPER_SNAP_TO:
                if (DAT_TileMapState::instance.editorSnapToMode == 0) {
                    DAT_TileMapState::instance.editorSnapToMode = 1;
                    return;
                }
                DAT_TileMapState::instance.editorSnapToMode = DAT_TileMapState::instance.editorSnapToMode == 1 ? 2 : 0;
                return;
            case OpenSHC::Commands::M_MAPPER_MAP_SIZE:
                if (DAT_TileMapState::instance.mapSize == 0) {
                    DAT_TileMapState::instance.mapSize = 400;
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
                DAT_GameSynchronyState::instance.editorPlacementPlayerID
                    = param_1 - OpenSHC::Commands::M_MAPPER_SUB_MODE_FEATURE_MP;
                if (DAT_GameCore::instance.mapU2MiddleBytes[2] == 0) {
                    DAT_TileMapState::instance.currentMapperCommand
                        = (OpenSHC::Commands::MappersEnum)((DAT_GameCore::instance.mapU2MiddleBytes[1] != 0)
                            + OpenSHC::Commands::M_MAPPER_KEEP1);
                    return;
                }
                DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_KEEP3;
                return;
            case OpenSHC::Commands::M_MAPPER_AREA_BACK: {
                int brush = DAT_TileMapState::instance.editorActiveBrush - 1;
                DAT_TileMapState::instance.editorActiveBrush = brush;
                if (brush < 1) {
                    brush = 7;
                    DAT_TileMapState::instance.editorActiveBrush = brush;
                }
                if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK1
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK2
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK3
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK4
                    || DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_BIGROCK5) {
                    if (brush == 2) {
                        brush = 1;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    } else if (brush == 4) {
                        brush = 3;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    } else if (brush == 6) {
                        brush = 5;
                        DAT_TileMapState::instance.editorActiveBrush = brush;
                    }
                }
                DAT_TileMapState::instance.unknownBrushRelated = brush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            }
            default:
                DAT_GameSynchronyState::instance.editorPlacementPlayerID = 1;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case OpenSHC::Commands::M_MAPPER_TEST:
                return;
            }
        }

    }
}
}
