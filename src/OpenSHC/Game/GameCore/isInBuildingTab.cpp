#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BB80
    BOOLEnum GameCore::isInBuildingTab()
    {
        if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            return FALSE;
        }
        if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_CATAPULT
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_FIREBALLISTA
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_TREBUCHET
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD) {
            return TRUE;
        }
        return DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
    }

}
}
