#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC810
    int TileMapState::computeClimbRampRotation(int tileUnk, uint x, uint y)
    {
        int high;
        if ((this->LogicLayer[tileUnk] & L_WALL_OR_GATEHOUSE) != 0) {
            high = this->DefaultHeightLayer[tileUnk];
        } else {
            high = this->HeightLayer[tileUnk];
        }

        int neighbour = this->directionTranslationMatrix[y][this->screenSouthDirection] + tileUnk;
        int heightAt86;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            heightAt86 = this->DefaultHeightLayer[neighbour];
        } else {
            heightAt86 = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenEastDirection] + tileUnk;
        int heightAt85;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            heightAt85 = this->DefaultHeightLayer[neighbour];
        } else {
            heightAt85 = this->HeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->screenSouthEastDirection] + tileUnk;
        int heightAt84;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) != 0) {
            heightAt84 = this->DefaultHeightLayer[neighbour];
        } else {
            heightAt84 = this->HeightLayer[neighbour];
        }

        uint rotation;
        if (high > heightAt86 + 0x14 && heightAt86 < 0x88) {
            if (high > heightAt85 + 0x14 && heightAt85 < 0x88) {
                if (high > heightAt84 + 0x14 && heightAt84 < 0x88) {
                    rotation = 5;
                } else {
                    rotation = 3;
                }
            } else {
                rotation = 1;
            }
        } else if (high > heightAt85 + 0x14 && heightAt85 < 0x88) {
            if (high > heightAt86 + 0x14 && heightAt86 < 0x88) {
                rotation = 3;
            } else {
                rotation = 2;
            }
        } else if (heightAt86 < 0x88 || heightAt85 < 0x88) {
            /* 0 when the tileUnk is not high enough above its neighbour, 5 when it is */
            rotation = (high <= heightAt84 + 0x14) - 1 & 5;
        } else {
            rotation = 4;
        }

        if (this->mapOrientation == 0) {
            if (rotation == 1) {
                this->wallCornerRotation = 0x20 - (x & 0x1f);
            } else {
                this->wallCornerRotation = 0x20 - (y & 0x1f);
            }
        } else if (this->mapOrientation == 4) {
            if (rotation == 1) {
                this->wallCornerRotation = (x & 0x1f) + 1;
            } else {
                this->wallCornerRotation = (y & 0x1f) + 1;
            }
        } else if (this->mapOrientation == 2) {
            this->wallCornerRotation = (y & 0x1f) + 1;
        } else {
            this->wallCornerRotation = 0x20 - (y & 0x1f);
        }
        if ((int)this->wallCornerRotation > 0x1f) {
            this->wallCornerRotation = 1;
        }
        return rotation;
    }

}
}
