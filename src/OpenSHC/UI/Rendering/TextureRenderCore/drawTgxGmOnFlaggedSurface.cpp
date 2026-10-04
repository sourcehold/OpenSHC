#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmImageType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmImageType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004554A0
        void TextureRenderCore::drawTgxGmOnFlaggedSurface(GmID gmId, int imageIndexInGm, int xPos, int yPos)
        {
            int _imageIndex;
            ushort* _tgxSourcePtr;
            _imageIndex = GMTotalPicturesProcessed::instance[gmId] + imageIndexInGm + -1;
            _tgxSourcePtr = (ushort*)(DAT_GMImageOffsets::instance[_imageIndex] + (int)this->gmProcessedImageData);
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == IO::Graphics::GIT_InterfaceElement) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos, yPos,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, _tgxSourcePtr);
            }
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == IO::Graphics::GIT_CompressedImage) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos, yPos,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, _tgxSourcePtr);
            }
        }

    }
}
}
