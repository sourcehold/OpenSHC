#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B300
    void GameCore::setTabToSwitchTo()
    {
        if (this->currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU) {
            this->secondaryActiveMenuTabToSwitchTo = this->buildmenuMenuTabToSwitchTo;
        }
        if (this->currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
            this->secondaryActiveMenuTabToSwitchTo.tabType = this->landscapingmenuMenuTabToSwitchTo;
        }
    }

}
}
