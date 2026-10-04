#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Text/FontRenderType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;
        using Text::FontRenderType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00455540
        void TextureRenderCore::renderTextChar(int xPos, int yPos, int imageId, FontRenderType renderType,
            int lineHeight, ushort fillColor, int blendStrength)
        {
            short sVar1;
            short sVar2;
            ushort* _imageSource;
            int iVar3;
            int _imageId;
            int _yPosUnk;
            _imageId = imageId;
            /*
              That makes it a bit harder: The given variables are assigned to locals and   then redefined...
              --TheRedDaemon
             */
            _yPosUnk = yPos;
            _imageSource = (ushort*)(DAT_GMImageOffsets::instance[imageId]
                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData);
            DAT_TextureRenderCoreObject::instance.mbr_0x6c = 0;
            if ((DAT_TextManagerObject::instance.field9_0x24 == 0)
                && (DAT_TextManagerObject::instance.field10_0x28 == 0))
                goto LAB_0045566a;
            yPos = 0;
            if (DAT_TextManagerObject::instance.field11_0x2c != 0) {
                yPos = 2;
            }
            if (lineHeight == 0x1b) {
                imageId = 0x13;
                iVar3 = 3;
            LAB_004555b4:
                sVar1 = *(short*)(PTR_ARRAY_Unknown_UnitGMHeights::instance
                    + (GMTotalPicturesProcessed::instance[0x9c] + imageId) * 4 + 0x1c);
                sVar2 = DAT_GMImageHeaders::instance.imh[_imageId].width;
                if ((DAT_TextManagerObject::instance.field9_0x24 != 0) && (blendStrength != 0x20)) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, this)(
                        IO::Graphics::GID_INTERFACE_ICONS_3, imageId, xPos, (iVar3 - lineHeight) + _yPosUnk,
                        blendStrength);
                }
                DAT_TextureRenderCoreObject::instance.mbr_0x6c
                    = ((int)sVar1 - (int)DAT_GMImageHeaders::instance.imh[_imageId].width) + 3;
                xPos = xPos + ((int)sVar1 - (int)sVar2) / 2 + yPos;
            } else if (lineHeight == 0x14) {
                imageId = lineHeight;
                iVar3 = 2;
                goto LAB_004555b4;
            }
            if (DAT_TextManagerObject::instance.field9_0x24 != 0) {
                DAT_TextManagerObject::instance.field9_0x24 = 0;
            }
            if (DAT_TextManagerObject::instance.field10_0x28 != 0) {
                DAT_TextManagerObject::instance.field10_0x28 = 0;
            }
        LAB_0045566a:
            if (blendStrength != 0x20) {
                if (DAT_TextManagerObject::instance.field5_0x14 == 0) {
                    iVar3 = _yPosUnk - DAT_GMImageHeaders::instance.imh[_imageId].tileOffset;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                        xPos + -1, iVar3 + -2, DAT_GMImageHeaders::instance.imh[_imageId].width + 1 + xPos,
                        iVar3 + 2 + lineHeight, (ushort)((int)(COL_WHITE::instance.shortValue)));
                }
                if (DAT_TextManagerObject::instance.field6_0x18 != 0) {
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(xPos,
                        _yPosUnk + 2, DAT_GMImageHeaders::instance.imh[_imageId].width + xPos, _yPosUnk + 2, fillColor);
                }
                if (renderType == Text::FRT_COLOR) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTgxWithColorUnk, this)(xPos,
                        _yPosUnk - DAT_GMImageHeaders::instance.imh[_imageId].tileOffset,
                        DAT_GMImageHeaders::instance.imh[_imageId].width,
                        DAT_GMImageHeaders::instance.imh[_imageId].height, _imageSource, fillColor);
                    return;
                }
                if (renderType == Text::FRT_BLENDED_COLOR) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderTgxWithColorAndBlendingUnk, this)(
                        xPos, _yPosUnk - DAT_GMImageHeaders::instance.imh[_imageId].tileOffset,
                        DAT_GMImageHeaders::instance.imh[_imageId].width,
                        DAT_GMImageHeaders::instance.imh[_imageId].height, _imageSource, fillColor, blendStrength);
                    return;
                }
                if (renderType == Text::FRT_RAW) {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects, this)(xPos,
                        _yPosUnk - DAT_GMImageHeaders::instance.imh[_imageId].tileOffset,
                        DAT_GMImageHeaders::instance.imh[_imageId].width,
                        DAT_GMImageHeaders::instance.imh[_imageId].height, _imageSource);
                }
            }
        }

    }
}
}
