#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC810
    int TileMapState::computeClimbRampRotation(int tile, uint x, uint y)
    {
        int tileHeight;
        if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
            tileHeight = this->DefaultHeightLayer[tile];
        } else {
            tileHeight = this->HeightLayer[tile];
        }

        int neighbour = this->directionTranslationMatrix[y][this->screenSouthDirection] + tile;
        int screenSouthHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            screenSouthHeight = this->DefaultHeightLayer[neighbour];
        } else {
            screenSouthHeight = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenEastDirection] + tile;
        int screenEastHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            screenEastHeight = this->DefaultHeightLayer[neighbour];
        } else {
            screenEastHeight = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenSouthEastDirection] + tile;
        int screenSouthEastHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            screenSouthEastHeight = this->DefaultHeightLayer[neighbour];
        } else {
            screenSouthEastHeight = this->HeightLayer[neighbour];
        }

        uint exposedFaces;
        if (tileHeight > screenSouthHeight + 20 && screenSouthHeight < 136) {
            if (tileHeight > screenEastHeight + 20 && screenEastHeight < 136) {
                if (tileHeight > screenSouthEastHeight + 20 && screenSouthEastHeight < 136) {
                    exposedFaces = 5;
                } else {
                    exposedFaces = 3;
                }
            } else {
                exposedFaces = 1;
            }
        } else if (tileHeight > screenEastHeight + 20 && screenEastHeight < 136) {
            if (tileHeight > screenSouthHeight + 20 && screenSouthHeight < 136) {
                exposedFaces = 3;
            } else {
                exposedFaces = 2;
            }
        } else if (screenSouthHeight < 136 || screenEastHeight < 136) {
            if (tileHeight > screenSouthEastHeight + 20) {
                exposedFaces = 5;
            } else {
                exposedFaces = 0;
            }
        } else {
            exposedFaces = 4;
        }

        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
            if (exposedFaces == 1) {
                this->wallCornerRotation = 32 - (x & 0x1f);
            } else {
                this->wallCornerRotation = 32 - (y & 0x1f);
            }
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
            if (exposedFaces == 1) {
                this->wallCornerRotation = (x & 0x1f) + 1;
            } else {
                this->wallCornerRotation = (y & 0x1f) + 1;
            }
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_EAST) {
            this->wallCornerRotation = (y & 0x1f) + 1;
        } else {
            this->wallCornerRotation = 32 - (y & 0x1f);
        }
        if ((int)this->wallCornerRotation > 31) {
            this->wallCornerRotation = 1;
        }
        return exposedFaces;
    }

}
}
