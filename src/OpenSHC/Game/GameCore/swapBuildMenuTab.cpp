#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

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
