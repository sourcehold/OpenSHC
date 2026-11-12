#include "../NewMapMaptype.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042F2B0
        void NewMapMaptype::MenuItemActionHandler_NewMapMaptype_Buttons(int button, ...)
        {
            if (DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU
                && DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE) {
                switch (button) {
                case 1:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = Map::MT_JUST_BUILD;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 2:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = Map::MT_INVASION;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 3:
                    MACRO_CALL(UI::Helpers_Func::InitializeBasicMap)();
                    DAT_GameCore::instance.U2_mapType_singleOrMulti = 1;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    for (int playerSlot = 0;
                        playerSlot < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++playerSlot) {
                        DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerSlot]
                            = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[playerSlot];
                    }
                    return;
                case 7:
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                }
            }
        }

    }
}
}
