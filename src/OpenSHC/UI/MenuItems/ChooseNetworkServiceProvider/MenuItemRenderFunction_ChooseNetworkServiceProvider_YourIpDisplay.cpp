#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CF50
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay(
            int unused, ...)
        {
            if (!DAT_GameSynchronyState::instance.hasHostAddress[0]) {
                return;
            }
            char ipText[100];
            // the first call takes y from a local and the second computes it again, as in the original
            int const textY = DAT_ButtonY::instance + 5;
            // "Your IP:"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 36),
                DAT_ButtonX::instance, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                FALSE, 0);
            if (DAT_GameSynchronyState::instance.hasHostAddress[1]) {
                // "   %d.%d.%d.%d  /  %d.%d.%d.%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(ipText, s__d_d_d_d____d_d_d_d_005a6f10,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b1,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b2,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b3,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b4,
                    DAT_GameSynchronyState::instance.hostAddress[1].S_un.S_un_b.s_b1,
                    DAT_GameSynchronyState::instance.hostAddress[1].S_un.S_un_b.s_b2,
                    DAT_GameSynchronyState::instance.hostAddress[1].S_un.S_un_b.s_b3,
                    DAT_GameSynchronyState::instance.hostAddress[1].S_un.S_un_b.s_b4);
            } else {
                // "   %d.%d.%d.%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(ipText, s__d_d_d_d_005a6f00,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b1,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b2,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b3,
                    DAT_GameSynchronyState::instance.hostAddress[0].S_un.S_un_b.s_b4);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(ipText,
                DAT_ButtonX::instance, DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE, 0);
        }

    }
}
}
