#include "../GameStateStructures.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004567A0
    void GameStateStructures::clearSignpostData()
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.signpostIDs), '\0', this->mapAndTime.signpostIDs);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.signpostEntryData), '\0', this->mapAndTime.signpostEntryData);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.signpostsMapEdge), '\0', this->mapAndTime.signpostsMapEdge);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->mapAndTime.unitMoveDestinationXYPairs), '\0', this->mapAndTime.unitMoveDestinationXYPairs);
    }

}
}
