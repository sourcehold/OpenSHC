#include "../BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F440
        int BuildingsState::getBuildingFlag1(int buildingID) { return this->buildings[buildingID].flag1; }

    }
}
}
