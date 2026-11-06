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
                if ((int)uVar2 < 240) {
                    return;
                }
                switch (uVar2) {
                case 245:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (iVar3 < ((iVar5 <= 0) - 1 & iVar5) - 18) {
                        iVar3 += 18;
                        if (((iVar5 <= 0) - 1 & iVar5) < iVar3) {
                            iVar3 = (iVar5 <= 0) - 1 & iVar5;
                        }
                    } else {
                        iVar3 = (iVar5 <= 0) - 1 & iVar5;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                    return;
                case 244:
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (18 <= iVar3) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3 - 18;
                        return;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 246:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 247:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = (iVar5 <= 0) - 1 & iVar5;
                    return;
                case 251:
                    iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight;
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (iVar3 < ((iVar5 <= 0) - 1 & iVar5) - DAT_TextEditorState::instance.dialogContentHeight) {
                        iVar3 += DAT_TextEditorState::instance.dialogContentHeight;
                        if (((iVar5 <= 0) - 1 & iVar5) < iVar3) {
                            iVar3 = (iVar5 <= 0) - 1 & iVar5;
                        }
                    } else {
                        iVar3 = (iVar5 <= 0) - 1 & iVar5;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                    return;
                case 250:
                    iVar3 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    iVar6 = DAT_TextEditorState::instance.dialogContentHeight;
                    if (iVar3 >= iVar6) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3 - iVar6;
                        return;
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                default:
                    return;
                }
            }
            uVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
            iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
            if (uVar2 != -1) {
                if ((int)uVar2 < 240) {
                    if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                        iVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(
                            (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar3;
                        DAT_TextEditorState::instance.pendingTokenTypeToSkip = (OpenSHC::Text::Enums::HTT_NONE);
                    }
                    if ((DAT_TextEditorState::instance.isCustomTextMode != 0)
                        && (-1 < DAT_TextEditorState::instance.customTextMaxLength)) {
                        pWVar4 = pWVar7;
                        do {
                            WVar1 = *pWVar4;
                            ++pWVar4;
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
                            --iVar3;
                            pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        } while (iVar3 >= DAT_TextEditorState::instance.activeHelpHotspotIndex);
                    }
                    WVar1 = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::singleMultiByteToWideChar,
                        DAT_WideCharMultiByteState::ptr)((char)uVar2);
                    // put character in memory
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = WVar1;
                    ++DAT_TextEditorState::instance.customHelpTextLength;
                    ++DAT_TextEditorState::instance.activeHelpHotspotIndex;
                } else {
                    switch (uVar2) {
                    case 240:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 9;
                            goto LAB_004616f7;
                        }
                        break;
                    case 241:
                        if (DAT_TextEditorState::instance.isCustomTextMode == 0) {
                            uVar2 = 6;
                            goto LAB_004616f7;
                        }
                        break;
                    case 242:
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 <= 0)
                            break;
                        iVar6 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3 - 1];
                        if (32 <= iVar6) {
                            DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 - 1;
                            break;
                        }
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 - iVar5;
                        break;
                    case 243:
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 >= DAT_TextEditorState::instance.customHelpTextLength)
                            break;
                        iVar6 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3];
                        if (32 <= iVar6) {
                            DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + 1;
                            break;
                        }
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = iVar3 + iVar5;
                        break;
                    case 244:
                        DAT_TextEditorState::instance.field_0x2396c = -1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 245:
                        DAT_TextEditorState::instance.field_0x2396c = 1;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                        break;
                    case 246:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex = 0;
                        break;
                    case 247:
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.customHelpTextLength;
                        break;
                    case 248:
                        iVar3 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                        if (iVar3 <= 0)
                            break;
                        pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                        iVar6 = pWVar7[iVar3 - 1];
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)iVar6);
                        if (DAT_TextEditorState::instance.customHelpTextLength > iVar3 + iVar5) {
                            iVar6 = (iVar3 - iVar5) * 2;
                            do {
                                // delete character in memory
                                *(WCHAR*)(iVar6 + (int)pWVar7) = pWVar7[iVar3];
                                pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                if (pWVar7[iVar3] == L'\0')
                                    break;
                                ++iVar3;
                                iVar6 += 2;
                            } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                        }
                        DAT_TextEditorState::instance.customHelpTextLength -= iVar5;
                        DAT_TextEditorState::instance.activeHelpHotspotIndex -= iVar5;
                        break;
                    case 249:
                        iVar5 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                        .activeHelpHotspotIndex]);
                        if (iVar3 < DAT_TextEditorState::instance.customHelpTextLength) {
                            if (DAT_TextEditorState::instance.customHelpTextLength > iVar3 + iVar5) {
                                iVar6 = (iVar3 + iVar5) * 2;
                                do {
                                    pWVar7[iVar3] = *(WCHAR*)(iVar6 + (int)pWVar7);
                                    if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[iVar3] == L'\0')
                                        break;
                                    ++iVar3;
                                    iVar6 += 2;
                                    pWVar7 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                                } while (iVar3 < DAT_TextEditorState::instance.customHelpTextLength + iVar5);
                            }
                            DAT_TextEditorState::instance.customHelpTextLength -= iVar5;
                        }
                    }
                }
            switchD_00461715_caseD_a:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
            }
            if ((ushort)DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                < 32) {
                DAT_TextEditorState::instance.field_0x23970
                    = (uint)(ushort)DAT_TextEditorState::instance
                          .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex];
                return;
            }
            DAT_TextEditorState::instance.field_0x23970 = 0;
        }

    }
}
}
