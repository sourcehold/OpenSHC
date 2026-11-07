#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00475CC0
        void PencilRenderCore::drawHeaderTextBanner(
            int textGroupIndex, int textNumInGroup, int xPos, int yPos, int width, int param_6)
        {
            int _textY;
            int _width;
            int iVar2;
            int iVar3;
            int iVar4;
            int _textX;
            int iVar1 = xPos;
            iVar2 = xPos + 8;
            _width = width - 16;
            for (int xPos = 0; xPos < 64; xPos = xPos + 8) {
                if (xPos == 0) {
                    iVar4 = 48;
                } else {
                    iVar4 = (-(uint)(xPos != 56) & 0xfffffffa) + 60;
                }
                iVar3 = 0;
                if (0 < _width) {
                    do {
                        int imageID = iVar4;
                        if ((iVar3 != 0) && (imageID = iVar4 + 2, iVar3 != width - 24)) {
                            imageID = iVar4 + 1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID,
                            iVar3 + iVar2, xPos + yPos + 8, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID + 3,
                            0);
                        iVar3 += 8;
                    } while (iVar3 < _width);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 91, iVar1 + 11,
                yPos + 17, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 92, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 91,
                (iVar2 - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[156] + 90].width) - 3 + _width,
                yPos + 17, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 92, 0);
            _textY = yPos + 22;
            _textX = _width / 2 + iVar2;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((OpenSHC::DE::SHCDE::eTextSections)textGroupIndex, textNumInGroup),
                _textX, _textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 15, FALSE, 0);
        }

    }
}
}
