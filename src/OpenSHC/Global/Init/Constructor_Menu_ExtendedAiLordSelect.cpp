#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_ExtendedAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ABC0
    void Init::Constructor_Menu_ExtendedAiLordSelect()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_ExtendedAiLordSelect::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_ExtendedAiLordSelect);
    }

}
}
