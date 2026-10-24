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
            /*
              Four separate guards, not two `||` chains: the original emits a `return 0` for
              the first of each pair inline and jumps back to it from the second, and the
              three return blocks have different `pop` sequences because they sit at
              different points in its register saves.
             */
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return (undefined4)(0);
            }
            if (param_1 <= 0) {
                return (undefined4)(0);
            }
            if (this->tribes[param_1].predatorNearby != 0) {
                return (undefined4)(0);
            }
            if (DAT_GameCore::instance.missionNumber1to20 == 0x26 && param_4 == 0x2f) {
                return (undefined4)(0);
            }
            {
                int iVar7 = (int)this->tribes[param_1].selectionTargetUnitID;
                int iVar6 = iVar7;
                if (param_4 == 0x2c) {
                    iVar6 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getNonDyingUnit, this)(param_1);
                    if (!iVar6) {
                        iVar6 = iVar7;
                    }
                }
                int bVar5 = (byte)SEC_RNG::instance.currentNumber2 & 0x7f;
                int sVar2 = DAT_UnitsState::instance.units[iVar6].x;
                int sVar3 = DAT_UnitsState::instance.units[iVar6].y;
                int sVar4 = DAT_UnitsState::instance.units[iVar6].terrainOrClimbHeight;
                this->tribes[param_1].field_0x288 = this->tribes[param_1].field_0x288 + 1;
                /*
                  Flat guards, not a nested chain. All three tests already had the right
                  sense; what differed was where the merged `return 0` landed. The
                  original puts it between the third guard and the success body, so the
                  first two jump forward into it (`jl 0x23`, `jl 0x15`) and the third
                  jumps over it (`jl 0xa`) - which is what early returns give. Nested,
                  MSVC moves the block to the end of the function and the third test
                  inverts to a `jge` reaching back for it.
                 */
                if (this->tribes[param_1].field_0x288 < param_2) {
                    return (undefined4)(0);
                }
                this->tribes[param_1].field_0x288 = 0;
                if (bVar5 < 100) {
                    return (undefined4)(0);
                }
                iVar6 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::countLivingNondyingUnitsForPlayer, DAT_UnitsState::ptr)(param_4);
                if (iVar6 >= param_3) {
                    return (undefined4)(0);
                }
                if (param_4 == 0x2f) {
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                        Commands::M_MAPPER_CAMEL, (uint)(sVar2), (uint)(sVar3), (int)(sVar4));
                }
                return (undefined4)(1);
            }
            return (undefined4)(0);
        }

    }
}
}
