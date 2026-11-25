#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedSelectRandomNumberOfEnemies.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedSelectRandomNumberOfEnemies.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A940
    void Init::Constructor_MenuView_UnusedSelectRandomNumberOfEnemies()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedSelectRandomNumberOfEnemies::ptr)(
            UI::Enums::MVT_UNUSED_SELECT_RANDOM_NUMBER_OF_ENEMIES,
            UI::MenuViews::General_Func::MenuView_General_Prepare_SwordShieldAndBorder::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::UnusedSelectRandomNumberOfEnemies_Func::
                MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedSelectRandomNumberOfEnemies::get());
    }

}
}
