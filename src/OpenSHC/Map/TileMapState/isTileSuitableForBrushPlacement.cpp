#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FBE70
    BOOLEnum TileMapState::isTileSuitableForBrushPlacement(int tile, uint x, uint y)
    {
        byte height = this->HeightLayer[tile];
        /* the tile suits a brush as soon as it stands above any one of its eight neighbours */
        uint neighbourY = y - 1;
        if (x <= 399 && neighbourY <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + x] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x]) > 0) {
            return TRUE;
        }
        uint neighbourX = x + 1;
        if (neighbourX <= 399 && neighbourY <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        if (neighbourX <= 399 && y <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + neighbourX] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        neighbourY = y + 1;
        if (neighbourX <= 399 && neighbourY <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x + 1]) > 0) {
            return TRUE;
        }
        if (x <= 399 && neighbourY <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + x] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x]) > 0) {
            return TRUE;
        }
        neighbourX = x - 1;
        if (neighbourX <= 399 && neighbourY <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[neighbourY * 400 + neighbourX] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y + 1].addXgetTile + x - 1]) > 0) {
            return TRUE;
        }
        if (neighbourX <= 399 && y <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + neighbourX] != 0
            && (int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x - 1]) > 0) {
            return TRUE;
        }

        if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid, DAT_ViewportRenderState::ptr)(
                neighbourX, y - 1)
            == FALSE) {
            return FALSE;
        }
        if ((int)(height - this->HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y - 1].addXgetTile + x - 1]) < 1) {
            return FALSE;
        }
        return TRUE;
    }

}
}
