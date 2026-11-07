#include "../TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F6AE0
    void TileMapState::setChangedLayerToThreeAndMapping0x40x40()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->ChangedLayer), 3, this->ChangedLayer);
        MACRO_CALL(OpenSHC::OS_Func::_memset)(this->mapping40x40, 3, sizeof(this->mapping40x40));
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setChangedLayerZeroBasedOn40x40Layer,
            DAT_PathFindingState::ptr)(1);
    }

}
}
