#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The border is drawn in tiles of 24 by 24 pixels. Each row of tiles has a left, a middle and a right picture
        // in GID_INTERFACE_ICONS_3, followed by their three alpha masks; these are the rows' first pictures.
        enum {
            BORDER_TILE_SIZE = 24,
            BORDER_TOP_PICTURES = 1,
            BORDER_MIDDLE_PICTURES = 7,
            BORDER_BOTTOM_PICTURES = 13
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x00471340
        void PencilRenderCore::drawBorderedBoxWithBlendedBackground(int xPos, int yPos, int width, int height)
        {
            // Rounded up to whole tiles
            width = ((width - 1) / BORDER_TILE_SIZE + 1) * BORDER_TILE_SIZE;
            height = ((height - 1) / BORDER_TILE_SIZE + 1) * BORDER_TILE_SIZE;
            // The custom version's blends for blendStrength 0: 0 on the tiles, 16 (half-way to 32) on the background
            for (int y = 0; y < height; y += BORDER_TILE_SIZE) {
                int rowPictures;
                if (y == 0) {
                    rowPictures = BORDER_TOP_PICTURES;
                } else if (y == height - BORDER_TILE_SIZE) {
                    rowPictures = BORDER_BOTTOM_PICTURES;
                } else {
                    rowPictures = BORDER_MIDDLE_PICTURES;
                }
                for (int x = 0; x < width; x += BORDER_TILE_SIZE) {
                    // The left picture first, replaced further in: a flat else-if chain doesn't match
                    int picture = rowPictures;
                    if (x != 0) {
                        if (x == width - BORDER_TILE_SIZE) {
                            picture = rowPictures + 2;
                        } else {
                            // The inside of the box is left to the blended background
                            if (rowPictures == BORDER_MIDDLE_PICTURES) {
                                continue;
                            }
                            picture = rowPictures + 1;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, picture,
                        x + xPos, y + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, picture + 3, 0);
                }
            }
            // The background always goes on the global pencil, not on this one.
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(xPos + BORDER_TILE_SIZE, yPos + BORDER_TILE_SIZE,
                xPos + width - BORDER_TILE_SIZE - 1, yPos + height - BORDER_TILE_SIZE - 1, 16);
        }

    }
}
}
