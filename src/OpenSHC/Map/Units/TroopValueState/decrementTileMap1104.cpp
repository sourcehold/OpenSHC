#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            // The original is unrolled five times. Collapsing it into a plain loop over 200 entries took
            // the match from 100% to 10.5%, so the outer loop steps by five.
            for (int offset = 0; offset < 200; offset += 5) {
                for (int i = 0; i < 5; ++i) {
                    char const value
                        = DAT_TileMapState::instance
                              .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + offset + i];
                    if (0 < (byte)value) {
                        DAT_TileMapState::instance
                            .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + offset + i]
                            = value - 1;
                    }
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tilemapOffset < 80200) {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset += 200;
            } else {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
            }
        }

    }
}
}
