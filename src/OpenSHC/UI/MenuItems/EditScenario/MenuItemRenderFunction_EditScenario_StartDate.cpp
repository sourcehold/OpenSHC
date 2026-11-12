#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditScenario {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BAC90
            void MenuItemRenderFunction_EditScenario_StartDate(int button, ...)
            {
                switch (button) {
                case -5: {
                    // "Start Date"; y read before x as in the original (x first: quick_diff 0.9306 -> 0.8750)
                    int const labelY = DAT_ButtonY::instance + 6;
                    int const labelX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, 39),
                        labelX, labelY, Text::TTA_CENTER, Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    break;
                }
                case -1: {
                    // "Name"
                    int const labelY = DAT_ButtonY::instance + 6;
                    int const labelX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, 32),
                        labelX, labelY, Text::TTA_CENTER, Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                    break;
                }
                case 0:
                    break;
                default:
                    // any other button shows its own scenario text, centred unless the button has no width
                    if (DAT_ButtonW::instance == 0) {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_SCENARIO, button, DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                            Text::TTA_LEFT, Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    } else {
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            DE::SHCDE::TEXT_SCENARIO, button, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                            DAT_ButtonY::instance + 6, Text::TTA_CENTER, Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    }
                    // the two calls share their tail only with this break (without it: quick_diff 0.9306 -> 0.8784)
                    break;
                }
            }

        }
    }
}
}
