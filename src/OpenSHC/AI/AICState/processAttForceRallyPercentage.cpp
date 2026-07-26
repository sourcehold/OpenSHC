#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEEA0
    BOOLEnum AICState ::processAttForceRallyPercentage(int playerID)

    {

        AITypeInt AVar1;

        int iVar2;

        int iVar3;

        int _tribeID;

        short* psVar4;

        int iVar5;

        int _tribeTotal;

        int _notReallyMoving;

        int* local_c;

        AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL) {

            return FALSE;
        }

        _tribeTotal = 0;

        _notReallyMoving = 0;

        local_c = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

        do {

            iVar2 = (*(int (*)[2])(local_c + -1))[0];

            iVar3 = *local_c;

            if ((((iVar2 != 0x12) && (iVar2 != 0xbe)) && (iVar2 != 0xf)) && (iVar5 = 0, 0 < iVar3)) {

                psVar4 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + iVar2;

                do {

                    _tribeID = (int)*psVar4;

                    if ((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[iVar5 + iVar2])) {

                        _tribeTotal = _tribeTotal + 1;

                        if (DAT_TribesState::instance.tribes[_tribeID].percentageMovingUnk < 0x14) {

                            _notReallyMoving = _notReallyMoving + 1;
                        }

                        DAT_TribesState::instance.tribes[_tribeID].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_STAND_GROUND;
                    }

                    iVar5 = iVar5 + 1;

                    psVar4 = psVar4 + 1;

                } while (iVar5 < iVar3);
            }

            local_c = local_c + 2;

        } while ((int)local_c < 0xb42a2c);

        if (0 < _tribeTotal) {

            /*
                  AttForceRallyPercentage */

            return (uint)(*(int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x200)
                <= (_notReallyMoving * 100) / _tribeTotal);
        }

        return FALSE;
    }

}
}
