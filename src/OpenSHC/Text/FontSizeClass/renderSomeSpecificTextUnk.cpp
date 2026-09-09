#include "../FontSizeClass.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004733A0
    void FontSizeClass::renderSomeSpecificTextUnk(
        int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, BGR24 color)
    {
        char strBuffer[128];

        int _runXPos = xPos;
        int _runYPos = yPos;

        int lineHeight = (this->lineHeight_0x14 * 38) >> 5;
        int blendValue = (otherBlendValueUnk * 32) / 100;

        if (1 > DAT_TextManagerObject::instance.count1 || DAT_TextManagerObject::instance.count1 > 32
            || lengthUnk < 1) {
            return;
        }

        if (DAT_TextManagerObject::instance.count1 == 1) {
            int lengthStr = strlen(DAT_TextManagerObject::instance.stringArray1[0]);
            if (1 <= lengthStr) {
                if (lengthUnk > lengthStr) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                        DAT_TextManagerObject::instance.stringArray1[0], lengthStr, _runXPos, yPos, color, 0);
                } else {
                    if (0 < lengthUnk - 1) {
                        MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                            strBuffer, DAT_TextManagerObject::instance.stringArray1[0], lengthStr);
                        strBuffer[lengthUnk - 1] = '\0';
                        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                            strBuffer, lengthUnk - 1, _runXPos, yPos, color, 0);
                        _runXPos = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText, this)(
                            strBuffer, lengthUnk - 1);
                        _runXPos += xPos;
                    }
                    strBuffer[0] = DAT_TextManagerObject::instance.stringArray1[0][lengthUnk - 1];
                    strBuffer[1] = '\0';
                    MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                        strBuffer, 1, _runXPos, yPos, color, blendValue);
                }
            }
        } else {
            for (int _index = 0; _index < (int)DAT_TextManagerObject::instance.count1; ++_index) {
                int lengthStr = strlen(DAT_TextManagerObject::instance.stringArray1[_index]);
                if (lengthStr < 1) {
                    break;
                }

                if (lengthUnk > lengthStr) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                        DAT_TextManagerObject::instance.stringArray1[_index], lengthStr, xPos, _runYPos, color, 0);
                    _runYPos += lineHeight;
                    lengthUnk -= lengthStr;
                    continue;
                }

                if (0 < lengthUnk + -1) {
                    MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                        strBuffer, DAT_TextManagerObject::instance.stringArray1[_index], lengthStr);
                    strBuffer[lengthUnk + -1] = '\0';
                    MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                        strBuffer, lengthUnk + -1, xPos, _runYPos, color, 0);
                    _runXPos = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText, this)(
                        strBuffer, lengthUnk + -1);
                    _runXPos += xPos;
                }
                strBuffer[0] = DAT_TextManagerObject::instance.stringArray1[_index][lengthUnk - 1];
                strBuffer[1] = '\0';
                MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, this)(
                    strBuffer, 1, _runXPos, _runYPos, color, blendValue);
                break;
            }
        }
    }
}
}
