#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_FindingNetworkSessions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AD40
    void Init::Constructor_Menu_FindingNetworkSessions()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_FindingNetworkSessions::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_FindingNetworkSessions);
    }

}
}
