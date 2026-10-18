#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530880
        void UnitsState::setRandomNumberOnCows(int playerID)
        {
            for (int unitID = 0; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[unitID].dying == 0 && this->units[unitID].unitType == OpenSHC::Map::Units::UT_COW
                    && this->units[unitID].owner == playerID) {
                    this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        = SEC_RNG::instance.currentNumber2 % 300;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                }
            }
        }

    }
}
}
