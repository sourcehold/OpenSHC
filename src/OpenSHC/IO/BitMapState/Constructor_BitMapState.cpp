#include "../BitMapState.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C580
    BitMapState* BitMapState::Constructor_BitMapState()
    {
        this->address = 0;
        this->surface = 0;
        this->mbr_0x18 = 0;
        return this;
    }

}
}
