#include "../TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469FA0
    void TextManager::fillIntegerTextBuffer(int numberInt)
    {
        memset(this->integerTextBuffer, '\0', sizeof(this->integerTextBuffer));

        BOOL hasSymbol;
        if (numberInt < 0) {
            numberInt = -numberInt;
            this->integerTextBuffer[0] = '-';
            hasSymbol = TRUE;
        } else if (numberInt <= 0 || !this->renderPlusSignForNumbers) {
            hasSymbol = FALSE;
        } else {
            this->integerTextBuffer[0] = '+';
            hasSymbol = TRUE;
        }

        int numberOfDigitsAndIndex = 0;
        for (int i = 0; i < 8; ++i) {
            if (numberInt <= DAT_TextInputDefinedData::instance.numberOfDigitsThresholds[i].maxNumber) {
                numberOfDigitsAndIndex = DAT_TextInputDefinedData::instance.numberOfDigitsThresholds[i].numberOfDigits;
                break;
            }
        }
        if (!numberOfDigitsAndIndex) {
            numberOfDigitsAndIndex = 9;
        }
        --numberOfDigitsAndIndex;
        while (numberOfDigitsAndIndex >= 0) {
            this->integerTextBuffer[numberOfDigitsAndIndex + hasSymbol] = numberInt + (numberInt / 10) * -10 + '0';
            numberInt /= 10;
            --numberOfDigitsAndIndex;
        }
    }

}
}
