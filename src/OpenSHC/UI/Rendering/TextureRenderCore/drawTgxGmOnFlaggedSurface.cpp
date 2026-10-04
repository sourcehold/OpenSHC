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
            int iVar1;
            ushort* _tgxSourcePtr;
            int _imageIndex;
            iVar1 = GMTotalPicturesProcessed::instance[gmId];
            _tgxSourcePtr = (ushort*)(DAT_GMImageOffsets::instance[iVar1 + -1 + imageIndexInGm]
                + (int)this->gmProcessedImageData);
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == IO::Graphics::GIT_InterfaceElement) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos,
                    yPos, (int)((int)(DAT_GMImageHeaders::instance.imh[imageIndexInGm + iVar1 + -1].width)),
                    (int)((int)(DAT_GMImageHeaders::instance.imh[imageIndexInGm + iVar1 + -1].height)), _tgxSourcePtr);
            }
            if (this->gmFileHeaderColorpaletteArray[gmId].ImageType == IO::Graphics::GIT_CompressedImage) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawTgxOnFlaggedSurface, this)(xPos,
                    yPos, (int)((int)(DAT_GMImageHeaders::instance.imh[imageIndexInGm + iVar1 + -1].width)),
                    (int)((int)(DAT_GMImageHeaders::instance.imh[imageIndexInGm + iVar1 + -1].height)), _tgxSourcePtr);
            }
        }

    }
}
}
