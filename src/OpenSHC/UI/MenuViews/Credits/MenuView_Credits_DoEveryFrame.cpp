#include "../Credits.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95954.hpp"
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
#include "OpenSHC/Globals/INT_00b960d0.hpp"
#include "OpenSHC/Globals/INT_00b960d4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00426340
        void Credits::MenuView_Credits_DoEveryFrame()
        {
            SHORT SVar1;
            DWORD DVar2;
            int iVar3;
            int left;
            int top;
            int bottom;
            DVar2 = timeGetTime();
            if (DAT_00b9610c::instance < 1) {
                if (DAT_00b9610c::instance < 0) {
                    DAT_00b95b70::instance = 0x20 - (int)(DVar2 - INT_00b960d0::instance) / 0x32;
                    DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
                    if (DAT_00b95b70::instance < 1) {
                        DAT_00b95b3c::instance = DAT_00b95b3c::instance + 1;
                        DAT_00b9610c::instance = 1;
                        DAT_00b95b70::instance = 0;
                        INT_00b960d0::instance = DVar2;
                        if (3 < DAT_00b95b3c::instance) {
                            DAT_00b95b3c::instance = 0;
                        }
                    }
                } else if (20000 < (int)(DVar2 - INT_00b960d0::instance) && !DAT_00b95954::instance) {
                    DAT_00b9610c::instance = -1;
                    INT_00b960d0::instance = DVar2;
                }
            } else {
                DAT_00b95b70::instance = (int)(DVar2 - INT_00b960d0::instance) / 0x32;
                DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
                if (0x1f < DAT_00b95b70::instance) {
                    DAT_00b9610c::instance = 0;
                    INT_00b960d0::instance = DVar2;
                }
            }
            SVar1 = GetAsyncKeyState(VK_DOWN);
            if (SVar1) {
                if (!DAT_ModifierKeyState::instance.shift) {
                    INT_00b960d4::instance = INT_00b960d4::instance + -0x3c;
                } else {
                    INT_00b960d4::instance = INT_00b960d4::instance + -200;
                }
            }
            iVar3 = (int)(DVar2 - INT_00b960d4::instance) / 0x1e + -600;
            if (iVar3 == DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                if (!DAT_TextEditorState::instance.pendingCreditsFadeBorder)
                    goto LAB_0042653a;
            } else {
                DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar3;
                if (DAT_TextEditorState::instance.topVisibleLineIndex < iVar3) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = -600;
                    INT_00b960d4::instance = DVar2;
                }
                DAT_TextEditorState::instance.pendingCreditsFadeBorder = TRUE;
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(DAT_00b95b3c::instance,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if (DAT_00b95b70::instance < 0x20) {
                timeGetTime();
                if (!DAT_00b95954::instance) {
                    iVar3 = DAT_MenuHandlerState::instance.x + 800;
                    left = DAT_MenuHandlerState::instance.x;
                    top = DAT_MenuHandlerState::instance.y;
                    bottom = DAT_MenuHandlerState::instance.y + 600;
                } else {
                    iVar3 = DAT_WindowAndDirectDraw::instance.resolutionX / 2;
                    top = 0;
                    left = 0;
                    bottom = DAT_WindowAndDirectDraw::instance.resolutionY;
                }
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    left, top, iVar3, bottom, DAT_00b95b70::instance);
            }
        LAB_0042653a:
            if (DAT_MouseState::instance.leftClickStart) {
                MACRO_CALL_MEMBER(
                    Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
            }
            return;
        }

    }
}
}
