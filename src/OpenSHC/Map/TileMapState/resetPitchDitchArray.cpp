#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/PitchDitch.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::PitchDitch;

    // FUNCTION: STRONGHOLDCRUSADER 0x005007D0
    void TileMapState::resetPitchDitchArray()
    {
        this->maxPitchDitchCount = 4000;
        for (int i = 0; i < 4000; i++) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x14, 0, &this->pitchDitches[i]);
        }
    }

}
}
