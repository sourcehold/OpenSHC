#include "../Rendering.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/TIME_LoadSaveBar.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00493690
    void Rendering::RenderLoadAndSaveBar(int progressValueUnk)
    {
        DWORD const currentTime = timeGetTime();
        if ((int)(currentTime - TIME_LoadSaveBar::instance) <= 30) {
            return;
        }
        TIME_LoadSaveBar::instance = currentTime;
        int const barWidth = (progressValueUnk * 300) / 1000;
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_MenuTextInputState::instance.progressBarX, DAT_MenuTextInputState::instance.progressBarY,
                DAT_MenuTextInputState::instance.progressBarX + barWidth,
                DAT_MenuTextInputState::instance.progressBarY + 15, COL_VERY_SOFT_YELLOW::instance.shortValue);
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                DAT_WindowAndDirectDraw::instance.pendingBltMode = 2;
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    DAT_WindowAndDirectDraw::instance.pendingBltMode = 1;
                }
            } else {
                DAT_WindowAndDirectDraw::instance.pendingBltMode = 1;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(1);
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_MenuTextInputState::instance.progressBarX, DAT_MenuTextInputState::instance.progressBarY,
                DAT_MenuTextInputState::instance.progressBarX + barWidth,
                DAT_MenuTextInputState::instance.progressBarY + 15, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                DAT_WindowAndDirectDraw::ptr)(DAT_MenuTextInputState::instance.progressBarX,
                DAT_MenuTextInputState::instance.progressBarY, DAT_MenuTextInputState::instance.progressBarX + 300,
                DAT_MenuTextInputState::instance.progressBarY + 15);
        }
    }

}
}
