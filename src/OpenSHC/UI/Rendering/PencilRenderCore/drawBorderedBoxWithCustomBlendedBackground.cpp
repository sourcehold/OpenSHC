#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmID;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00471440
        void PencilRenderCore::drawBorderedBoxWithCustomBlendedBackground(
            int xPos, int yPos, int width, int height, int blendStrength)
        {
            int iVar1;
            int iVar2;
            int imageID;
            int iVar3;
            int iVar4;
            int iVar5;
            iVar1 = ((width + -1) / 0x18 + 1) * 0x18;
            iVar2 = ((height + -1) / 0x18 + 1) * 0x18;
            iVar3 = 0;
            if (0 < iVar2) {
                do {
                    if (iVar3 == 0) {
                        iVar4 = 1;
                    } else {
                        iVar4 = (-(uint)(iVar3 != iVar2 + -0x18) & 0xfffffffa) + 0xd;
                    }
                    iVar5 = 0;
                    if (0 < iVar1) {
                        do {
                            imageID = iVar4;
                            if (iVar5 == 0) {
                            LAB_004714da:
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID, iVar5 + xPos, iVar3 + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID + 3, blendStrength);
                            } else {
                                if (iVar5 == iVar1 + -0x18) {
                                    imageID = iVar4 + 2;
                                    goto LAB_004714da;
                                }
                                if (iVar4 != 7) {
                                    imageID = iVar4 + 1;
                                    goto LAB_004714da;
                                }
                            }
                            iVar5 = iVar5 + 0x18;
                        } while (iVar5 < iVar1);
                    }
                    iVar3 = iVar3 + 0x18;
                } while (iVar3 < iVar2);
            }
            iVar3 = (blendStrength + -0x20) * 0x10;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, this)(xPos + 0x18,
                yPos + 0x18, xPos + -0x19 + iVar1, yPos + -0x19 + iVar2,
                ((int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5) + 0x20);
        }

    }
}
}
