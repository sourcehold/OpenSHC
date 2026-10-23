#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F580
    BOOLEnum TextEditorState::loadAndParseHelpFile(char const* searchedPart)
    {
        FILE* _File = MACRO_CALL_MEMBER(TextEditorState_Func::readCrusaderHelpHlp, this)(searchedPart);
        if (_File) {
            MACRO_CALL(OS_Func::_fclose)(_File);
            if (this->helpSectionParseSucceeded) {
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
