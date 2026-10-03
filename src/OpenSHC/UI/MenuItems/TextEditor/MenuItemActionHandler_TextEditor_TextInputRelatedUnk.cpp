#include "../TextEditor.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextToken.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::Enums::HelpTextToken;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00461570
        void TextEditor::MenuItemActionHandler_TextEditor_TextInputRelatedUnk()
        {
            WCHAR WVar1;
            uint uVar2;
            int iVar3;
            WCHAR* pWVar4;
            int iVar5;
            int iVar6;
            WCHAR* pWVar7;
            if (DAT_TextEditorState::instance.useAlternateHelpTab == 0) {
                uVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
                if ((int)uVar2 < 0xf0) {}
                switch (uVar2) {
                case 0xf4:
                    if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY < 0x12) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + -0x12;
                    return;
                case 0xf5:
                    uVar2 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    if ((int)((((int)uVar2 < 1) - 1 & uVar2) - 0x12)
                        <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)
                        goto LAB_004615e1;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + 0x12;
                    break;
                case 0xf6:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 0xf7:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.topVisibleLineIndex
                            - DAT_TextEditorState::instance.dialogContentHeight
                        & (DAT_TextEditorState::instance.topVisibleLineIndex
                                  - DAT_TextEditorState::instance.dialogContentHeight
                              < 1)
                            - 1;
                    return;
                default:
                    break;
                case 0xfa:
                    if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY
                        < DAT_TextEditorState::instance.dialogContentHeight) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    return;
                case 0xfb:
                    uVar2 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    if ((int)((((int)uVar2 < 1) - 1 & uVar2) - DAT_TextEditorState::instance.dialogContentHeight)
                        <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)
                        goto LAB_004615e1;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY
                        + DAT_TextEditorState::instance.dialogContentHeight;
                }
                if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY
                    <= (int)(((int)uVar2 < 1) - 1 & uVar2)) {}
            LAB_004615e1:
                DAT_TextEditorState::instance.helpContentScrollOffsetY = ((int)uVar2 < 1) - 1 & uVar2;
            }
            uVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
            iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
            if (uVar2 != 0xffffffff) {
                if ((int)uVar2 < 0xf0) {
                    if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                        iVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(
                            (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar3;
                        DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                    }
                    if ((DAT_TextEditorState::instance.isCustomTextMode != 0)
                        && (-1 < DAT_TextEditorState::instance.customTextMaxLength)) {
                        pWVar4 = pWVar7;
                        do {
                            WVar1 = *pWVar4;
                            pWVar4 = pWVar4 + 1;
                        } while (WVar1 != L'\0');
                        if (DAT_TextEditorState::instance.customTextMaxLength <= (int)pWVar4 - (int)(pWVar7 + 1) >> 1)
                            goto switchD_00461715_caseD_a;
                    }
                LAB_004616f7:
                    iVar3 = DAT_TextEditorState::instance.customHelpTextLength;
                    if (DAT_TextEditorState::instance.activeHelpHotspotIndex
                        <= DAT_TextEditorState::instance.customHelpTextLength) {
                        do {
                            pWVar7[iVar3 + 1] = pWVar7[iVar3];
                            iVar3 = iVar3 + -1;
                            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        } while (DAT_TextEditorState::instance.activeHelpHotspotIndex <= iVar3);
                    }
                    WVar1 = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::singleMultiByteToWideChar,
                        DAT_WideCharMultiByteState::ptr)((char)uVar2);
                    /*
                      put character in memory
                     */
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = WVar1;
                    DAT_TextEditorState::instance.customHelpTextLength
                        = DAT_TextEditorState::instance.customHelpTextLength + 1;
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + 1;
                } else {
                    switch (uVar2) {
                    case 0xf0:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 9;
                            goto LAB_004616f7;
                        }
                        break;
                    case 0xf1:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 6;
                            goto LAB_004616f7;
                        }
                        break;
                    case 0xf2:
                        if (0 < DAT_TextEditorState::instance.activeHelpHotspotIndex) {
                            if ((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.activeHelpHotspotIndex + -1]
                                < ((HelpTextToken)0x20)) {
                                iVar5 = MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)
                                        DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                            [DAT_TextEditorState::instance.activeHelpHotspotIndex + -1]);
                                DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 - iVar5;
                            } else {
                                DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    = DAT_TextEditorState::instance.activeHelpHotspotIndex + -1;
                            }
                        }
                        break;
                    case 0xf3:
                        if (DAT_TextEditorState::instance.activeHelpHotspotIndex
                            < DAT_TextEditorState::instance.customHelpTextLength) {
                            if ((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.activeHelpHotspotIndex]
                                < ((HelpTextToken)0x20)) {
                                iVar5 = MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)(
                                    (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                                .activeHelpHotspotIndex]);
                                DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + iVar5;
                            } else {
                                DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    = DAT_TextEditorState::instance.activeHelpHotspotIndex + 1;
                            }
                        }
                        break;
                    case 0xf4:
                        DAT_TextEditorState::instance.field51_0x2396c = -1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf5:
                        DAT_TextEditorState::instance.field51_0x2396c = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 0xf6:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = 0;
                        break;
                    case 0xf7:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.customHelpTextLength;
                        break;
                    case 0xf8:
                        if (0 < DAT_TextEditorState::instance.activeHelpHotspotIndex) {
                            iVar5 = MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)
                                    DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + -1]);
                            if (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5) {
                                iVar6 = (iVar3 - iVar5) * 2;
                                do {
                                    /*
                                      delete character in memory
                                     */
                                    *(WCHAR*)(iVar6 + (int)pWVar7) = pWVar7[iVar3];
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    iVar3 = iVar3 + 1;
                                    iVar6 = iVar6 + 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.customHelpTextLength
                                = DAT_TextEditorState::instance.customHelpTextLength - iVar5;
                            DAT_TextEditorState::instance.activeHelpHotspotIndex
                                = DAT_TextEditorState::instance.activeHelpHotspotIndex - iVar5;
                        }
                        break;
                    case 0xf9:
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                        .activeHelpHotspotIndex]);
                        if (iVar3 < DAT_TextEditorState::instance.customHelpTextLength) {
                            if (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5) {
                                iVar6 = (iVar3 + iVar5) * 2;
                                do {
                                    pWVar7[iVar3] = *(WCHAR*)(iVar6 + (int)pWVar7);
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    iVar3 = iVar3 + 1;
                                    iVar6 = iVar6 + 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.customHelpTextLength
                                = DAT_TextEditorState::instance.customHelpTextLength - iVar5;
                        }
                    }
                }
            switchD_00461715_caseD_a:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
            }
            if ((ushort)DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                < 0x20) {
                DAT_TextEditorState::instance.field52_0x23970
                    = (uint)(ushort)DAT_TextEditorState::instance
                          .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex];
            }
            DAT_TextEditorState::instance.field52_0x23970 = 0;
        }

    }
}
}
