#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/MpConnection.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MpConnection.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A280
    void Init::Constructor_MenuView_MpConnection()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MpConnection::ptr)(
            UI::Enums::MVT_MP_CONNECTION, UI::MenuViews::MpConnection_Func::MenuView_MpConnection_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure::get(),
            UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_MpConnection::get());
    }

}
}
