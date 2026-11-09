#include "../TriggerEventSlider.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC280
        void TriggerEventSlider::MenuModalRenderFunction_TriggerEventSlider(int x, int y, int width, int height)
        {
            int textNumInGroup = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa0;
            int iconIndex = -1;
            // 148 shows 146\'s text, and both show the icon
            if (textNumInGroup == 148) {
                textNumInGroup = 146;
            }
            if (textNumInGroup == 146) {
                iconIndex = 2;
            }
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup, x, y, width, height);
            if (iconIndex != -1) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, iconIndex + 128,
                    width / 2 + 8 + DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + x, y + 26);
            }
        }

    }
}
}
