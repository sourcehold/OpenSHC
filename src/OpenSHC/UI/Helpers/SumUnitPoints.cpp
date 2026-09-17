#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B8200
    void Helpers::SumUnitPoints()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
    }

}
}
