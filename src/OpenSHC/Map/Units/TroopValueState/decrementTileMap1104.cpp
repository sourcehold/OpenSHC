#include "OpenSHC/Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            int _offset;
            // The original is unrolled five times. Collapsing it into a plain loop over 200 entries took
            // the match from 100% to 10.5%, so the copies stay.
            for (_offset = 0; _offset < 200; _offset += 5) {
                char _value = DAT_TileMapState::instance
                                  .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset];
                if (0 < (byte)_value) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset]
                        = _value + -1;
                }
                _value = DAT_TileMapState::instance
                             .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 1];
                if (0 < (byte)_value) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 1]
                        = _value + -1;
                }
                _value = DAT_TileMapState::instance
                             .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 2];
                if (0 < (byte)_value) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 2]
                        = _value + -1;
                }
                _value = DAT_TileMapState::instance
                             .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 3];
                if (0 < (byte)_value) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 3]
                        = _value + -1;
                }
                _value = DAT_TileMapState::instance
                             .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 4];
                if (0 < (byte)_value) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + _offset + 4]
                        = _value + -1;
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
