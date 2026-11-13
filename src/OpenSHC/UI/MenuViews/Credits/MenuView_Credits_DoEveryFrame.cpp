#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuViews/Credits.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b95b3c.hpp"
#include "OpenSHC/Globals/DAT_00b95b70.hpp"
#include "OpenSHC/Globals/DAT_00b9610c.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95954.hpp"
#include "OpenSHC/Globals/INT_00b960d0.hpp"
#include "OpenSHC/Globals/INT_00b960d4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Credits {

            // FUNCTION: STRONGHOLDCRUSADER 0x00426340
            void MenuView_Credits_DoEveryFrame()
            {
                DWORD now = timeGetTime();
                if ((int)DAT_00b9610c::instance > 0) {
                    int fade = (int)(now - INT_00b960d0::instance) / 50;
                    DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
                    DAT_00b95b70::instance = fade;
                    if (fade >= 32) {
                        DAT_00b9610c::instance = 0;
                        INT_00b960d0::instance = now;
                    }
                } else if ((int)DAT_00b9610c::instance < 0) {
                    int fade = 32 - (int)(now - INT_00b960d0::instance) / 50;
                    DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
                    DAT_00b95b70::instance = fade;
                    if (fade <= 0) {
                        INT_00b960d0::instance = now;
                        DAT_00b9610c::instance = 1;
                        DAT_00b95b70::instance = 0;
                        DAT_00b95b3c::instance += 1;
                        if ((int)DAT_00b95b3c::instance >= 4) {
                            DAT_00b95b3c::instance = 0;
                        }
                    }
                } else if ((int)(now - INT_00b960d0::instance) > 20000 && INT_00b95954::instance == 0) {
                    DAT_00b9610c::instance = -1;
                    INT_00b960d0::instance = now;
                }
                if (GetAsyncKeyState(VK_DOWN)) {
                    if (DAT_ModifierKeyState::instance.shift != 0) {
                        INT_00b960d4::instance -= 200;
                    } else {
                        INT_00b960d4::instance -= 60;
                    }
                }
                int scrollOffset = (int)(now - INT_00b960d4::instance) / 30 - 600;
                if (scrollOffset != DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = scrollOffset;
                    if (scrollOffset > DAT_TextEditorState::instance.topVisibleLineIndex) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = -600;
                        INT_00b960d4::instance = now;
                    }
                    DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
                }
                if (DAT_TextEditorState::instance.pendingCreditsFadeBorder != FALSE) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                        DAT_TextureRenderCoreObject::ptr)(DAT_00b95b3c::instance,
                        (DAT_WindowAndDirectDraw::instance.resolutionX
                            - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                            / 2,
                        (DAT_WindowAndDirectDraw::instance.resolutionY
                            - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                            / 2);
                    if ((int)DAT_00b95b70::instance < 32) {
                        timeGetTime();
                        if (INT_00b95954::instance == 0) {
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                                DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x,
                                DAT_MenuHandlerState::instance.y, DAT_MenuHandlerState::instance.x + 800,
                                DAT_MenuHandlerState::instance.y + 600, DAT_00b95b70::instance);
                        } else {
                            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                                DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX / 2,
                                DAT_WindowAndDirectDraw::instance.resolutionY, DAT_00b95b70::instance);
                        }
                    }
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    MACRO_CALL_MEMBER(
                        Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_MAIN_MENU, 0);
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                }
            }

        }
    }
}
}
