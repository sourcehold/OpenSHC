#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047C860
        void ChooseNetworkServiceProvider::MenuModalRenderFunction_ChooseNetworkServiceProvider(
            int x, int y, int width, int height)
        {
            // "Service Providers"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 6, x, y, width, height);
            if (DAT_GameSynchronyState::instance.kickedAtTime != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x, y - 60, x + width, y - 18, 16);
                // "You Were Ejected!"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 92),
                    width / 2 + x, y - 50, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE,
                    0);
                if (timeGetTime() - DAT_GameSynchronyState::instance.kickedAtTime > 5000) {
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                }
            }
            // the list: a dimmed box, its outline and the scroll bar's column, every coordinate from the four edges in
            // a block of their own: with only the top, the bottom and left - 1 as locals, x and y swap registers
            {
                int const left = x + 40;
                int const top = y + 85;
                int const right = x + 460;
                int const bottom = y + 165;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                // the modem's box below it, drawn the same way, from its own four edges: with y moved on to the
                // bottom and x to the outline's right edge, the box's top and left edge get each other's registers
                int const left = x + 40;
                int const top = y + 265;
                int const right = x + 460;
                int const bottom = y + 345;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }
        }
    }
}
}
