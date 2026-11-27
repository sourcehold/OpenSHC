#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Returns 2 if the current text slot is at capacity (cannot accept more input), 0 otherwise.   Capacity is reached
      if either: (1) the rendered pixel width of the current text meets or exceeds   textBoxMaxTextWidthDimensionArray
      for this slot, or (2) the cursor index is at or beyond   textBoxMaxCharactersArray. Used as a boolean gate before
      inserting a new character.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00472CB0
    int UserTextHandler::isTextInputAtCapacity()
    {
        int const textWidth
            = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                this->textArray[this->textArrayIndex], this->textArrayFontSizes[this->textArrayIndex]);
        if (textWidth >= this->textBoxMaxTextWidthDimensionArray[this->textArrayIndex]) {
            return 2;
        }
        return this->textCursorIndexArray[this->textArrayIndex] < this->textBoxMaxCharactersArray[this->textArrayIndex]
            ? 0
            : 2;
    }

}
}
