#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            int iVar2;
            for (iVar2 = 0; iVar2 < 200; iVar2 += 5) {
                char cVar1 = *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef88 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef88 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef89 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef89 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8a + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8a + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8b + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8b + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8c + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(DAT_TroopValueState::instance.attackInfo.tilemapOffset + 0x1ecef8c + iVar2) = cVar1 + -1;
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tilemapOffset < 80200) {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset
                    = DAT_TroopValueState::instance.attackInfo.tilemapOffset + 200;
            }
            DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
        }

    }
}
}
