// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../TextEditorState.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DAE0
    int TextEditorState::findOrAddSoundName(char* param_1)
    {
        int index = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findSoundIndexByName, this)(param_1);
        if (index != -1) {
            return index;
        }

        index = this->soundFileCount;
        strcpy(this->soundFileNames[index], param_1);
        this->soundFilePlayedFlags[index] = 0;
        if (this->soundFileCount < 5) {
            ++this->soundFileCount;
        }
        return index;
    }

}
}
