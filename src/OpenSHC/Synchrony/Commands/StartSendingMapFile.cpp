#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00485C10
    void Commands::StartSendingMapFile()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 1,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        char hasMap;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&hasMap, 1, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        // the host notes who has the map (2) and who waits for it (1)
        if (DAT_GameSynchronyState::instance.isHost) {
            if (hasMap) {
                DAT_GameSynchronyState::instance
                    .mapTransferStatePerPlayer[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 2;
            } else {
                DAT_GameSynchronyState::instance
                    .mapTransferStatePerPlayer[DAT_GameSynchronyState::instance.protocolInvokerPlayerID] = 1;
            }
        }
        // once every player has a state, the dialog that sends the map opens
        for (int playerID = 1; playerID < countof(DAT_GameSynchronyState::instance.mapTransferStatePerPlayer);
            ++playerID) {
            if (DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[playerID] == 0) {
                return;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            OpenSHC::UI::Enums::MMT_SEND_MAP_TO, FALSE);
    }

}
}
