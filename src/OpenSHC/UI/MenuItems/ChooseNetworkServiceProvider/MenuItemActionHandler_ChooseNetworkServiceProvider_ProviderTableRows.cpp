#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00487200
        void ChooseNetworkServiceProvider::MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows(
            int row, ...)
        {
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + row
                >= DAT_GameSynchronyState::instance.scrollBarItemCount) {
                return;
            }
            DAT_GameSynchronyState::instance.selectedProviderIndex = row;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::setMenuTypeBasedOnDirectPlayGUID,
                DAT_GameSynchronyState::ptr)();
            // a sparse switch; the TCPIP arm comes first in the original's layout
            switch (DAT_GameCore::instance.activeMenuTab.tabType) {
            case OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP:
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT);
                break;
            case OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM:
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY);
                break;
            }
        }

    }
}
}
