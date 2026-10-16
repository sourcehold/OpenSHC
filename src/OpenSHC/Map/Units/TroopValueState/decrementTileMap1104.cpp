#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            int iVar2;
            for (iVar2 = 0; iVar2 < 200; iVar2 += 5) {
                char cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef88 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef88 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef89 + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef89 + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8a + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8a + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8b + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8b + iVar2) = cVar1 + -1;
                }
                cVar1 = *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8c + iVar2);
                if (cVar1 != '\0') {
                    *(char*)(this->attackInfo.tilemapOffset + 0x1ecef8c + iVar2) = cVar1 + -1;
                }
            }
            if (this->attackInfo.tilemapOffset < 80200) {
                this->attackInfo.tilemapOffset = this->attackInfo.tilemapOffset + 200;
            }
            this->attackInfo.tilemapOffset = 0;
        }

    }
}
}
