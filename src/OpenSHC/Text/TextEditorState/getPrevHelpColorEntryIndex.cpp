#include "../TextEditorState.func.hpp"

#include "OpenSHC/Text/HelpTextRelatedColorStruct.hpp"

#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::HelpTextRelatedColorStruct;

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DA40
    int TextEditorState::getPrevHelpColorEntryIndex(int param_1)
    {
        int iVar1 = param_1 + -1;
        if (iVar1 < 0) {
            iVar1 = 0;
            while (DAT_UserHelpDefinedData::instance.field6_0x7a16c[iVar1].name_0x0 != (char*)0x0) {
                iVar1++;
            }
            iVar1 = iVar1 + -1;
        }
        return iVar1;
    }

}
}
