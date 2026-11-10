#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_SingleplayerMapChoice.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC00
    void Init::Constructor_Menu_SingleplayerMapChoice()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_SingleplayerMapChoice::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_SingleplayerMapChoice);
    }

}
}
