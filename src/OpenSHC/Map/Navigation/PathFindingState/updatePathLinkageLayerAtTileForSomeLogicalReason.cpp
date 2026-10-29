#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00499DC0
        void PathFindingState::updatePathLinkageLayerAtTileForSomeLogicalReason(int tileUnk, int y)
        {
            int _link;
            int _direction;
            int _neighbour;
            _link = (int)(char)DAT_TileMapState::instance.PathLinkageLayer[tileUnk];
            for (_direction = 0; _direction < 8; _direction++) {
                _neighbour = DAT_TileMapState::instance.directionTranslationMatrix[y][_direction] + tileUnk;
                if ((DAT_TileMapState::instance.LogicLayer[_neighbour] & 0x30) == 0
                    && (DAT_TileMapState::instance.LogicLayer[_neighbour] & 0x4a5014b1) == 0) {
                    if ((_link & (int)(char)DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                        == 0) {
                        DAT_TileMapState::instance.PathLinkageLayer[_neighbour]
                            &= ~DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[(_direction + 4) % 8];
                    } else {
                        DAT_TileMapState::instance.PathLinkageLayer[_neighbour]
                            |= DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[(_direction + 4) % 8];
                    }
                }
            }
            return;
        }

    }
}
}
