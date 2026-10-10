#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using Commands::MappersEnum;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004314E0
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(MappersEnum param_1, ...)
        {
            if (0x14b < (int)param_1) {
                DAT_GameSynchronyState::instance.editorPlacementPlayerID = 1;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
            }
            if (param_1 == Commands::M_MAPPER_AREA_BACK) {
                DAT_TileMapState::instance.editorActiveBrush = DAT_TileMapState::instance.editorActiveBrush + -1;
                if (DAT_TileMapState::instance.editorActiveBrush <= 0) {
                    DAT_TileMapState::instance.editorActiveBrush = 7;
                }
                if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK1
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK2
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK3
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK4
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK5)
                    goto LAB_004315c1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 1;
                    goto LAB_004315c1;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4)
                    goto LAB_004315a2;
                if (DAT_TileMapState::instance.editorActiveBrush != 6)
                    goto LAB_004315c1;
            LAB_00431832:
                DAT_TileMapState::instance.editorActiveBrush = 5;
            LAB_004315c1:
                DAT_TileMapState::instance.unknownBrushRelated = DAT_TileMapState::instance.editorActiveBrush >> 1;
                DAT_StopHandlingMenuItems::instance = 0;
            }
            switch (param_1) {
            case Commands::M_MAPPER_AREA:
                DAT_TileMapState::instance.editorActiveBrush = DAT_TileMapState::instance.editorActiveBrush + 1;
                if (7 < DAT_TileMapState::instance.editorActiveBrush) {
                    DAT_TileMapState::instance.editorActiveBrush = 1;
                }
                if (DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK1
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK2
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK3
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK4
                    && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_BIGROCK5)
                    goto LAB_004315c1;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                LAB_004315a2:
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                    goto LAB_004315c1;
                }
                if (DAT_TileMapState::instance.editorActiveBrush != 4) {
                    if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                        DAT_TileMapState::instance.editorActiveBrush = 7;
                    }
                    goto LAB_004315c1;
                }
                goto LAB_00431832;
            default:
                break;
            case Commands::M_MAPPER_MIN:
                DAT_TileMapState::instance.mapperMax = FALSE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case Commands::M_MAPPER_MAX:
                DAT_TileMapState::instance.mapperMax = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                return;
            case Commands::M_MAPPER_EXIT:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_UNUSED_OLD_TITLE_MENU, 0);
                return;
            case Commands::M_MAPPER_TOMAIN:
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
                return;
            case Commands::M_MAPPER_AFFECT_TYPE:
                if (DAT_TileMapState::instance.editorAffectType + 1 < 2) {
                    DAT_TileMapState::instance.editorAffectType = DAT_TileMapState::instance.editorAffectType + 1;
                }
                DAT_TileMapState::instance.editorAffectType = 0;
                return;
            case Commands::M_MAPPER_TO_MAP_EDIT:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                return;
            case Commands::M_MAPPER_TEST:
                break;
            case Commands::M_MAPPER_REBUILD:
                MACRO_CALL_MEMBER(Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                return;
            case Commands::M_MAPPER_SNAP_TO:
                if (DAT_TileMapState::instance.editorSnapToMode) {
                    DAT_TileMapState::instance.editorSnapToMode
                        = (-(uint)(DAT_TileMapState::instance.editorSnapToMode != 1) & 0xfffffffe) + 2;
                }
                DAT_TileMapState::instance.editorSnapToMode = 1;
                return;
            case Commands::M_MAPPER_BIGROCK1:
                DAT_TileMapState::instance.editorRockType = 1;
                DAT_TileMapState::instance.rockOrientation = 0;
                break;
            case Commands::M_MAPPER_BIGROCK2:
                DAT_TileMapState::instance.editorRockType = 2;
                DAT_TileMapState::instance.rockOrientation = 2;
                break;
            case Commands::M_MAPPER_BIGROCK3:
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                DAT_TileMapState::instance.editorRockType = 3;
                DAT_TileMapState::instance.rockOrientation = 4;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                }
                goto LAB_00431642;
            case Commands::M_MAPPER_BIGROCK4:
                DAT_TileMapState::instance.editorRockType = 4;
                DAT_TileMapState::instance.rockOrientation = 6;
                break;
            case Commands::M_MAPPER_BIGROCK5:
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                DAT_TileMapState::instance.editorRockType = 5;
                DAT_TileMapState::instance.rockOrientation = 0;
                if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                    DAT_TileMapState::instance.rockOrientation = 0;
                    DAT_TileMapState::instance.editorRockType = 5;
                    DAT_TileMapState::instance.editorActiveBrush = 3;
                }
                if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                    DAT_TileMapState::instance.editorActiveBrush = 5;
                }
                goto LAB_00431652;
            case Commands::M_MAPPER_MAP_SIZE:
                if (!DAT_TileMapState::instance.mapSize) {
                    DAT_TileMapState::instance.mapSize = 400;
                }
                MACRO_CALL_MEMBER(Map::TileMapState_Func::setMapSize, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::resetHeightAndMapBorders, DAT_TileMapState::ptr)(
                    DAT_TileMapState::instance.mapSize);
                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::forceFullTileMapRedraw, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(
                    UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(
                    UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
                MACRO_CALL_MEMBER(
                    Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
                return;
            case Commands::M_MAPPER_MP_KEEP1:
            case Commands::M_MAPPER_MP_KEEP2:
            case Commands::M_MAPPER_MP_KEEP3:
            case Commands::M_MAPPER_MP_KEEP4:
            case Commands::M_MAPPER_MP_KEEP5:
            case Commands::M_MAPPER_MP_KEEP6:
            case Commands::M_MAPPER_MP_KEEP7:
            case Commands::M_MAPPER_MP_KEEP8:
                DAT_GameSynchronyState::instance.editorPlacementPlayerID
                    = param_1 - Commands::M_MAPPER_SUB_MODE_FEATURE_MP;
                if (DAT_GameCore::instance.mapU2MiddleBytes[2] == 0) {
                    DAT_TileMapState::instance.currentMapperCommand
                        = (Commands::MappersEnum)((DAT_GameCore::instance.mapU2MiddleBytes[1] != 0)
                            + Commands::M_MAPPER_KEEP1);
                }
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_KEEP3;
            }
            if (DAT_TileMapState::instance.editorActiveBrush == 2) {
                DAT_TileMapState::instance.currentMapperCommand = param_1;
                DAT_TileMapState::instance.editorActiveBrush = 3;
            }
        LAB_00431642:
            DAT_TileMapState::instance.currentMapperCommand = param_1;
            if (DAT_TileMapState::instance.editorActiveBrush == 4) {
                DAT_TileMapState::instance.editorActiveBrush = 5;
            }
        LAB_00431652:
            DAT_TileMapState::instance.currentMapperCommand = param_1;
            if (DAT_TileMapState::instance.editorActiveBrush == 6) {
                DAT_TileMapState::instance.editorActiveBrush = 7;
            }
        }

    }
}
}
