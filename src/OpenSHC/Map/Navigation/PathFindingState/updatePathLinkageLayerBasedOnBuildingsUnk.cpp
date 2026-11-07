#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004999C0
        BOOLEnum PathFindingState::updatePathLinkageLayerBasedOnBuildingsUnk(int yUnk, int tile)
        {
            int iVar6;
            int (*paiVar8)[8];
            uint _height;
            int _directionIndex;
            int _building;
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
            if (_building != 0) {
                _buildingType = DAT_BuildingsState::instance.buildings[_building].buildingType;
                _result
                    = (BOOLEnum)(DAT_BuildingDefinedData::instance.BuildingIsGateHouseArray[(short)_buildingType] != 0);
                if (DAT_BuildingDefinedData::instance.BuildingIsKeepArray[(short)_buildingType] != 0) {
                    _result = TRUE;
                }
            }
            int bVar2 = 0;
            int bVar4 = 0;
            int bVar3 = 0;
            int bVar5 = 0;
            byte bVar7 = 0;
            iVar6 = 0;
            _linkageResult = 0;
            DAT_TileMapState::instance.PathLinkageLayer[tile] = 0;
            // classify the tile itself
            if ((_logic & 0x800000) == 0) {
                if ((_logic & 0x10000000) != 0) {
                    bVar2 = 1;
                    iVar6 = 1;
                } else if ((_logic & 2) != 0 || (_logic & 0x200000) != 0) {
                    bVar5 = 1;
                } else if ((_logic & 0x800) != 0) {
                    bVar4 = 1;
                } else if ((_logic & 0x400000) != 0) {
                    return _result;
                } else if ((_logic & 0x100) != 0) {
                    bVar3 = 1;
                    if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                        iVar6 = 2;
                    }
                } else if ((_logic & 0x4a5014b1) != 0) {
                    return _result;
                } else {
                    bVar5 = 1;
                }
            }
            paiVar8 = DAT_TileMapState::instance.directionTranslationMatrix + yUnk;
            for (_directionIndex = 0; _directionIndex < 8;
                _directionIndex = _directionIndex + 1, paiVar8 = (int (*)[8])(*paiVar8 + 1)) {
                int _tile = (*paiVar8)[0] + tile;
                _logic = DAT_TileMapState::instance.LogicLayer[_tile];
                local_20[_directionIndex] = _logic;
                // which neighbours can be linked at all; structures count into bVar7 for the corner checks below
                if ((_logic & 0x200000) == 0) {
                    if ((_logic & 0x800) != 0) {
                        if (iVar6 == 1 || (char)DAT_TileMapState::instance.DamageLayer[_tile] > 0x14) {
                            continue;
                        }
                    } else if ((_logic & 2) != 0) {
                        if (bVar2) {
                            continue;
                        }
                        if ((_logic & 0x400) != 0 && DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                            continue;
                        }
                    } else if ((_logic & 0x400) != 0) {
                        if (DAT_BuildingDefinedData::instance.field_0x1774[(short)DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                                    .buildingType]
                            != FALSE) {
                            bVar7 = bVar7
                                + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        }
                        continue;
                    } else if ((_logic & 0x10000000) != 0) {
                        bVar7
                            = bVar7 + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                    } else if ((_logic & 0x400000) != 0) {
                        bVar7
                            = bVar7 + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        continue;
                    } else if ((_logic & 0x100) != 0) {
                        bVar7
                            = bVar7 + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                    } else if ((_logic & 0x30) != 0) {
                        bVar7
                            = bVar7 + DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
                        continue;
                    } else if ((_logic & 0x4a5014b1) != 0) {
                        continue;
                    }
                }
                // damaged gates and walls do not link, and neither do heights more than 16 apart
                if ((_logic & 0x10000000) != 0) {
                    if (!bVar2) {
                        if (!bVar3) {
                            continue;
                        }
                        if ((char)DAT_TileMapState::instance.DamageLayer[tile] > 0x14) {
                            continue;
                        }
                    }
                } else if ((_logic & 0x100) != 0 && iVar6 != 0) {
                    if ((char)DAT_TileMapState::instance.DamageLayer[_tile] > 0x14) {
                        continue;
                    }
                } else if ((bVar3 || bVar4) && (_logic & 0x100) != 0
                    && DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                    if ((char)DAT_TileMapState::instance.DamageLayer[tile] > 0x14) {
                        continue;
                    }
                } else {
                    _logic = (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                    if ((int)_logic < local_28) {
                        continue;
                    }
                    if ((int)_logic > (int)local_24) {
                        continue;
                    }
                }
                _linkageResult
                    = _linkageResult | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_directionIndex];
            }
            if (bVar5) {
                if ((_linkageResult & 1) == 0 && (bVar7 & 1) != 0) {
                    if ((_linkageResult & 4) == 0 && (bVar7 & 4) != 0) {
                        _linkageResult = _linkageResult & 0xfd;
                    }
                    if ((_linkageResult & 0x40) == 0 && (bVar7 & 0x40) != 0) {
                        _linkageResult = _linkageResult & 0x7f;
                    }
                }
                if ((_linkageResult & 0x10) == 0 && (bVar7 & 0x10) != 0) {
                    if ((_linkageResult & 4) == 0 && (bVar7 & 4) != 0) {
                        _linkageResult = _linkageResult & 0xf7;
                    }
                    if ((_linkageResult & 0x40) == 0 && (bVar7 & 0x40) != 0) {
                        _linkageResult = _linkageResult & 0xdf;
                    }
                }
            } else {
                if ((local_20[0] & 0x10000100) != 0 && (local_20[2] & 0x10000100) != 0
                    && (local_20[1] & 0x10000100) == 0 && (local_20[1] & 2) == 0 && (local_20[0] & 0x800) == 0
                    && (local_20[2] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xfd;
                }
                if ((local_20[0] & 0x10000100) != 0 && (local_20[6] & 0x10000100) != 0
                    && (local_20[7] & 0x10000100) == 0 && (local_20[7] & 2) == 0 && (local_20[0] & 0x800) == 0
                    && (local_20[6] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0x7f;
                }
                if ((local_20[4] & 0x10000100) != 0 && (local_20[2] & 0x10000100) != 0
                    && (local_20[3] & 0x10000100) == 0 && (local_20[3] & 2) == 0 && (local_20[4] & 0x800) == 0
                    && (local_20[2] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xf7;
                }
                if ((local_20[4] & 0x10000100) != 0 && (local_20[6] & 0x10000100) != 0
                    && (local_20[5] & 0x10000100) == 0 && (local_20[5] & 2) == 0 && (local_20[4] & 0x800) == 0
                    && (local_20[6] & 0x800) == 0) {
                    _linkageResult = _linkageResult & 0xdf;
                }
            }
            DAT_TileMapState::instance.PathLinkageLayer[tile] = _linkageResult;
            return _result;
        }

    }
}
}
