#include "../GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B300
    void GameCore::setTabToSwitchTo()
    {
        if (this->currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
            this->secondaryActiveMenuTabToSwitchTo = this->buildmenuMenuTabToSwitchTo;
        }
        if (this->currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
            this->secondaryActiveMenuTabToSwitchTo.tabType = this->landscapingmenuMenuTabToSwitchTo;
        }
    }

}
}
