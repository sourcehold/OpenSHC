#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedHelpTextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedHelpTextEditor.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A460
    void Init::Constructor_MenuView_UnusedHelpTextEditor()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedHelpTextEditor::ptr)(
            UI::Enums::MVT_UNUSED_HELP_TEXT_EDITOR,
            UI::MenuViews::UnusedHelpTextEditor_Func::MenuView_UnusedHelpTextEditor_Prepare::get(),
            UI::MenuViews::General_Func::MenuView_General_DoInitial_OnlySetMenuXY::get(),
            UI::MenuViews::UnusedHelpTextEditor_Func::MenuView_UnusedHelpTextEditor_DoEveryFrame::get());
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuView_UnusedHelpTextEditor::get());
    }

}
}
