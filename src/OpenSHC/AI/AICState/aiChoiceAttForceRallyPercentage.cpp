#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEC80
    uint AICState ::aiChoiceAttForceRallyPercentage(int param_1)

    {

        AITypeInt AVar1;

        int iVar2;

        int iVar3;

        short* psVar4;

        int local_14;

        int local_10;

        int* local_c;

        AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {

            return 0;
        }

        local_14 = 0;

        local_10 = 0;

        local_c = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

        do {

            iVar3 = 0;

            if (0 < *local_c) {

                psVar4 = DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs + (*(int (*)[2])(local_c + -1))[0];

                do {

                    iVar2 = (int)*psVar4;

                    if (((iVar2 != 0)
                            && (DAT_TribesState::instance.tribes[iVar2].uid
                                == DAT_GameState::instance.playerDataArray[param_1]
                                    .aiTribeUIDs[iVar3 + (*(int (*)[2])(local_c + -1))[0]]))
                        && (local_14 = local_14 + 1,
                            DAT_TribesState::instance.tribes[iVar2].percentageMovingUnk < 0x14)) {

                        local_10 = local_10 + 1;
                    }

                    iVar3 = iVar3 + 1;

                    psVar4 = psVar4 + 1;

                } while (iVar3 < *local_c);
            }

            local_c = local_c + 2;

        } while ((int)local_c < 0xb42a2c);

        if (0 < local_14) {

            return (uint)(*(int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x200)
                <= (local_10 * 100) / local_14);
        }

        return 0;
    }

}
}
