#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DA20
    int TextEditorState::getNextHelpColorEntryIndex(int param_1)
    {
        int newIndex = param_1 + 1;
        if (DAT_UserHelpDefinedData::instance.field6_0x7a16c[newIndex].name_0x0 == NULL) {
            newIndex = 0;
        }
        return newIndex;
    }

}
}
