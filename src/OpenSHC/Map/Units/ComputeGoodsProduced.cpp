#include "../Units.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530D70
    int Units::ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost)
    {
        // an apple farm, for example, passes goodsCount 3 and boost TRUE
        int productivity = DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[unitID].owner]
                               .fearFactorProductivityUnk;
        DAT_UnitsState::instance.units[unitID].productivityDiv100 = 0;
        // Lowered productivity means more breaks, not fewer goods.
        if (productivity <= 100) {
            productivity = 100;
        }
        // Skirmish modes boost productivity by 50.
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY && boost) {
            productivity += 50;
        }
        // Fractional bonus goods are kept as a percentage and added next time.
        // the original multiplies by 100 and divides by 100 again (without: quick_diff 0.9737 -> 0.4058)
        int const bonusPercentage
            = (productivity - 100) * goodsCount * 100 / 100 + DAT_UnitsState::instance.units[unitID].productivityMod100;
        // a variable, so one idiv gives quotient and remainder (a literal 100: quick_diff 0.9737 -> 0.7561)
        int divisor = 100;
        DAT_UnitsState::instance.units[unitID].productivityDiv100 = (short)(bonusPercentage / divisor);
        DAT_UnitsState::instance.units[unitID].productivityMod100 = (short)(bonusPercentage % divisor);
        return DAT_UnitsState::instance.units[unitID].productivityDiv100 + goodsCount;
    }

}
}
