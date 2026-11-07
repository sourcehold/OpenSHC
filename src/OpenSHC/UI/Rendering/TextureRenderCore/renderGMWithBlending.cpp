#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/GmImageType.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455390
        void TextureRenderCore::renderGMWithBlending(GmID GmID, int imageID, int drawX, int drawY, int blendStrengthUnk)
        {
            // picture imageID of the gm file, counted from 1; a blend strength of 32 draws nothing, 0 draws unblended
            int const imageIndex = GMFirstPictureIndex::instance[GmID] + imageID - 1;
            ushort* const source = (ushort*)(this->gmProcessedImageData + DAT_GMImageOffsets::instance[imageIndex]);
            if (blendStrengthUnk == 32) {
                return;
            }
            // one branch per image type, the type read in each test (|| and a local: quick_diff 1.0000 -> 0.8000)
            if (blendStrengthUnk == 0) {
                if (this->gmFileHeaderColorpaletteArray[GmID].ImageType
                    == OpenSHC::IO::Graphics::GIT_InterfaceElement) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects,
                        this)(drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                        DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
                } else if (this->gmFileHeaderColorpaletteArray[GmID].ImageType
                    == OpenSHC::IO::Graphics::GIT_CompressedImage) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects,
                        this)(drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                        DAT_GMImageHeaders::instance.imh[imageIndex].height, source);
                } else if (this->gmFileHeaderColorpaletteArray[GmID].ImageType
                    == OpenSHC::IO::Graphics::GIT_Animation) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(
                        drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                        DAT_GMImageHeaders::instance.imh[imageIndex].height, (byte*)source);
                }
                return;
            }
            if (this->gmFileHeaderColorpaletteArray[GmID].ImageType == OpenSHC::IO::Graphics::GIT_InterfaceElement) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source, blendStrengthUnk);
            } else if (this->gmFileHeaderColorpaletteArray[GmID].ImageType
                == OpenSHC::IO::Graphics::GIT_CompressedImage) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(
                    drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, source, blendStrengthUnk);
            } else if (this->gmFileHeaderColorpaletteArray[GmID].ImageType == OpenSHC::IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                    this)(drawX, drawY, DAT_GMImageHeaders::instance.imh[imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[imageIndex].height, (byte*)source, blendStrengthUnk);
            }
        }

    }
}
}
