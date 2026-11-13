#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/HistoricMissionPicture.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_HistoricMissionPicture.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A880
    void Init::Constructor_MenuView_HistoricMissionPicture()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_HistoricMissionPicture::ptr)(
            UI::Enums::MVT_HISTORIC_MISSION_PICTURE,
            UI::MenuViews::HistoricMissionPicture_Func::MenuView_HistoricMissionPicture_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_BlackBorderAndGfx::get(),
            UI::MenuViews::HistoricMissionPicture_Func::MenuView_HistoricMissionPicture_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_HistoricMissionPicture::get());
    }

}
}
