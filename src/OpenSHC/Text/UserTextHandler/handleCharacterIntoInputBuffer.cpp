#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469980
    void UserTextHandler::handleCharacterIntoInputBuffer(int characterCode)
    {
        if (DAT_TextInputDefinedData::instance.UserTextHandler_CharacterFilter_B_1_8_9[characterCode] == 0
            && characterCode < 240) {
            return;
        }
        if (this->inputBufferIndex == countof(this->inputBuffer)) {
            for (int i = 0; i < countof(this->inputBuffer) - 1; ++i) {
                this->inputBuffer[i] = this->inputBuffer[i + 1];
            }
            this->inputBuffer[countof(this->inputBuffer) - 1] = (byte)characterCode;
            return;
        }
        this->inputBuffer[this->inputBufferIndex] = (byte)characterCode;
        ++this->inputBufferIndex;
    }

}
}
