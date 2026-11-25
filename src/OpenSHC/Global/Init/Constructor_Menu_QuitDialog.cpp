#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_QuitDialog.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AE40
    void Init::Constructor_Menu_QuitDialog()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_QuitDialog::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_QuitDialog);
    }

}
}
