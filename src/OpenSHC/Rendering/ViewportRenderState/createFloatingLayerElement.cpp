#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E63A0
    void ViewportRenderState::createFloatingLayerElement(
        GmID gmID, int imageID, int imageX, int imageY, int tile, int variation)
    {
        int newFloaterIndex = this->availableFloaterIndex;
        if (tile < 0) {
            return;
        }
        if (250 <= (int)this->availableFloaterIndex) {
            return;
        }

        if (DAT_TileMapState::instance.FloatingLayer[tile] == 0) {
            this->floatersArray[newFloaterIndex].id = 0;
        } else {
            ushort idAtTile = DAT_TileMapState::instance.FloatingLayer[tile];
            uint floaterID = idAtTile;
            if (249 < floaterID) {
                return;
            }
            for (; floaterID != 0; floaterID = this->floatersArray[floaterID].id) {
                if (this->floatersArray[floaterID].imageID == imageID && this->floatersArray[floaterID].gmID == gmID) {
                    return;
                }
            }
            this->floatersArray[newFloaterIndex].id = idAtTile;
        }

        DAT_TileMapState::instance.FloatingLayer[tile] = (ushort)newFloaterIndex;
        this->floatersArray[newFloaterIndex].gmID = gmID;
        this->floatersArray[newFloaterIndex].imageID = imageID;
        this->floatersArray[newFloaterIndex].originX
            = imageX - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[gmID].originX;
        this->floatersArray[newFloaterIndex].originY
            = imageY - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[gmID].originY;
        this->floatersArray[newFloaterIndex].tile = tile;
        this->floatersArray[newFloaterIndex].variation = variation;
        this->availableFloaterIndex = this->availableFloaterIndex + 1;
    }

}
}
