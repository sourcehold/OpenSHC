#include "OpenSHC/UI/MinimapViewState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B5300
    void MinimapViewState::triggerMinimapRedraw()
    {
        if (this->field14_0x38 == 0) {
            this->field13_0x34 = 0;
            this->field14_0x38 = 2;
            return;
        }
        this->field14_0x38 = 1;
    }

}
}
