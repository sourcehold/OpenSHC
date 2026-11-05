#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_RankingGames.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ACF0
    void Init::Constructor_Menu_RankingGames()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_RankingGames::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_RankingGames);
    }

}
}
