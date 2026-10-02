#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmID;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00468FE0
        void PencilRenderCore::drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk)
        {
            int _imageID;
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int _x;
            _x = xPos;
            iVar1 = xPos + 8;
            iVar2 = width + -0x10;
            xPos = 0;
            do {
                if (xPos == 0) {
                    iVar4 = 0x30;
                } else {
                    iVar4 = (-(uint)(xPos != 0x38) & 0xfffffffa) + 0x3c;
                }
                iVar3 = 0;
                if (0 < iVar2) {
                    do {
                        _imageID = iVar4;
                        if ((iVar3 != 0) && (_imageID = iVar4 + 2, iVar3 != width + -0x18)) {
                            _imageID = iVar4 + 1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID,
                            iVar3 + iVar1, xPos + yPos + 8, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID + 3,
                            0);
                        iVar3 = iVar3 + 8;
                    } while (iVar3 < iVar2);
                }
                xPos = xPos + 8;
            } while (xPos < 0x40);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b, _x + 0xb,
                yPos + 0x11, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x5b,
                (iVar1 - DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x9c] + 0x5a].width) + -3
                    + iVar2,
                yPos + 0x11, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x5c, 0);
        }

    }
}
}
