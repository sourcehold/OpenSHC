#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            int iVar2;
            for (iVar2 = 0; iVar2 < 200; iVar2 += 5) {
                char cVar1 = DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2];
                if (0 < (byte)cVar1) {
                    DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2] = cVar1 + -1;
                }
                cVar1 = DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 1];
                if (0 < (byte)cVar1) {
                    DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 1] = cVar1 + -1;
                }
                cVar1 = DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 2];
                if (0 < (byte)cVar1) {
                    DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 2] = cVar1 + -1;
                }
                cVar1 = DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 3];
                if (0 < (byte)cVar1) {
                    DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 3] = cVar1 + -1;
                }
                cVar1 = DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 4];
                if (0 < (byte)cVar1) {
                    DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + iVar2 + 4] = cVar1 + -1;
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tilemapOffset < 80200) {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset
                    = DAT_TroopValueState::instance.attackInfo.tilemapOffset + 200;
            } else {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
            }
        }

    }
}
}
