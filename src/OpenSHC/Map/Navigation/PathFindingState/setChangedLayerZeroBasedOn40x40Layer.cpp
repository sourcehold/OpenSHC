#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0049AF50
        void PathFindingState::setChangedLayerZeroBasedOn40x40Layer(uint flag_and_offset)
        {
            if (this->field_0x28 == 0 && flag_and_offset == 0) {
                for (int row = DAT_TileMapState::instance.someIndex; row <= (int)DAT_TileMapState::instance.someLimit;
                    ++row) {
                    for (int column = DAT_TileMapState::instance.someYLike;
                        column <= (int)DAT_TileMapState::instance.someYLikeLimit; ++column) {
                        if (DAT_TileMapState::instance.mapping40x40[row][column] == 0) {
                            continue;
                        }
                        DAT_TileMapState::instance.mapping40x40[row][column] = 0;
                        // every tile of the 10x10 block this 40x40 cell covers
                        for (int dy = 0; dy < 10; ++dy) {
                            uint const y = row * 10 + dy;
                            for (int dx = 0; dx < 10; ++dx) {
                                uint const x = column * 10 + dx;
                                if (x <= 399 && y <= 399
                                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                                    DAT_TileMapState::instance
                                        .ChangedLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile
                                            + x] = 0;
                                }
                            }
                        }
                    }
                }
                this->mappingYRelated = 1000;
                this->yLimit = 0;
                DAT_TileMapState::instance.someIndex = 1000;
                DAT_TileMapState::instance.someLimit = 0;
                DAT_TileMapState::instance.someYLike = 1000;
                DAT_TileMapState::instance.someYLikeLimit = 0;
                return;
            }
            this->field_0x28 = 0;
            this->mappingYRelated = 0;
            this->yLimit = 399;
            DAT_TileMapState::instance.someIndex = 0;
            DAT_TileMapState::instance.someLimit = 39;
            DAT_TileMapState::instance.someYLike = 0;
            DAT_TileMapState::instance.someYLikeLimit = 39;
        }

    }
}
}
