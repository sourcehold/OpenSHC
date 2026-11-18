#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC810
    int TileMapState::computeClimbRampRotation(int tileUnk, uint x, uint y)
    {
        int height;
        if ((this->LogicLayer[tileUnk] & L_WALL_OR_GATEHOUSE) != 0) {
            height = this->DefaultHeightLayer[tileUnk];
        } else {
            height = this->HeightLayer[tileUnk];
        }

        int neighbour = this->directionTranslationMatrix[y][this->screenSouthDirection] + tileUnk;
        int southHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            southHeight = this->DefaultHeightLayer[neighbour];
        } else {
            southHeight = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenEastDirection] + tileUnk;
        int eastHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            eastHeight = this->DefaultHeightLayer[neighbour];
        } else {
            eastHeight = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenSouthEastDirection] + tileUnk;
        int southEastHeight;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            southEastHeight = this->DefaultHeightLayer[neighbour];
        } else {
            southEastHeight = this->HeightLayer[neighbour];
        }

        uint rotation;
        if (height > southHeight + 20 && southHeight < 136) {
            if (height > eastHeight + 20 && eastHeight < 136) {
                if (height > southEastHeight + 20 && southEastHeight < 136) {
                    rotation = 5;
                } else {
                    rotation = 3;
                }
            } else {
                rotation = 1;
            }
        } else if (height > eastHeight + 20 && eastHeight < 136) {
            if (height > southHeight + 20 && southHeight < 136) {
                rotation = 3;
            } else {
                rotation = 2;
            }
        } else if (southHeight < 136 || eastHeight < 136) {
            if (height > southEastHeight + 20) {
                rotation = 5;
            } else {
                rotation = 0;
            }
        } else {
            rotation = 4;
        }

        if (this->mapOrientation == OpenSHC::Map::Enums::MO_NORTH) {
            if (rotation == 1) {
                this->wallCornerRotation = 32 - (x & 0x1f);
            } else {
                this->wallCornerRotation = 32 - (y & 0x1f);
            }
        } else if (this->mapOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
            if (rotation == 1) {
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
        return rotation;
    }

}
}
