#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BB20
    void GameCore::viewportAndScrollingRelated()
    {
        if (this->countdown > 0) {
            --this->countdown;
        }
        if (DAT_ViewportRenderState::instance.viewportState.field0_0x0 == 0
            && !DAT_ScrollingHandler::instance.isScrolling_0x0) {
            this->countdown = 1;
            this->forty = 0;
        }
    }

}
}
