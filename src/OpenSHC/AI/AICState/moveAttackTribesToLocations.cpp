#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE830
    void AICState ::moveAttackTribesToLocations(short* playerID)

    {

        int iVar1;

        int iVar2;

        short* psVar3;

        int tribeID;

        int iVar4;

        int iVar5;

        int* local_c;

        psVar3 = playerID;

        if (DAT_GameState::instance.playerDataArray[(int)playerID].aiType != OpenSHC::AI::AIT_NULL) {

            iVar4 = 0;

            local_c = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

            do {

                iVar1 = *local_c;

                iVar2 = (*(int (*)[2])(local_c + -1))[0];

                iVar5 = 0;

                if (0 < iVar1) {

                    playerID = DAT_GameState::instance.playerDataArray[(int)psVar3].aiTribeIDs + iVar2;

                    do {

                        tribeID = (int)*playerID;

                        if ((tribeID != 0)
                            && (DAT_TribesState::instance.tribes[tribeID].uid
                                == DAT_GameState::instance.playerDataArray[(int)psVar3].aiTribeUIDs[iVar5 + iVar2])) {

                            DAT_TribesState::instance.tribes[tribeID].unitStance
                                = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                            /*
                                          fixme: array too small?
                                */

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                DAT_TribesState::ptr)(tribeID,
                                (uint)((int)(DAT_GameState::instance.mapAndTime
                                        .aiTribeMoveDestinationXYPairArray1[(int)psVar3 * 5][iVar4]
                                        .xOffset)),
                                (uint)((int)(DAT_GameState::instance.mapAndTime
                                        .aiTribeMoveDestinationXYPairArray1[(int)psVar3 * 5][iVar4]
                                        .yOffset)),
                                0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                            iVar4 = iVar4 + 1;
                        }

                        playerID = playerID + 1;

                        iVar5 = iVar5 + 1;

                    } while (iVar5 < iVar1);
                }

                local_c = local_c + 2;

            } while ((int)local_c < 0xb42a2c);
        }

        return;
    }

}
}
