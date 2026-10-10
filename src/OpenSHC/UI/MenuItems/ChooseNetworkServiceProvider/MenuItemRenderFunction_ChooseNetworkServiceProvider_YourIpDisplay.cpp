#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eTextSections;
        using Rendering::Colors::BGR24;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CF50
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay(
            int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            char local_68[100];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_68;
            if (DAT_GameSynchronyState::instance.displayYourIP) {
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x12;
                color = 0xccfaff;
                alignment = Text::TTA_LEFT;
                yParam = DAT_ButtonY::instance + 5;
                xParam = DAT_ButtonX::instance;
                /*
                  added by script: "Your IP:"
                 */
                textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x24);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                if (!DAT_GameSynchronyState::instance.lanOrWan) {
                    MACRO_CALL(OS_Func::_sprintf)(local_68, "   %d.%d.%d.%d",
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b4);
                } else {
                    MACRO_CALL(OS_Func::_sprintf)(local_68, "   %d.%d.%d.%d  /  %d.%d.%d.%d",
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b4,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b4);
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(local_68,
                    (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 5), Text::TTA_LEFT, 0xccfaff, 0x12,
                    TRUE, 0);
            };
        }

    }
}
}
