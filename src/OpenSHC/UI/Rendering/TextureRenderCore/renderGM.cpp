#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmImageType.hpp"
#include "OpenSHC/IO/Graphics/GmImageTypeInt.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmImageType;
        using IO::Graphics::GmImageTypeInt;

        // FUNCTION: STRONGHOLDCRUSADER 0x00455300
        void TextureRenderCore::renderGM(eGM gmID, int imageID, int drawX, int drawY)
        {
            int iVar1;
            GmImageTypeInt _imageType;
            iVar1 = GMTotalPicturesProcessed::instance[gmID];
            _imageType = this->gmFileHeaderColorpaletteArray[gmID].ImageType;
            if ((_imageType != IO::Graphics::GIT_InterfaceElement)
                && (_imageType != IO::Graphics::GIT_CompressedImage)) {
                if (_imageType == IO::Graphics::GIT_Animation) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(
                        drawX, drawY, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                        (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                        (byte*)((int)((
                            DAT_GMImageOffsets::instance[iVar1 + -1 + imageID] + (int)this->gmProcessedImageData))));
                }
            }
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(
                drawX, drawY, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                (ushort*)((int)(

                    (DAT_GMImageOffsets::instance[iVar1 + -1 + imageID] + (int)this->gmProcessedImageData))));
        }

    }
}
}
