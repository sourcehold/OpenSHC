#include "../Helpers.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00437CC0
    void Helpers::HandleWallTerrainMouseDrag()
    {
        if (!DAT_ViewportRenderState::instance.viewportState.field_0x0) {
            return;
        }
        if (DAT_TileMapState::instance.flatViewToggleValue1) {
            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::setupMouseTileXY2, DAT_ViewportRenderState::ptr)();
        } else {
            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::setupMouseTileXY, DAT_ViewportRenderState::ptr)();
        }
        if (DAT_MouseState::instance.leftClickStart) {
            DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
        } else if (!DAT_MouseState::instance.draggingStopped && !DAT_MouseState::instance.leftClickState) {
            if (DAT_ScrollingHandler::instance.isScrolling_0x0) {
                return;
            }
            DAT_TileMapState::instance.dragStartX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragStartY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
            DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
        } else {
            DAT_TileMapState::instance.dragEndX = DAT_ViewportRenderState::instance.viewportState.mouseTileX;
            DAT_TileMapState::instance.dragEndY = DAT_ViewportRenderState::instance.viewportState.mouseTileY;
        }
        if (!DAT_MouseState::instance.draggingStopped) {
            int const tile
                = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.dragStartY].addXgetTile
                + DAT_TileMapState::instance.dragStartX;
            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_TileMapState::instance.dragStartX,
                DAT_TileMapState::instance.dragStartY, DAT_TileMapState::instance.dragEndX,
                DAT_TileMapState::instance.dragEndY);
            int orientation = DAT_DirectionAlgorithmState::instance.orientation;
            if (orientation == 15) {
                orientation = 0;
            }
            // The preview image turns with the map orientation.
            int image;
            switch (DAT_TileMapState::instance.mapOrientation) {
            case 0:
                image = GMFirstPictureIndex::instance[5] + 908 + orientation * 8;
                break;
            case 2:
                image = GMFirstPictureIndex::instance[5] + 908 + ((orientation - 2) & 7) * 8;
                break;
            case 4:
                image = GMFirstPictureIndex::instance[5] + 908 + ((orientation - 4) & 7) * 8;
                break;
            default:
                image = GMFirstPictureIndex::instance[5] + 908 + ((orientation + 2) & 7) * 8;
                break;
            }
            if (DAT_MouseState::instance.leftClickState) {
                if (DAT_TileMapState::instance.LogicLayer[tile] & Map::LogicHelpers::L_RIVER) {
                    DAT_TileMapState::instance.ConstructionGFXLayer[tile] = image;
                }
                DAT_TileMapState::instance.buildingPlacementFail = FALSE;
                return;
            }
            DAT_TileMapState::instance.buildingPlacementFail = TRUE;
            MACRO_CALL_MEMBER(Map::TileMapState_Func::renderPreviewMapperWithBrush, DAT_TileMapState::ptr)(
                DAT_ViewportRenderState::instance.viewportState.mouseTileX,
                DAT_ViewportRenderState::instance.viewportState.mouseTileY,
                DAT_TileMapState::instance.currentMapperCommand);
            return;
        }
        int const tile
            = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.dragStartY].addXgetTile
            + DAT_TileMapState::instance.dragStartX;
        if (DAT_TileMapState::instance.LogicLayer[tile] & Map::LogicHelpers::L_RIVER) {
            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_TileMapState::instance.dragStartX,
                DAT_TileMapState::instance.dragStartY, DAT_TileMapState::instance.dragEndX,
                DAT_TileMapState::instance.dragEndY);
            int orientation = DAT_DirectionAlgorithmState::instance.orientation;
            if (orientation == 15) {
                orientation = 0;
            }
            DAT_TileMapState::instance.WallGFXLayer[tile] = orientation;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TileMapState::instance.dragStartX;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_TileMapState::instance.dragStartY;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = 1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = Map::LogicHelpers::L_RIVER;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = 32;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_SET_TERRAIN);
        }
    }

}
}
