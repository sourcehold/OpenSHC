#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00491680
    MenuTextInputState* MenuTextInputState::Constructor_MenuTextInputState()
    {
        this->currentModalDialog = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_2 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_3 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_4 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_5 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->modalDialog_6 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->field0_0x0 = 3;
        this->field1_0x4 = 0;
        this->field2_0x8 = 0;
        this->field3_0xc = 2;
        this->field4_0x10 = 0;
        this->field5_0x14 = 0;
        this->field6_0x18 = 2;
        this->field7_0x1c = 0;
        this->field8_0x20 = 0;
        this->field9_0x24 = 2;
        return this;
    }

}
}
