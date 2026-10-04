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
            int _imageIndex;
            GmImageTypeInt _imageType;
            ushort* _imageDataPtr;
            _imageIndex = GMTotalPicturesProcessed::instance[gmID] + imageID + -1;
            _imageType = this->gmFileHeaderColorpaletteArray[gmID].ImageType;
            _imageDataPtr = (ushort*)(DAT_GMImageOffsets::instance[_imageIndex] + (int)this->gmProcessedImageData);
            if ((_imageType == IO::Graphics::GIT_InterfaceElement)
                || (_imageType == IO::Graphics::GIT_CompressedImage)) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects,
                    this)(drawX, drawY, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, _imageDataPtr);
                return;
            }
            if (_imageType == IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(drawX, drawY,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height, (byte*)_imageDataPtr);
            }
        }

    }
}
}
