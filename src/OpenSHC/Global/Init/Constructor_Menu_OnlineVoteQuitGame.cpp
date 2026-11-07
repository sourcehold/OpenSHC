#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_OnlineVoteQuitGame.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AEF0
    void Init::Constructor_Menu_OnlineVoteQuitGame()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_OnlineVoteQuitGame::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_OnlineVoteQuitGame);
    }

}
}
