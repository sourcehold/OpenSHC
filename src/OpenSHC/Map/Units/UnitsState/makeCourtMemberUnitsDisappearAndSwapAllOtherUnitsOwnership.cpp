#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530500
        void UnitsState::makeCourtMemberUnitsDisappearAndSwapAllOtherUnitsOwnership(
            int firstPlayerID, int secondPlayerID)
        {
            for (int unitID = 1; unitID < 2500; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].isStalked != 0) {
                    switch (this->units[unitID].unitType) {
                    case OpenSHC::Map::Units::UT_QUARRYOX:
                    case OpenSHC::Map::Units::UT_COW:
                    case OpenSHC::Map::Units::UT_HUNTERDOG:
                    case OpenSHC::Map::Units::UT_CHICKEN:
                    case OpenSHC::Map::Units::UT_MOTHER:
                    case OpenSHC::Map::Units::UT_CHILD:
                    case OpenSHC::Map::Units::UT_JUGGLER:
                    case OpenSHC::Map::Units::UT_FIREEATER:
                        break;
                    default:
                        continue;
                    }
                }
                if (this->units[unitID].owner == firstPlayerID) {
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LADY) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_JESTER) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else {
                        this->units[unitID].owner = (short)secondPlayerID;
                        if (this->units[unitID].isStalked == 0 || this->units[unitID].calculatedOwnerPlayerIndex != 0) {
                            this->units[unitID].calculatedOwnerPlayerIndex = secondPlayerID;
                        }
                    }
                } else if (this->units[unitID].owner == secondPlayerID) {
                    if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LADY) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_JESTER) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    } else {
                        this->units[unitID].owner = (short)firstPlayerID;
                        if (this->units[unitID].isStalked == 0 || this->units[unitID].calculatedOwnerPlayerIndex != 0) {
                            this->units[unitID].calculatedOwnerPlayerIndex = firstPlayerID;
                        }
                    }
                }
            }
        }

    }
}
}
