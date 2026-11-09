#include "../NewEventCondition.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ABA20
        void NewEventCondition::MenuModalRenderFunction_NewEventCondition(int x, int y, int width, int height)
        {
            // "Event Conditions"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 102, x, y, width, height);
            if (DAT_MissionAestheticsDefinedData::instance
                    .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                != 0) {
                int numInGroup = DAT_MapPropertiesState::instance.invasionTroopIndex + 106;
                if (125 < numInGroup) {
                    numInGroup += 64;
                }
                if (numInGroup == 111 || numInGroup == 112 || numInGroup == 113 || numInGroup == 123) {
                    numInGroup = 113;
                }
                int yParam = y + 463;
                int xParam = x + 0x1e;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, numInGroup),
                    xParam, yParam, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
            }
        }

    }
}
}
