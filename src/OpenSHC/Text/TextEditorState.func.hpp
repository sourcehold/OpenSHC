/**
  path: 'OpenSHC/Text/TextEditorState.func.hpp'
*/

#include "OpenSHC/Text/TextEditorState.hpp"
#include "mbstring.h"
#include "winnt.h"
namespace OpenSHC {
namespace Text {
    namespace TextEditorState_Func {

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4, undefined4, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x0045D080, &TextEditorState::meth_0x45d080)
        meth_0x45d080;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D0C0, &TextEditorState::meth_0x45d0c0)
        meth_0x45d0c0;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D140, &TextEditorState::meth_0x45d140)
        meth_0x45d140;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D1A0, &TextEditorState::meth_0x45d1a0)
        meth_0x45d1a0;

        MACRO_FUNCTION_RESOLVER(
            WCHAR (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045D200, &TextEditorState::parseHLPPart)
        parseHLPPart;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D370, &TextEditorState::meth_0x45d370)
        meth_0x45d370;

        MACRO_FUNCTION_RESOLVER(undefined* (TextEditorState::*)(int*), false, Address::SHC_3BB0A8C1_0x0045D3C0,
            &TextEditorState::getWideCharPointer)
        getWideCharPointer;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D430, &TextEditorState::meth_0x45d430)
        meth_0x45d430;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D690,
            &TextEditorState::bltTextToScreenIfNeedBe)
        bltTextToScreenIfNeedBe;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0045D6C0,
            &TextEditorState::drawBorderStyle0x20)
        drawBorderStyle0x20;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D740, &TextEditorState::meth_0x45d740)
        meth_0x45d740;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D890, &TextEditorState::meth_0x45d890)
        meth_0x45d890;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D8F0, &TextEditorState::meth_0x45d8f0)
        meth_0x45d8f0;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D950, &TextEditorState::FUN_0045d950)
        FUN_0045d950;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D990, &TextEditorState::FUN_0045d990)
        FUN_0045d990;

        MACRO_FUNCTION_RESOLVER(
            char* (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D9E0, &TextEditorState::FUN_0045d9e0)
        FUN_0045d9e0;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045DA20, &TextEditorState::FUN_0045da20)
        FUN_0045da20;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045DA40, &TextEditorState::FUN_0045da40)
        FUN_0045da40;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DA80, &TextEditorState::meth_0x45da80)
        meth_0x45da80;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DAE0, &TextEditorState::meth_0x45dae0)
        meth_0x45dae0;

        MACRO_FUNCTION_RESOLVER(undefined4 (TextEditorState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0045F080,
            &TextEditorState::FUN_0045f080)
        FUN_0045f080;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0045F0D0,
            &TextEditorState::meth_0x45f0d0)
        meth_0x45f0d0;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F240,
            &TextEditorState::someKindOfTextEscape)
        someKindOfTextEscape;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(LPCSTR), false, Address::SHC_3BB0A8C1_0x0045F470,
            &TextEditorState::readCrusaderHelpHlp)
        readCrusaderHelpHlp;

        MACRO_FUNCTION_RESOLVER(undefined4 (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045F580,
            &TextEditorState::meth_0x45f580)
        meth_0x45f580;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F5B0, &TextEditorState::parseHlp)
        parseHlp;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045FDC0, &TextEditorState::FUN_0045fdc0)
        FUN_0045fdc0;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004613E0,
            &TextEditorState::setTextRenderingLogic)
        setTextRenderingLogic;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004614D0, &TextEditorState::meth_0x4614d0)
        meth_0x4614d0;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00461550, &TextEditorState::meth_0x461550)
        meth_0x461550;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004619D0, &TextEditorState::meth_0x4619d0)
        meth_0x4619d0;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461A20, &TextEditorState::meth_0x461a20)
        meth_0x461a20;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461B90, &TextEditorState::meth_0x461b90)
        meth_0x461b90;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461CF0, &TextEditorState::meth_0x461cf0)
        meth_0x461cf0;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461E50, &TextEditorState::meth_0x461e50)
        meth_0x461e50;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461F90, &TextEditorState::meth_0x461f90)
        meth_0x461f90;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*, undefined4), false, Address::SHC_3BB0A8C1_0x004620F0,
            &TextEditorState::meth_0x4620f0)
        meth_0x4620f0;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00462150, &TextEditorState::FUN_00462150)
        FUN_00462150;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00462190, &TextEditorState::meth_0x462190)
        meth_0x462190;

    } // namespace TextEditorState_Func
} // namespace Text
} // namespace OpenSHC
