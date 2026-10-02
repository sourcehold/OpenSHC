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

        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042F2B0
        void NewMapMaptype::MenuItemActionHandler_NewMapMaptype_Buttons(int param_1, ...)
        {
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                switch (param_1) {
                case 1:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_JUST_BUILD;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 2:
                    DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_INVASION;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    return;
                case 3:
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::InitializeBasicMap)();
                    DAT_GameCore::instance.U2_mapType_singleOrMulti = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                }
            }
        }

    }
}
}
