#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuHandlerState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildMenuTabType;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00433030
        void BuildMenu::MenuView_BuildMenu_DoEveryFrame()
        {
            DWORD _currentTime;
            if ((DAT_GameCore::instance.activeMenuTab.buildMenuTab != OpenSHC::UI::Enums::BMTT_MENU_HIDDEN)
                && (DAT_GameCore::instance.activeMenuTab.buildMenuTab
                    != (OpenSHC::UI::Enums::BuildMenuTabTypeShort)0x3e)) {
                if (DAT_MinimapViewState::instance.field3_0xc == 0) {
                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
                }
                if (DAT_MenuHandlerState::instance.isBuildMenuTransitioning_0x18 != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuHandlerState_Func::computeBuildMenuTransitionShift,
                        DAT_MenuHandlerState::ptr)();
                }
                if (DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated == 2) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, 2,
                            DAT_MenuHandlerState::instance.x, (int)((int)(DAT_MenuHandlerState::instance.y + 472)));
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                            DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x,
                            DAT_MenuHandlerState::instance.y + 0x196, DAT_MenuHandlerState::instance.x + 799,
                            DAT_MenuHandlerState::instance.y + 0x1d7,
                            (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                        if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, 5,
                                DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y + 0x1bd);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, 1,
                                DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y + 0x1c2);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                                DAT_TextureRenderCoreObject::ptr)(DAT_MenuHandlerState::instance.x + 0x11,
                                DAT_MenuHandlerState::instance.y + 0x1d9, DAT_MenuHandlerState::instance.x + 0x201,
                                DAT_MenuHandlerState::instance.y + 0x240);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_BUTTONS, 7,
                                (DAT_MenuHandlerState::instance.x
                                    - DAT_MenuHandlerState::instance.buildMenuBackgroundLeftShift_0x24)
                                    + 0x11,
                                DAT_MenuHandlerState::instance.y + 0x1d9);
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                                DAT_TextureRenderCoreObject::ptr)();
                        }
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                DAT_MinimapViewState::instance.field0_0x0 = 1;
                if (DAT_GameCore::instance.isBinkVideoPlaying == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MinimapViewState_Func::renderMinimapMain, DAT_MinimapViewState::ptr)();
                }
            }
            if (DAT_GameCore::instance.isVictoryOrDefeatUnk != 0) {
                DAT_GameCore::instance.isVictoryOrDefeatUnk = 0;
                DAT_GameState::instance.mapAndTime.gameOver = TRUE;
                _currentTime = timeGetTime();
                DAT_GameState::instance.mapAndTime.gameOverTime = _currentTime - 6000;
                DAT_GameState::instance.mapAndTime.playerIsAlive[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    = 1;
                DAT_GameCore::instance.skipStoreSKMasters = 1;
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
            }
            return;
        }

    }
}
}
