#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_InGameHelpText.hpp"
#include "OpenSHC/Globals/Menu_InGameHelpText.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B760
    void Init::Constructor_MenuModal_InGameHelpText()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_InGameHelpText::ptr)(
            UI::Enums::MMT_IN_GAME_HELP_TEXT, -1, -1, 768, 432, 32, COL_BLACK::instance.shortValue,
            UI::MenuModals::TextEditor_Func::MenuModalRenderFunction_TextEditor::get(), Menu_InGameHelpText::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_InGameHelpText::get());
    }

}
}
