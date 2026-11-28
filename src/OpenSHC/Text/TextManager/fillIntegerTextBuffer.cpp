#include "../TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469FA0
    void TextManager::fillIntegerTextBuffer(int numberInt)
    {
        memset(this->integerTextBuffer, 0, sizeof(this->integerTextBuffer));
        int signLength;
        if (numberInt < 0) {
            numberInt = -numberInt;
            this->integerTextBuffer[0] = '-';
            signLength = 1;
        } else if (numberInt <= 0 || !this->renderPlusSignForNumbers) {
            signLength = 0;
        } else {
            this->integerTextBuffer[0] = '+';
            signLength = 1;
        }
        int numberOfDigits = 0;
        for (int i = 0; i < countof(DAT_TextInputDefinedData::instance.numberOfDigitsThresholds); ++i) {
            if (numberInt <= DAT_TextInputDefinedData::instance.numberOfDigitsThresholds[i].maxNumber) {
                numberOfDigits = DAT_TextInputDefinedData::instance.numberOfDigitsThresholds[i].numberOfDigits;
                break;
            }
        }
        if (numberOfDigits == 0) {
            numberOfDigits = 9;
        }
        // the digit count itself is counted down: a separate loop index does not match
        for (--numberOfDigits; numberOfDigits >= 0; --numberOfDigits) {
            this->integerTextBuffer[numberOfDigits + signLength] = numberInt % 10 + '0';
            numberInt /= 10;
        }
    }

}
}
