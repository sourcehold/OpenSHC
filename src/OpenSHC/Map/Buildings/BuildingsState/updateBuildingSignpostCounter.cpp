#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F360
        int BuildingsState::updateBuildingSignpostCounter(int param_1, int param_2)
        {
            if (param_2 == 2) {
                this->buildings[param_1].field14_0x2c = 0;
                this->buildings[param_1].state = 0;
                this->buildings[param_1].animationIndex = 0;
                return 0;
            }

            if (param_2 == 3) {
                this->buildings[param_1].animationIncrement = 0;
            } else {
                this->buildings[param_1].animationIncrement = 1;
            }
            short related = this->buildings[param_1].unknownStockpileOrSignpostRelated;
            this->buildings[param_1].renderAnimation = param_2;
            if (related == 0) {
                this->buildings[param_1].renderAnimation = 0;
            }
            if (this->buildings[param_1].renderAnimation == 0) {
                this->buildings[param_1].animationIndex = 0;
                this->buildings[param_1].field13_0x28 = 0;
                this->buildings[param_1].field14_0x2c = 0;
            }
            return this->buildings[param_1].field14_0x2c;
        }

    }
}
}
