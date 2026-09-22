#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE930
    void AICState::findAttackTribePositionAndPathToDefenses(int playerID)
    {
        int x = 0;
        int y = 0;
        for (int i = 0; i < 11; i++) {
            int targetUnitID = 0;
            for (int j = 0; j < DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID]
                                  .aiTribeIDs[DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType + j];
                if (tribeID == 0)
                    continue;
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID]
                           .aiTribeUIDs[j + DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType])
                    continue;

                targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                x = DAT_UnitsState::instance.units[targetUnitID].x;
                y = DAT_UnitsState::instance.units[targetUnitID].y;
                break;
            }
            if (targetUnitID != 0)
                break;
        }

        DAT_GameState::instance.playerDataArray[playerID].someTile = 0;
        if (x == 0)
            return;

        int tile = MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::tracePathToFriendlyDefensesAndReturnTileUnk,
            DAT_PathFindingState::ptr)(playerID, x, y);
        if (tile <= 0)
            return;

        short tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
        DAT_GameState::instance.playerDataArray[playerID].someTile = tile;
        DAT_GameState::instance.playerDataArray[playerID].someY = tileY;
        DAT_GameState::instance.playerDataArray[playerID].someX
            = tile - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
    }
}
}
