#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuModals/TextEditor.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {
        namespace TextEditor {

            // FUNCTION: STRONGHOLDCRUSADER 0x004AAB40
            void MenuModalRenderFunction_TextEditor(int x, int y, int width, int height)
            {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
            }

        }
    }
}
}
