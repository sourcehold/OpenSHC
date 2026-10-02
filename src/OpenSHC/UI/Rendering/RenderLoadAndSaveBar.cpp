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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00493690
    void Rendering::RenderLoadAndSaveBar(int progressValueUnk)
    {
        int iVar1;
        DWORD _currentTime;
        BOOLEnum _areWeInAnInGameMenu;
        _currentTime = timeGetTime();
        if (0x1e < (int)(_currentTime - TIME_LoadSaveBar::instance)) {
            iVar1 = (progressValueUnk * 300) / 1000;
            TIME_LoadSaveBar::instance = _currentTime;
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu != FALSE) {
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_MenuTextInputState::instance.field40_0x94,
                    (int)((int)(DAT_MenuTextInputState::instance.field41_0x98)),
                    DAT_MenuTextInputState::instance.field40_0x94 + iVar1,
                    (int)((int)(DAT_MenuTextInputState::instance.field41_0x98 + 0xf)),
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                if (((DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                            != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD))
                    || (DAT_WindowAndDirectDraw::instance.mbr_0xd0 = 2,
                        DAT_GameCore::instance.currentMenuViewType
                            == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)) {
                    DAT_WindowAndDirectDraw::instance.mbr_0xd0 = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip,
                    DAT_WindowAndDirectDraw::ptr)(1);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_MenuTextInputState::instance.field40_0x94,
                (int)((int)(DAT_MenuTextInputState::instance.field41_0x98)),
                DAT_MenuTextInputState::instance.field40_0x94 + iVar1,
                (int)((int)(DAT_MenuTextInputState::instance.field41_0x98 + 0xf)),
                (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltScreenMenuSurfaceToScreen,
                DAT_WindowAndDirectDraw::ptr)(DAT_MenuTextInputState::instance.field40_0x94,
                (int)((int)(DAT_MenuTextInputState::instance.field41_0x98)),
                (int)((int)(DAT_MenuTextInputState::instance.field40_0x94 + 300)),
                (int)((int)(DAT_MenuTextInputState::instance.field41_0x98 + 0xf)));
        }
    }

}
}
