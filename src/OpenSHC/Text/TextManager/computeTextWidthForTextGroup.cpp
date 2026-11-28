#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004246B0
    int TextManager::computeTextWidthForTextGroup(eTextSections textOffsetIndex, int textNumInGroup, int fontSize)
    {
        return MACRO_CALL_MEMBER(TextManager_Func::computeTextWidth, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup),
            fontSize);
    }

}
}
