#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052E830
        int UnitsState::assignPeasantToBuilding(UnitType unitType, int buildingID, int playerID, int workerIndex)
        {
            /* Finds a valid peasant, changes them into specified workertype and assignes
               them to building */
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_PEASANT) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(buildingID, workerIndex + 1, FALSE);
                this->units[unitID].workplaceBuildingID_1 = (short)buildingID;
                this->units[unitID].workplaceBuildingUID = DAT_BuildingsState::instance.buildings[buildingID].uid;
                this->units[unitID].targetX_2 = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                this->units[unitID].targetY_2 = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                this->units[unitID].unitTypeToChangeInto = (undefined2)unitType;
                this->units[unitID].state_2 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(buildingID, 1, FALSE);
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                this->units[unitID].disappearFadeAlphaCountdown = 0;
                this->units[unitID].engineerManningSiegeStateRef_checkType = 1;
                this->units[unitID].cachedState = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                this->units[unitID].isDisappearingUnk = 1;
                return unitID;
            }
            return 0;
        }

    }
}
}
