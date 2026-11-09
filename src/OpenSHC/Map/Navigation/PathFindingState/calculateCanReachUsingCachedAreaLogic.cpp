#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A5B00
        BOOLEnum PathFindingState::calculateCanReachUsingCachedAreaLogic(int tile1, int tile2)
        {
            int const _area1 = DAT_TileMapState::instance.PathConnectionLayer[tile1];
            int _area2 = DAT_TileMapState::instance.PathConnectionLayer[tile2];
            if (_area1 == _area2) {
                return TRUE;
            }
            if (_area1 == 0) {
                return FALSE;
            }
            if (_area2 == 0) {
                return FALSE;
            }
            if (this->field_0x90 == 0) {
                this->field_0x90 = 1;
                for (int _index = 0; _index < countof(this->searchQueue.acceptAreaPairArray1); ++_index) {
                    this->searchQueue.acceptAreaPairArray1[_index].area1 = -1;
                    this->searchQueue.acceptAreaPairArray1[_index].area2 = -1;
                    this->searchQueue.rejectionAreaPairArray[_index].area1 = -1;
                    this->searchQueue.rejectionAreaPairArray[_index].area2 = -1;
                }
            } else {
                for (int _index = 0; _index < countof(this->searchQueue.acceptAreaPairArray1); ++_index) {
                    AreaPairInt const& _pair = this->searchQueue.acceptAreaPairArray1[_index];
                    if (_pair.area1 != -1) {
                        if (_pair.area1 == _area1 && _pair.area2 == _area2) {
                            return TRUE;
                        }
                        if (_pair.area2 == _area1 && _pair.area1 == _area2) {
                            return TRUE;
                        }
                    }
                }
                for (int _index = 0; _index < countof(this->searchQueue.rejectionAreaPairArray); ++_index) {
                    AreaPairInt const& _pair = this->searchQueue.rejectionAreaPairArray[_index];
                    if (_pair.area1 != -1) {
                        if (_pair.area1 == _area1 && _pair.area2 == _area2) {
                            return FALSE;
                        }
                        if (_pair.area2 == _area1 && _pair.area1 == _area2) {
                            return FALSE;
                        }
                    }
                }
            }
            int _y1 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile1];
            int _x1 = tile1 - DAT_ViewportRenderState::instance.translationMatrix[_y1].addXgetTile;
            int _y2 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile2];
            int _x2 = tile2 - DAT_ViewportRenderState::instance.translationMatrix[_y2].addXgetTile;
            BOOLEnum const _canReach
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded,
                    this)(_x1, _y1, _x2, _y2, 100000, 0);
            if (_canReach) {
                for (int _index = 0; _index < countof(this->searchQueue.acceptAreaPairArray1); ++_index) {
                    if (this->searchQueue.acceptAreaPairArray1[_index].area1 == -1) {
                        this->searchQueue.acceptAreaPairArray1[_index].area1 = _area1;
                        this->searchQueue.acceptAreaPairArray1[_index].area2 = _area2;
                        return TRUE;
                    }
                }
                return TRUE;
            }
            for (int _index = 0; _index < countof(this->searchQueue.rejectionAreaPairArray); ++_index) {
                if (this->searchQueue.rejectionAreaPairArray[_index].area1 == -1) {
                    this->searchQueue.rejectionAreaPairArray[_index].area1 = _area1;
                    this->searchQueue.rejectionAreaPairArray[_index].area2 = _area2;
                    return FALSE;
                }
            }
            return FALSE;
        }

    }
}
}
