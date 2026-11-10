#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_TutorialBox.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AF20
    void Init::Constructor_Menu_TutorialBox()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_TutorialBox::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_TutorialBox);
    }

}
}
