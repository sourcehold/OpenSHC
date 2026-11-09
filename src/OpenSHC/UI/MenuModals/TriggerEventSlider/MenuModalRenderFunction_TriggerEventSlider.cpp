#include "../TriggerEventSlider.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"

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
            int textNumInGroup;
            int iconIndex = -1;
            if (DAT_MapPropertiesState::instance.invasionEventContent.field_0xa0 == 148) {
                textNumInGroup = 146;
                iconIndex = 2;
            } else {
                textNumInGroup = DAT_MapPropertiesState::instance.invasionEventContent.field_0xa0;
                if (DAT_MapPropertiesState::instance.invasionEventContent.field_0xa0 == 146) {
                    iconIndex = 2;
                }
            }
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                199, textNumInGroup, x, y, width, height);
            if (iconIndex != -1) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, iconIndex + 128,
                    width / 2 + 8 + DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + x, y + 26);
            }
        }

    }
}
}
