/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Input/MouseState.hpp'
*/

#pragma once

#include "OpenSHC/Input/Mouse/ClickTypeBitMaskEnumByte.hpp"
#include "OpenSHC/Input/Mouse/MouseClickInteractionInt.hpp"
#include "OpenSHC/Input/Mouse/MouseXYUUStruct.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Input {

    using OpenSHC::Input::Mouse::ClickTypeBitMaskEnumByte;
    using OpenSHC::Input::Mouse::MouseClickInteractionInt;
    using OpenSHC::Input::Mouse::MouseXYUUStruct;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000274
    class MouseState {
    public:
        undefined4 inactiveTime; // 0x00000000 length: 4
        undefined4 time0; // 0x00000004 length: 4
        BOOLEnum anyActivity; // 0x00000008 length: 4
        undefined4 flag; // 0x0000000C length: 4
        undefined4 screenSpaceX; // 0x00000010 length: 4
        undefined4 screenSpaceY; // 0x00000014 length: 4
        undefined4 cursorPosX; // 0x00000018 length: 4
        undefined4 cursorPosY; // 0x0000001C length: 4
        undefined4 previousScreenSpaceX; // 0x00000020 length: 4
        undefined4 previousScreenSpaceY; // 0x00000024 length: 4
        BOOLEnum draggingStopped; // 0x00000028 length: 4
        undefined4 midClickStop; // 0x0000002C length: 4
        undefined4 rightClickStop; // 0x00000030 length: 4
        undefined4 leftClickStart; // 0x00000034 length: 4
        undefined4 midClickStart; // 0x00000038 length: 4
        undefined4 rightClickStart; // 0x0000003C length: 4
        BOOLEnum leftClickState; // 0x00000040 length: 4
        BOOLEnum midClickState; // 0x00000044 length: 4
        BOOLEnum rightClickState; // 0x00000048 length: 4
        BOOLEnum previousLeftClickState; // 0x0000004C length: 4
        undefined4 previousMidClickStateUnk; // 0x00000050 length: 4
        uint previousRightClickState; // 0x00000054 length: 4
        undefined4 scrollEventData; // 0x00000058 length: 4
        undefined4 field23_0x5c; // 0x0000005C length: 4
        undefined4 field24_0x60; // 0x00000060 length: 4
        undefined4 field25_0x64; // 0x00000064 length: 4
        undefined4 field26_0x68; // 0x00000068 length: 4
        undefined4 field27_0x6c; // 0x0000006C length: 4
        undefined4 left; // 0x00000070 length: 4
        undefined4 top; // 0x00000074 length: 4
        undefined4 right; // 0x00000078 length: 4
        undefined4 bottom; // 0x0000007C length: 4
        undefined4 hitboxXStart; // 0x00000080 length: 4
        undefined4 hitboxYStart; // 0x00000084 length: 4
        undefined4 hitboxXEnd; // 0x00000088 length: 4
        undefined4 hitboxYEnd; // 0x0000008C length: 4
        int field36_0x90; // 0x00000090 length: 4
        undefined4 field37_0x94; // 0x00000094 length: 4
        undefined1 padding_0x98[4]; // 0x00000098 length: 4
        undefined4 field42_0x9c; // 0x0000009C length: 4
        MouseXYUUStruct mouseXY[9]; // 0x000000A0 length: 144
        undefined4 field44_0x130; // 0x00000130 length: 4
        undefined4 field45_0x134; // 0x00000134 length: 4
        undefined4 field46_0x138; // 0x00000138 length: 4
        undefined4 field47_0x13c; // 0x0000013C length: 4
        undefined4 field48_0x140; // 0x00000140 length: 4
        undefined4 field49_0x144; // 0x00000144 length: 4
        undefined4 field50_0x148; // 0x00000148 length: 4
        undefined4 field51_0x14c; // 0x0000014C length: 4
        undefined4 field52_0x150; // 0x00000150 length: 4
        undefined4 field53_0x154; // 0x00000154 length: 4
        undefined4 field54_0x158; // 0x00000158 length: 4
        undefined4 field55_0x15c; // 0x0000015C length: 4
        undefined4 field56_0x160; // 0x00000160 length: 4
        undefined4 field57_0x164; // 0x00000164 length: 4
        undefined4 index; // 0x00000168 length: 4
        undefined4 storedScreenSpaceX; // 0x0000016C length: 4
        undefined4 storedScreenSpaceY; // 0x00000170 length: 4
        undefined4 field61_0x174; // 0x00000174 length: 4
        undefined4 field62_0x178; // 0x00000178 length: 4
        undefined4 field63_0x17c; // 0x0000017C length: 4
        undefined4 mouseBasedEvent; // 0x00000180 length: 4
        undefined4 field65_0x184; // 0x00000184 length: 4
        undefined4 field66_0x188; // 0x00000188 length: 4
        undefined4 mapOrientationCopy1; // 0x0000018C length: 4
        undefined4 mapOrientationCopy2; // 0x00000190 length: 4
        undefined4 mapOrientationCopy3; // 0x00000194 length: 4
        undefined4 field70_0x198; // 0x00000198 length: 4
        undefined4 field71_0x19c; // 0x0000019C length: 4
        undefined4 currentTime1; // 0x000001A0 length: 4
        undefined4 currentTime2; // 0x000001A4 length: 4
        undefined4 currentTime3; // 0x000001A8 length: 4
        undefined4 field75_0x1ac; // 0x000001AC length: 4
        undefined4 field76_0x1b0; // 0x000001B0 length: 4
        undefined4 field77_0x1b4; // 0x000001B4 length: 4
        undefined4 field78_0x1b8; // 0x000001B8 length: 4
        undefined4 field79_0x1bc; // 0x000001BC length: 4
        undefined4 field80_0x1c0; // 0x000001C0 length: 4
        undefined4 field81_0x1c4; // 0x000001C4 length: 4
        undefined4 field82_0x1c8; // 0x000001C8 length: 4
        int leftClickStartMoment; // 0x000001CC length: 4
        undefined4 dragReleaseX; // 0x000001D0 length: 4
        undefined4 dragReleaseY; // 0x000001D4 length: 4
        undefined4 field86_0x1d8; // 0x000001D8 length: 4
        int field87_0x1dc; // 0x000001DC length: 4
        int waitCursorToggle; // 0x000001E0 length: 4
        int field89_0x1e4; // 0x000001E4 length: 4
        undefined1 padding_0x1e8[8]; // 0x000001E8 length: 8
        undefined4 cursorType; // 0x000001F0 length: 4
        undefined2 mouseWindowX; // 0x000001F4 length: 2
        undefined2 mouseWindowY; // 0x000001F6 length: 2
        undefined2 mouseWheelDelta; // 0x000001F8 length: 2
        ClickTypeBitMaskEnumByte mouseClickTypes; // 0x000001FA length: 1
        undefined1 padding1; // 0x000001FB length: 1
        HCURSOR currentDefaultCursor; // 0x000001FC length: 4
        HCURSOR currentDeleteCursor_0x200; // 0x00000200 length: 4
        HCURSOR unknownNotAniDeleteNotCursor_0x204; // 0x00000204 length: 4
        HCURSOR currentWaitCursor_0x208; // 0x00000208 length: 4
        HCURSOR currentHandCursor_0x20c; // 0x0000020C length: 4
        HCURSOR currentDeleteNotCursor_0x210; // 0x00000210 length: 4
        HCURSOR currentDefaultArabCursor_0x214; // 0x00000214 length: 4
        HCURSOR unknownNotAniCursor_0x218; // 0x00000218 length: 4
        undefined1 padding_0x21c[8]; // 0x0000021C length: 8
        HCURSOR swordCursor_0x224; // 0x00000224 length: 4
        HCURSOR deleteCursor_0x228; // 0x00000228 length: 4
        undefined1 padding_0x22c[4]; // 0x0000022C length: 4
        HCURSOR jesterCursor_0x230; // 0x00000230 length: 4
        HCURSOR handCursor_0x234; // 0x00000234 length: 4
        HCURSOR deleteNotCursor_0x238; // 0x00000238 length: 4
        HCURSOR scimitarCursor_0x23c; // 0x0000023C length: 4
        undefined1 padding_0x240[12]; // 0x00000240 length: 12
        HCURSOR notAniDefaultCursor_0x24c; // 0x0000024C length: 4
        HCURSOR notAniDeleteCursor_0x250; // 0x00000250 length: 4
        undefined1 padding_0x254[4]; // 0x00000254 length: 4
        HCURSOR notAniWaitCursor_0x258; // 0x00000258 length: 4
        HCURSOR notAniHandCursor_0x25c; // 0x0000025C length: 4
        HCURSOR notAniDeleteNotCursor_0x260; // 0x00000260 length: 4
        HCURSOR notAniDefaultArabCursor_0x264; // 0x00000264 length: 4
        undefined1 padding_0x268[12]; // 0x00000268 length: 12

    private:
        MouseState(MouseState const&);
        void operator=(MouseState const&);

        MouseState();
        ~MouseState();

    public:
        // Constructor
        MouseState* Constructor_MouseState();

        void makeSelectedCursorTypeCurrent();

        void updateMousePositionAndClicks(short xMousePos, short yMousePos, MouseClickInteractionInt clickType);

        void updateMouseWheelStatus(int delta);

        BOOLEnum isMouseInsideBox(int xPos, int yPos, int width, int heigth);

        void updateMouseStateBasedOnCursorAndTime();

        HCURSOR setCursor(DWORD cursorType);

        void meth_0x468420();

        void setupHitBox(int width, int height);

        void resetMouseCursorState();

        void renderPreviewAtMouseLocation();

        void storeXYAndResetMouseState();

        void resetMouseState2();

        void loadAndSetCursor(int notAniDefaultCursorRef, int notAniDeleteCursorRef, int notAniDeleteNotCursorRef,
            int unused1, int unused2, int unused3, int unused4, int notAniUnknownCursorRef);

        void meth_0x470b30();

        void rightClickMenuUnk();

        void drawMouseBasedBox();
    };

    static_assert_cpp98_obj(sizeof(MouseState) == 628, MouseState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MouseState, false, Address::SHC_3BB0A8C1_0x00F2C9B0) pDAT_MouseState;

} // namespace Input
} // namespace OpenSHC
