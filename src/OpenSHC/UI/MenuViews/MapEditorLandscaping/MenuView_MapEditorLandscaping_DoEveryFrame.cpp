#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004313C0
        void MapEditorLandscaping::MenuView_MapEditorLandscaping_DoEveryFrame()
        {
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER) {
                return;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                return;
            }
            if (DAT_MinimapViewState::instance.field3_0xc == 0) {
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            } else if (DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated != 2)
                goto LAB_00431429;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, 3,
                DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y + 0x1b2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        LAB_00431429:
            DAT_MinimapViewState::instance.field0_0x0 = 1;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapLandscaping, DAT_MinimapViewState::ptr)(
                DAT_MenuHandlerState::instance.x + 0x298, DAT_MenuHandlerState::instance.y + 0x1d0, 0x80, 0x80);
        }

    }
}
}
