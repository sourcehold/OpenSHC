// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D8F0
    int TextEditorState::findOrAddHelpGraphicName(char* param_1)
    {
        int graphicIndex = MACRO_CALL_MEMBER(TextEditorState_Func::findHelpGraphicIndexByName, this)(param_1);
        if (graphicIndex != -1) {
            return graphicIndex;
        }
        graphicIndex = this->graphicFileCount;
        strcpy(this->graphicFileNames[graphicIndex], param_1);
        if (this->graphicFileCount < 20) {
            ++this->graphicFileCount;
        }
        return graphicIndex;
    }

}
}
