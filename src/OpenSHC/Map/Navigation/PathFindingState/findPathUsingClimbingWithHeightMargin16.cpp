#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00498020
        BOOLEnum PathFindingState::findPathUsingClimbingWithHeightMargin16(
            uint x, uint y, uint x2, uint y2, int budget, BOOLEnum continueSearch)
        {
            int (*paiVar4)[8];
            int _keepHeight;
            int _tDiff;
            int _direction;
            uint _cHeight;
            int _candidate;
            BuildingTypeShort _cType;
            uint _cLogic;
            uint _tLogic;
            BuildingTypeShort _tType;
            uint _tile;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            if (x2 != 0xffffffff) {
                if (399 < x2) {
                    return FALSE;
                }
                if (399 < y2) {
                    return FALSE;
                }
                if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0') {
                    return FALSE;
                }
            }
            if (continueSearch == FALSE) {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.currentDistance = 1;
            }
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (x2 == 0xffffffff) {
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile == x) {
                    /*
                      if candidate matches target tile
                     */
                    this->searchMatchCounter = this->searchMatchCounter + 1;
                    return TRUE;
                }
                if ((budget <= this->searchQueue.readIndex) || (0x13a0f < _tile))
                    break;
                int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0x78 < this->searchQueue.currentDistance)
                    break;
                uint _tHeight = (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                _tLogic = DAT_TileMapState::instance.LogicLayer[_tile];
                _direction = 0;
                paiVar4 = DAT_TileMapState::instance.directionTranslationMatrix + sVar2;
                do {
                    /*
                      for each direction, do:
                     */
                    _candidate = (*paiVar4)[0] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                            == 0) {
                            /*
                              tile is not wall or gatehouse
                             */
                            if ((_tLogic & 0x100) == 0) {
                                /*
                                  tile is not moat
                                 */
                                _cLogic = DAT_TileMapState::instance.LogicLayer[_candidate];
                                if ((_tLogic & 0x40000000) == 0) {
                                    if ((_cLogic & 0x40000000) != 0)
                                        goto LAB_0049825d;
                                } else if ((_cLogic & 0x40000800) != 0 || (_cLogic & 0x4a5015b1) == 0) {
                                LAB_0049825d:
                                    /*
                                      candidate is moat or stairs OR not sea, border (edge), rocky, wall or
                                      gatehouse, building, tree, rivere, crenel, farm field, moat
                                     */
                                    _cHeight = (uint)DAT_TileMapState::instance.HeightLayer[_candidate];
                                    if ((_cLogic & 0x10000000) != 0) {
                                        /*
                                          candidate is keep
                                         */
                                        _keepHeight
                                            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                                                    getBuildingHeightForBuildingID,
                                                DAT_BuildingsState::ptr)(
                                                (int)DAT_TileMapState::instance.BuildingLayer[_candidate]);
                                        _cHeight = _cHeight + _keepHeight;
                                    }
                                    /*
                                      test if height difference is within margin
                                     */
                                    if ((int)_tHeight <= (int)(_cHeight + 16)
                                        && (int)(_cHeight - 4294967280) <= (int)_tHeight)
                                        goto LAB_00498308;
                                    _cType = DAT_BuildingsState::instance
                                                 .buildings[DAT_TileMapState::instance.BuildingLayer[_candidate]]
                                                 .buildingType;
                                    _tDiff = 0;
                                    if ((_cType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)
                                        || (_cType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)) {
                                        _cHeight = _cHeight - 90;
                                    } else {
                                        _tType = DAT_BuildingsState::instance
                                                     .buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                                                     .buildingType;
                                        if ((_tType != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)
                                            && (_tType != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))
                                            goto LAB_0049838d;
                                        _tDiff = -90;
                                    }
                                    /*
                                      test if height difference is within margin
                                     */
                                    if ((int)(_tHeight + _tDiff) <= (int)(_cHeight + 0x10)
                                        && (int)(_cHeight - 0x10) <= (int)(_tHeight + _tDiff))
                                        goto LAB_00498308;
                                }
                            }
                        } else {
                        LAB_00498308:
                            /*
                              add to queue   also jumped to when height difference is within margin
                             */
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            short sVar3
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                      + _direction * 8 + 4)
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                LAB_0049838d:
                    _direction = _direction + 1;
                    paiVar4 = (int (*)[8])(*paiVar4 + 1);
                } while (_direction < 8);
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a0f < this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
                }
            this->searchNonmatchCount = this->searchNonmatchCount + 1;
            return FALSE;
        }

    }
}
}
