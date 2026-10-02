#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00465360
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1, ...)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                = DAT_BuildingsState::instance.menuSelectedBuildingID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].uid;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                ((GameCommandType)0x25));
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .gateOpenOrCloseClick = param_1;
        }

    }
}
}
