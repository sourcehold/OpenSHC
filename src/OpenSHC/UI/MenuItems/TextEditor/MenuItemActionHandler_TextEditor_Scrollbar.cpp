#include "../TextEditor.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0045EDF0
        void TextEditor::MenuItemActionHandler_TextEditor_Scrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            uint uVar2;
            uVar2
                = DAT_TextEditorState::instance.topVisibleLineIndex - DAT_TextEditorState::instance.dialogContentHeight;
            if ((int)(((int)uVar2 < 1) - 1 & uVar2) / 0x14 < 2) {
                iVar1 = 1;
            } else {
                iVar1 = (int)(((int)uVar2 < 1) - 1 & uVar2) / 0x14;
            }
            switch (param_2) {
            case 1:
                *minValue = 0;
                uVar2 = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight
                    & (DAT_TextEditorState::instance.topVisibleLineIndex
                              - DAT_TextEditorState::instance.dialogContentHeight
                          < 1)
                        - 1;
                *maxValue = uVar2;
                if ((int)uVar2 < 0) {
                    *maxValue = 0;
                }
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                return;
            case 2:
            case 3:
                DAT_TextEditorState::instance.helpContentScrollOffsetY = *currentValue;
                return;
            case 4:
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                *maxValue = DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight
                    & (DAT_TextEditorState::instance.topVisibleLineIndex
                              - DAT_TextEditorState::instance.dialogContentHeight
                          < 1)
                        - 1;
                return;
            case 5:
                break;
            case 6:
                if ((int)DAT_TextEditorState::instance.helpContentScrollOffsetY
                    < (int)((((int)uVar2 < 1) - 1 & uVar2) - iVar1)) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + iVar1;
                    if ((int)(((int)uVar2 < 1) - 1 & uVar2)
                        < (int)DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = ((int)uVar2 < 1) - 1 & uVar2;
                        *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                    }
                } else {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = ((int)uVar2 < 1) - 1 & uVar2;
                }
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                return;
            case 7:
                *currentValue = DAT_TextEditorState::instance.dialogContentHeight + -0x14;
                return;
            default:
                break;
            }
            if (iVar1 <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                DAT_TextEditorState::instance.helpContentScrollOffsetY
                    = DAT_TextEditorState::instance.helpContentScrollOffsetY - iVar1;
                *currentValue = DAT_TextEditorState::instance.helpContentScrollOffsetY;
            }
            DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
            *currentValue = 0;
        }

    }
}
}
