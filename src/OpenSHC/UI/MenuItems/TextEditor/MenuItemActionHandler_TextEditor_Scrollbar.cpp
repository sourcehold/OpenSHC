#include "../TextEditor.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0045EDF0
        void TextEditor::MenuItemActionHandler_TextEditor_Scrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            // the arrows scroll a twentieth of the text, at least one line
            int const step = max(max(DAT_TextEditorState::instance.topVisibleLineIndex
                                         - DAT_TextEditorState::instance.dialogContentHeight,
                                     0)
                    / 20,
                1);
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = max(DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight,
                    0);
                // clamped again after max, as the original does (without it: quick_diff 1.0000 -> 0.7126)
                if (*maxValue < 0) {
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
                *maxValue = max(DAT_TextEditorState::instance.topVisibleLineIndex
                        - DAT_TextEditorState::instance.dialogContentHeight,
                    0);
                return;
            case 7:
                *currentValue = DAT_TextEditorState::instance.dialogContentHeight - 20;
                return;
            case 5: {
                // one step up
                int offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                if (offset >= step) {
                    offset -= step;
                } else {
                    offset = 0;
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = offset;
                *currentValue = offset;
                return;
            }
            case 6: {
                // one step down
                int offset = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                if (offset < max(DAT_TextEditorState::instance.topVisibleLineIndex
                                     - DAT_TextEditorState::instance.dialogContentHeight,
                                 0)
                        - step) {
                    offset += step;
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
                *currentValue = offset;
                return;
            }
            }
        }

    }
}
}
