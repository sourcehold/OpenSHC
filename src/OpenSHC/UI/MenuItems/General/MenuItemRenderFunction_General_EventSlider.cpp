#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BA3C0
        void General::MenuItemRenderFunction_General_EventSlider(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged)
        {
            undefined2 color;
            switch (param_1) {
            case 5:
            case 0xc:
            case 0x12:
            case 0x13:
            case 0x15:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    != param_1 + -1) {}
                break;
            case -2:
            case -1:
                switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                case 5:
                case 0xb:
                case 0xc:
                case 0xd:
                case 0xe:
                case 0xf:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1d:
                case 0x1e:
                    break;
                default:
                    return;
                }
            }
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            color = COL_DARK_LIME::instance.shortValue;
            if (isDragged == 0) {
                color = COL_GREYISH_YELLOW::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance + thumbYPos + 1, (int)((int)(DAT_ButtonY::instance + 2)),
                DAT_ButtonX::instance + thumbYPos + -2 + thumbHeight,
                (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)), (ushort)((int)(color)));
            if ((param_1 == -2) && (param_3 == 10)) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)("-", (int)((int)(DAT_ButtonW::instance + 0xc + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0, 0x12, FALSE, 0);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(param_3,
                (int)((int)(DAT_ButtonW::instance + 0xc + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0, 0x12, FALSE, 0);
        }

    }
}
}
