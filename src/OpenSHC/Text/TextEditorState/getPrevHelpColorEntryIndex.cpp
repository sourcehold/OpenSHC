#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DA40
    int TextEditorState::getPrevHelpColorEntryIndex(int param_1)
    {
        --param_1;
        if (param_1 < 0) {
            param_1 = 0;
            while (DAT_UserHelpDefinedData::instance.field6_0x7a16c[param_1].name_0x0 != NULL) {
                ++param_1;
            }
            --param_1;
        }
        return param_1;
    }

}
}
