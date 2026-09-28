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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A370
        BOOLEnum PathFindingState::tracePathPlanToDestinationViaUnoccupiedTiles(uint x, uint y, uint destX, uint destY)
        {
            byte* pbVar1;
            short _gen_2;
            int _direction;
            int _budget;
            uint _ppIndex;
            int _axgt2;
            byte _canTraverseThisDirection;
            int _fc;
            int _gen;
            byte* _pPathPlan;
            if (399 < x || 399 < y || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                return FALSE;
            }
            if (destX < 400 && destY < 400 && *(char*)(destY * 400 + 0x21aec98 + destX) != '\0') {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                _fc = DAT_EntityState::instance.fireCount;
                _pPathPlan = this->searchQueue.ptrPathPlan;
                _gen = this->searchGeneration;
                _budget = 0;
                int _candidate = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                _axgt2 = DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile;
                _ppIndex = this->searchQueue.pathPlanIndex;
                while (true) {
                    _budget = _budget + 1;
                    if (399 < _budget) {
                        this->searchQueue.pathPlanIndex = _ppIndex;
                        return FALSE;
                    }
                    _gen_2 = (short)_gen;
                    DAT_TileMapState::instance.WalkLayer[_candidate] = _gen_2;
                    /*
                      tile2 matches tile ?
                     */
                    if (_candidate == _axgt2 + destX) {
                        this->searchQueue.pathPlanIndex = _ppIndex;
                        return TRUE;
                    }
                    /*
                      tile is occupied and fire?
                     */
                    if ((_fc != 0) && (DAT_TileMapState::instance.OccupancyLayer[_candidate] != '\0')) {
                        this->searchQueue.pathPlanIndex = _ppIndex;
                        return FALSE;
                    }
                    _canTraverseThisDirection = DAT_TileMapState::instance.PathLinkageLayer[_candidate];
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
                            this->searchQueue.pathPlanIndex = _ppIndex;
                            return FALSE;
                        }
                        _direction = 2;
                        _canTraverseThisDirection = _canTraverseThisDirection & 4;
                    }
                    /*
                      if cannot go any direciton, break
                     */
                    if (_canTraverseThisDirection == 0)
                        break;
                    /*
                      update tile with new direction
                     */
                    _candidate = _candidate + DAT_TileMapState::instance.directionTranslationMatrix[y][_direction];
                    x = x
                        + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset;
                    y = y
                        + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                            + _direction * 8 + 4);
                    /*
                      store direction in path plan
                     */
                    if ((_ppIndex & 1) == 0) {
                        _pPathPlan[_ppIndex >> 1] = (byte)_direction;
                        _ppIndex = _ppIndex + 1;
                    } else {
                        pbVar1 = _pPathPlan + (_ppIndex >> 1);
                        *pbVar1 = *pbVar1 & 0xf;
                        *pbVar1 = *pbVar1 | (byte)(_direction << 4);
                        _ppIndex = _ppIndex + 1;
                    }
                }
                this->searchQueue.pathPlanIndex = _ppIndex;
                return FALSE;
            }
            return FALSE;
        }

    }
}
}
