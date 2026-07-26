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

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEA50
    void AICState ::makeUnitsGoDefensiveAndBackToSomeLocation(int param_1)

    {

        int iVar1;

        int iVar2;

        int _commandResult;

        short* psVar3;

        int tribeID;

        int iVar4;

        int* local_c;

        uint _x;

        if ((DAT_GameState::instance.playerDataArray[param_1].aiType != OpenSHC::AI::AIT_NULL)
            && (DAT_GameState::instance.playerDataArray[param_1].someTile != 0)) {

            local_c = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

            do {

                iVar1 = *local_c;

                iVar2 = (*(int (*)[2])(local_c + -1))[0];

                iVar4 = 0;

                if (0 < iVar1) {

                    psVar3 = DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs + iVar2;

                    do {

                        tribeID = (int)*psVar3;

                        if ((tribeID != 0)
                            && (DAT_TribesState::instance.tribes[tribeID].uid
                                == DAT_GameState::instance.playerDataArray[param_1].aiTribeUIDs[iVar4 + iVar2])) {

                            _x = DAT_GameState::instance.playerDataArray[param_1].someX;

                            DAT_TribesState::instance.tribes[tribeID].unitStance
                                = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                            _commandResult = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                tribeID, _x, (uint)((int)(DAT_GameState::instance.playerDataArray[param_1].someY)), 0,
                                0, OpenSHC::Map::Units::Instructions::UMSE_0);

                            if (_commandResult == 0) {

                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeAllTribeUnits,
                                    DAT_TribesState::ptr)(tribeID);
                            }
                        }

                        iVar4 = iVar4 + 1;

                        psVar3 = psVar3 + 1;

                    } while (iVar4 < iVar1);
                }

                local_c = local_c + 2;

            } while ((int)local_c < 0xb42a2c);
        }

        return;
    }

}
}
