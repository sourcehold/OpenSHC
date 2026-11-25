#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00491D70
        void IdentityOptions::MenuItemRenderFunction_IdentityOptions_LordIcons(int button, ...)
        {
            // 40 and 41 are the two image buttons beside the face; inside a game they are drawn inactive
            if (button >= 40) {
                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::
                            RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                    return;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 555, DAT_ButtonX::instance, DAT_ButtonY::instance);
            if (button == 23) {
                // the lord's own face in its frame
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace, DAT_TextureRenderCoreObject::ptr)(
                    DAT_GameCore::instance.lordIconUnk - 2, DAT_ButtonX::instance + 4, DAT_ButtonY::instance + 4);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 541, DAT_ButtonX::instance, DAT_ButtonY::instance);
                return;
            }
            int imageID = 539;
            if (button == 22) {
                imageID = 540;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, imageID, DAT_ButtonX::instance, DAT_ButtonY::instance);
            // buttons 21 and 22 are the two lord types: the selected one is framed
            if ((button == 21 && DAT_GameCore::instance.selectedLordTypeUnk == 0)
                || (button == 22 && DAT_GameCore::instance.selectedLordTypeUnk == 1)) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 514,
                    DAT_ButtonX::instance - 6, DAT_ButtonY::instance - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                    513, 0);
            }
        }

    }
}
}
