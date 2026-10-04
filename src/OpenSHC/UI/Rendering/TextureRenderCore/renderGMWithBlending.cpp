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
            int iVar1;
            ushort* _imageDataPtr;
            GmImageTypeInt _imageType;
            iVar1 = GMTotalPicturesProcessed::instance[GmID];
            _imageDataPtr
                = (ushort*)(DAT_GMImageOffsets::instance[iVar1 + -1 + imageID] + (int)this->gmProcessedImageData);
            if (blendStrengthUnk != 0x20) {
                _imageType = this->gmFileHeaderColorpaletteArray[GmID].ImageType;
                if (blendStrengthUnk == 0) {
                    if ((_imageType == IO::Graphics::GIT_InterfaceElement)
                        || (_imageType == IO::Graphics::GIT_CompressedImage)) {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects,
                            this)(drawX, drawY,
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)), _imageDataPtr);
                    }
                    if (_imageType == IO::Graphics::GIT_Animation) {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk, this)(
                            drawX, drawY, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                            (byte*)((int)(_imageDataPtr)));
                    }
                } else {
                    if ((_imageType == IO::Graphics::GIT_InterfaceElement)
                        || (_imageType == IO::Graphics::GIT_CompressedImage)) {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea,
                            this)(drawX, drawY,
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)), _imageDataPtr,
                            blendStrengthUnk);
                    }
                    if (_imageType == IO::Graphics::GIT_Animation) {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk, this)(
                            drawX, drawY, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                            (byte*)((int)(_imageDataPtr)), blendStrengthUnk);
                    }
                }
            }
        }

    }
}
}
