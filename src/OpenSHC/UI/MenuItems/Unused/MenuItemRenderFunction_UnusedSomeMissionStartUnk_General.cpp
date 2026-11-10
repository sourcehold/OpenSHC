#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00426FB0
        void Unused::MenuItemRenderFunction_UnusedSomeMissionStartUnk_General(int button, ...)
        {
            // nothing while a dialog is open
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            // two calls, one per colour (one call with colour locals: 100.0% -> 71.1%)
            if (DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                    COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                int const textY = DAT_ButtonY::instance + 8;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, button),
                    textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_FFFFFF,
                    OpenSHC::Rendering::Colors::COL_000000, 17, FALSE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonY::instance + DAT_ButtonH::instance,
                OpenSHC::UI::Enums::RBERL_SLIGHT);
            int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            int const textY = DAT_ButtonY::instance + 8;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS, button),
                textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_00A2FF,
                OpenSHC::Rendering::Colors::COL_003E66, 17, FALSE, 0);
        }

    }
}
}
