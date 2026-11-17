#include "../MenuTextInputState.func.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00491680
    MenuTextInputState* MenuTextInputState::Constructor_MenuTextInputState()
    {
        this->currentModalDialog = OpenSHC::UI::Enums::MMT_NO_MENU;
        for (int i = 0; i < countof(this->previousModalDialogs); ++i) {
            this->previousModalDialogs[i] = OpenSHC::UI::Enums::MMT_NO_MENU;
        }
        this->fileListContext = 3;
        this->savedListOffset1 = 0;
        this->savedListSelection1 = 0;
        this->savedListSortOrder1 = 2;
        this->savedListOffset2 = 0;
        this->savedListSelection2 = 0;
        this->savedListSortOrder2 = 2;
        this->savedListOffset3 = 0;
        this->savedListSelection3 = 0;
        this->savedListSortOrder3 = 2;
        return this;
    }

}
}
