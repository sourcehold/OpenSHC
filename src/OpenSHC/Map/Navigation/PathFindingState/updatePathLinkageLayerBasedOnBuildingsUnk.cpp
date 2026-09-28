#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
            using OpenSHC::Map::Buildings::BuildingTypeShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004999C0
        BOOLEnum PathFindingState::updatePathLinkageLayerBasedOnBuildingsUnk(int yUnk, int tile)
        {
            byte bVar1;
            bool bVar2;
            bool bVar3;
            bool bVar4;
            bool bVar5;
            int iVar6;
            int _tile;
            byte bVar7;
            int (*paiVar8)[8];
            uint _height;
            int _directionIndex;
            int _building;
            bool bVar9;
            bool bVar10;
            bool bVar11;
            byte _linkageResult;
            BOOLEnum _result;
            int local_28;
            uint local_24;
            uint local_20[8];
            BuildingTypeShort _buildingType;
            uint _logic;
            _logic = DAT_TileMapState::instance.LogicLayer[tile];
            _height = (uint)DAT_TileMapState::instance.HeightLayer[tile];
            _building = (int)DAT_TileMapState::instance.BuildingLayer[tile];
            _result = FALSE;
            if ((_logic & 0x10000000) != 0) {
                iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(_building);
                _height = _height + iVar6;
            }
            local_24 = _height + 0x10;
            local_28 = _height - 0x10;
            if ((_building != 0)
                && (_buildingType = DAT_BuildingsState::instance.buildings[_building].buildingType,
                    _result
                    = (BOOLEnum)(DAT_BuildingDefinedData::instance.BuildingIsGateHouseArray[(short)_buildingType] != 0),
                    DAT_BuildingDefinedData::instance.BuildingIsKeepArray[(short)_buildingType] != 0)) {
                _result = TRUE;
            }
            bVar2 = false;
            bVar4 = false;
            bVar3 = false;
            bVar5 = false;
            bVar7 = 0;
            iVar6 = 0;
            _linkageResult = 0;
            DAT_TileMapState::instance.PathLinkageLayer[tile] = '\0';
            if ((_logic & 0x800000) == 0) {
                if ((_logic & 0x10000000) == 0) {
                    if (((_logic & 2) == 0) && ((_logic & 0x200000) == 0)) {
                        if ((_logic & 0x800) != 0) {
                            bVar4 = true;
                            goto LAB_00499ada;
                        }
                        if ((_logic & 0x400000) != 0) {
                            return _result;
                        }
                        if ((_logic & 0x100) != 0) {
                            bVar3 = true;
                            if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                                iVar6 = 2;
                            }
                            goto LAB_00499ada;
                        }
                        if ((_logic & 0x4a5014b1) != 0) {
                            return _result;
                        }
                    }
                    bVar5 = true;
                } else {
                    bVar2 = true;
                    iVar6 = 1;
                }
            }
        LAB_00499ada:
            _directionIndex = 0;
            paiVar8 = DAT_TileMapState::instance.directionTranslationMatrix + yUnk;
            do {
                _tile = (*paiVar8)[0] + tile;
                _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                local_20[_directionIndex] = _logic;
                if ((_logic & 0x200000) == 0) {
                    if ((_logic & 0x800) != 0) {
                        if ((iVar6 == 1) || ('\x14' < (char)DAT_TileMapState::instance.DamageLayer[_tile]))
                            goto LAB_00499c4b;
                        goto LAB_00499bce;
                    }
                    if ((_logic & 2) == 0) {
                        if ((_logic & 0x400) == 0) {
                            if ((_logic & 0x10000000) != 0) {
                                bVar7 = bVar7
                                    + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                                goto LAB_00499bce;
                            }
                            if ((_logic & 0x400000) == 0) {
                                if ((_logic & 0x100) != 0) {
                                    bVar7 = bVar7
                                        + DAT_ClimbLogicDefinedData::instance
                                              .BitFlagHelperForPathLinkage[_directionIndex];
                                    goto LAB_00499bce;
                                }
                                if ((_logic & 0x30) == 0) {
                                    bVar9 = (_logic & 0x4a5014b1) == 0;
                                    goto LAB_00499bcc;
                                }
                                bVar7 = bVar7
                                    + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                            } else {
                                bVar7 = bVar7
                                    + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                            }
                        } else if (DAT_BuildingDefinedData::instance.field17_0x1774[(short)DAT_BuildingsState::instance
                                           .buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                                           .buildingType]
                            != FALSE) {
                            bVar7 = bVar7
                                + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        }
                    } else if (!bVar2) {
                        if ((_logic & 0x400) != 0) {
                            bVar9 = DAT_TileMapState::instance.BuildingLayer[_tile] == 0;
                        LAB_00499bcc:
                            if (!bVar9)
                                goto LAB_00499c4b;
                        }
                        goto LAB_00499bce;
                    }
                } else {
                LAB_00499bce:
                    if ((_logic & 0x10000000) == 0) {
                        if (((_logic & 0x100) == 0) || (iVar6 == 0)) {
                            if (((bVar3) || (bVar4))
                                && ((
                                    (_logic & 0x100) != 0 && (DAT_TileMapState::instance.BuildingLayer[_tile] != 0)))) {
                                bVar1 = DAT_TileMapState::instance.DamageLayer[tile];
                                bVar11 = (bVar1 < '\x14');
                                bVar10 = (char)(bVar1 - 0x14) < '\0';
                                bVar9 = bVar1 == 0x14;
                            } else {
                                _logic = (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                                if ((int)_logic < local_28)
                                    goto LAB_00499c4b;
                                bVar11 = (_logic < local_24);
                                bVar10 = (int)(_logic - local_24) < 0;
                                bVar9 = _logic == local_24;
                            }
                        } else {
                            bVar1 = DAT_TileMapState::instance.DamageLayer[_tile];
                            bVar11 = (bVar1 < '\x14');
                            bVar10 = (char)(bVar1 - 0x14) < '\0';
                            bVar9 = bVar1 == 0x14;
                        }
                    LAB_00499c3f:
                        if (!bVar9 && bVar11 == bVar10)
                            goto LAB_00499c4b;
                    } else if (!bVar2) {
                        if (!bVar3)
                            goto LAB_00499c4b;
                        bVar1 = DAT_TileMapState::instance.DamageLayer[tile];
                        bVar11 = (bVar1 < '\x14');
                        bVar10 = (char)(bVar1 - 0x14) < '\0';
                        bVar9 = bVar1 == 0x14;
                        goto LAB_00499c3f;
                    }
                    _linkageResult = _linkageResult
                        | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                }
            LAB_00499c4b:
                _directionIndex = _directionIndex + 1;
                paiVar8 = (int (*)[8])(*paiVar8 + 1);
                if (7 < _directionIndex) {
                    if (bVar5) {
                        if (((_linkageResult & 1) == 0) && ((bVar7 & 1) != 0)) {
                            if (((_linkageResult & 4) == 0) && ((bVar7 & 4) != 0)) {
                                _linkageResult = _linkageResult & 0xfd;
                            }
                            if (((_linkageResult & 0x40) == 0) && ((bVar7 & 0x40) != 0)) {
                                _linkageResult = _linkageResult & 0x7f;
                            }
                        }
                        if (((_linkageResult & 0x10) == 0) && ((bVar7 & 0x10) != 0)) {
                            if (((_linkageResult & 4) == 0) && ((bVar7 & 4) != 0)) {
                                _linkageResult = _linkageResult & 0xf7;
                            }
                            if (((_linkageResult & 0x40) == 0) && ((bVar7 & 0x40) != 0)) {
                                _linkageResult = _linkageResult & 0xdf;
                            }
                        }
                    } else {
                        if ((((((local_20[0] & 0x10000100) != 0) && ((local_20[2] & 0x10000100) != 0))
                                 && ((local_20[1] & 0x10000100) == 0))
                                && (((local_20[1] & 2) == 0 && ((local_20[0] & 0x800) == 0))))
                            && ((local_20[2] & 0x800) == 0)) {
                            _linkageResult = _linkageResult & 0xfd;
                        }
                        if ((((local_20[0] & 0x10000100) != 0) && ((local_20[6] & 0x10000100) != 0))
                            && (((local_20[7] & 0x10000100) == 0
                                && ((((local_20[7] & 2) == 0 && ((local_20[0] & 0x800) == 0))
                                    && ((local_20[6] & 0x800) == 0)))))) {
                            _linkageResult = _linkageResult & 0x7f;
                        }
                        if (((((local_20[4] & 0x10000100) != 0) && ((local_20[2] & 0x10000100) != 0))
                                && (((local_20[3] & 0x10000100) == 0
                                    && (((local_20[3] & 2) == 0 && ((local_20[4] & 0x800) == 0))))))
                            && ((local_20[2] & 0x800) == 0)) {
                            _linkageResult = _linkageResult & 0xf7;
                        }
                        if (((((local_20[4] & 0x10000100) != 0) && ((local_20[6] & 0x10000100) != 0))
                                && ((local_20[5] & 0x10000100) == 0))
                            && ((((local_20[5] & 2) == 0 && ((local_20[4] & 0x800) == 0))
                                && ((local_20[6] & 0x800) == 0)))) {
                            _linkageResult = _linkageResult & 0xdf;
                        }
                    }
                    DAT_TileMapState::instance.PathLinkageLayer[tile] = _linkageResult;
                    return _result;
                }
            } while (true);
        }

    }
}
}
