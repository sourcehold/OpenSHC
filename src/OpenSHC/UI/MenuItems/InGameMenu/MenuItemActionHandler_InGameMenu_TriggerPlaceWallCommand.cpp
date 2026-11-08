#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00437ED0
        void InGameMenu::MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand()
        {
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {
                return;
            }
            // only for the wall, wooden wall, stairs and crenel tools
            if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_WALL
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_WOODWALL
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_STAIR
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_CRENAL) {
                return;
            }
            if (!DAT_ViewportRenderState::instance.viewportState.field_0x0) {
                return;
            }
            DAT_MouseState::instance.field_0x1dc = 1000;
            // the tile under the mouse
            if (DAT_TileMapState::instance.flatViewToggleValue1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
            } else {
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
            }
            // a click starts the drag, a held button or a finished drag moves its end, no button puts both ends here
            if (DAT_MouseState::instance.leftClickStart) {
                DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            } else if (DAT_MouseState::instance.draggingStopped || DAT_MouseState::instance.leftClickState) {
                DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            } else {
                if (DAT_ScrollingHandler::instance.isScrolling_0x0) {
                    return;
                }
                DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
                DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
                DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            }
            DAT_TileMapState::instance.buildingPlacementFailReason
                = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
            DAT_TileMapState::instance.wallPlacementCost = 0;
            DAT_TileMapState::instance.constructionTileCount = MACRO_CALL_MEMBER(
                OpenSHC::Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Resources::RT_STONE);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateWallBuildPath, DAT_TileMapState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, DAT_TileMapState::instance.dragStartX,
                DAT_TileMapState::instance.dragStartY, DAT_TileMapState::instance.dragEndX,
                DAT_TileMapState::instance.dragEndY, (ushort)DAT_TileMapState::instance.currentMapperCommand);
            // until the drag stops, only the preview is drawn
            if (!DAT_MouseState::instance.draggingStopped) {
                DAT_TileMapState::instance.wallDragButtonUp = !DAT_MouseState::instance.leftClickState;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::renderWallDragPreview, DAT_TileMapState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, DAT_TileMapState::instance.dragStartX,
                    DAT_TileMapState::instance.dragStartY, DAT_TileMapState::instance.dragEndX,
                    DAT_TileMapState::instance.dragEndY, (ushort)DAT_TileMapState::instance.currentMapperCommand);
                return;
            }
            if (DAT_TileMapState::instance.illegalBuild) {
                // the panel feedback text with the fail reason's number
                if (DAT_TileMapState::instance.buildingPlacementFailReason
                    != OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                        DAT_BottomLeftTextDisplayState::ptr)(1, OpenSHC::DE::SHCDE::TEXT_PANEL_FEEDBACK,
                        DAT_TileMapState::instance.buildingPlacementFailReason, 0, 100, 6000);
                }
                return;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TileMapState::instance.dragStartX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TileMapState::instance.dragStartY;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = DAT_TileMapState::instance.dragEndX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = DAT_TileMapState::instance.dragEndY;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = DAT_TileMapState::instance.currentMapperCommand;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam5 = DAT_TileMapState::instance.constructionTileCount;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_PLACE_WALL);
        }

    }
}
}
