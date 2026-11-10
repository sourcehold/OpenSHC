#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditScenario {

            // FUNCTION: STRONGHOLDCRUSADER 0x004B9060
            void MenuItemRenderFunction_EditScenario_UpDownButtons(int button, ...)
            {
                // -1 is the event list's up arrow, the other negative buttons its down arrow.
                if (button < 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (button == -1) {
                        MACRO_CALL_MEMBER(
                            Rendering::PencilRenderCore_Func::renderUpDownButtonUnk, DAT_PencilRenderCore::ptr)(0, 0);
                    } else {
                        MACRO_CALL_MEMBER(
                            Rendering::PencilRenderCore_Func::renderUpDownButtonUnk, DAT_PencilRenderCore::ptr)(1, 0);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                // The other buttons show their scenario text, in white while hovered.
                MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                // One call per colour pair (one call with colour locals: quick_diff 0.9231 -> 0.5455)
                // The position in each branch (once, before the test: quick_diff 0.9231 -> 0.9038)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, button),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_00A2FF,
                        OpenSHC::Rendering::Colors::COL_003E66, 18, FALSE, 0);
                    return;
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_SCENARIO, button),
                    textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_FFFFFF,
                    OpenSHC::Rendering::Colors::COL_000000, 18, FALSE, 0);
            }

        }
    }
}
}
