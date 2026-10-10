#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00518A10
        void TroopValueState::assignBehaviorTypeAndLinkSupportTribe(
            int param_1, int param_2, SomeTribeBehaviorType param_3, undefined4 param_4, undefined4 param_5)
        {
            int iVar1;
            int iVar2;
            short* psVar3;
            int iVar4;
            if (param_2 < 1) {
                param_2 = 2;
            }
            psVar3 = &DAT_TribesState::instance.tribes[1].tribeID;
            do {
                if (*(int*)(psVar3 + -0xfa) == param_2) {
                    *psVar3 = 0;
                }
                psVar3 = psVar3 + 0x19a;
            } while ((int)psVar3 < 0x1762580);
            iVar4 = 0;
            if (this->attackInfo.tribeIDArraySize < 1) {}
        LAB_00518a50:
            iVar1 = this->attackInfo.tribeIDArray[iVar4];
            if (10 < this->attackInfo.tribeRelatedArrayValue0UpTo12[iVar4]) {}
            iVar2 = (int)DAT_TribesState::instance.tribes[iVar1].supportTribeID;
            if ((iVar2)
                && (DAT_TribesState::instance.tribes[iVar1].uid2 == DAT_TribesState::instance.tribes[iVar2].uid)) {}
            DAT_TribesState::instance.tribes[iVar1].tribeBehaviorType = (undefined2)param_3;
            DAT_TribesState::instance.tribes[iVar1].someUpdateUpperLimit
                = ((short)iVar4 + 1) * (short)param_5 + (short)param_4;
            DAT_TribesState::instance.tribes[iVar1].attackInfo_someCounter1 = (short)this->attackInfo.someCounter1;
            DAT_TribesState::instance.tribes[iVar1].unknownAttackRelatedUpdateCounter = 0;
            iVar2 = 1;
            psVar3 = &DAT_TribesState::instance.tribes[1].tribeState;
            do {
                if (((((*psVar3 != 0) && (*psVar3 != 3))
                         && (*(int*)(psVar3 + -10) == DAT_TribesState::instance.tribes[iVar1].owner))
                        && (psVar3[0xf0] == 0))
                    && ((psVar3[1] == ((AITribeType)0x16) || (psVar3[1] == ((AITribeType)0x17)))))
                    goto LAB_00518b70;
                psVar3 = psVar3 + 0x19a;
                iVar2 = iVar2 + 1;
            } while ((int)psVar3 < 0x17623a0);
            iVar2 = 1;
            psVar3 = &DAT_TribesState::instance.tribes[1].tribeState;
            do {
                if (this->attackInfo.value3Array01[param_1] == 4)
                    break;
                if ((((*psVar3 != 0) && (*psVar3 != 3))
                        && ((*(int*)(psVar3 + -10) == DAT_TribesState::instance.tribes[iVar1].owner
                            && (psVar3[0xf0] == 0))))
                    && ((psVar3[1] == AI::Tribes::AITT_ARCHERS
                        || (psVar3[1] == AI::Tribes::AITT_CROSSBOWMEN))))
                    goto LAB_00518b70;
                psVar3 = psVar3 + 0x19a;
                iVar2 = iVar2 + 1;
            } while ((int)psVar3 < 0x17623a0);
            goto LAB_00518b92;
        LAB_00518b70:
            DAT_TribesState::instance.tribes[iVar1].supportTribeID = (short)iVar2;
            DAT_TribesState::instance.tribes[iVar1].uid2 = DAT_TribesState::instance.tribes[iVar2].uid;
            DAT_TribesState::instance.tribes[iVar2].tribeID = (short)iVar1;
        LAB_00518b92:
            iVar4 = iVar4 + 1;
            if (this->attackInfo.tribeIDArraySize <= iVar4) {}
            goto LAB_00518a50;
        }

    }
}
}
