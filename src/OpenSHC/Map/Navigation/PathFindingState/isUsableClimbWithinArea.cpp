#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4B30
        BOOLEnum PathFindingState::isUsableClimbWithinArea(int area, int wallDataID)
        {
            if ((this->climbData[wallDataID].canBeUsed == 1)
                && (this->climbData[wallDataID].isRecognizedByPathfinding != 0)) {
                if (this->climbData[wallDataID].area == area) {
                    return TRUE;
                }
                return (uint)(this->climbData[wallDataID].wallGroupAreaID == area);
            }
            return FALSE;
        }

    }
}
}
