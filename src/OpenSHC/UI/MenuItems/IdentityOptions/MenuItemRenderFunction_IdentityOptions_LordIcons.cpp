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

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491D70
        void IdentityOptions::MenuItemRenderFunction_IdentityOptions_LordIcons(int param_1, ...)
        {
            BOOLEnum BVar1;
            int imageID;
            if (0x27 < param_1) {
                BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                if (BVar1 == FALSE) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x22b,
                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            if (param_1 == 0x17) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                    DAT_TextureRenderCoreObject::ptr)(DAT_GameCore::instance.lordIconUnk + -2,
                    (int)((int)(DAT_ButtonX::instance + 4)), (int)((int)(DAT_ButtonY::instance + 4)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            }
            imageID = 0x21b;
            if (param_1 == 0x16) {
                imageID = 0x21c;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID,
                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            if (param_1 == 0x15) {
                if (DAT_GameCore::instance.selectedLordTypeUnk != 0) {}
            } else {
                if (param_1 != 0x16) {}
                if (DAT_GameCore::instance.selectedLordTypeUnk != 1) {}
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                (int)((int)(DAT_ButtonX::instance + -6)), (int)((int)(DAT_ButtonY::instance + -6)),
                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
        }

    }
}
}
