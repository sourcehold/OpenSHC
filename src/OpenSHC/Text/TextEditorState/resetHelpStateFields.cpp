#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D0C0
    void TextEditorState::resetHelpStateFields()
    {
        for (int i = 0; i < 30; ++i) {
            this->helpSectionHistoryStack[i] = -1;
        }
        this->currentHelpSectionID = -1;
    }

}
}
