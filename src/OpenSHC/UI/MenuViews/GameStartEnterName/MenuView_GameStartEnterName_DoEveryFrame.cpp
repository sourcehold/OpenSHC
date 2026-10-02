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

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00424B10
        void GameStartEnterName::MenuView_GameStartEnterName_DoEveryFrame()
        {
            DWORD DVar1;
            bool bVar2;
            if (DAT_GameCore::instance.unknownFlag_0x118 != TRUE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                    DAT_TextureRenderCoreObject::ptr)(0,
                    (DAT_WindowAndDirectDraw::instance.resolutionX
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2,
                    (DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                        / 2);
                if (DAT_GameCore::instance.unknownFlag_0x118 == TRUE) {
                    DVar1 = timeGetTime();
                    if ((DVar1 - DAT_GameCore::instance.unknownTime_0x11c < 0x3e9)
                        && (DAT_MouseState::instance.draggingStopped == FALSE)) {
                        if (DAT_MouseState::instance.rightClickStop == 0) {
                            return;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                        return;
                    }
                } else {
                    bVar2 = DAT_UserTextHandlerState::instance.returnPressed == 0;
                    DAT_UserTextHandlerState::instance.returnPressed = 0;
                    if (bVar2) {
                        DAT_UserTextHandlerState::instance.returnPressed = 0;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
            }
            return;
        }

    }
}
}
