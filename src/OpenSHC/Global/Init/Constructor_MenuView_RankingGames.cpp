#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/RankingGames.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_RankingGames.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA00
    void Init::Constructor_MenuView_RankingGames()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_RankingGames::ptr)(
            UI::Enums::MVT_RANKING_GAMES, UI::MenuViews::RankingGames_Func::MenuView_RankingGames_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_CrusadeAndRankMenu::get(),
            UI::MenuViews::RankingGames_Func::MenuView_RankingGames_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_RankingGames::get());
    }

}
}
