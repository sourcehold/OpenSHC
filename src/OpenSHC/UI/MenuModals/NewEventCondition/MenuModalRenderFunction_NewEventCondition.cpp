#include "../NewEventCondition.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABA20
        void NewEventCondition::MenuModalRenderFunction_NewEventCondition(int x, int y, int width, int height)
        {
            int yParam;
            int xParam;
            /*
              added by script: "Event Conditions"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 0x66, x, y, width, height);
            if (DAT_MissionAestheticsDefinedData::instance
                    .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                != 0) {
                int numInGroup = DAT_MapPropertiesState::instance.invasionTroopIndex + 0x6a;
                if (0x7d < numInGroup) {
                    numInGroup = numInGroup + 0x40;
                }
                if (numInGroup == 0x6f || numInGroup == 0x70 || numInGroup == 0x71 || numInGroup == 0x7b) {
                    numInGroup = 0x71;
                }
                yParam = y + 0x1cf;
                xParam = x + 0x1e;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, numInGroup),
                    xParam, yParam, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x11, FALSE, 0);
            }
        }

    }
}
}
