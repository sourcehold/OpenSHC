#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"
#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00474110
    void UserTextHandler::handleCharacterCode(byte characterCode)
    {
        if (this->unknown01 == 0) {
            return;
        }

        if ((this->textArrayIndex == OpenSHC::Text::TAIT_TWO__FILTER_A)
            || (this->textArrayIndex == OpenSHC::Text::TAIT_THREE__FILTER_A)) {
            if (DAT_TextInputDefinedData::instance.UserTextHandler_CharacterFilter_A_2_3[characterCode] == 0) {
                return;
            }
        } else if (((this->textArrayIndex == OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT)
                       || (this->textArrayIndex == OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY))
            || (this->textArrayIndex == OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY)) {
            if ((characterCode < 48) || (57 < characterCode)) {
                if (this->textArrayIndex != OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT) {
                    return;
                }
                if (characterCode != 0x2e) {
                    return;
                }
            }
        } else if (DAT_TextInputDefinedData::instance.UserTextHandler_CharacterFilter_B_1_8_9[characterCode] == 0) {
            return;
        }

        if (MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::isTextInputAtCapacity, this)() == 2) {
            return;
        }

        if ((DAT_InsertKeyState::instance.insert != 0)
            && (this->textContentLengthArray[this->textArrayIndex]
                < this->textBoxMaxCharactersArray[this->textArrayIndex])) {
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::shiftTextRightAtCursor, this)(
                this->textCursorIndexArray[this->textArrayIndex],
                this->textContentLengthArray[this->textArrayIndex]
                    - this->textCursorIndexArray[this->textArrayIndex]);
        }

        if (this->textBoxMaxCharactersArray[this->textArrayIndex]
            <= this->textContentLengthArray[this->textArrayIndex]) {
            return;
        }

        /*
          write character
         */
        this->textArray[this->textArrayIndex][this->textCursorIndexArray[this->textArrayIndex]] = characterCode;
        this->textCursorIndexArray[this->textArrayIndex] = this->textCursorIndexArray[this->textArrayIndex] + 1;
        if (this->textBoxMaxCharactersArray[this->textArrayIndex]
            < this->textCursorIndexArray[this->textArrayIndex]) {
            this->textCursorIndexArray[this->textArrayIndex] = this->textBoxMaxCharactersArray[this->textArrayIndex];
        }
        if (this->textCursorIndexArray[this->textArrayIndex] < 0) {
            this->textCursorIndexArray[this->textArrayIndex] = 0;
        }

        char* scan = this->textArray[this->textArrayIndex];
        while (*scan != '\0') {
            ++scan;
        }
        this->textContentLengthArray[this->textArrayIndex] = scan - this->textArray[this->textArrayIndex];
    }

}
}
