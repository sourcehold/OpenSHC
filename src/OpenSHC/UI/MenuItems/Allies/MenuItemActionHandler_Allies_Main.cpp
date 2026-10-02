#include "../Allies.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004B12D0
        void Allies::MenuItemActionHandler_Allies_Main(int param_1, ...)
        {
            short sVar1;
            if ((param_1 == -1) || (param_1 == 100)) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
            } else {
                if (6 < param_1) {
                    if (param_1 == 0x14) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_ORDER, FALSE);
                    }
                    if (param_1 != 0x15) {
                        if (param_1 == 0x16) {
                            DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                            DAT_SentOrRequestedGoodsAmount::instance = 0;
                            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_REQUEST_GOODS, FALSE);
                        }
                        if (param_1 == 0x6e) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 4;
                        } else {
                            if (param_1 != 0x6f) {}
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 5;
                        }
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                            = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                            = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                    }
                    DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                    sVar1
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .requestedGoodsArray1Unk
                                  [DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]];
                    DAT_SentOrRequestedGoodsAmount::instance = 0;
                    if (1 < sVar1) {
                        DAT_SentOrRequestedGoodsAmount::instance
                            = (int)DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .requestedGoodsArray2Unk
                                      [DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]];
                        DAT_RequestedGoodsByWhoArray::instance[0] = sVar1 + -1;
                    }
                    DAT_00df4284::instance = (uint)(1 < sVar1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES_SEND_GOODS, FALSE);
                }
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::RecalculateAllies)();
                if (param_1 + -1 < DAT_AlliesCount::instance) {
                    DAT_LastTeamMemberIndex::instance = param_1 + -1;
                }
            }
        }

    }
}
}
