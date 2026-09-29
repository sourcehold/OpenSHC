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
    int TileMapState::computeClimbRampRotation(int tile, uint x, uint y)
    {
        uint height;
        if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0) {
            height = this->HeightLayer[tile];
        } else {
            height = this->DefaultHeightLayer[tile];
        }

        int neighbour = this->directionTranslationMatrix[y][this->field86_0x5548ac] + tile;
        uint heightAt86;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) == 0) {
            heightAt86 = this->HeightLayer[neighbour];
        } else {
            heightAt86 = this->DefaultHeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->field85_0x5548a8] + tile;
        uint heightAt85;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) == 0) {
            heightAt85 = this->HeightLayer[neighbour];
        } else {
            heightAt85 = this->DefaultHeightLayer[neighbour];
        }

        neighbour = this->directionTranslationMatrix[y][this->field84_0x5548a4] + tile;
        uint heightAt84;
        if ((this->LogicLayer[neighbour] & L_WALL_OR_GATEHOUSE) == 0) {
            heightAt84 = this->HeightLayer[neighbour];
        } else {
            heightAt84 = this->DefaultHeightLayer[neighbour];
        }

        uint rotation;
        if (heightAt86 + 0x14 < height && heightAt86 < 0x88) {
            if (heightAt85 + 0x14 < height && heightAt85 < 0x88) {
                if (heightAt84 + 0x14 < height && heightAt84 < 0x88) {
                    rotation = 5;
                } else {
                    rotation = 3;
                }
            } else {
                rotation = 1;
            }
        } else if (heightAt85 + 0x14 < height && heightAt85 < 0x88) {
            if (heightAt86 + 0x14 < height && heightAt86 < 0x88) {
                rotation = 3;
            } else {
                rotation = 2;
            }
        } else if (heightAt86 < 0x88 || heightAt85 < 0x88) {
            /* 0 when the tile is not high enough above its neighbour, 5 when it is */
            rotation = (uint)(height <= heightAt84 + 0x14) - 1 & 5;
        } else {
            rotation = 4;
        }

        if (this->mapOrientation == 0) {
            if (rotation == 1) {
                this->field112_0x554908 = 0x20 - (x & 0x1f);
            } else {
                this->field112_0x554908 = 0x20 - (y & 0x1f);
            }
        } else if (this->mapOrientation == 4) {
            if (rotation == 1) {
                this->field112_0x554908 = (x & 0x1f) + 1;
            } else {
                this->field112_0x554908 = (y & 0x1f) + 1;
            }
        } else if (this->mapOrientation == 2) {
            this->field112_0x554908 = (y & 0x1f) + 1;
        } else {
            this->field112_0x554908 = 0x20 - (y & 0x1f);
        }
        if (this->field112_0x554908 > 0x1f) {
            this->field112_0x554908 = 1;
        }
        return rotation;
    }

}
}
