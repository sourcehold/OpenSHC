#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Commands::MappersEnum;
        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x005262A0
        void TribesState::spawnWildlifeOrMercAtAvailableSlot()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                || 0xa0 <= DAT_GameState::instance.mapAndTime.wildlifeCount) {
                return;
            }
            /*
              fixme: the merc slots' coordinate pair is reached through a pointer because
              the generated header cannot express it. The original walks
              mapAndTime + 0x1ddc in steps of 0x320 (400 shorts), which is a row stride
              playerPopulationStatistics[9][300] does not have, and reads a dword either
              side of the cursor. mercRecruitable is indexed [_slot + 4] for _slot 4..11,
              which is past the end of its declared int[7] as well. Both arrays need
              correcting in Ghidra before this can be written with named fields.
             */
            /*
              The slot counter is declared before the cursor rather than in the `for`
              header: MSVC assigns registers in declaration order, and the original zeroes
              the counter first (quick_diff 0.9245 -> 0.9434).
             */
            int _slot = 0;
            short* _mercSpawnXY = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[6] + 0xe4;
            for (; _slot < 0xc; _slot = _slot + 1, _mercSpawnXY = _mercSpawnXY + 400) {
                uint x;
                uint y;
                if (_slot < 4) {
                    x = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][0];
                    y = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[_slot][1];
                } else {
                    if (DAT_GameState::instance.mapAndTime.mercRecruitable[_slot + 4] == 0) {
                        continue;
                    }
                    x = *(uint*)(_mercSpawnXY + -2);
                    y = *(uint*)_mercSpawnXY;
                }
                if (x <= 399 && y <= 399
                    && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0) {
                    int const _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x50501581U) == 0) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                            Commands::M_MAPPER_RABBIT, x, y, (int)(DAT_TileMapState::instance.HeightLayer[_tile]));
                        this->unknownX_01 = x;
                        this->unknownY_01 = y;
                        return;
                    }
                }
            }
        }

    }
}
}
