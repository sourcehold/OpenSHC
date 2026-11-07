#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {

namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00491730
    void MenuTextInputState::clearModalDialog2to6()
    {
        for (int i = 0; i < countof(this->previousModalDialogs); ++i) {
            this->previousModalDialogs[i] = OpenSHC::UI::Enums::MMT_NO_MENU;
        }
    }
}

}
