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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004557B0
        void TextureRenderCore::renderGMWithAlphaMask(
            GmID gmID, int imageID, int xPos, int yPos, GmID maskGmID, int alphaImageID, int blendStrength)
        {
            int iVar1;
            void* pvVar2;
            RenderTargetInt _tempBufferChoiceValueUnk;
            pvVar2 = DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
            if (DAT_TextureRenderCoreObject::instance.isZoom2 != 0) {
                iVar1 = GMTotalPicturesProcessed::instance[gmID];
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(xPos,
                    yPos, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                    (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                    (ushort*)((int)(

                        (DAT_GMImageOffsets::instance[iVar1 + -1 + imageID]
                            + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                    blendStrength);
            }
            AlphaAndButtonSurfaceObj::instance.currentImageWidth
                = (int)DAT_GMImageHeaders::instance
                      .imh[alphaImageID + GMTotalPicturesProcessed::instance[maskGmID] + -1]
                      .width;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                DAT_GMImageHeaders::instance.imh[alphaImageID + GMTotalPicturesProcessed::instance[maskGmID] + -1]
                        .height
                    * AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2,
                (ushort)((int)(COL_MAGENTA::instance.shortValue)),
                (void*)((int)(AlphaAndButtonSurfaceObj::instance.surfacePtr)));
            _tempBufferChoiceValueUnk = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, this)(
                (OpenSHC::DE::SHCDE::eGM)maskGmID, alphaImageID, 0, 0);
            iVar1 = GMTotalPicturesProcessed::instance[gmID];
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _tempBufferChoiceValueUnk;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGmWithPreparedAlphaMask, this)(xPos,
                yPos, (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].width)),
                (int)((int)(DAT_GMImageHeaders::instance.imh[imageID + iVar1 + -1].height)),
                (ushort*)((int)((DAT_GMImageOffsets::instance[iVar1 + -1 + imageID] + (int)pvVar2))), blendStrength);
        }

    }
}
}
