#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::TribesState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521180
        TribesState* TribesState::Constructor_TribesState()
        {
            this->constructorTime = timeGetTime();
            this->clans = 0;
            this->fcn_mtribe = 0;
            this->field2_0x8 = 1;
            return this;
        }

    }
}
}
