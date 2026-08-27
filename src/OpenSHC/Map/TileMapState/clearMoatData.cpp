#include "../TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x005002D0
    void TileMapState::clearMoatData(uint moatID)

    {
        if (moatID < 16000) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x10, '\0', (void*)((int)(this->moats + moatID)));
            this->moatTileCount = this->moatTileCount + -1;
        }
        return;
    }

}
}
