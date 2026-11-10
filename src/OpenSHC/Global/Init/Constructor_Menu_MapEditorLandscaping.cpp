#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_MapEditorLandscaping.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AFE0
    void Init::Constructor_Menu_MapEditorLandscaping()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_MapEditorLandscaping::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Menu_MapEditorLandscaping);
    }

}
}
