#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Commands/CommandBuildingType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECAB0
    BOOLEnum AICState::woodCuttersHutWhileNoWoodAvailable(
        undefined4 playerID, Commands::CommandBuildingType commandBuildingType)
    {
        if ((commandBuildingType == Commands::CBT_WOODCUTTERSHUT)
            && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0)) {
            return TRUE;
        }
        return FALSE;
    }
}
}
