/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/UserTextHandler.hpp'
*/

#pragma once

#include "OpenSHC/Text/TextArrayIndexTypeInt.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::Text::TextArrayIndexTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00001114
    class UserTextHandler {
    public:
        TextArrayIndexTypeInt textArrayIndex; // 0x00000000 length: 4
        dword unknown01; // 0x00000004 length: 4
        dword returnPressed; // 0x00000008 length: 4
        dword allowUserTextInput; // 0x0000000C length: 4
        int textArrayFontSizes[16]; // 0x00000010 length: 64
        int textBoxMaxCharactersArray[16]; // 0x00000050 length: 64
        int textContentLengthArray[16]; // 0x00000090 length: 64
        int textCursorIndexArray[16]; // 0x000000D0 length: 64
        int textBoxMaxTextWidthDimensionArray[16]; // 0x00000110 length: 64
        char textArray[16][250]; // 0x00000150 length: 4000
        char inputBuffer[30]; // 0x000010F0 length: 30
        undefined1 padding_0x110e[2]; // 0x0000110E length: 2
        int inputBufferIndex; // 0x00001110 length: 4

    private:
        UserTextHandler(UserTextHandler const&);
        void operator=(UserTextHandler const&);

        UserTextHandler();
        ~UserTextHandler();

    public:
        void resetToTextIndex(undefined4 textIndex);

        char* getCurrentText();

        int getTextArrayPointer(int param_1);

        void FUN_00469800(undefined4 param_1, undefined4 param_2);

        int FUN_00469860();

        void handleReturnKey();

        void handleRightKey();

        void handleLeftKey();

        void FUN_004698c0();

        void moveCursorToEnd();

        void FUN_004698f0(int param_1, int param_2);

        void FUN_00469930(int param_1, int param_2);

        void handleCharacterIntoInputBuffer(int characterCode);

        uint FUN_004699e0();

        void handleBackspace();

        void clearTextAndCursor();

        void copyIntoTextArray(char* param_1);

        int FUN_00472cb0();

        void handleDeleteKey();

        void handleCharacterCode(byte characterCode);
    };

    static_assert_cpp98_obj(sizeof(UserTextHandler) == 4372, UserTextHandler);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(UserTextHandler, false, Address::SHC_3BB0A8C1_0x01652740) pDAT_UserTextHandler;

} // namespace Text
} // namespace OpenSHC
