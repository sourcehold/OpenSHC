#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            using WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x00466320
            void MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton(int unused, ...)
            {
                int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
                BOOLEnum notDamaged = FALSE;
                DAT_ButtonUnknownZero::instance = FALSE;
                if (DAT_BuildingsState::instance.buildings[buildingID].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                }
                if (!MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateRepairCostAndReturnIfDamaged,
                        DAT_BuildingsState::ptr)(buildingID)) {
                    notDamaged = TRUE;
                }
                // The button is live when there is damage to repair and no enemy is within 30 (15 in a multiplayer
                // game).
                int requiredDistance;
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    requiredDistance = 15;
                } else {
                    requiredDistance = 30;
                }
                // tested twice through a flag, so MSVC lays the disabled arm out first as the original does
                BOOLEnum const disabled
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                          DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].owner,
                          DAT_BuildingsState::instance.buildings[buildingID].x,
                          DAT_BuildingsState::instance.buildings[buildingID].y, requiredDistance)
                    || notDamaged;
                if (disabled) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(8, OpenSHC::Rendering::Enums::RT_SCREEN_MENU);
                } else {
                    MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_SCREEN_MENU);
                }
                // "Repair", with the position read in each arm as the original does
                if (disabled) {
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    int const textY = DAT_ButtonY::instance + 7;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, 257),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7CAAAF, 18, FALSE, 0);
                } else if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    int const textY = DAT_ButtonY::instance + 7;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, 257),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                } else {
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    int const textY = DAT_ButtonY::instance + 7;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, 257),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                }
            }

        }
    }
}
}
