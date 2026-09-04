#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Moat.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Moat;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500680
    void TileMapState::resetMoatArray()
    {
        for (int i = 0; i < 16000; i++) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x10, 0, &this->moats[i]);
        }
        this->moatTileCount = 0;
    }

}
}
