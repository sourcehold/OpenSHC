#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandParameterLocation;
    using Commands::GameCommandParameterReadWrite;

    // FUNCTION: STRONGHOLDCRUSADER 0x004805D0
    void GameSynchronyState::serializeOrDeserializeCommandParameter(void* destination, size_t size,
        GameCommandParameterLocation srcSwitch, GameCommandParameterReadWrite destSwitch)
    {
        if ((0 < (int)size) && (destination != (void*)0x0)) {
            byte* _parameter;
            if (srcSwitch == Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS) {
                _parameter = this->DAT_GameCommandFixedParameterLocation + this->DAT_CommandParameterOffset;
            } else {
                _parameter = &this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].parameters
                    + this->DAT_CommandParameterOffset;
            }
            if (destSwitch == Commands::GCPRW_SERIALIZE_INTO_PARAM_1) {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                    size, destination, _parameter);
            } else {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                    size, _parameter, destination);
            }
            this->DAT_CommandParameterOffset = this->DAT_CommandParameterOffset + size;
        }
    }

}
}
