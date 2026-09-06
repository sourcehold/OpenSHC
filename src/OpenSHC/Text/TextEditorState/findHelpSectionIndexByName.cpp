#include "../TextEditorState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D140
    int TextEditorState::findHelpSectionIndexByName(char* param_1)
    {
        for (int counter = 0; counter < this->counter; ++counter) {
            if (!MACRO_CALL(OS_Func::__stricmp)(DAT_UserHelpDefinedData::instance.HelpSections[counter], param_1)) {
                return counter;
            }
        }
        return -1;
    }

}
}
