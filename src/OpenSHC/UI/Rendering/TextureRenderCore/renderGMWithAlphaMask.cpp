#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004557B0
        void TextureRenderCore::renderGMWithAlphaMask(
            GmID gmID, int imageID, int xPos, int yPos, GmID maskGmID, int alphaImageID, int blendStrength)
        {
            byte* const imageData = this->gmProcessedImageData;
            // Read before the zoom test (read at its use: quick_diff 1.0000 -> 0.9091)
            ushort* const alphaSurface = AlphaAndButtonSurfaceObj::instance.surfacePtr;
            // With isZoom2 set the image is drawn blended, without the mask
            if (DAT_TextureRenderCoreObject::instance.isZoom2) {
                int const picture = GMFirstPictureIndex::instance[gmID] + imageID - 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderInterfaceOrBuildingOccupationArea, this)(xPos,
                    yPos, DAT_GMImageHeaders::instance.imh[picture].width,
                    DAT_GMImageHeaders::instance.imh[picture].height,
                    (ushort*)(imageData + DAT_GMImageOffsets::instance[picture]), blendStrength);
                return;
            }
            // Clear the alpha surface to magenta, draw the mask into it, then draw the image through it
            int const maskPicture = GMFirstPictureIndex::instance[maskGmID] + alphaImageID - 1;
            AlphaAndButtonSurfaceObj::instance.currentImageWidth = DAT_GMImageHeaders::instance.imh[maskPicture].width;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                DAT_GMImageHeaders::instance.imh[maskPicture].height
                    * AlphaAndButtonSurfaceObj::instance.currentImageWidth * 2,
                COL_MAGENTA::instance.shortValue, alphaSurface);
            RenderTargetInt const savedTarget = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
            // The original draws the mask through the global instance (with this: quick_diff 1.0000 -> 0.7841)
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((eGM)maskGmID, alphaImageID, 0, 0);
            int const picture = GMFirstPictureIndex::instance[gmID] + imageID - 1;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = savedTarget;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGmWithPreparedAlphaMask, this)(xPos,
                yPos, DAT_GMImageHeaders::instance.imh[picture].width, DAT_GMImageHeaders::instance.imh[picture].height,
                (ushort*)(imageData + DAT_GMImageOffsets::instance[picture]), blendStrength);
        }

    }
}
}
