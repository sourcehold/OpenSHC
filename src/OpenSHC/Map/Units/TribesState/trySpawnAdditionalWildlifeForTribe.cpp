#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Commands::MappersEnum;
        using UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005260B0
        undefined4 TribesState::trySpawnAdditionalWildlifeForTribe(int param_1, int param_2, int param_3, int param_4)
        {
            int sVar2;
            int sVar3;
            int sVar4;
            byte bVar5;
            int iVar6;
            int iVar7;
            if ((DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
                || (param_1 < 1)) {
                return (undefined4)(0);
            }
            if (this->tribes[param_1].predatorNearby == 0
                && (DAT_GameCore::instance.missionNumber1to20 != 0x26 || (param_4 != 0x2f))) {
                iVar7 = (int)this->tribes[param_1].selectionTargetUnitID;
                iVar6 = iVar7;
                if (param_4 == 0x2c) {
                    iVar6 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getNonDyingUnit, this)(param_1);
                    if (!iVar6) {
                        iVar6 = iVar7;
                    }
                }
                bVar5 = (byte)SEC_RNG::instance.currentNumber2;
                sVar2 = DAT_UnitsState::instance.units[iVar6].x;
                sVar3 = DAT_UnitsState::instance.units[iVar6].y;
                sVar4 = DAT_UnitsState::instance.units[iVar6].terrainOrClimbHeight;
                this->tribes[param_1].field_0x288 = this->tribes[param_1].field_0x288 + 1;
                if (param_2 <= this->tribes[param_1].field_0x288
                    && (this->tribes[param_1].field_0x288 = 0, 99 < (bVar5 & 0x7f))) {
                    iVar6 = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::countLivingNondyingUnitsForPlayer, DAT_UnitsState::ptr)(param_4);
                    if (iVar6 < param_3) {
                        if (param_4 == 0x2f) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                                Commands::M_MAPPER_CAMEL, (uint)(sVar2), (uint)(sVar3), (int)(sVar4));
                        }
                        return (undefined4)(1);
                    }
                }
                return (undefined4)(0);
            }
            return (undefined4)(0);
        }

    }
}
}
