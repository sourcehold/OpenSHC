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
            bool _someLinkageResult;
            _someLinkageResult = false;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                y, tile);
            paiVar1 = DAT_TileMapState::instance.directionTranslationMatrix + y;
            piVar2 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
            do {
                BOOLEnum _tileIsKeepUnk = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerBasedOnBuildingsUnk, this)(
                    *piVar2 + y, (*paiVar1)[0] + tile);
                if (_tileIsKeepUnk != FALSE) {
                    _someLinkageResult = true;
                }
                piVar2 = piVar2 + 2;
                paiVar1 = (int (*)[8])(*paiVar1 + 1);
            } while ((int)piVar2 < 0xb4908c);
            if (_someLinkageResult) {
                DAT_BuildingsState::instance.pathLinkageKeepWasUpdatedUnk = 1;
            }
            return;
        }

    }
}
}
