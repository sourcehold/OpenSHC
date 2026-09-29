#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005334A0
        int UnitsState::getRemainingRequiredEngineers(int unitID)
        {
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                return 3 - this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_CATAPULT) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                    return 4
                        - this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    return 4
                        - this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                    return 1
                        - this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                }
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_MANGONEL) {
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                        return 2
                            - this->units[unitID]
                                  .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                    }
                    if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_FBALLISTA) {
                        if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_SIEGETENT) {
                            return 0;
                        }
                        if ((this->units[unitID].fixedRng & 2) != 0) {
                            return 3
                                - this->units[unitID]
                                      .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                        }
                    }
                }
            }
            return 2 - this->units[unitID].digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
        }

    }
}
}
