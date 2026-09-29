#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F540
        int PathFindingState::algFindAttackAngle(int maxDistance200, uint x, uint y, int tribeID)
        {
            int _siegeIndex;
            int _tile;
            int _tileOption;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return 0;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while ((_tileOption = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < _tileOption && (_tileOption < 80400))) {
                    int _xOption = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int _yOption = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tileOption];
                    if (80400 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    if (this->searchQueue.currentDistance > maxDistance200) {
                        return 0;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tileOption]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                != 0
                            && (_tile = DAT_TileMapState::instance.directionTranslationMatrix[_yOption][_direction]
                                    + _tileOption,
                                DAT_TileMapState::instance.WalkLayer[_tile] != this->searchGeneration)) {
                            if (4 < this->searchQueue.currentDistance
                                && (DAT_TileMapState::instance.AIInfoLayer[_tile] & 0x80) != 0
                                && (_siegeIndex
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getSiegeIndexForTile,
                                        DAT_TroopValueState::ptr)(_tile),
                                    _siegeIndex != 0)
                                && _siegeIndex != DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1
                                && _siegeIndex != DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2
                                && DAT_TroopValueState::instance.attackInfo.tentPointsValues[_siegeIndex].three == 0
                                && DAT_TroopValueState::instance.attackInfo.tentPointsValues[_siegeIndex].tribeID
                                    == 0) {
                                return _siegeIndex;
                            }
                            DAT_TileMapState::instance.CertainPathLayer[_tile]
                                = (short)this->searchQueue.currentDistance + 1;
                            short _xOffset
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset;
                            DAT_TileMapState::instance.WalkLayer[_tile] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = _xOffset + _xOption;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                      + _direction * 8 + 4)
                                + _yOption;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (80400 < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return 0;
                    }
                }
            }
            return 0;
        }

    }
}
}
