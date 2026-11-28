#include "../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052E120
    void WildlifeState::updateNofFpoints()
    {
        uint const signX = DAT_GameState::instance.mapAndTime
                               .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field_0x469d4]
                               .x;
        uint const signY = DAT_GameState::instance.mapAndTime
                               .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field_0x469d4]
                               .y;
        if (signX > 399 || signY > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[signY * 400 + signX] == '\0') {
            return;
        }
        int const separateAreaID
            = (short)DAT_TileMapState::instance
                  .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[signY].addXgetTile + signX];
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            return;
        }
        MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillCasDisFromSignpost, this)();
        DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
        for (int i = 0; i < 50; i++) {
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][3] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][2] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][1] = 0;
            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][0] = 0;
        }
        for (int gridY = 0; gridY < 40; gridY++) {
            uint const y = gridY * 10 + 5;
            for (int gridX = 0; gridX < 40; gridX++) {
                uint const x = gridX * 10 + 5;
                if (!this->grid[gridX][gridY].field_0x6c || this->grid[gridX][gridY].firstMember <= 0) {
                    continue;
                }
                int const areaID
                    = (short)DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                if (separateAreaID != areaID || x > 399 || y > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                    continue;
                }
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][0] = (short)x;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = (short)y;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = (short)areaID;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                    = (short)this->grid[gridX][gridY].field_0x70;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                    = (short)this->grid[gridX][gridY].casDisRelated2;
                DAT_TroopValueState::instance.attackInfo
                    .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                    = (DAT_TroopValueState::instance.attackInfo
                              .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                          + 4)
                        * 50
                    - DAT_TroopValueState::instance.attackInfo
                          .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                DAT_TroopValueState::instance.attackInfo.nof_fpoints
                    = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
            }
        }
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.nof_fpoints - 1; i++) {
                if (DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1][6]
                    < DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i][6]) {
                    swapped = true;
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy);
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1],
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i]);
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy,
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[i + 1]);
                }
            }
        } while (swapped);
    }

}
}
