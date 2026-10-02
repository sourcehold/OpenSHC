#include "../AlliesOrder.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B1410
        void AlliesOrder::MenuItemActionHandler_AlliesOrder_Main(int param_1, ...)
        {
            int _allyID;
            if (param_1 != -2) {
                if (((6 < param_1) || (param_1 + -1 < DAT_EnemyArrayIndex::instance))
                    && ((_allyID = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance],
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_allyID] != -1
                            || (DAT_GameSynchronyState::instance.currentAIArray[_allyID] != 0)))) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    if (param_1 <= 6) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_RequestedGoodsByWhoArray::instance[param_1];
                    } else {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = param_1;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = _allyID;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                    if (param_1 == 10)
                        goto LAB_004b14a1;
                    DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                }
            }
        LAB_004b14a1:
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
        }

    }
}
}
