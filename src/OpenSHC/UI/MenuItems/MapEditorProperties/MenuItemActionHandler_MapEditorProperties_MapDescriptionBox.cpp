#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95f68.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042EDF0
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MapDescriptionBox()
        {
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti && DAT_GameCore::instance.mapLoadedForEditor
                && DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE
                && (INT_00b95f68::instance = 1, !DAT_GameCore::instance.unknownAlwaysZero03)) {
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                DAT_TextEditorState::instance.customTextMaxLength = 1000;
                MACRO_CALL_MEMBER(Text::TextEditorState_Func::openMapDescriptionEditorDialog, DAT_TextEditorState::ptr)(
                    0);
                MACRO_CALL_MEMBER(Text::TextEditorState_Func::setCustomHelpText, DAT_TextEditorState::ptr)(
                    DAT_GameCore::instance.temporaryTextBufferOfSize1000, 999);
                MACRO_CALL(OS_Func::_memset)(DAT_GameCore::instance.temporaryTextBufferOfSize1000, 0, 1000);
                DAT_GameCore::instance.descriptionUseStringTable = 0;
            }
        }

    }
}
}
