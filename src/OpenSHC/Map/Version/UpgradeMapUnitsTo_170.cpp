#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::Unit;
    using Map::Units::UnitType;
    using Map::Units::UnitTypeShort;
    using Map::Units::States::UnitState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B800
    void Version::UpgradeMapUnitsTo_170()
    {
        int iVar3;
        short* psVar4;
        int* piVar5;
        Unit* pUVar6;
        pUVar6 = &DAT_UnitsState::instance.units[1];
        do {
            UnitTypeShort UVar1 = pUVar6->unitType;
            if ((((((UVar1 == Map::Units::UT_S_CATAPULT) || (UVar1 == Map::Units::UT_S_TREBUCHET))
                      || (UVar1 == Map::Units::UT_S_MANGONEL))
                     || ((UVar1 == Map::Units::UT_S_TOWER || (UVar1 == Map::Units::UT_S_BATTERINGRAM))))
                    || ((UVar1 == Map::Units::UT_S_SHIELD
                        || ((UVar1 == Map::Units::UT_S_BALLISTA || (UVar1 == Map::Units::UT_S_FBALLISTA))))))
                && (iVar3 = 0, 0 < pUVar6->digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300)) {
                piVar5 = pUVar6->manningEngineerUIDRef;
                psVar4 = pUVar6->manningEngineerRef;
                do {
                    short sVar2 = *psVar4;
                    if ((DAT_UnitsState::instance.units[sVar2].uid == *piVar5)
                        && (DAT_UnitsState::instance.units[sVar2].state.generic
                            == Map::Units::States::US_LOOK_AROUNDUnk)) {
                        DAT_UnitsState::instance.units[sVar2].state.generic = Map::Units::States::US_AIM_WEAPONUnk;
                    }
                    iVar3 = iVar3 + 1;
                    psVar4 = psVar4 + 1;
                    piVar5 = piVar5 + 1;
                } while (iVar3 < pUVar6->digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300);
            }
            pUVar6 = pUVar6 + 0x248;
        } while ((int)pUVar6 < 0x165141a);
    }

}
}
