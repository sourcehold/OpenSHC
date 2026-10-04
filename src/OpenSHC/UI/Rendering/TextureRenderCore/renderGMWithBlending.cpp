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

        // FUNCTION: STRONGHOLDCRUSADER 0x00455390
        void TextureRenderCore::renderGMWithBlending(GmID GmID, int imageID, int drawX, int drawY, int blendStrengthUnk)
        {
            int _imageIndex;
            ushort* _imageDataPtr;
            GmImageTypeInt _imageType;
            _imageIndex = GMTotalPicturesProcessed::instance[GmID] + imageID + -1;
            _imageDataPtr = (ushort*)(DAT_GMImageOffsets::instance[_imageIndex] + (int)this->gmProcessedImageData);
            if (blendStrengthUnk == 0x20) {
                return;
            }
            _imageType = this->gmFileHeaderColorpaletteArray[GmID].ImageType;
            if (blendStrengthUnk == 0) {
                if ((_imageType == IO::Graphics::GIT_InterfaceElement)
                    || (_imageType == IO::Graphics::GIT_CompressedImage)) {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(drawX,
                        drawY, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                        DAT_GMImageHeaders::instance.imh[_imageIndex].height, _imageDataPtr);
                    return;
                }
                if (_imageType == IO::Graphics::GIT_Animation) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(drawX, drawY,
                        DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                        DAT_GMImageHeaders::instance.imh[_imageIndex].height, (byte*)_imageDataPtr);
                }
                return;
            }
            if ((_imageType == IO::Graphics::GIT_InterfaceElement)
                || (_imageType == IO::Graphics::GIT_CompressedImage)) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, _imageDataPtr, blendStrengthUnk);
                return;
            }
            if (_imageType == IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, (byte*)_imageDataPtr, blendStrengthUnk);
            }
        }

    }
}
}
