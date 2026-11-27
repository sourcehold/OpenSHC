#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D500
    void GameSynchronyState::setMenuTypeBasedOnDirectPlayGUID()
    {
        GUID provider;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGUIDForSelectedProvider, this)(&provider);
        if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_MODEM::ptr)) {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
        } else if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_TCPIP::ptr)) {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP;
        } else if (MACRO_CALL(OS_Func::isEqualGUID)(&provider, GUID_DPSPGUID_IPX::ptr)) {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_INN_OR_MPMMENU_UNK;
        } else {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
        }
    }

}
}
