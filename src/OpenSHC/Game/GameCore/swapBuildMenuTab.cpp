#include "../GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B320
    void GameCore::swapBuildMenuTab()
    {
        if (this->buildmenuMenuTabToSwitchTo.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
            this->buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
            return;
        }
        this->buildmenuMenuTabToSwitchTo = this->secondaryActiveMenuTabToSwitchTo;
    }

}
}
