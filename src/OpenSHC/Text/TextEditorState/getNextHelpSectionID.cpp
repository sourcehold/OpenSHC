#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D950
    int TextEditorState::getNextHelpSectionID(int param_1)
    {
        for (int index = 0; DAT_UserHelpDefinedData::instance.field5_0x7a124[index].unknown_0x4 != -1; ++index) {
            if (DAT_UserHelpDefinedData::instance.field5_0x7a124[index].unknown_0x4 != param_1) {
                continue;
            }

            ++index;
            if (DAT_UserHelpDefinedData::instance.field5_0x7a124[index].unknown_0x4 == -1) {
                index = 0;
            }
            return DAT_UserHelpDefinedData::instance.field5_0x7a124[index].unknown_0x4;
        }
        return -1;
    }

}
}
