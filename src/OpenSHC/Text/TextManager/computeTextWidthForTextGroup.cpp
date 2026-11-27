#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004246B0
    int TextManager::computeTextWidthForTextGroup(eTextSections textOffsetIndex, int textNumInGroup, int fontSize)
    {
        char* text;
        int _width;
        _width = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            fontSize);
        return _width;
    }

}
}
