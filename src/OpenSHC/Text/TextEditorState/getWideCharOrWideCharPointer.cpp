#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00df2b78.hpp"

namespace OpenSHC {
namespace Text {

    // NOTE: Return is essentially a "union", however, it needs to be a value for the proper structure
    //   Also, it might be likely that this function is "known" by its only user "processHelpRichTextTokens"

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D3C0
    uint TextEditorState::getWideCharOrWideCharPointer(int* param_1)
    {
        int result = this->DAT_PointerToTemporaryTextMemory[*param_1];
        *param_1 += 1;

        if (result >= L' ') {
            DAT_ARRAY_00df2b78::instance[0] = result;

            int length = 1;
            while (this->DAT_PointerToTemporaryTextMemory[*param_1] >= L' ') {
                DAT_ARRAY_00df2b78::instance[length] = this->DAT_PointerToTemporaryTextMemory[*param_1];
                *param_1 += 1;
                ++length;
                if (this->DAT_PointerToTemporaryTextMemory[*param_1 - 1] == L' ') {
                    break;
                }
            }
            DAT_ARRAY_00df2b78::instance[length] = L'\0';
            result = (int)DAT_ARRAY_00df2b78::instance;
        }
        return (uint)result;
    }

}
}
