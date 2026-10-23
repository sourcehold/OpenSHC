#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_00df5588.hpp"
#include "OpenSHC/Globals/DAT_00df558c.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      Sets DAT_00df5588 (tutorial action type) and DAT_00df558c (building type) unless actionState is 11
       and DAT_00df5588 is already 7 — in which case the update is skipped to avoid overwriting a
       pending state. Used to record which building-related action the player last performed for
       tutorial step evaluation.

       renamed by: Claude Sonnet 4.6
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004BC690
    void Helpers::SetTutorialBuildingActionState(int actionState, BuildingType buildingType)
    {
        if (actionState != 11 || DAT_00df5588::instance != 7) {
            DAT_00df5588::instance = actionState;
            DAT_00df558c::instance = buildingType;
        }
    }

}
}
