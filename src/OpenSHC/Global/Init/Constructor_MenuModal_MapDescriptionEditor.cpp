#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_MapDescriptionEditor.hpp"
#include "OpenSHC/Globals/Menu_MapDescriptionEditor.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B7A0
    void Init::Constructor_MenuModal_MapDescriptionEditor()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_MapDescriptionEditor::ptr)(
            UI::Enums::MMT_MAP_DESCRIPTION_EDITOR, -1, -1, 400, 230, 32, COL_BLACK::instance.shortValue,
            UI::MenuModals::TextEditor_Func::MenuModalRenderFunction_TextEditor::get(), Menu_MapDescriptionEditor::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_MapDescriptionEditor::get());
    }

}
}
