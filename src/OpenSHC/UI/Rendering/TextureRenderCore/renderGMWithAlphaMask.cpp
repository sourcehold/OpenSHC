#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        // FUNCTION: STRONGHOLDCRUSADER 0x004557B0
        void TextureRenderCore::renderGMWithAlphaMask(
            GmID gmID, int imageID, int xPos, int yPos, GmID maskGmID, int alphaImageID, int blendStrength)
        {
            int _imageIndex;
            int _maskImageIndex;
            void* pvVar2;
            RenderTargetInt _tempBufferChoiceValueUnk;
            pvVar2 = this->gmProcessedImageData;
            if (DAT_TextureRenderCoreObject::instance.isZoom2 != 0) {
                _imageIndex = GMTotalPicturesProcessed::instance[gmID] + imageID + -1;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(xPos,
                    yPos, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                    DAT_GMImageHeaders::instance.imh[_imageIndex].height,
                    (ushort*)(DAT_GMImageOffsets::instance[_imageIndex] + (int)pvVar2), blendStrength);
                return;
            }
            _maskImageIndex = GMTotalPicturesProcessed::instance[maskGmID] + alphaImageID + -1;
            AlphaAndButtonSurfaceObj::instance.currentImageWidth
                = DAT_GMImageHeaders::instance.imh[_maskImageIndex].width;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                DAT_GMImageHeaders::instance.imh[_maskImageIndex].height
                    * AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2,
                COL_MAGENTA::instance.shortValue, (void*)AlphaAndButtonSurfaceObj::instance.surfacePtr);
            _tempBufferChoiceValueUnk = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, this)(
                (OpenSHC::DE::SHCDE::eGM)maskGmID, alphaImageID, 0, 0);
            _imageIndex = GMTotalPicturesProcessed::instance[gmID] + imageID + -1;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _tempBufferChoiceValueUnk;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGmWithPreparedAlphaMask, this)(xPos,
                yPos, DAT_GMImageHeaders::instance.imh[_imageIndex].width,
                DAT_GMImageHeaders::instance.imh[_imageIndex].height,
                (ushort*)(DAT_GMImageOffsets::instance[_imageIndex] + (int)pvVar2), blendStrength);
        }

    }
}
}
