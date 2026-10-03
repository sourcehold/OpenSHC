#include "../ScrollingHandler.func.hpp"

#include "OpenSHC/UI/ScrollDirection.hpp"
#include "OpenSHC/UI/ScrollSpeed.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ScrollDirection;
    using OpenSHC::UI::ScrollSpeed;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00468A90
    ScrollingHandler* ScrollingHandler::Constructor_ScrollingHandler()
    {
        this->isScrolling_0x0 = FALSE;
        this->scrollRight = FALSE;
        this->rightKeyDown_0x18 = FALSE;
        this->scrollLeft = FALSE;
        this->leftKeyDown_0x1c = FALSE;
        this->scrollDown = FALSE;
        this->downKeyDown_0x20 = FALSE;
        this->scrollUp = FALSE;
        this->upKeyDown_0x24 = FALSE;
        this->scrollDirection_0x4 = OpenSHC::UI::SD_NONE;
        this->field12_0x30 = 0x14;
        this->field13_0x34 = 0x28;
        this->field11_0x2c = 1;
        this->scrollSpeedSetting_0x38 = OpenSHC::UI::SS_NORMAL;
        return this;
    }

}
}
