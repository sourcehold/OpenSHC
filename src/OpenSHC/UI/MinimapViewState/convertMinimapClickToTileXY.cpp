#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B51A0
    void MinimapViewState::convertMinimapClickToTileXY(int* tileX, int* tileY)
    {
        // Guarded, not an early return (an early return when disabled: quick_diff 1.0000 -> 0.9000)
        if (this->minimapClickEnabled) {
            // Y and the offset up front (Y inline: quick_diff 1.0000 -> 0.7770; offset at first use: 0.6714)
            int const mouseY = DAT_MouseState::instance.screenSpaceY - this->y;
            int orientationOffset = 0;
            // The original adds 6 here and takes it off again in the index below, so both stay.
            *tileX = (((DAT_MouseState::instance.screenSpaceX - this->x) * this->oneOrTwo) / this->widthFactor + 6
                         + this->tileOffsetX)
                * 32;
            int const screenY = ((this->oneOrTwo * mouseY) / this->heightFactor + this->tileOffsetY) * 8;
            // The out parameters hold the screen point until the tile is known.
            *tileY = screenY;
            // Four tables, 80400 entries apart (computed from the orientation: quick_diff 1.0000 -> 0.5507)
            if (DAT_TileMapState::instance.mapOrientation == 0) {
                // Set again, as in renderPreviewAtMouseLocation (without this arm: quick_diff 1.0000 -> 0.8714)
                orientationOffset = 0;
            } else if (DAT_TileMapState::instance.mapOrientation == 6) {
                orientationOffset = 80400;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                orientationOffset = 160800;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                orientationOffset = 241200;
            }
            int const tile = DAT_ViewportRenderState::instance
                                 .screenPointToTileNumber[*tileX / 32 + screenY / 16 * 401 + orientationOffset + 2];
            int const row = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            *tileY = row;
            *tileX = tile - DAT_ViewportRenderState::instance.translationMatrix[row].addXgetTile;
        } else {
            *tileX = -1;
            *tileY = -1;
        }
    }

}
}
