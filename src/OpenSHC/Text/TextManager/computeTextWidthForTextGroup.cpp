#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::DE::SHCDE::eTextSections;

    // FUNCTION: STRONGHOLDCRUSADER 0x004246B0
    int TextManager::computeTextWidthForTextGroup(eTextSections textOffsetIndex, int textNumInGroup, int fontSize)
    {
        return MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            fontSize);
    }

}
}
