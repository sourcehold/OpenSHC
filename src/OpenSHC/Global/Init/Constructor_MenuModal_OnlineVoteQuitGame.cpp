#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OnlineVoteQuitGame.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_OnlineVoteQuitGame.hpp"
#include "OpenSHC/Globals/Menu_OnlineVoteQuitGame.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BEE0
    void Init::Constructor_MenuModal_OnlineVoteQuitGame()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_OnlineVoteQuitGame::ptr)(
            UI::Enums::MMT_ONLINE_VOTE_QUIT_GAME, -1, 10, 400, 200, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::OnlineVoteQuitGame_Func::MenuModalRenderFunction_OnlineVoteQuitGame::get(),
            Menu_OnlineVoteQuitGame::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_OnlineVoteQuitGame::get());
    }

}
}
