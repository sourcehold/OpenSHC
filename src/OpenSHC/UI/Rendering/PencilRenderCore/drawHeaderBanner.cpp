#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00468FE0
        void PencilRenderCore::drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk)
        {
            int iVar4;
            yPos += 8;
            int iVar1 = xPos + 8;
            int iVar2 = width - 16;
            xPos = 0;
            do {
                if (xPos == 0) {
                    iVar4 = 48;
                } else {
                    iVar4 = (-(uint)(xPos != 56) & 0xfffffffa) + 60;
                }
                int iVar3 = 0;
                if (0 < iVar2) {
                    do {
                        int _imageID = iVar4;
                        if ((iVar3 != 0) && (_imageID = iVar4 + 2, iVar3 != iVar2 - 8)) {
                            _imageID = iVar4 + 1;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID,
                            iVar3 + iVar1, xPos + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID + 3, 0);
                        iVar3 += 8;
                    } while (iVar3 < iVar2);
                }
                xPos += 8;
            } while (xPos < 64);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 91, iVar1 + 3, yPos + 9,
                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 92, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 91,
                (iVar1 - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[156] + 90].width) - 3 + iVar2,
                yPos + 9, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 92, 0);
        }

    }
}
}
