#include "../AIVState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EDD00
    int AIVState::computeLargestSeparateArea()
    {
        int areaSizes[10000];
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(areaSizes), 0, areaSizes);
        for (int tile = 0; tile < 80400; ++tile) {
            int const areaID = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
            if (areaID > 0) {
                ++areaSizes[areaID];
            }
        }

        int highestSize = 0;
        int largestAreaID = 0;
        for (int areaID = 0; areaID < 10000; ++areaID) {
            if (areaSizes[areaID] > highestSize) {
                highestSize = areaSizes[areaID];
                largestAreaID = areaID;
            }
        }
        return largestAreaID;
    }

}
}
