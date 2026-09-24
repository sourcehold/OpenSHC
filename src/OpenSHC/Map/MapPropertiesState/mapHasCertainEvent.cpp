#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7890
    BOOLEnum MapPropertiesState::mapHasCertainEvent()
    {
        for (int i = 0; i < this->eventsCount; ++i) {
            switch (this->scenarioEvents[i].header.tl_type) {
            case 1:
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
