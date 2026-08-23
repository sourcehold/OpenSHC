#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2A10
    int LandscapeState::getRandomRockImageOffset(int param_1)
    {
        return DAT_OrganismDefinedData::instance.RandomRockImageGMImageOffsets[param_1];
    }

}
}
