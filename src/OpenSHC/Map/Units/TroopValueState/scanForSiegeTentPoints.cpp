#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F5C0
        void TroopValueState::scanForSiegeTentPoints()
        {
            int* piVar6;
            int iVar7;
            int iVar8;
            uint _x;
            uint _y;
            int (*local_1c)[8];
            int _candidateTile;
            int local_14;
            int local_10;
            int _index;
            DAT_TroopValueState::instance.attackInfo.tentPoints = 0;
            _candidateTile = 0;
            do {
                if ((DAT_TileMapState::instance.AIInfoLayer[_candidateTile] == '\b')
                    && (iVar7 = 0, DAT_TileMapState::instance.UnitLayer[_candidateTile] == 0)) {
                    _y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_candidateTile];
                    uint uVar5 = (uint)DAT_TileMapState::instance.HeightLayer[_candidateTile];
                    local_1c = DAT_TileMapState::instance.directionTranslationMatrix + _y;
                    for (local_10 = 0; local_10 < 8; local_10++) {
                        uint uVar1 = (uint) * (byte*)((*local_1c)[0] + 0x1d32c38 + _candidateTile);
                        iVar8 = (*local_1c)[0] + _candidateTile;
                        if ((((uVar5 + 6 < uVar1) || ((int)uVar1 < (int)(uVar5 - 6)))
                                || (DAT_TileMapState::instance.UnitLayer[iVar8] != 0))
                            || (((short)DAT_TileMapState::instance.PathConnectionLayer[iVar8]
                                    != DAT_TroopValueState::instance.attackInfo.startCon
                                || ((DAT_TileMapState::instance.LogicLayer[iVar8] & 0xa0002400U)))))
                            break;
                        uVar1 = uVar5 + 8;
                        local_14 = 0;
                        piVar6 = DAT_TileMapState::instance.directionTranslationMatrix[_y] + 1;
                        do {
                            uint uVar4 = (uint) * (byte*)((*(int (*)[8])(piVar6 + -1))[0] + 0x1d32c38 + iVar8);
                            int iVar2 = (*(int (*)[8])(piVar6 + -1))[0] + iVar8;
                            if (((uVar1 < uVar4) || ((int)uVar4 < (int)(uVar5 - 8)))
                                || ((DAT_TileMapState::instance.UnitLayer[iVar2] != 0
                                    || (((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2]
                                            != DAT_TroopValueState::instance.attackInfo.startCon
                                        || ((DAT_TileMapState::instance.LogicLayer[iVar2] & 0xa0002400U)))))))
                                break;
                            uVar4 = (uint) * (byte*)(*piVar6 + 0x1d32c38 + iVar8);
                            iVar2 = *piVar6 + iVar8;
                            if (((uVar1 < uVar4)
                                    || ((((((int)uVar4 < (int)(uVar5 - 8)
                                               || (DAT_TileMapState::instance.UnitLayer[iVar2] != 0))
                                              || ((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2]
                                                  != DAT_TroopValueState::instance.attackInfo.startCon))
                                             || ((uVar4 = DAT_TileMapState::instance.LogicLayer[iVar2],
                                                 (uVar4 & 0x2000) != 0 || ((uVar4 & 0x20000000)))))
                                        || ((int)uVar4 < 0))))
                                || ((uVar4 & 0x400))) {
                                iVar7 = iVar7 + 1;
                                break;
                            }
                            uVar4 = (uint) * (byte*)(piVar6[1] + 0x1d32c38 + iVar8);
                            iVar2 = piVar6[1] + iVar8;
                            if ((((uVar1 < uVar4) || ((int)uVar4 < (int)(uVar5 - 8)))
                                    || ((DAT_TileMapState::instance.UnitLayer[iVar2] != 0
                                        || ((((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2]
                                                     != DAT_TroopValueState::instance.attackInfo.startCon
                                                 || (uVar4 = DAT_TileMapState::instance.LogicLayer[iVar2],
                                                     (uVar4 & 0x2000) != 0))
                                            || ((uVar4 & 0x20000000)))))))
                                || (((int)uVar4 < 0 || ((uVar4 & 0x400))))) {
                                iVar7 = iVar7 + 2;
                                break;
                            }
                            uVar4 = (uint) * (byte*)(piVar6[2] + 0x1d32c38 + iVar8);
                            iVar2 = piVar6[2] + iVar8;
                            if ((((uVar1 < uVar4) || ((int)uVar4 < (int)(uVar5 - 8)))
                                    || ((DAT_TileMapState::instance.UnitLayer[iVar2] != 0
                                        || ((((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2]
                                                     != DAT_TroopValueState::instance.attackInfo.startCon
                                                 || (uVar4 = DAT_TileMapState::instance.LogicLayer[iVar2],
                                                     (uVar4 & 0x2000) != 0))
                                            || ((uVar4 & 0x20000000)))))))
                                || (((int)uVar4 < 0 || ((uVar4 & 0x400))))) {
                                iVar7 = iVar7 + 3;
                                break;
                            }
                            local_14 = local_14 + 4;
                            piVar6 = piVar6 + 4;
                            iVar7 = iVar7 + 4;
                        } while (local_14 < 8);
                        local_1c = (int (*)[8])(*local_1c + 1);
                    }
                    if (64 < iVar7) {
                        _x = _candidateTile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                        BOOLEnum BVar3
                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(6, _x, _y, 0x80);
                        if (!BVar3) {
                            DAT_TileMapState::instance.AIInfoLayer[_candidateTile]
                                = DAT_TileMapState::instance.AIInfoLayer[_candidateTile] | 0x80;
                            int _sIndex = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::getSiegeIndexForTile, this)(_candidateTile);
                            _index = DAT_TroopValueState::instance.attackInfo.tentPointsNext;
                            if (!_sIndex) {
                                DAT_TroopValueState::instance.attackInfo
                                    .tentPointsValues[DAT_TroopValueState::instance.attackInfo.tentPointsNext]
                                    .x = _x;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].y = _y;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tile = _candidateTile;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].someCounter
                                    = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].zero = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].three = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tribeUID = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tribeID = 0;
                            } else {
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_sIndex].someCounter
                                    = DAT_TroopValueState::instance.attackInfo.someCounter1;
                            }
                            DAT_TroopValueState::instance.attackInfo.tentPoints
                                = DAT_TroopValueState::instance.attackInfo.tentPoints + 1;
                            if (1999 < DAT_TroopValueState::instance.attackInfo.tentPoints) {}
                        }
                    }
                }
                _candidateTile = _candidateTile + 1;
                if (0x13a0f < _candidateTile) {}
            } while (true);
        }

    }
}
}
