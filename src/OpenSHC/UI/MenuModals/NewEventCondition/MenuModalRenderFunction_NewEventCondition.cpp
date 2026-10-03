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

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004ABA20
        void NewEventCondition::MenuModalRenderFunction_NewEventCondition(int x, int y, int width, int height)
        {
            int numInGroup;
            char* textAddress;
            int yParam;
            int xParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            /*
              added by script: "Event Conditions"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 0x66, x, y, width, height);
            if (DAT_MissionAestheticsDefinedData::instance
                    .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                != 0) {
                numInGroup = DAT_MapPropertiesState::instance.invasionTroopIndex + 0x6a;
                if (0x7d < numInGroup) {
                    numInGroup = DAT_MapPropertiesState::instance.invasionTroopIndex + 0xaa;
                }
                if ((((numInGroup == 0x6f) || (numInGroup == 0x70)) || (numInGroup == 0x71)) || (numInGroup == 0x7b)) {
                    numInGroup = 0x71;
                }
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                color = 0xccfaff;
                alignment = OpenSHC::Text::TTA_LEFT;
                yParam = y + 0x1cf;
                xParam = x + 0x1e;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, numInGroup),
                    xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
