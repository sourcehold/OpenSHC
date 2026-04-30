/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Text/TextEditorState.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "mbstring.h"
#include "winnt.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00023974
    class TextEditorState {
    public:
        pointer* DAT_PointerToTemporaryTextMemory; // 0x00000000 length: 4
        undefined4 field1_0x4; // 0x00000004 length: 4
        undefined4 field2_0x8; // 0x00000008 length: 4
        undefined4 field3_0xc; // 0x0000000C length: 4
        undefined4 field4_0x10; // 0x00000010 length: 4
        undefined4 field5_0x14; // 0x00000014 length: 4
        undefined4 field6_0x18; // 0x00000018 length: 4
        undefined4 field7_0x1c; // 0x0000001C length: 4
        BOOLEnum field8_0x20; // 0x00000020 length: 4
        BOOLEnum field9_0x24; // 0x00000024 length: 4
        undefined4 field10_0x28; // 0x00000028 length: 4
        undefined4 field11_0x2c; // 0x0000002C length: 4
        undefined4 field12_0x30; // 0x00000030 length: 4
        undefined4 field13_0x34; // 0x00000034 length: 4
        undefined4 field14_0x38; // 0x00000038 length: 4
        undefined4 field15_0x3c; // 0x0000003C length: 4
        undefined4 field16_0x40; // 0x00000040 length: 4
        undefined4 field17_0x44; // 0x00000044 length: 4
        undefined4 field18_0x48; // 0x00000048 length: 4
        undefined4 field19_0x4c; // 0x0000004C length: 4
        undefined4 field20_0x50; // 0x00000050 length: 4
        undefined4 field21_0x54; // 0x00000054 length: 4
        undefined4 field22_0x58; // 0x00000058 length: 4
        undefined4 field23_0x5c; // 0x0000005C length: 4
        undefined4 field24_0x60; // 0x00000060 length: 4
        undefined4 field25_0x64; // 0x00000064 length: 4
        undefined4 field26_0x68; // 0x00000068 length: 4
        undefined4 field27_0x6c; // 0x0000006C length: 4
        undefined4 field28_0x70; // 0x00000070 length: 4
        undefined4 field29_0x74; // 0x00000074 length: 4
        undefined4 field30_0x78; // 0x00000078 length: 4
        undefined4 field31_0x7c; // 0x0000007C length: 4
        undefined4 field32_0x80; // 0x00000080 length: 4
        undefined4 field33_0x84; // 0x00000084 length: 4
        undefined4 field34_0x88; // 0x00000088 length: 4
        undefined4 field35_0x8c; // 0x0000008C length: 4
        undefined4 field36_0x90; // 0x00000090 length: 4
        undefined4 field37_0x94; // 0x00000094 length: 4
        undefined4 field38_0x98; // 0x00000098 length: 4
        undefined4 field39_0x9c; // 0x0000009C length: 4
        undefined4 field40_0xa0; // 0x000000A0 length: 4
        undefined4 counter; // 0x000000A4 length: 4
        undefined4 field42_0xa8; // 0x000000A8 length: 4
        undefined4 field43_0xac; // 0x000000AC length: 4
        undefined4 field44_0xb0; // 0x000000B0 length: 4
        undefined4 field45_0xb4; // 0x000000B4 length: 4
        undefined4 field46_0xb8; // 0x000000B8 length: 4
        undefined4 field47_0xbc; // 0x000000BC length: 4
        undefined4 field48_0xc0; // 0x000000C0 length: 4
        undefined4 field49_0xc4; // 0x000000C4 length: 4
        undefined4 shortArray1Related; // 0x000000C8 length: 4
        undefined4 field51_0xcc; // 0x000000CC length: 4
        undefined4 field52_0xd0; // 0x000000D0 length: 4
        undefined4 field53_0xd4; // 0x000000D4 length: 4
        undefined4 field54_0xd8; // 0x000000D8 length: 4
        undefined4 field55_0xdc; // 0x000000DC length: 4
        undefined4 field56_0xe0; // 0x000000E0 length: 4
        undefined4 field57_0xe4; // 0x000000E4 length: 4
        undefined4 field58_0xe8; // 0x000000E8 length: 4
        undefined4 field59_0xec; // 0x000000EC length: 4
        undefined4 field60_0xf0; // 0x000000F0 length: 4
        undefined4 field61_0xf4; // 0x000000F4 length: 4
        undefined4 field62_0xf8; // 0x000000F8 length: 4
        undefined4 field63_0xfc; // 0x000000FC length: 4
        undefined4 field64_0x100; // 0x00000100 length: 4
        char stringArray1[5][1000]; // 0x00000104 length: 5000
        byte stringArray1Companion[5]; // 0x0000148C length: 5
        undefined1 padding_0x1491[3]; // 0x00001491 length: 3
        undefined4 count1; // 0x00001494 length: 4
        char stringArray2[20][1000]; // 0x00001498 length: 20000
        undefined4 count2; // 0x000062B8 length: 4
        short shortArray1[60000]; // 0x000062BC length: 120000
        int shortArray1Count; // 0x0002377C length: 4
        short shortArray1Companion2[50][4]; // 0x00023780 length: 400
        int intArray1[25]; // 0x00023910 length: 100

    private:
        TextEditorState(TextEditorState const&);
        void operator=(TextEditorState const&);

        TextEditorState();
        ~TextEditorState();

    public:
        // Constructor
        TextEditorState* Constructor_TextEditorState();

        void meth_0x45d080(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);

        void meth_0x45d0c0();

        int meth_0x45d140(char* param_1);

        int meth_0x45d1a0(char* param_1);

        WCHAR parseHLPPart(FILE* filePointer);

        void meth_0x45d370();

        undefined* getWideCharPointer(int* param_1);

        void meth_0x45d430();

        void bltTextToScreenIfNeedBe();

        void drawBorderStyle0x20(int param_1, int param_2, int param_3, int param_4);

        void meth_0x45d740();

        int meth_0x45d890(char* param_1);

        void meth_0x45d8f0(char* param_1);

        int FUN_0045d950(int param_1);

        int FUN_0045d990(int param_1);

        char* FUN_0045d9e0(int param_1);

        int FUN_0045da20(int param_1);

        int FUN_0045da40(int param_1);

        int meth_0x45da80(char* param_1);

        void meth_0x45dae0(char* param_1);

        undefined4 FUN_0045f080(undefined4 param_1);

        void meth_0x45f0d0(undefined4 param_1);

        void someKindOfTextEscape();

        void readCrusaderHelpHlp(LPCSTR param_1);

        undefined4 meth_0x45f580(FILE* param_1);

        void parseHlp();

        void FUN_0045fdc0(int param_1);

        void setTextRenderingLogic();

        void meth_0x4614d0();

        void meth_0x461550();

        void meth_0x4619d0();

        void meth_0x461a20(int param_1);

        void meth_0x461b90(int param_1);

        void meth_0x461cf0(int param_1);

        void meth_0x461e50(int param_1);

        void meth_0x461f90(int param_1);

        void meth_0x4620f0(char* param_1, undefined4 param_2);

        void FUN_00462150();

        void meth_0x462190(int param_1);
    };

    static_assert_cpp98_obj(sizeof(TextEditorState) == 145780, TextEditorState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(TextEditorState, false, Address::SHC_3BB0A8C1_0x02403AF8) pDAT_TextEditorState;

} // namespace Text
} // namespace OpenSHC
