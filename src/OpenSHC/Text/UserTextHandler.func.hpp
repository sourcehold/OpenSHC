/**
  path: 'OpenSHC/Text/UserTextHandler.func.hpp'
*/

#include "OpenSHC/Text/UserTextHandler.hpp"
namespace OpenSHC {
namespace Text {
    namespace UserTextHandler_Func {

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(undefined4), false, Address::SHC_3BB0A8C1_0x00469790,
            &UserTextHandler::resetToTextIndex)
        resetToTextIndex;

        MACRO_FUNCTION_RESOLVER(
            char* (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004697C0, &UserTextHandler::getCurrentText)
        getCurrentText;

        MACRO_FUNCTION_RESOLVER(int (UserTextHandler::*)(int), false, Address::SHC_3BB0A8C1_0x004697E0,
            &UserTextHandler::getTextArrayPointer)
        getTextArrayPointer;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x00469800, &UserTextHandler::FUN_00469800)
        FUN_00469800;

        MACRO_FUNCTION_RESOLVER(
            int (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00469860, &UserTextHandler::FUN_00469860)
        FUN_00469860;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00469870, &UserTextHandler::handleReturnKey)
        handleReturnKey;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00469880, &UserTextHandler::handleRightKey)
        handleRightKey;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004698A0, &UserTextHandler::handleLeftKey)
        handleLeftKey;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004698C0, &UserTextHandler::FUN_004698c0)
        FUN_004698c0;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004698D0, &UserTextHandler::moveCursorToEnd)
        moveCursorToEnd;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(int, int), false, Address::SHC_3BB0A8C1_0x004698F0,
            &UserTextHandler::FUN_004698f0)
        FUN_004698f0;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(int, int), false, Address::SHC_3BB0A8C1_0x00469930,
            &UserTextHandler::FUN_00469930)
        FUN_00469930;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(int), false, Address::SHC_3BB0A8C1_0x00469980,
            &UserTextHandler::handleCharacterIntoInputBuffer)
        handleCharacterIntoInputBuffer;

        MACRO_FUNCTION_RESOLVER(
            uint (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004699E0, &UserTextHandler::FUN_004699e0)
        FUN_004699e0;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x004715A0, &UserTextHandler::handleBackspace)
        handleBackspace;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00472B90, &UserTextHandler::clearTextAndCursor)
        clearTextAndCursor;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(char*), false, Address::SHC_3BB0A8C1_0x00472C30,
            &UserTextHandler::copyIntoTextArray)
        copyIntoTextArray;

        MACRO_FUNCTION_RESOLVER(
            int (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00472CB0, &UserTextHandler::FUN_00472cb0)
        FUN_00472cb0;

        MACRO_FUNCTION_RESOLVER(
            void (UserTextHandler::*)(), false, Address::SHC_3BB0A8C1_0x00472D00, &UserTextHandler::handleDeleteKey)
        handleDeleteKey;

        MACRO_FUNCTION_RESOLVER(void (UserTextHandler::*)(byte), false, Address::SHC_3BB0A8C1_0x00474110,
            &UserTextHandler::handleCharacterCode)
        handleCharacterCode;

    } // namespace UserTextHandler_Func
} // namespace Text
} // namespace OpenSHC
