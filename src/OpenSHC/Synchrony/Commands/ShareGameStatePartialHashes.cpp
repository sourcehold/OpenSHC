#include "../Commands.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004856E0
    void Commands::ShareGameStatePartialHashes()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 48;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            for (int domain = 0;
                domain < countof(DAT_GameSynchronyState::instance.HASH_PartialHashPerPlayer.player[0].domain);
                ++domain) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.HASH_PartialHashPerPlayer
                                                     .player[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                     .domain[domain],
                    4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            }
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        for (int domain = 0;
            domain < countof(DAT_GameSynchronyState::instance.HASH_PartialHashPerPlayer.player[0].domain); ++domain) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.HASH_PartialHashPerPlayer
                                                 .player[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
                                                 .domain[domain],
                4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        }
        DAT_GameSynchronyState::instance.syncStatus10Related[DAT_GameSynchronyState::instance.protocolInvokerPlayerID]
            = 1;
    }

}
}
