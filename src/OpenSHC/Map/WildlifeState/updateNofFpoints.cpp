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
        uint uVar1;
        ushort uVar2;
        bool bVar3;
        short* psVar4;
        WildlifeGridElement* piVar5;
        int iVar5;
        uint uVar6;
        int iVar7;
        short sVar8;
        short (*src)[8];
        uint local_10;
        int local_c;
        WildlifeGridElement* local_4;
        ushort _area;
        uint _someX;
        uint _someY;
        ushort _separateAreaID;
        /*
          has nothing to do with mercrecruitable
         */
        uVar6 = DAT_GameState::instance.mapAndTime
                    .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                    .x;
        _someY = DAT_GameState::instance.mapAndTime
                     .signpostEntryData[DAT_TroopValueState::instance.attackInfo.field128056_0x469d4]
                     .y;
        if (uVar6 < 400 && _someY < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_someY * 400 + uVar6] != '\0'
            && (_separateAreaID = DAT_TileMapState::instance
                    .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[_someY].addXgetTile
                        + uVar6],
                DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)) {
            MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillCasDisFromSignpost, this)();
            DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
            psVar4 = DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[0] + 2;
            do {
                psVar4[1] = 0;
                *psVar4 = 0;
                psVar4[-1] = 0;
                (*(short (*)[8])(psVar4 + -2))[0] = 0;
                psVar4 = psVar4 + 8;
            } while ((int)psVar4 < 0x1784940);
            sVar8 = 5;
            local_c = 2000;
            local_4 = &this->grid[0][0];
            local_10 = 60;
            iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints;
            do {
                uVar6 = 0xf;
                piVar5 = local_4;
                do {
                    if ((piVar5->field27_0x6c) && (0 < piVar5->firstMember)) {
                        uVar1 = uVar6 - 10;
                        _area = DAT_TileMapState::instance.MacroLayer[uVar6
                            + *(int*)((int)&DAT_ViewportRenderState::instance.translationMatrix[0].addXgetTile
                                + local_10)
                            + 0x13a06];
                        if (_separateAreaID == _area && uVar1 < 400 && local_10 < 4788
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[local_c + uVar1] != '\0') {
                            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[iVar5][0] = (short)uVar1;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = sVar8;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = _area;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                                = (short)piVar5->field28_0x70;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                = (short)piVar5->casDisRelated2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                                = (DAT_TroopValueState::instance.attackInfo
                                          .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                      + 4)
                                    * 0x32
                                - DAT_TroopValueState::instance.attackInfo
                                      .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                            iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
                            DAT_TroopValueState::instance.attackInfo.nof_fpoints = iVar5;
                        }
                    }
                    if (piVar5[40].field27_0x6c != 0 && 0 < piVar5[40].firstMember
                        && (uVar2 = DAT_TileMapState::instance.PathConnectionLayer
                                [*(int*)((int)&DAT_ViewportRenderState::instance.translationMatrix[0].addXgetTile
                                     + local_10)
                                    + uVar6],
                            _separateAreaID == uVar2)
                        && uVar6 < 400 && local_10 < 0x12b5 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[local_c + uVar6] != '\0') {
                        DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[iVar5][0] = (short)uVar6;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = sVar8;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = uVar2;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                            = (short)piVar5[40].field28_0x70;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                            = (short)piVar5[40].casDisRelated2;
                        DAT_TroopValueState::instance.attackInfo
                            .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                            = (DAT_TroopValueState::instance.attackInfo
                                      .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                  + 4)
                                * 0x32
                            - DAT_TroopValueState::instance.attackInfo
                                  .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                        iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
                        DAT_TroopValueState::instance.attackInfo.nof_fpoints = iVar5;
                    }
                    if ((piVar5[80].field27_0x6c != 0) && (0 < piVar5[80].firstMember)) {
                        uVar1 = uVar6 + 10;
                        uVar2 = DAT_TileMapState::instance.PathConnectionLayer[uVar6
                            + *(int*)((int)&DAT_ViewportRenderState::instance.translationMatrix[0].addXgetTile
                                + local_10)
                            + 10];
                        if (_separateAreaID == uVar2 && uVar1 < 400 && local_10 < 0x12b5
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[local_c + uVar1] != '\0') {
                            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[iVar5][0] = (short)uVar1;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = sVar8;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = uVar2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                                = (short)piVar5[80].field28_0x70;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                = (short)piVar5[80].casDisRelated2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                                = (DAT_TroopValueState::instance.attackInfo
                                          .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                      + 4)
                                    * 0x32
                                - DAT_TroopValueState::instance.attackInfo
                                      .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                            iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
                            DAT_TroopValueState::instance.attackInfo.nof_fpoints = iVar5;
                        }
                    }
                    if ((piVar5[120].field27_0x6c != 0) && (0 < piVar5[120].firstMember)) {
                        uVar1 = uVar6 + 0x14;
                        uVar2 = DAT_TileMapState::instance.PathConnectionLayer[uVar6
                            + *(int*)((int)&DAT_ViewportRenderState::instance.translationMatrix[0].addXgetTile
                                + local_10)
                            + 0x14];
                        if (_separateAreaID == uVar2 && uVar1 < 400 && local_10 < 0x12b5
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[local_c + uVar1] != '\0') {
                            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[iVar5][0] = (short)uVar1;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = sVar8;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = uVar2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                                = (short)piVar5[120].field28_0x70;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                = (short)piVar5[120].casDisRelated2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                                = (DAT_TroopValueState::instance.attackInfo
                                          .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                      + 4)
                                    * 0x32
                                - DAT_TroopValueState::instance.attackInfo
                                      .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                            iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
                            DAT_TroopValueState::instance.attackInfo.nof_fpoints = iVar5;
                        }
                    }
                    if ((piVar5[160].field27_0x6c != 0) && (0 < piVar5[160].firstMember)) {
                        uVar1 = uVar6 + 0x1e;
                        uVar2 = DAT_TileMapState::instance.PathConnectionLayer[uVar6
                            + *(int*)((int)&DAT_ViewportRenderState::instance.translationMatrix[0].addXgetTile
                                + local_10)
                            + 0x1e];
                        if (_separateAreaID == uVar2 && uVar1 < 400 && local_10 < 0x12b5
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[local_c + uVar1] != '\0') {
                            DAT_TroopValueState::instance.attackInfo.nof_fpointsArray[iVar5][0] = (short)uVar1;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][1] = sVar8;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][2] = 0;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][3] = uVar2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4]
                                = (short)piVar5[160].field28_0x70;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                = (short)piVar5[160].casDisRelated2;
                            DAT_TroopValueState::instance.attackInfo
                                .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][6]
                                = (DAT_TroopValueState::instance.attackInfo
                                          .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][5]
                                      + 4)
                                    * 0x32
                                - DAT_TroopValueState::instance.attackInfo
                                      .nof_fpointsArray[DAT_TroopValueState::instance.attackInfo.nof_fpoints][4];
                            iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints + 1;
                            DAT_TroopValueState::instance.attackInfo.nof_fpoints = iVar5;
                        }
                    }
                    uVar6 = uVar6 + 0x32;
                    piVar5 = piVar5 + 200;
                } while ((int)uVar6 < 0x19f);
                local_c = local_c + 4000;
                local_10 = local_10 + 0x78;
                local_4 = local_4 + 1;
                sVar8 = sVar8 + 10;
            } while ((int)local_10 < 0x12fc);
            do {
                bVar3 = false;
                iVar7 = 0;
                if (iVar5 == 1 || iVar5 + -1 < 0) {}
                src = DAT_TroopValueState::instance.attackInfo.nof_fpointsArray;
                do {
                    if (src[1][6] < (*src)[6]) {
                        bVar3 = true;
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(16,
                            (void*)((int)(src)),
                            (void*)((int)(DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy)));
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                            0x10, (void*)((int)(src + 1)), (void*)((int)(src)));
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(0x10,
                            (void*)((int)(DAT_TroopValueState::instance.attackInfo.nof_fpointsArrayCopy)),
                            (void*)((int)(src + 1)));
                        iVar5 = DAT_TroopValueState::instance.attackInfo.nof_fpoints;
                    }
                    iVar7 = iVar7 + 1;
                    src = src + 1;
                } while (iVar7 < iVar5 + -1);
            } while (bVar3);
        }
    }

}
}
