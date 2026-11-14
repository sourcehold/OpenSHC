#include "../AlliesOrder.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B1410
        void AlliesOrder::MenuItemActionHandler_AlliesOrder_Main(int button, ...)
        {
            // -2 shows the allies dialog again
            if (button == -2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                return;
            }
            // buttons 1 to 6 name an enemy from the list BuildEnemyPlayerList made
            if (button <= 6 && button - 1 >= DAT_EnemyArrayIndex::instance) {
                return;
            }
            int const allyPlayerID = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[allyPlayerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[allyPlayerID] == 0) {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
            if (button <= 6) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = DAT_RequestedGoodsByWhoArray::instance[button];
            } else {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = allyPlayerID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = button;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
            // 10 shows the allies dialog again after its order, the others close it
            if (button == 10) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
            } else {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            }
        }

    }
}
}
