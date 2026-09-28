#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Trees::TreeType;
        using OpenSHC::Map::Trees::TreeTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C370
        BOOLEnum PathFindingState::findNoTreeInRange(int budget, uint x, uint y)
        {
            int (*paiVar2)[8];
            short* psVar3;
            int _tile;
            TreeTypeShort _treeType;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (399 < x || 399 < y || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                return FALSE;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < _tile && (_tile < 0x13a10))) {
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (budget < this->searchQueue.currentDistance) {
                        return TRUE;
                    }
                    int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        /*
                          for each direction, do:
                         */
                        int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + _tile;
                        if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                            int _org = (int)DAT_TileMapState::instance.OrganismLayer[_candidate];
                            if ((_org == 0) || (1999 < _org)) {
                                if ((DAT_TileMapState::instance.LogicLayer[_candidate] & 0x30) == 0) {
                                    /*
                                      not map edge? add to queue
                                     */
                                    DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                        = (short)this->searchQueue.currentDistance + 1;
                                    DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar1;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if (0x13a0f < this->searchQueue.writeIndex) {
                                        this->searchQueue.writeIndex = 0;
                                    }
                                }
                            } else {
                                _treeType = DAT_LandscapeState::instance.trees[_org].treeType;
                                if (_treeType == (TreeType)1) {
                                    return FALSE;
                                }
                                if (_treeType == (TreeType)2) {
                                    return FALSE;
                                }
                                if (_treeType == (TreeType)3) {
                                    return FALSE;
                                }
                                if (_treeType == (TreeType)4) {
                                    return FALSE;
                                }
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return FALSE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
