#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Synchrony {

    using UI::Enums::BuildingsAndStatusMenuTabType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D500
    void GameSynchronyState::setMenuTypeBasedOnDirectPlayGUID()
    {
        GUID _guid;
        uint local_4 = MSVC_SecurityCookie::instance ^ (uint)&_guid;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGUIDForSelectedProvider, this)((GUID*)&_guid);
        BOOLEnum BVar1 = MACRO_CALL(OS_Func::isEqualGUID)(&_guid, (GUID*)GUID_DPSPGUID_MODEM::ptr);
        if (BVar1) {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
            return;
        }
        BVar1 = MACRO_CALL(OS_Func::isEqualGUID)(&_guid, (GUID*)GUID_DPSPGUID_TCPIP::ptr);
        if (BVar1) {
            DAT_GameCore::instance.activeMenuTab.tabType = UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP;
            return;
        }
        BVar1 = MACRO_CALL(OS_Func::isEqualGUID)(&_guid, (GUID*)GUID_DPSPGUID_IPX::ptr);
        DAT_GameCore::instance.activeMenuTab.tabType
            = (BuildingsAndStatusMenuTabType)((BVar1 != FALSE) + UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX);
    }

}
}
