#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECA90
    BOOLEnum AICState::shouldNotBuildKillingPits(int playerID, MappersEnum commandBuildingType)
    {
        BOOLEnum _totalAbove99 = FALSE;
        if (commandBuildingType == OpenSHC::Commands::M_MAPPER_KILLING_PIT) {
            _totalAbove99 = 100 <= DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[playerID];
        }
        return _totalAbove99;
    }

}
}
