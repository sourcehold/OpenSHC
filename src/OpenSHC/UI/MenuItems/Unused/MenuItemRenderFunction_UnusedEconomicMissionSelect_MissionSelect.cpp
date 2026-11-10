#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00426D30
        void Unused::MenuItemRenderFunction_UnusedEconomicMissionSelect_MissionSelect(int button, ...)
        {
            // nothing while a dialog is open
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU
                || DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            // The button holds minus the mission number: shown as mission - 32, named by entry mission - 11 of
            // TEXT_MISSION_NAMES. A mission not reached yet is an empty cell.
            if (!DAT_GameCore::instance.unlockAllHistoricalCampaigns
                && -button > DAT_GameCore::instance.furthestMission) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                    DAT_PencilRenderCore::ptr)(FALSE, button, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(-button == DAT_GameCore::instance.missionNumber1to20, button, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (-button == DAT_GameCore::instance.missionNumber1to20) {
                // the selected mission: its number and name
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    -32 - button, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                // y then x for the name (in the call: quick_diff 0.9302 -> 0.7608; x first: 0.8992)
                int const nameY = DAT_ButtonY::instance + 5;
                int const nameX = DAT_ButtonX::instance + 30;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, -11 - button),
                    nameX, nameY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                DAT_ButtonUnknownZero::instance = FALSE;
                return;
            }
            // The number's position and value in each branch (once, before the test: quick_diff 0.9302 -> 0.8760)
            // and one call per colour (one renderText2 with a colour local: 0.6615)
            if (DAT_ButtonCurrentlyInteracting::instance) {
                int const numberY = DAT_ButtonY::instance + 5;
                int const numberX = DAT_ButtonX::instance + 8;
                int const number = -32 - button;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, numberX, numberY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19,
                    FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, -11 - button, DAT_ButtonX::instance + 30,
                    DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19,
                    FALSE);
            } else {
                int const numberY = DAT_ButtonY::instance + 5;
                int const numberX = DAT_ButtonX::instance + 8;
                int const number = -32 - button;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, numberX, numberY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                    FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, -11 - button, DAT_ButtonX::instance + 30,
                    DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                    FALSE);
            }
            DAT_ButtonUnknownZero::instance = FALSE;
        }

    }
}
}
