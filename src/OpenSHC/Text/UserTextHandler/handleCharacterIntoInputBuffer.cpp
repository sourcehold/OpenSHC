#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469980
    void UserTextHandler::handleCharacterIntoInputBuffer(int characterCode)
    {
        if ((DAT_TextInputDefinedData::instance.UserTextHandler_CharacterFilter_B_1_8_9[characterCode] == 0)
            && (characterCode < 240)) {
            return;
        }

        if (this->inputBufferIndex == 30) {
            /*
              consume the first character and append the char at the end
             */
            for (int i = 0; i < 29; ++i) {
                this->inputBuffer[i] = this->inputBuffer[i + 1];
            }
            this->inputBuffer[29] = (char)characterCode;
            return;
        }

        this->inputBuffer[this->inputBufferIndex] = (char)characterCode;
        this->inputBufferIndex = this->inputBufferIndex + 1;
    }

}
}
