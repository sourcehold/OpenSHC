#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using Commands::MappersEnum;
        using Map::Buildings::BuildingFailReasonEnum;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00437ED0
        void InGameMenu::MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand()
        {
            UI::TextMessageBLLookupStructUnion _noBlLookup;
            _noBlLookup.buildingType = (Commands::MappersEnum)0;
            if (!DAT_GameSynchronyState::instance.syncStatus && !DAT_GameSynchronyState::instance.saveRelated
                && (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_WALL
                    || (((DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_WOODWALL
                             || (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_STAIR))
                        || (DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_CRENAL))))
                && DAT_ViewportRenderState::instance.viewportState.field0_0x0) {
                DAT_MouseState::instance.field68_0x1dc = 1000;
                if (!DAT_TileMapState::instance.flatViewToggleValue1) {
                    /*
                      set up currently hovering x and y
                     */
                    MACRO_CALL_MEMBER(
                        Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
                } else {
                    MACRO_CALL_MEMBER(
                        Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
                }
                if (!DAT_MouseState::instance.leftClickStart) {
                    if ((!DAT_MouseState::instance.draggingStopped) && (!DAT_MouseState::instance.leftClickState)) {
                        if (DAT_ScrollingHandler::instance.isScrolling_0x0) {}
                        DAT_TileMapState::instance.dragStartX
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                        DAT_TileMapState::instance.dragStartY
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                        DAT_TileMapState::instance.dragEndX
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                        DAT_TileMapState::instance.dragEndY
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                    } else {
                        DAT_TileMapState::instance.dragEndX
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                        DAT_TileMapState::instance.dragEndY
                            = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                    }
                } else {
                    DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                    DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                }
                DAT_TileMapState::instance.buildingPlacementFailReason
                    = Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                DAT_TileMapState::instance.wallPlacementCost = 0;
                DAT_TileMapState::instance.constructionTileCount
                    = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, 4);
                MACRO_CALL_MEMBER(Map::TileMapState_Func::validateWallBuildPath, DAT_TileMapState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (uint)((int)(DAT_TileMapState::instance.dragStartX)),
                    (uint)((int)(DAT_TileMapState::instance.dragStartY)),
                    (uint)((int)(DAT_TileMapState::instance.dragEndX)),
                    (uint)((int)(DAT_TileMapState::instance.dragEndY)),
                    (undefined4)((int)(DAT_TileMapState::instance.currentMapperCommand & 0xffff)));
                if (!DAT_MouseState::instance.draggingStopped) {
                    DAT_TileMapState::instance.wallDragButtonUp = (uint)(!DAT_MouseState::instance.leftClickState);
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::renderWallDragPreview, DAT_TileMapState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (uint)((int)(DAT_TileMapState::instance.dragStartX)),
                        (uint)((int)(DAT_TileMapState::instance.dragStartY)),
                        (uint)((int)(DAT_TileMapState::instance.dragEndX)),
                        (uint)((int)(DAT_TileMapState::instance.dragEndY)),
                        (undefined4)((int)(DAT_TileMapState::instance.currentMapperCommand & 0xffff)));
                }
                if (!DAT_TileMapState::instance.illegalBuild) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TileMapState::instance.dragStartY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TileMapState::instance.dragStartX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.dragEndX;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                        = DAT_TileMapState::instance.currentMapperCommand;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.dragEndY;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam5
                        = DAT_TileMapState::instance.constructionTileCount;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_PLACE_WALL);
                } else if (DAT_TileMapState::instance.buildingPlacementFailReason
                    != Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                    MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d,
                        (int)((int)(DAT_TileMapState::instance.buildingPlacementFailReason)), _noBlLookup, 100, 6000);
                }
            }
        }

    }
}
}
