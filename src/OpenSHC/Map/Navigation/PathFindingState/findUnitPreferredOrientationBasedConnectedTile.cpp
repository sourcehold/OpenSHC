#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
            using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8780
        int PathFindingState::findUnitPreferredOrientationBasedConnectedTile(int unitID, int tile)
        {
            int _x;
            dword _toArea;
            int _can;
            XYPair* pXVar1;
            int _y;
            int _candidate;
            ushort _area;
            _y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            _x = tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                DAT_DirectionAlgorithmState::ptr)(_x, _y, (int)((int)(DAT_UnitsState::instance.units[unitID].x)),
                (int)((int)(DAT_UnitsState::instance.units[unitID].y)));
            _area = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            pXVar1
                = DAT_ClimbLogicDefinedData::instance
                      .OrderedOrientationBasedCardinalDirectionList[DAT_DirectionAlgorithmState::instance.orientation];
            tile = 0;
            while (true) {
                _candidate = DAT_ViewportRenderState::instance.translationMatrix[pXVar1->y + _y].addXgetTile
                    + ((XYPair*)&pXVar1->x)->x + _x;
                _toArea = (dword) * (short*)((int)DAT_TileMapState::ptr + _candidate * 2 + 0x363ed0);
                if (((int)(short)_area == _toArea)
                    || (_can = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                            this)((int)DAT_UnitsState::instance.units[unitID].owner, (dword)((int)((int)(short)_area)),
                            (dword)((int)(_toArea)), 0),
                        _can != 0))
                    break;
                tile = tile + 1;
                pXVar1 = pXVar1 + 1;
                if (3 < tile) {
                    return 0;
                }
            }
            return _candidate;
        }

    }
}
}
