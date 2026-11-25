#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_DisplayScenarioHelpText.hpp"
#include "OpenSHC/Globals/Menu_DisplayScenarioHelpText.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BD20
    void Init::Constructor_MenuModal_DisplayScenarioHelpText()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisplayScenarioHelpText::ptr)(
            UI::Enums::MMT_DISPLAY_SCENARIO_HELP_TEXT, -1, 30, 696, 408, 4608, COL_BLACK::instance.shortValue,
            UI::MenuModals::TextEditor_Func::MenuModalRenderFunction_TextEditor::get(),
            Menu_DisplayScenarioHelpText::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DisplayScenarioHelpText::get());
    }

}
}
