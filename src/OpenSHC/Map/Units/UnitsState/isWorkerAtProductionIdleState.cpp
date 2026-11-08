#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A070
        BOOLEnum UnitsState::isWorkerAtProductionIdleState(int unitID)
        {
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_WOODCUTTER:
            case OpenSHC::Map::Units::UT_HOPSFARMER:
            case OpenSHC::Map::Units::UT_MILLER:
            case OpenSHC::Map::Units::UT_BREWER:
            case OpenSHC::Map::Units::UT_POLETURNER:
            case OpenSHC::Map::Units::UT_SMITH:
            case OpenSHC::Map::Units::UT_ARMORER:
            case OpenSHC::Map::Units::UT_TANNER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_FLETCHER:
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_HUNTER:
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
            case OpenSHC::Map::Units::UT_PITCHMAN:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_QUARRYOX:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                if (this->units[unitID].state.generic == (UnitState)10) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_BAKER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return TRUE;
                }
                break;
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
