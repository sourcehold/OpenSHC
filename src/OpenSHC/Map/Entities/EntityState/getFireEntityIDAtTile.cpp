#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00401540
        int EntityState::getFireEntityIDAtTile(int tile)
        {
            int _current = DAT_TileMapState::instance.EntityLayer[tile];
            while (_current != 0) {
                if (this->entityArray[_current].entityType == OpenSHC::Map::Entities::ET_FIRE)
                    return _current;
                _current = this->entityArray[_current].nextEntityOnThisTileByID;
            }
            return 0;
        }

    }
}
}
