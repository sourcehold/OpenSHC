#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456870
    void GameStateStructures::nof_fpoints_locationFinder()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
            DAT_PathFindingState::ptr)(DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[0][0],
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[0][1], -1, -1, 1000000, 0);
        DAT_PathFindingState::instance.calculations = DAT_PathFindingState::instance.calculations + 1;
        DAT_PathFindingState::instance.searchQueue.readIndex = 0;
        if (DAT_PathFindingState::instance.searchQueue.writeIndex == 0) {
            return;
        }
        int pairIndex = 0;
        do {
            uint y = DAT_PathFindingState::instance.searchQueue
                         .yQueue[DAT_PathFindingState::instance.searchQueue.readIndex];
            int tile = DAT_PathFindingState::instance.searchQueue
                           .tilesQueue[DAT_PathFindingState::instance.searchQueue.readIndex];
            uint x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            if (DAT_TileMapState::instance.CertainPathLayer[tile] != 100) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer,
                    DAT_PathFindingState::ptr)(x, y, 100, 0x3c);
                this->mapAndTime.somePairArray[pairIndex].x = x;
                this->mapAndTime.somePairArray[pairIndex].y = y;
                pairIndex = pairIndex + 1;
            }
            if (pairIndex >= 40) {
                return;
            }
            DAT_PathFindingState::instance.searchQueue.readIndex
                = DAT_PathFindingState::instance.searchQueue.readIndex + 1;
            if (DAT_PathFindingState::instance.searchQueue.readIndex > 0x13a0f) {
                DAT_PathFindingState::instance.searchQueue.readIndex = 0;
            }
        } while (DAT_PathFindingState::instance.searchQueue.readIndex
            != DAT_PathFindingState::instance.searchQueue.writeIndex);
    }
}
}
