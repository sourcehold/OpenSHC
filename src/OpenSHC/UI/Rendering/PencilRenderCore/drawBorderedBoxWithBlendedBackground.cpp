#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00471340
        void PencilRenderCore::drawBorderedBoxWithBlendedBackground(int xPos, int yPos, int width, int height)
        {
            int iVar4;
            int iVar1 = ((height + -1) / 0x18 + 1) * 0x18;
            int iVar2 = ((width + -1) / 0x18 + 1) * 0x18;
            int iVar3 = 0;
            if (0 < iVar1) {
                do {
                    if (!iVar3) {
                        iVar4 = 1;
                    } else {
                        iVar4 = (-(uint)(iVar3 != iVar1 + -0x18) & 0xfffffffa) + 0xd;
                    }
                    int iVar5 = 0;
                    if (0 < iVar2) {
                        do {
                            int imageID = iVar4;
                            if (!iVar5) {
                            LAB_004713ce:
                                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, imageID,
                                    iVar5 + xPos, iVar3 + yPos, IO::Graphics::GID_INTERFACE_ICONS_3, imageID + 3, 0);
                            } else {
                                if (iVar5 == iVar2 + -0x18) {
                                    imageID = iVar4 + 2;
                                    goto LAB_004713ce;
                                }
                                if (iVar4 != 7) {
                                    imageID = iVar4 + 1;
                                    goto LAB_004713ce;
                                }
                            }
                            iVar5 = iVar5 + 0x18;
                        } while (iVar5 < iVar2);
                    }
                    iVar3 = iVar3 + 0x18;
                } while (iVar3 < iVar1);
            }
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, this)(
                xPos + 0x18, yPos + 0x18, xPos + -0x19 + iVar2, yPos + -0x19 + iVar1, 0x10);
        }

    }
}
}
