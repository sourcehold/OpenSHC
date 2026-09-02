#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D9E0
    char* TextEditorState::getHelpSectionText(int param_1)
    {
        int _entry = 0;
        while (DAT_UserHelpDefinedData::instance.field5_0x7a124[_entry].unknown_0x4 != -1) {
            if (DAT_UserHelpDefinedData::instance.field5_0x7a124[_entry].unknown_0x4 == param_1) {
                return DAT_UserHelpDefinedData::instance.field5_0x7a124[_entry].text_0x0;
            }
            _entry++;
        }
        return NULL;
    }

}
}
