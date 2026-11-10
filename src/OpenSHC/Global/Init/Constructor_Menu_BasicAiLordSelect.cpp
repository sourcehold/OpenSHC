#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_BasicAiLordSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ABB0
    void Init::Constructor_Menu_BasicAiLordSelect()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_BasicAiLordSelect::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_BasicAiLordSelect);
    }

}
}
