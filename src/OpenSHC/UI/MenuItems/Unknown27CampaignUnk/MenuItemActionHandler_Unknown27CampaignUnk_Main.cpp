#include "../Unknown27CampaignUnk.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D6F20
        void Unknown27CampaignUnk::MenuItemActionHandler_Unknown27CampaignUnk_Main(int param_1, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE && param_1 == 10) {
                if (DAT_GameCore::instance.missionNumber1to20 == 1) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                }
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_UNKNOWN_26_CAMPAIGN_RELATEDUnk, 0);
            }
        }

    }
}
}
