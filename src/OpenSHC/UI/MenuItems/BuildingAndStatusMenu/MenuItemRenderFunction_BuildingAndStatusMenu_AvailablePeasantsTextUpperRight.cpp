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
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x0043A8E0
            void MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight(int param_1, ...)
            {
                // x in a local first: without it the two loads swap registers.
                int const x = DAT_ButtonX::instance - 5;
                // "Available Peasants"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_IN_BARRACKS, 3),
                    x, DAT_ButtonY::instance, Text::TTA_RIGHT, Rendering::Colors::COL_B8EEFB, 0, 18, FALSE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .availablePeasantsOrHousedPeasants
                        - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .count,
                    DAT_ButtonX::instance, DAT_ButtonY::instance, Text::TTA_LEFT, Rendering::Colors::COL_B8EEFB, 0, 18,
                    FALSE, 0);
            }

        }
    }
}
}
