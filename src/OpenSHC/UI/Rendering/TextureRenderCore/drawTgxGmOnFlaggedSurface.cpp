#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/GmImageType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004554A0
        void TextureRenderCore::drawTgxGmOnFlaggedSurface(GmID gmId, int imageIndexInGm, int xPos, int yPos)
        {
            // picture imageIndexInGm of the gm file, counted from 1
            int const imageIndex = GMFirstPictureIndex::instance[gmId] + imageIndexInGm - 1;
            ushort* const source = (ushort*)(this->gmProcessedImageData + DAT_GMImageOffsets::instance[imageIndex]);
            // interface elements and compressed images draw the same way
            // two tests as in the original (one test with ||: quick_diff 1.0000 -> 0.3014)
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == OpenSHC::IO::Graphics::GIT_InterfaceElement) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos,
                    yPos, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
            }
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == OpenSHC::IO::Graphics::GIT_CompressedImage) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos,
                    yPos, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
            }
        }

    }
}
}
