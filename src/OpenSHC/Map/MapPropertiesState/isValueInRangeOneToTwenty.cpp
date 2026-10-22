#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B77E0
    BOOLEnum MapPropertiesState::isValueInRangeOneToTwenty(int value) { return value - 1 < 20; }

}
}
