#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0043A8E0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight(
            int param_1, ...)
        {
            // "Available Peasants"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BARRACKS, 3),
                DAT_ButtonX::instance - 5, DAT_ButtonY::instance, OpenSHC::Text::TTA_RIGHT,
                OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .availablePeasantsOrHousedPeasants
                    - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .count,
                DAT_ButtonX::instance, DAT_ButtonY::instance, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 18, FALSE, 0);
        }

    }
}
}
