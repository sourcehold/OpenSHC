#include "../HistoricMissionSelect.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b95b2c.hpp"
#include "OpenSHC/Globals/DAT_00b96100.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x004269E0
        void HistoricMissionSelect::MenuItemRenderFunction_HistoricMissionSelect_MissionRows(int row, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                // a mission not reached yet is drawn greyed, with no text
                if (!DAT_GameCore::instance.unlockAllHistoricalCampaigns
                    && (int)(DAT_00b96100::instance - row - 1)
                        > (&DAT_GameCore::instance.scenarioProgress.progressCallToArms)[DAT_00b95b2c::instance]) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                        DAT_PencilRenderCore::ptr)(FALSE, row, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                    DAT_00b96100::instance - row - 1 == DAT_GameCore::instance.missionNumber1to20, row, 0);
                int const number = -row;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                // written in each arm: MSVC then hoists the calls' common pushes, as the original has them
                if (number == DAT_GameCore::instance.missionNumber1to20) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(number, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 5,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                    // read before the nested call, in the order the original loads them
                    int const nameY = DAT_ButtonY::instance + 5;
                    int const nameX = DAT_ButtonX::instance + 30;
                    int const mission = DAT_00b96100::instance - row - 1;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, mission),
                        nameX, nameY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                } else if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(number, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 5,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, DAT_00b96100::instance - row - 1,
                        DAT_ButtonX::instance + 30, DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(number, DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 5,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MISSION_NAMES, DAT_00b96100::instance - row - 1,
                        DAT_ButtonX::instance + 30, DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE);
                }
                DAT_ButtonUnknownZero::instance = FALSE;
            }
        }

    }
}
}
