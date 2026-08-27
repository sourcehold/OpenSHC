#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F580
    undefined4 TextEditorState::loadAndParseHelpFile(char const* param_1)
    {
        FILE* _File = (FILE*)MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::readCrusaderHelpHlp, this)(param_1);
        if (_File != (FILE*)0x0) {
            MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
            // fixme: I thought I could return the comparison directly, but that produces different bytecode.
            if (this->helpSectionParseSucceeded != FALSE) {
                return 1;
            }
        }
        return 0;
    }

}
}
