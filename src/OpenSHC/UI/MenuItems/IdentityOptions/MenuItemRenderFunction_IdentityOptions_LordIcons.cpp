#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eGM;
        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00491D70
        void IdentityOptions::MenuItemRenderFunction_IdentityOptions_LordIcons(int param_1, ...)
        {
            if (0x27 < param_1) {
                BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                if (!BVar1) {
                    MACRO_CALL(UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                MACRO_CALL(UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, 0x22b, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
            if (param_1 == 0x17) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                    DAT_TextureRenderCoreObject::ptr)(DAT_GameCore::instance.lordIconUnk + -2,
                    (int)(DAT_ButtonX::instance + 4), (int)(DAT_ButtonY::instance + 4));
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
            }
            int imageID = 0x21b;
            if (param_1 == 0x16) {
                imageID = 0x21c;
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, imageID, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
            if (param_1 == 0x15) {
                if (DAT_GameCore::instance.selectedLordTypeUnk) {}
            } else {
                if (param_1 != 0x16) {}
                if (DAT_GameCore::instance.selectedLordTypeUnk != 1) {}
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                (int)(DAT_ButtonX::instance + -6), (int)(DAT_ButtonY::instance + -6),
                IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
        }

    }
}
}
