#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00487200
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows(
            int param_1, ...)
        {
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1
                < DAT_GameSynchronyState::instance.scrollBarItemCount) {
                DAT_GameSynchronyState::instance.selectedProviderIndex = param_1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::setMenuTypeBasedOnDirectPlayGUID,
                    DAT_GameSynchronyState::ptr)();
                if (DAT_GameCore::instance.activeMenuTab.tabType
                    == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(7);
                } else if (DAT_GameCore::instance.activeMenuTab.tabType
                    == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                }
            }
        }

    }
}
}
