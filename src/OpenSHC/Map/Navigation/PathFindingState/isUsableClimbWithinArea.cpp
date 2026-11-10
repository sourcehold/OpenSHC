#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A4B30
        BOOLEnum PathFindingState::isUsableClimbWithinArea(int area, int wallDataID)
        {
            if (this->climbData[wallDataID].canBeUsed != 1) {
                return FALSE;
            }
            if (this->climbData[wallDataID].isRecognizedByPathfinding == 0) {
                return FALSE;
            }
            if (this->climbData[wallDataID].area == area) {
                return TRUE;
            }
            return this->climbData[wallDataID].wallGroupAreaID == area;
        }

    }
}
}
