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

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047D190
        void FindingNetworkSessions::MenuModalRenderFunction_FindingNetworkSessions(int x, int y, int width, int height)
        {
            int top;
            int x2;
            uint uVar1;
            int x1;
            int bottom;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            /*
              added by script: "Finding Sessions"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4c, 0xb, x, y, width, height);
            top = y + 0x55;
            bottom = y + 0x11d;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, top, x + 0x1b8, bottom);
            x2 = x + 0x1cd;
            x1 = x + 0x27;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x54, x2, y + 0x54, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x11e, x2, y + 0x11e, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1b8, y + 0x69, x2, y + 0x69, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, top, x1, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, top, x2, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1b8, top, x + 0x1b8, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1b9, y + 0x109, x + 0x1cc, y + 0x109, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            UI_NetworkSessionsShadeLogic::instance = UI_NetworkSessionsShadeLogic::instance + 1;
            uVar1 = UI_NetworkSessionsShadeLogic::instance / 2 & 0x8000001f;
            if ((int)uVar1 < 0) {
                uVar1 = (uVar1 - 1 | 0xffffffe0) + 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                (int)((int)(DAT_ProtocolDefinedData::instance.field135_0x474[uVar1] + 0x18e)), width / 2 + -0xe + x,
                y + 0x138);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if ((DAT_GameSynchronyState::instance.scrollBarIndex == -1)
                && (DAT_GameSynchronyState::instance.DPLAY_SessionsCount != 0)) {
                DAT_GameSynchronyState::instance.scrollBarIndex = 0;
            }
        }

    }
}
}
