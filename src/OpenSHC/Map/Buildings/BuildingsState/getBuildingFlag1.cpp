#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F440
        int BuildingsState::getBuildingFlag1(int param_1) { return this->buildings[param_1].flag1; }

    }
}
}
