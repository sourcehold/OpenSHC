#include "../UnitsState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F680
        void UnitsState::triggerDesyncIfTileUnitLinkageInvalid(int tile)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && (DAT_GameSynchronyState::instance.syncStatus != 0
                    || DAT_GameSynchronyState::instance.saveRelated != 0)) {
                return;
            }
            if (DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow != 0) {
                return;
            }
            int unitID = DAT_TileMapState::instance.UnitLayer[tile];
            if ((uint)unitID <= 2499) {
                for (; unitID != 0; unitID = this->units[unitID].nextUnitOnTheSameTile) {
                    if (this->units[unitID].tile != tile && this->units[unitID].usingTeleport == 0
                        && this->units[unitID].field_0x413 == 0) {
                        DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)((GameCommandType)79);
                        return;
                    }
                }
                return;
            }
            DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                (GameCommandType)79);
        }

    }
}
}
