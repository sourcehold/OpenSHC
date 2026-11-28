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
            if (!DAT_TextEditorState::instance.useAlternateHelpTab) {
                // the help text is only scrolled: by a line (244, 245), a page (250, 251) or to an end (246, 247)
                int const key = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
                if (key < 240) {
                    return;
                }
                // 244, 247, 250 break to one store behind the switch; the rest store themselves (else the match drops)
                int offset;
                switch (key) {
                case 245:
                    offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (offset < max(DAT_TextEditorState::instance.topVisibleLineIndex
                                         - DAT_TextEditorState::instance.dialogContentHeight,
                                     0)
                            - 18) {
                        offset += 18;
                        if (offset > max(DAT_TextEditorState::instance.topVisibleLineIndex
                                    - DAT_TextEditorState::instance.dialogContentHeight,
                                0)) {
                            offset = max(DAT_TextEditorState::instance.topVisibleLineIndex
                                    - DAT_TextEditorState::instance.dialogContentHeight,
                                0);
                        }
                    } else {
                        offset = max(DAT_TextEditorState::instance.topVisibleLineIndex
                                - DAT_TextEditorState::instance.dialogContentHeight,
                            0);
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = offset;
                    return;
                case 244:
                    offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (offset >= 18) {
                        offset -= 18;
                    } else {
                        offset = 0;
                    }
                    break;
                case 246:
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                    return;
                case 247:
                    offset = max(DAT_TextEditorState::instance.topVisibleLineIndex
                            - DAT_TextEditorState::instance.dialogContentHeight,
                        0);
                    break;
                case 251:
                    offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (offset < max(DAT_TextEditorState::instance.topVisibleLineIndex
                                         - DAT_TextEditorState::instance.dialogContentHeight,
                                     0)
                            - DAT_TextEditorState::instance.dialogContentHeight) {
                        offset += DAT_TextEditorState::instance.dialogContentHeight;
                        if (offset > max(DAT_TextEditorState::instance.topVisibleLineIndex
                                    - DAT_TextEditorState::instance.dialogContentHeight,
                                0)) {
                            offset = max(DAT_TextEditorState::instance.topVisibleLineIndex
                                    - DAT_TextEditorState::instance.dialogContentHeight,
                                0);
                        }
                    } else {
                        offset = max(DAT_TextEditorState::instance.topVisibleLineIndex
                                - DAT_TextEditorState::instance.dialogContentHeight,
                            0);
                    }
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = offset;
                    return;
                case 250:
                    offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    if (offset >= DAT_TextEditorState::instance.dialogContentHeight) {
                        offset -= DAT_TextEditorState::instance.dialogContentHeight;
                    } else {
                        offset = 0;
                    }
                    break;
                default:
                    return;
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = offset;
                return;
            }
            int character = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::dequeueInputBufferChar, DAT_UserTextHandlerState::ptr)();
            if (character != -1) {
                if (character < 240) {
                    // a typed character: a pending token is stepped over first
                    if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(
                            (HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                        DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                    }
                    if (!DAT_TextEditorState::instance.isCustomTextMode
                        || DAT_TextEditorState::instance.customTextMaxLength < 0
                        || (int)wcslen(DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory)
                            < DAT_TextEditorState::instance.customTextMaxLength) {
                    insert:
                        for (int i = DAT_TextEditorState::instance.customHelpTextLength;
                            i >= DAT_TextEditorState::instance.activeHelpHotspotIndex; --i) {
                            DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i + 1]
                                = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i];
                        }
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::singleMultiByteToWideChar,
                                DAT_WideCharMultiByteState::ptr)((char)character);
                        ++DAT_TextEditorState::instance.customHelpTextLength;
                        ++DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    }
                } else {
                    switch (character) {
                    case 240:
                        if (!DAT_TextEditorState::instance.isCustomTextMode) {
                            character = OpenSHC::Text::Enums::HTT_TAB;
                            // to the one insert block: behind a flag the match is lower
                            goto insert;
                        }
                        break;
                    case 241:
                        if (!DAT_TextEditorState::instance.isCustomTextMode) {
                            character = OpenSHC::Text::Enums::HTT_NEWPARAGRAPH;
                            // as in 240
                            goto insert;
                        }
                        break;
                    case 242: {
                        // left; the cursor is re-read from the state, as in 243, 248, 249 (a local loses the match)
                        if (DAT_TextEditorState::instance.activeHelpHotspotIndex > 0) {
                            int const token = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                                  [DAT_TextEditorState::instance.activeHelpHotspotIndex - 1];
                            if (token >= 32) {
                                --DAT_TextEditorState::instance.activeHelpHotspotIndex;
                            } else {
                                DAT_TextEditorState::instance.activeHelpHotspotIndex -= MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)((HelpTextToken)token);
                            }
                        }
                        break;
                    }
                    case 243: {
                        // right
                        if (DAT_TextEditorState::instance.activeHelpHotspotIndex
                            < DAT_TextEditorState::instance.customHelpTextLength) {
                            int const token = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                                  [DAT_TextEditorState::instance.activeHelpHotspotIndex];
                            if (token >= 32) {
                                ++DAT_TextEditorState::instance.activeHelpHotspotIndex;
                            } else {
                                DAT_TextEditorState::instance.activeHelpHotspotIndex += MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                    DAT_TextEditorState::ptr)((HelpTextToken)token);
                            }
                        }
                        break;
                    }
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
                    case 248: {
                        // removes what stands in front of the cursor: the rest moves down, the terminator included
                        if (DAT_TextEditorState::instance.activeHelpHotspotIndex > 0) {
                            int const advance = MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                                DAT_TextEditorState::ptr)(
                                (HelpTextToken)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.activeHelpHotspotIndex - 1]);
                            for (int i = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                                i < DAT_TextEditorState::instance.customHelpTextLength + advance; ++i) {
                                DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i - advance]
                                    = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i];
                                if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i] == L'\0') {
                                    break;
                                }
                            }
                            DAT_TextEditorState::instance.customHelpTextLength -= advance;
                            DAT_TextEditorState::instance.activeHelpHotspotIndex -= advance;
                        }
                        break;
                    }
                    case 249: {
                        // removes what stands at the cursor
                        int const advance = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)((HelpTextToken)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance
                                        .activeHelpHotspotIndex]);
                        if (DAT_TextEditorState::instance.activeHelpHotspotIndex
                            < DAT_TextEditorState::instance.customHelpTextLength) {
                            for (int i = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                                i < DAT_TextEditorState::instance.customHelpTextLength + advance; ++i) {
                                DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i]
                                    = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i + advance];
                                if (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory[i] == L'\0') {
                                    break;
                                }
                            }
                            DAT_TextEditorState::instance.customHelpTextLength -= advance;
                        }
                        break;
                    }
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
            }
            if (DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                < 32) {
                DAT_TextEditorState::instance.field_0x23970
                    = DAT_TextEditorState::instance
                          .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex];
                return;
            }
            DAT_TextEditorState::instance.field_0x23970 = 0;
        }

    }
}
}
