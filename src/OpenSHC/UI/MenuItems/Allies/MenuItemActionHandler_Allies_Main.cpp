#include "../Allies.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00df4284.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B12D0
        void Allies::MenuItemActionHandler_Allies_Main(int button, ...)
        {
            if (button == -1 || button == 100) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                return;
            }
            if (button <= 6) {
                // buttons 1 to 6 pick an ally
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::RecalculateAllies)();
                int const ally = button - 1;
                if (ally < DAT_AlliesCount::instance) {
                    DAT_LastTeamMemberIndex::instance = ally;
                }
                return;
            }
            if (button == 20) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_ORDER, FALSE);
                return;
            }
            if (button == 21) {
                DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                int const allyPlayerID = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
                short const requestedResource
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .requestedGoodsArray1Unk[allyPlayerID];
                DAT_SentOrRequestedGoodsAmount::instance = 0;
                DAT_00df4284::instance = 0;
                if (requestedResource >= OpenSHC::Game::Resources::RT_WOOD) {
                    DAT_00df4284::instance = 1;
                    DAT_RequestedGoodsByWhoArray::instance[0] = requestedResource - 1;
                    DAT_SentOrRequestedGoodsAmount::instance
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .requestedGoodsArray2Unk[allyPlayerID];
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_SEND_GOODS, FALSE);
                return;
            }
            if (button == 22) {
                DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                DAT_SentOrRequestedGoodsAmount::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_REQUEST_GOODS, FALSE);
                return;
            }
            // the answer to the ally's request: 4 accepts it, 5 denies it
            if (button == 110) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 4;
            } else if (button == 111) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 5;
            } else {
                return;
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
        }

    }
}
}
