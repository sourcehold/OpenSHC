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

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5F90
        void PathFindingState::updatePathLinkagesInAllEightDirections(int y, int tile)
        {
            int (*paiVar1)[8];
            int* piVar2;
            int _someLinkageResult;
            _someLinkageResult = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                y, tile);
            for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                BOOLEnum _tileIsKeepUnk = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset + y,
                    DAT_TileMapState::instance.directionTranslationMatrix[y][_direction] + tile);
                if (_tileIsKeepUnk != FALSE) {
                    _someLinkageResult = 1;
                }
            }

            if (_someLinkageResult) {
                DAT_BuildingsState::instance.pathLinkageKeepWasUpdatedUnk = 1;
            }
            return;
        }

    }
}
}
