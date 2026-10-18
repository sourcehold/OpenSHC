#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005334A0
        int UnitsState::getRemainingRequiredEngineers(int unitID)
        {
            /* the original tests each siege engine type in turn */
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                return 3
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                return 2
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                return 4
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                return 4
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                return 1
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                return 2
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                return 2
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                return 2
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_SIEGETENT) {
                if ((this->units[unitID].fixedRng & 2) != 0) {
                    return 3
                        - DAT_UnitsState::instance.units[unitID]
                              .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
                }
                return 2
                    - DAT_UnitsState::instance.units[unitID]
                          .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300;
            }
            return 0;
        }

    }
}
}
