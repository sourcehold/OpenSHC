#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005002D0
    void TileMapState::clearMoatData(uint moatID)
    {
        if (moatID > 15999) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0x10, 0, &this->moats[moatID]);
        this->moatTileCount -= 1;
    }

}
}
