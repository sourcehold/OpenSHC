#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_YesNoDialog.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AE30
    void Init::Constructor_Menu_YesNoDialog()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_YesNoDialog::ptr)(
            DAT_RenderingDefinedData::instance.MenuItem_YesNoDialog);
    }

}
}
