#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_EditorMapTypeQuickChange.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AFB0
    void Init::Constructor_Menu_EditorMapTypeQuickChange()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_EditorMapTypeQuickChange::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_EditorMapTypeQuickChange);
    }

}
}
