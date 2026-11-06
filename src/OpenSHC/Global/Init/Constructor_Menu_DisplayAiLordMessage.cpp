#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_DisplayAiLordMessage.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AF10
    void Init::Constructor_Menu_DisplayAiLordMessage()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_DisplayAiLordMessage::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_DisplayAiLordMessage);
    }

}
}
