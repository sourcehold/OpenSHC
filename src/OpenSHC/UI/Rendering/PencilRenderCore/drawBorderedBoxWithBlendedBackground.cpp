#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00471340
        void PencilRenderCore::drawBorderedBoxWithBlendedBackground(int xPos, int yPos, int width, int height)
        {
            int iVar4;
            int iVar1 = ((height - 1) / 24 + 1) * 24;
            int iVar2 = ((width - 1) / 24 + 1) * 24;
            int iVar3 = 0;
            if (0 < iVar1) {
                do {
                    if (iVar3 == 0) {
                        iVar4 = 1;
                    } else {
                        iVar4 = (-(uint)(iVar3 != iVar1 - 24) & 0xfffffffa) + 13;
                    }
                    int iVar5 = 0;
                    if (0 < iVar2) {
                        do {
                            int imageID = iVar4;
                            if (iVar5 == 0) {
                            LAB_004713ce:
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID, iVar5 + xPos, iVar3 + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID + 3, 0);
                            } else {
                                if (iVar5 == iVar2 - 24) {
                                    imageID = iVar4 + 2;
                                    goto LAB_004713ce;
                                }
                                if (iVar4 != 7) {
                                    imageID = iVar4 + 1;
                                    goto LAB_004713ce;
                                }
                            }
                            iVar5 += 24;
                        } while (iVar5 < iVar2);
                    }
                    iVar3 += 24;
                } while (iVar3 < iVar1);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, this)(
                xPos + 24, yPos + 24, xPos - 25 + iVar2, yPos - 25 + iVar1, 16);
        }

    }
}
}
