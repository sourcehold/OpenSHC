#include "../GameStartEnterName.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424B10
        void GameStartEnterName::MenuView_GameStartEnterName_DoEveryFrame()
        {
            // == TRUE as in the original, which compares with 1 (truthiness: quick_diff 0.9375 -> 0.8542)
            if (DAT_GameCore::instance.isNameEntryActive == TRUE) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            // the original tests the flag again after the draw call; nothing sets it there, so this branch does not run
            if (DAT_GameCore::instance.isNameEntryActive == TRUE) {
                // after a second, once draggingStopped is set or on a right click, back to the main menu
                DWORD const now = timeGetTime();
                if (now - DAT_GameCore::instance.nameEntryStartTime <= 1000 && !DAT_MouseState::instance.draggingStopped
                    && !DAT_MouseState::instance.rightClickStop) {
                    return;
                }
            } else {
                // return pressed: close the dialog and go to the main menu
                // read, cleared, then tested (testing the field itself: quick_diff 0.9375 -> 0.9053)
                dword const returnPressed = DAT_UserTextHandlerState::instance.returnPressed;
                DAT_UserTextHandlerState::instance.returnPressed = 0;
                if (returnPressed == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
        }

    }
}
}
