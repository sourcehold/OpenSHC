#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D890
    int TextEditorState::findHelpGraphicIndexByName(char* param_1)
    {
        for (int i = 0; i < this->graphicFileCount; ++i) {
            if (!MACRO_CALL(OS_Func::__stricmp)(this->graphicFileNames[i], param_1)) {
                return i;
            }
        }
        return -1;
    }

}
}
