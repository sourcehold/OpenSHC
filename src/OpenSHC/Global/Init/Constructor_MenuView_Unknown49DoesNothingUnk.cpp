#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown49DoesNothingUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A3A0
    void Init::Constructor_MenuView_Unknown49DoesNothingUnk()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown49DoesNothingUnk::ptr)(
            UI::Enums::MVT_UNKNOWN_49_DOES_NOTHINGUnk, Global_Func::DoNothing::get(), Global_Func::DoNothing::get(),
            Global_Func::DoNothing::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_Unknown49DoesNothingUnk::get());
    }

}
}
