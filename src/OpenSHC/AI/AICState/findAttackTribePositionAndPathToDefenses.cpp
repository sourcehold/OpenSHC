#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE930
    void AICState ::findAttackTribePositionAndPathToDefenses(int playerID)
    {
        uint local_8 = 0;
        uint local_4 = 0;
        int* local_c = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

        bool _found = false;
        do {
            int iVar2 = 0;
            if (0 < *local_c) {
                short* psVar3 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs
                    + (*(int (*)[2])(local_c + -1))[0];
                do {
                    int iVar1 = (int)*psVar3;
                    if ((iVar1 != 0)
                        && (DAT_TribesState::instance.tribes[iVar1].uid
                            == DAT_GameState::instance.playerDataArray[playerID]
                                   .aiTribeUIDs[iVar2 + (*(int (*)[2])(local_c + -1))[0]])) {
                        iVar2 = (int)DAT_TribesState::instance.tribes[iVar1].selectionTargetUnitID;
                        local_8 = (uint)DAT_UnitsState::instance.units[iVar2].x;
                        local_4 = (uint)DAT_UnitsState::instance.units[iVar2].y;
                        if (iVar2 != 0) {
                            _found = true;
                            break;
                        }
                        break;
                    }
                    iVar2 = iVar2 + 1;
                    psVar3 = psVar3 + 1;
                } while (iVar2 < *local_c);
            }
            if (_found)
                break;
            local_c = local_c + 2;
        } while ((int)local_c <= 0xb42a2b);

        DAT_GameState::instance.playerDataArray[playerID].someTile = 0;

        if (local_8 != 0) {
            int _tile = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::tracePathToFriendlyDefensesAndReturnTileUnk,
                DAT_PathFindingState::ptr)(playerID, local_8, local_4);
            if (0 < _tile) {
                short _y = DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_tile];
                DAT_GameState::instance.playerDataArray[playerID].someTile = _tile;
                int iVar2 = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                DAT_GameState::instance.playerDataArray[playerID].someY = (int)_y;
                DAT_GameState::instance.playerDataArray[playerID].someX = _tile - iVar2;
            }
        }
    }
}
}
