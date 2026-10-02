#include "../TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469FA0
    void TextManager::fillIntegerTextBuffer(int numberInt)
    {
        int iVar2;
        this->integerTextBuffer[0] = '\0';
        this->integerTextBuffer[1] = '\0';
        this->integerTextBuffer[2] = '\0';
        this->integerTextBuffer[3] = '\0';
        this->integerTextBuffer[4] = '\0';
        this->integerTextBuffer[5] = '\0';
        this->integerTextBuffer[6] = '\0';
        this->integerTextBuffer[7] = '\0';
        this->integerTextBuffer[8] = '\0';
        this->integerTextBuffer[9] = '\0';
        this->integerTextBuffer[10] = '\0';
        this->integerTextBuffer[0xb] = '\0';
        this->integerTextBuffer[0xc] = '\0';
        this->integerTextBuffer[0xd] = '\0';
        this->integerTextBuffer[0xe] = '\0';
        this->integerTextBuffer[0xf] = '\0';
        this->integerTextBuffer[0x10] = '\0';
        this->integerTextBuffer[0x11] = '\0';
        this->integerTextBuffer[0x12] = '\0';
        this->integerTextBuffer[0x13] = '\0';
        if (numberInt < 0) {
            numberInt = -numberInt;
            this->integerTextBuffer[0] = 45;
            this->integerTextBuffer[1] = '\0';
            this->integerTextBuffer[2] = '\0';
            this->integerTextBuffer[3] = '\0';
            iVar2 = 1;
        } else if ((numberInt < 1) || (this->field8_0x20 == 0)) {
            iVar2 = 0;
        } else {
            this->integerTextBuffer[0] = 43;
            this->integerTextBuffer[1] = '\0';
            this->integerTextBuffer[2] = '\0';
            this->integerTextBuffer[3] = '\0';
            iVar2 = 1;
        }
        int iVar1 = 0;
        do {
            if (numberInt <= DAT_TextInputDefinedData::instance.field5_0x684[iVar1][0]) {
                iVar1 = DAT_TextInputDefinedData::instance.field5_0x684[iVar1][1];
                if (iVar1 != 0)
                    goto LAB_0046a014;
                break;
            }
            iVar1 = iVar1 + 1;
        } while (iVar1 < 8);
        iVar1 = 9;
    LAB_0046a014:
        iVar1 = iVar1 + -1;
        while (-1 < iVar1) {
            iVar1 = iVar1 + -1;
            *(char*)(iVar2 + 0x2158899 + iVar1) = (char)numberInt + (char)(numberInt / 10) * -10 + '0';
            numberInt = numberInt / 10;
        }
        this->integerTextBuffer[0] = DAT_TextManagerObject::instance.integerTextBuffer[0];
        this->integerTextBuffer[1] = DAT_TextManagerObject::instance.integerTextBuffer[1];
        this->integerTextBuffer[2] = DAT_TextManagerObject::instance.integerTextBuffer[2];
        this->integerTextBuffer[3] = DAT_TextManagerObject::instance.integerTextBuffer[3];
        this->integerTextBuffer[4] = DAT_TextManagerObject::instance.integerTextBuffer[4];
        this->integerTextBuffer[5] = DAT_TextManagerObject::instance.integerTextBuffer[5];
        this->integerTextBuffer[6] = DAT_TextManagerObject::instance.integerTextBuffer[6];
        this->integerTextBuffer[7] = DAT_TextManagerObject::instance.integerTextBuffer[7];
        this->integerTextBuffer[8] = DAT_TextManagerObject::instance.integerTextBuffer[8];
        this->integerTextBuffer[9] = DAT_TextManagerObject::instance.integerTextBuffer[9];
        this->integerTextBuffer[10] = DAT_TextManagerObject::instance.integerTextBuffer[10];
        this->integerTextBuffer[0xb] = DAT_TextManagerObject::instance.integerTextBuffer[0xb];
        this->integerTextBuffer[0xc] = DAT_TextManagerObject::instance.integerTextBuffer[0xc];
        this->integerTextBuffer[0xd] = DAT_TextManagerObject::instance.integerTextBuffer[0xd];
        this->integerTextBuffer[0xe] = DAT_TextManagerObject::instance.integerTextBuffer[0xe];
        this->integerTextBuffer[0xf] = DAT_TextManagerObject::instance.integerTextBuffer[0xf];
        this->integerTextBuffer[0x10] = DAT_TextManagerObject::instance.integerTextBuffer[0x10];
        this->integerTextBuffer[0x11] = DAT_TextManagerObject::instance.integerTextBuffer[0x11];
        this->integerTextBuffer[0x12] = DAT_TextManagerObject::instance.integerTextBuffer[0x12];
        this->integerTextBuffer[0x13] = DAT_TextManagerObject::instance.integerTextBuffer[0x13];
        return;
    }

}
}
