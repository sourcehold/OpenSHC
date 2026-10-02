#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004244C0
    int TextManager::renderMultilineText2(eTextSections param_1, int param_2, int param_3, int param_4)
    {
        char* text;
        int iVar1;
        int yPos;
        BGR24 color;
        int blendStrength;
        int modeUnk;
        modeUnk = 1;
        blendStrength = 0;
        color = 0;
        yPos = 0;
        iVar1 = 0;
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[param_4])(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(param_1, param_2),
            iVar1, yPos, param_3, color, blendStrength, modeUnk);
        return iVar1;
    }

}
}
