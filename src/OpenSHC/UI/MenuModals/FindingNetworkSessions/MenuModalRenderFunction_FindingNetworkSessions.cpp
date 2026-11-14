#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
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
                DAT_PencilRenderCore::ptr)(76, 11, x, y, width, height);
            int const top = y + 85;
            int const bottom = y + 285;
            int const right = x + 460;
            // The session list: a dimmed box with a frame, a header row and a scrollbar column
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x + 40, top, right - 20, bottom);
            int const outerRight = right + 1;
            int const outerLeft = x + 39;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                outerLeft, top - 1, outerRight, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                outerLeft, bottom + 1, outerRight, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                right - 20, top + 20, outerRight, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                outerLeft, top, outerLeft, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                outerRight, top, outerRight, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                right - 19, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
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
