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
            int iVar1;
            short* psVar3;
            uint y;
            uint x;
            if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                || (0x9f < DAT_GameState::instance.mapAndTime.wildlifeCount)) {}
            int iVar2 = 0;
            psVar3 = DAT_GameState::instance.mapAndTime.playerPopulationStatistics[6] + 0xe4;
            do {
                if (iVar2 < 4) {
                    x = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar2][0];
                    y = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar2][1];
                LAB_005262f6:
                    if (x < 400 && y < 400 && *(char*)(y * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + x) != '\0'
                        && (iVar1 = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x,
                            (DAT_TileMapState::instance.LogicLayer[iVar1] & 0x50501581U) == 0)) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                            Commands::M_MAPPER_RABBIT, x, y, (int)(DAT_TileMapState::instance.HeightLayer[iVar1]));
                        this->unknownX_01 = x;
                        this->unknownY_01 = y;
                    }
                } else if (DAT_GameState::instance.mapAndTime.mercRecruitable[iVar2 + 4] != 0) {
                    x = *(uint*)(psVar3 + -2);
                    y = *(uint*)psVar3;
                    goto LAB_005262f6;
                }
                iVar2 = iVar2 + 1;
                psVar3 = psVar3 + 400;
                if (0xb < iVar2) {}
            } while (true);
        }

    }
}
}
