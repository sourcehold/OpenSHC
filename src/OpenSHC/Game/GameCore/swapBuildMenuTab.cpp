#include "../GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B320
    void GameCore::swapBuildMenuTab()
    {
        if (this->buildmenuMenuTabToSwitchTo.buildMenuTab == 62) {
            this->buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_SOLDIERS;
            return;
        }
        this->buildmenuMenuTabToSwitchTo = this->secondaryActiveMenuTabToSwitchTo;
    }

}
}
