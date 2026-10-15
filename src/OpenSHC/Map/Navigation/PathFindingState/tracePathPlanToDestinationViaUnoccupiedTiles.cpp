#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
             @return bool whether destination was reached   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
#pragma optimize("y", off) // original keeps an ebp frame
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A370
        BOOLEnum PathFindingState::tracePathPlanToDestinationViaUnoccupiedTiles(uint x, uint y, uint destX, uint destY)
        {
            byte* _pPathPlan;
            int _budget;
            int _direction;
            uint _ppIndexInit;
            uint _ppIndex;
            Point8* _cardinal;
            int* _dirMatrix;
            uchar* _linkage;
            uchar* _occupancy;
            int _fireCount;
            int _destTile;
            uint _gen;
            int _tile;
            short* _walkLayer;
            if (399 < x || 399 < y) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            if (399 < destX || 399 < destY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] == '\0') {
                return FALSE;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            _budget = 0;
            _ppIndexInit = 0;
            _direction = 0;
            _gen = (ushort)this->searchGeneration;
            _fireCount = DAT_EntityState::instance.fireCount;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            _destTile = DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile + destX;
            _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            _walkLayer = DAT_TileMapState::instance.WalkLayer;
            _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            _cardinal = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix;
            _ppIndex = this->searchQueue.pathPlanIndex;
            _pPathPlan = this->searchQueue.ptrPathPlan;
            while (true) {
                _budget = _budget + 1;
                if (399 < _budget) {
                    break;
                }
                _walkLayer[_tile] = (short)_gen;
                if (_tile == _destTile) {
                    this->searchQueue.pathPlanIndex = _ppIndex;
                    return TRUE;
                }
                if (_fireCount != 0 && _occupancy[_tile] != '\0') {
                    break;
                }
                int _canTraverseThisDirection = _linkage[_tile];
                if ((int)destY < (int)y) {
                    if ((int)destX < (int)x) {
                        _direction = 7;
                        _canTraverseThisDirection = _canTraverseThisDirection & 0x80;
                    } else if ((int)x < (int)destX) {
                        _direction = 1;
                        _canTraverseThisDirection = _canTraverseThisDirection & 2;
                    } else {
                        _direction = 0;
                        _canTraverseThisDirection = _canTraverseThisDirection & 1;
                    }
                } else if ((int)y < (int)destY) {
                    if ((int)destX < (int)x) {
                        _direction = 5;
                        _canTraverseThisDirection = _canTraverseThisDirection & 0x20;
                    } else if ((int)x < (int)destX) {
                        _direction = 3;
                        _canTraverseThisDirection = _canTraverseThisDirection & 8;
                    } else {
                        _direction = 4;
                        _canTraverseThisDirection = _canTraverseThisDirection & 0x10;
                    }
                } else if ((int)destX < (int)x) {
                    _direction = 6;
                    _canTraverseThisDirection = _canTraverseThisDirection & 0x40;
                } else {
                    if ((int)destX <= (int)x) {
                        break;
                    }
                    _direction = 2;
                    _canTraverseThisDirection = _canTraverseThisDirection & 4;
                }
                if (_canTraverseThisDirection == 0) {
                    break;
                }
                _tile = _tile + _dirMatrix[y * 8 + _direction];
                x = x + _cardinal[_direction].int_.xOffset;
                y = y + _cardinal[_direction].int_.yOffset;
                if ((_ppIndex & 1) == 0) {
                    _pPathPlan[_ppIndex >> 1] = (byte)_direction;
                } else {
                    _pPathPlan[_ppIndex >> 1] = (_pPathPlan[_ppIndex >> 1] & 0xf) | (byte)(_direction << 4);
                }
                _ppIndex = _ppIndex + 1;
            }
            this->searchQueue.pathPlanIndex = _ppIndex;
            return FALSE;
        }
    }
#pragma optimize("", on)
}
}
