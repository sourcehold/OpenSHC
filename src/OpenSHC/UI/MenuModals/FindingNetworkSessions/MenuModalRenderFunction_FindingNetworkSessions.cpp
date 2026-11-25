#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/UI_NetworkSessionsShadeLogic.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047D190
        void FindingNetworkSessions::MenuModalRenderFunction_FindingNetworkSessions(int x, int y, int width, int height)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            // "Finding Sessions"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 11, x, y, width, height);
            // the session list: box, outline, scroll column and squares, all from the four edges in a block. In 21 of
            // the other 23 orders, or with top, bottom, right, right + 1 and left - 1 as locals, the listing differs
            {
                int const left = x + 40;
                int const top = y + 85;
                int const right = x + 460;
                int const bottom = y + 285;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top + 20, right + 1, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    right - 19, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            }
            // The searching animation, a frame every second call
            int const shadeTick = UI_NetworkSessionsShadeLogic::instance + 1;
            UI_NetworkSessionsShadeLogic::instance = shadeTick;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                DAT_ProtocolDefinedData::instance.field_0x474[shadeTick / 2 % 32] + 398, width / 2 - 14 + x, y + 312);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameSynchronyState::instance.scrollBarIndex == -1
                && DAT_GameSynchronyState::instance.DPLAY_SessionsCount != 0) {
                DAT_GameSynchronyState::instance.scrollBarIndex = 0;
            }
        }

    }
}
}
