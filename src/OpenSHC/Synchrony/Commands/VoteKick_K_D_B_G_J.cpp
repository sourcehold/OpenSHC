#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00485140
    void Commands::VoteKick_K_D_B_G_J()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A**)0x0) {
                ((IDirectPlay4A*)DAT_GameSynchronyState::instance.DPLAYX_4A)->CancelMessage(0, 0);
            }
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0 == 0) {
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                MACRO_CALL(
                    OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                    0x16);
                return;
            }
            DAT_GameState::instance.mapAndTime.playerIsAlive[0] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[1] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[2] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[3] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[4] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[5] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[6] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[7] = 0;
            DAT_GameState::instance.mapAndTime.playerIsAlive[8] = 0;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
        }
    }

}
}
