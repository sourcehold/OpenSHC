#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DA80
    int TextEditorState::findSoundIndexByName(char* param_1)
    {
        for (int i = 0; i < this->soundFileCount; i = i + 1) {
            if (!MACRO_CALL(OpenSHC::OS_Func::__stricmp)(this->soundFileNames[i], param_1)) {
                return i;
            }
        }
        return -1;
    }

}
}
