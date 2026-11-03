#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B51A0
    void MinimapViewState::convertMinimapClickToTileXY(int* tileX, int* tileY)
    {
        if (this->minimapClickEnabled != 0) {
            int const mouseY = DAT_MouseState::instance.screenSpaceY - this->y;
            int orientationOffset = 0;
            *tileX = (((DAT_MouseState::instance.screenSpaceX - this->x) * this->oneOrTwo) / this->widthFactor + 6
                         + this->tileOffsetX)
                * 32;
            int const screenY = ((this->oneOrTwo * mouseY) / this->heightFactor + this->tileOffsetY) * 8;
            *tileY = screenY;
            if (DAT_TileMapState::instance.mapOrientation != 0) {
                if (DAT_TileMapState::instance.mapOrientation == 6) {
                    orientationOffset = 0x13a10;
                } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                    orientationOffset = 0x27420;
                } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                    orientationOffset = 0x3ae30;
                }
            }
            int const tile = DAT_ViewportRenderState::instance
                                 .screenPointToTileNumber[*tileX / 32 + screenY / 16 * 0x191 + orientationOffset - 6];
            int const row = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            *tileY = row;
            *tileX = tile - DAT_ViewportRenderState::instance.translationMatrix[row].addXgetTile;
            return;
        }
        *tileX = -1;
        *tileY = -1;
    }

}
}
