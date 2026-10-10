#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::Unit;
    using Map::Units::UnitLogicState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B260
    void Version::UpgradeMapUnitsTo_UnknownVersion2()
    {
        short sVar2;
        Unit* psVar3;
        psVar3 = &DAT_UnitsState::instance.units[1];
        DAT_CurrentUnitSlotID::instance = 0x9c4;
        do {
            if (psVar3->logicalState == Map::Units::ULS_NORMAL) {
                psVar3->someUnitStat2_meleeDamageUnk
                    = (short)DAT_UnitPropertiesDefinedData::instance.UNIT_CAN_MELEE[(short)psVar3->unitType];
                if (1 < psVar3->movementCooldown) {
                    psVar3->movementCooldown = 0;
                }
                if (psVar3->maxHealth <= psVar3->health) {
                    int iVar1 = DAT_UnitPropertiesDefinedData::instance.BASE_HP[(short)psVar3->unitType];
                    psVar3->maxHealth = iVar1;
                    psVar3->health = iVar1;
                    if (!psVar3->maxHealth) {
                        sVar2 = 100;
                    } else {
                        sVar2 = (short)((iVar1 * 100) / psVar3->maxHealth);
                    }
                    psVar3->healthPercentage = sVar2;
                    psVar3->healthbar
                        = (sVar2 / 10 + (sVar2 >> 0xf)) - (short)((longlong)(int)sVar2 * 0x66666667 >> 0x3f);
                }
            }
            psVar3 = psVar3 + 0x248;
        } while ((int)psVar3 < 0x165165e);
    }

}
}
