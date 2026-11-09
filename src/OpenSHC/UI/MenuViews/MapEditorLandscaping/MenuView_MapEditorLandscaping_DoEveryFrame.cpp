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

        // FUNCTION: STRONGHOLDCRUSADER 0x004313C0
        void MapEditorLandscaping::MenuView_MapEditorLandscaping_DoEveryFrame()
        {
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                || DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                return;
            }
            if (DAT_MinimapViewState::instance.field_0xc == 0) {
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            }
            if (DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated == 2) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, 3,
                    DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y + 434);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_MinimapViewState::instance.needsRedraw = TRUE;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapLandscaping, DAT_MinimapViewState::ptr)(
                DAT_MenuHandlerState::instance.x + 664, DAT_MenuHandlerState::instance.y + 464, 128, 128);
        }

    }
}
}
