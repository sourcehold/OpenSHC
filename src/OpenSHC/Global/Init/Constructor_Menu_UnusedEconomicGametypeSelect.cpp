#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_UnusedEconomicGametypeSelect.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AAC0
    void Init::Constructor_Menu_UnusedEconomicGametypeSelect()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_UnusedEconomicGametypeSelect::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_UnusedEconomicGametypeSelect);
    }

}
}
