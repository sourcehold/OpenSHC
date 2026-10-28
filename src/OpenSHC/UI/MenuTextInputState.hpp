/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuTextInputState.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuModalTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00001828
    class MenuTextInputState {
    public:
        undefined4 fileListContext; // 0x00000000 length: 4
        undefined4 savedListOffset1; // 0x00000004 length: 4
        undefined4 savedListSelection1; // 0x00000008 length: 4
        undefined4 savedListSortOrder1; // 0x0000000C length: 4
        undefined4 savedListOffset2; // 0x00000010 length: 4
        undefined4 savedListSelection2; // 0x00000014 length: 4
        undefined4 savedListSortOrder2; // 0x00000018 length: 4
        undefined4 savedListOffset3; // 0x0000001C length: 4
        undefined4 savedListSelection3; // 0x00000020 length: 4
        undefined4 savedListSortOrder3; // 0x00000024 length: 4
        undefined4 menuCurrentlySelectedResolution; // 0x00000028 length: 4
        undefined4 unknownZoomRelatedFlag01; // 0x0000002C length: 4
        undefined4 pendingGameSpeedLevel; // 0x00000030 length: 4
        undefined4 menuScrollSpeedSetting; // 0x00000034 length: 4
        undefined4 pendingSettingBubbleHelp; // 0x00000038 length: 4
        undefined1 pendingUnusedOption1; // 0x0000003C length: 1
        undefined1 padding_0x3d[3]; // 0x0000003D length: 3
        undefined4 DAT_SoundActiveMenuVar; // 0x00000040 length: 4
        undefined4 pendingStreamVolume0; // 0x00000044 length: 4
        undefined4 pendingStreamVolume1; // 0x00000048 length: 4
        undefined4 pendingStreamVolume3; // 0x0000004C length: 4
        undefined4 menuCursorType; // 0x00000050 length: 4
        undefined4 DAT_GenieVoiceActiveMenuVar; // 0x00000054 length: 4
        undefined4 DAT_MenuOptionsActionParameter; // 0x00000058 length: 4
        MenuModalTypeInt currentModalDialog; // 0x0000005C length: 4
        MenuModalTypeInt modalDialog_2; // 0x00000060 length: 4
        MenuModalTypeInt modalDialog_3; // 0x00000064 length: 4
        MenuModalTypeInt modalDialog_4; // 0x00000068 length: 4
        MenuModalTypeInt modalDialog_5; // 0x0000006C length: 4
        MenuModalTypeInt modalDialog_6; // 0x00000070 length: 4
        int fileListEntryCount; // 0x00000074 length: 4
        undefined4 fileListSortOrder; // 0x00000078 length: 4
        int menuLoadGameRelativeSelectionIndex; // 0x0000007C length: 4
        int menuLoadGameRelativeSelectionOffset; // 0x00000080 length: 4
        int fileListVisibleRowCount; // 0x00000084 length: 4
        undefined4 DAT_SomeTextArrayIndex; // 0x00000088 length: 4
        undefined4 lastClickedListIndex; // 0x0000008C length: 4
        undefined4 lastListClickTime; // 0x00000090 length: 4
        undefined4 progressBarX; // 0x00000094 length: 4
        undefined4 progressBarY; // 0x00000098 length: 4
        undefined4 field42_0x9c; // 0x0000009C length: 4
        undefined4 previewedListIndex; // 0x000000A0 length: 4
        int field44_0xa4; // 0x000000A4 length: 4
        int dialogResult; // 0x000000A8 length: 4
        undefined4 field46_0xac; // 0x000000AC length: 4
        int DAT_ArrayOfMapU3EndInt2[500]; // 0x000000B0 length: 2000
        undefined4 DAT_MapSelectionPreloadMapIndexMapping; // 0x00000880 length: 4
        int DAT_ArrayOfMapIndices[500]; // 0x00000884 length: 2000
        undefined4 DAT_ArrayOfMapIndices2[500]; // 0x00001054 length: 2000
        undefined1 padding_0x1824[4]; // 0x00001824 length: 4

    private:
        MenuTextInputState(MenuTextInputState const&);
        void operator=(MenuTextInputState const&);

    public:
        MenuTextInputState() {};
        ~MenuTextInputState() {};

        // Constructor
        MenuTextInputState* Constructor_MenuTextInputState();

        void activateModalDialogAndClearText(MenuModalType dialogID);

        void clearModalDialog2to6();

        void clearAnyOtherModalDialogs();

        void meth_0x4917c0();

        void popModalDialog();

        void activateLoadOrSaveMapUI(int loadOrSaveMap);

        void loadOrSaveMap(MenuModalType param_1);

        void loadOrSaveGame(int action);
    };

    static_assert_cpp98_obj(sizeof(MenuTextInputState) == 6184, MenuTextInputState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
