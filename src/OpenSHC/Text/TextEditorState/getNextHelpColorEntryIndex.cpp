#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DA20
    int TextEditorState::getNextHelpColorEntryIndex(int param_1)
    {
        int iVar1 = param_1 + 1;
        if (DAT_UserHelpDefinedData::instance.field6_0x7a16c[iVar1].name_0x0 == (char*)NULL) {
            iVar1 = 0;
        }
        return iVar1;
    }

}
}
