#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523410
        undefined4 TribesState::findRecentOrSignpostSpawnLocation(uint* param_1, uint* param_2)
        {
            int iVar4 = 0;
            do {
                uint uVar2 = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + iVar4) % 4;
                short sVar1 = DAT_GameState::instance.mapAndTime.lionLocationsXY[uVar2].x;
                if (sVar1) {
                    *param_1 = (int)sVar1;
                    uVar2 = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + iVar4) % 4;
                    uint uVar3 = (uint)DAT_GameState::instance.mapAndTime.lionLocationsXY[uVar2].y;
                    *param_2 = uVar3;
                    uVar2 = *param_1;
                    if (uVar2 <= 399 && uVar3 <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[uVar3 * 400 + uVar2] != 0
                        && !(DAT_TileMapState::instance
                                 .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[uVar3].addXgetTile
                                     + uVar2]
                            & 0x4a5014b1U)) {
                        uVar2 = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + 1 + iVar4) % 4;
                        DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor = (short)uVar2;
                        return (undefined4)(1);
                    }
                }
                iVar4 = iVar4 + 1;
                if (4 <= iVar4) {
                    for (iVar4 = 0; iVar4 < 8; iVar4++) {
                        if (DAT_GameState::instance.mapAndTime.signpostIDs[iVar4] != 0) {
                            *param_1 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar4][0].x;
                            *param_2 = DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar4][0].y;
                            return (undefined4)(1);
                        }
                    }
                    return (undefined4)(0);
                }
            } while (true);
        }

    }
}
}
