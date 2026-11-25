#include "../Units.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053A020
    BOOLEnum Units::CurrentUnitHasHealer()
    {
        int const currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                && DAT_UnitsState::instance.units[unitID].owner == currentPlayer
                && DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_HEALER) {
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
