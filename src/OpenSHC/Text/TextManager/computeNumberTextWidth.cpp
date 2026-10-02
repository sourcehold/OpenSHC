#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      WARNING: Removing unreachable block (ram,0x004716e7)
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004716D0
    int TextManager::computeNumberTextWidth(int param_1, int param_2)
    {
        char* pcVar1;
        char* pcVar2;
        int iVar3;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::fillIntegerTextBuffer, this)(param_1);
        pcVar1 = this->integerTextBuffer;
        do {
            pcVar2 = pcVar1;
            pcVar1 = pcVar2 + 1;
        } while (*pcVar2 != '\0');
        iVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText,
            &DAT_TextManagerObject::instance.fontSizeClassArray[param_2])(
            this->integerTextBuffer, (int)(pcVar2 + -0x2158898));
        return iVar3;
    }

}
}
