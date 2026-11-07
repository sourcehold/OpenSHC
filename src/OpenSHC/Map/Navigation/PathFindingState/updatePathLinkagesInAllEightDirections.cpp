#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A5F90
        void PathFindingState::updatePathLinkagesInAllEightDirections(int y, int tile)
        {
            BOOLEnum _someLinkageResult = FALSE;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                y, tile);
            for (int _direction = 0; _direction < 8; ++_direction) {
                int _nextTile = DAT_TileMapState::instance.directionTranslationMatrix[y][_direction] + tile;
                int _nextY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset + y;
                BOOLEnum _tileIsKeepUnk = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    _nextY, _nextTile);
                if (_tileIsKeepUnk != FALSE) {
                    _someLinkageResult = TRUE;
                }
            }

            if (_someLinkageResult) {
                DAT_BuildingsState::instance.pathLinkageKeepWasUpdatedUnk = 1;
            }
        }

    }
}
}
