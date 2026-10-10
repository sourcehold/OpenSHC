#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004692E0
        void PencilRenderCore::drawTableCellBackground(BOOLEnum isSelected, int indexToGetStripes, int blendStrength)
        {
            int iVar1;
            uint imageID;
            iVar1 = DAT_ButtonX::instance;
            imageID = ((int)(char)indexToGetStripes & 1U) * 2 | 0x45;
            if (!isSelected) {
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    if (DAT_ButtonW::instance + DAT_ButtonX::instance <= DAT_ButtonX::instance) {}
                    iVar1 = DAT_ButtonX::instance;
                    do {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, (int)(imageID),
                            iVar1, (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3,
                            (int)(imageID + 1), blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < DAT_ButtonW::instance + DAT_ButtonX::instance);
                }
                if (DAT_ButtonW::instance < 0x15) {
                    DAT_ButtonW::instance = DAT_ButtonW::instance + 1;
                } else {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x49,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3,
                        0x4c, blendStrength);
                    iVar1 = iVar1 + 0x14;
                }
                if (iVar1 < DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance) {
                    do {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x4a, iVar1,
                            (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d, blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance);
                }
            } else {
                if (DAT_ButtonW::instance < 0x15) {
                    DAT_ButtonW::instance = DAT_ButtonW::instance + 1;
                } else {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x49,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3,
                        0x4c, blendStrength);
                    iVar1 = iVar1 + 0x14;
                }
                if (iVar1 < DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance) {
                    do {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x4a, iVar1,
                            (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d, blendStrength);
                        iVar1 = iVar1 + 0x14;
                    } while (iVar1 < DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance);
                }
            }
            if (DAT_ButtonW::instance < 0x16) {}
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x4b, iVar1,
                (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3, 0x4d, blendStrength);
        }

    }
}
}
