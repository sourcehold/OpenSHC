#include "../GameStartEnterName.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00424B10
        void GameStartEnterName::MenuView_GameStartEnterName_DoEveryFrame()
        {
            if (DAT_GameCore::instance.isNameEntryActive != TRUE) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface, DAT_TextureRenderCoreObject::ptr)(0,
                    (DAT_WindowAndDirectDraw::instance.resolutionX
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2,
                    (DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                        / 2);
                if (DAT_GameCore::instance.isNameEntryActive == TRUE) {
                    DWORD DVar1 = timeGetTime();
                    if ((DVar1 - DAT_GameCore::instance.nameEntryStartTime < 0x3e9)
                        && (!DAT_MouseState::instance.draggingStopped)) {
                        if (!DAT_MouseState::instance.rightClickStop) {
                            return;
                        }
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_MAIN_MENU, 0);
                        return;
                    }
                } else {
                    bool bVar2 = DAT_UserTextHandlerState::instance.returnPressed == 0;
                    DAT_UserTextHandlerState::instance.returnPressed = 0;
                    if (bVar2) {
                        DAT_UserTextHandlerState::instance.returnPressed = 0;
                        return;
                    }
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                }
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
            }
            return;
        }

    }
}
}
