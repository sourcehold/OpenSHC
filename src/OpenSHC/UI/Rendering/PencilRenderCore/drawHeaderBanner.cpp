#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // The banner is 8 rows of 8 by 8 pixel tiles. Each y has a left, a middle and a right picture in
        // GID_INTERFACE_ICONS_3, followed by their three alpha masks; these are the rows' first pictures.
        enum {
            BANNER_TILE_SIZE = 8,
            BANNER_HEIGHT = 64,
            BANNER_TOP_PICTURES = 48,
            BANNER_MIDDLE_PICTURES = 54,
            BANNER_BOTTOM_PICTURES = 60,
            BANNER_CAP_PICTURE = 91,
            BANNER_CAP_MASK = 92
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x00468FE0
        void PencilRenderCore::drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk)
        {
            // The banner is one tile inside the box at the top and on both sides; width becomes the banner's own.
            yPos += BANNER_TILE_SIZE;
            int const left = xPos + BANNER_TILE_SIZE;
            width -= 2 * BANNER_TILE_SIZE;
            for (int y = 0; y < BANNER_HEIGHT; y += BANNER_TILE_SIZE) {
                int rowPictures;
                if (y == 0) {
                    rowPictures = BANNER_TOP_PICTURES;
                } else if (y == BANNER_HEIGHT - BANNER_TILE_SIZE) {
                    rowPictures = BANNER_BOTTOM_PICTURES;
                } else {
                    rowPictures = BANNER_MIDDLE_PICTURES;
                }
                for (int x = 0; x < width; x += BANNER_TILE_SIZE) {
                    // Nested, not a flat else-if chain (a flat chain: quick_diff 1.0000 -> 0.9827)
                    int picture = rowPictures;
                    if (x != 0) {
                        if (x == width - BANNER_TILE_SIZE) {
                            picture = rowPictures + 2;
                        } else {
                            picture = rowPictures + 1;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, picture,
                        x + left, y + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, picture + 3, 0);
                }
            }
            // An end cap 3 pixels in from each end of the banner
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, BANNER_CAP_PICTURE,
                left + 3, yPos + 9, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, BANNER_CAP_MASK, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, BANNER_CAP_PICTURE,
                left
                    - DAT_GMImageHeaders::instance
                        .imh[GMFirstPictureIndex::instance[OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3]
                            + BANNER_CAP_PICTURE - 1]
                        .width
                    + width - 3,
                yPos + 9, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, BANNER_CAP_MASK, 0);
        }

    }
}
}
