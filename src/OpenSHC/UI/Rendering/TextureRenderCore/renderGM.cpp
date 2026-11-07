#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/GmImageType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455300
        void TextureRenderCore::renderGM(eGM gmID, int imageID, int drawX, int drawY)
        {
            // imageID counts from 1 within the gm file
            int const imageIndex = GMFirstPictureIndex::instance[gmID] + imageID - 1;
            ushort* const source = (ushort*)(this->gmProcessedImageData + DAT_GMImageOffsets::instance[imageIndex]);
            OpenSHC::IO::Graphics::GmImageTypeInt const imageType = this->gmFileHeaderColorpaletteArray[gmID].ImageType;
            // One call per arm, as the original (one test with ||: quick_diff 1.0000 -> 0.6585)
            if (imageType == OpenSHC::IO::Graphics::GIT_InterfaceElement) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
            } else if (imageType == OpenSHC::IO::Graphics::GIT_CompressedImage) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
            } else if (imageType == OpenSHC::IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(drawX,
                    drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, (byte*)source);
            }
        }

    }
}
}
