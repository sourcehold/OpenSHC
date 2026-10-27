#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      example: goodsCount = 3, boost = TRUE for apple farm */

    // FUNCTION: STRONGHOLDCRUSADER 0x00530D70
    int Units::ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost)
    {
        int productivity = DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[unitID].owner]
                               .fearFactorProductivityUnk;
        DAT_UnitsState::instance.units[unitID].productivityDiv100 = 0;
        // Lowered productivity means more breaks, not fewer goods.
        if (productivity <= 100) {
            productivity = 100;
        }
        // Skirmish modes boost productivity by 50.
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY && boost != FALSE) {
            productivity += 50;
        }
        // Fractional bonus goods are kept as a percentage and added next time.
        int bonusPercentage
            = (productivity - 100) * goodsCount * 100 / 100 + DAT_UnitsState::instance.units[unitID].productivityMod100;
        DAT_UnitsState::instance.units[unitID].productivityDiv100 = (short)(bonusPercentage / 100);
        DAT_UnitsState::instance.units[unitID].productivityMod100 = (short)(bonusPercentage % 100);
        return DAT_UnitsState::instance.units[unitID].productivityDiv100 + goodsCount;
    }

}
}
