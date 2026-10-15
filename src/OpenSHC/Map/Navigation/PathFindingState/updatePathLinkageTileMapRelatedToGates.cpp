#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00499FA0
        void PathFindingState::updatePathLinkageTileMapRelatedToGates(int buildingID)
        {
            int iVar2;
            int iVar3;
            int _anotherTile;
            int iVar4;
            int _middleTileUnk;
            uint uVar5;
            int _xMiddleUnk;
            int _pl2;
            uint _widthOrHeight;
            _middleTileUnk = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            _widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            int _half = (int)_widthOrHeight / 2;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 80) {
                iVar2 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                iVar4 = iVar2 + _half;
                _pl2 = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
                int _blocked = _pl2 == 2;
                _anotherTile = _widthOrHeight + _middleTileUnk;
                iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + _middleTileUnk + -1;
                if ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x4a5014b1U) != 0
                    || (int)DAT_TileMapState::instance.HeightLayer[iVar3]
                        > (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar3 + 1] + 0x10)
                    || (int)DAT_TileMapState::instance.HeightLayer[iVar3]
                        < (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar3 + 1] - 0x10)
                    || _blocked != 0) {
                    DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                        = DAT_TileMapState::instance.PathLinkageLayer[iVar3] & 0xfb;
                    DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                        = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] & 0xbf;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                        = DAT_TileMapState::instance.PathLinkageLayer[iVar3] | 4;
                    DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                        = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] | 0x40;
                }
                _blocked = _pl2 == 2;
                _middleTileUnk
                    = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + _anotherTile;
                if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) != 0
                    || (int)DAT_TileMapState::instance.HeightLayer[_middleTileUnk]
                        > (int)(DAT_TileMapState::instance.DefaultHeightLayer[_middleTileUnk + -1] + 0x10)
                    || (int)DAT_TileMapState::instance.HeightLayer[_middleTileUnk]
                        < (int)(DAT_TileMapState::instance.DefaultHeightLayer[_middleTileUnk + -1] - 0x10)
                    || _blocked != 0) {
                    DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                        = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xbf;
                    DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk + -1]
                        = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk + -1] & 0xfb;
                    return;
                }
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 0x40;
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk + -1]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk + -1] | 4;
                return;
            }
            iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            _xMiddleUnk = _middleTileUnk + _half;
            _pl2 = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
            int _rowBelow = _widthOrHeight + iVar3;
            int _blocked = _pl2 == 2;
            int _row = iVar3 + -1;
            _middleTileUnk = DAT_ViewportRenderState::instance.translationMatrix[_row].addXgetTile;
            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[_row + 1].addXgetTile;
            uVar5 = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_middleTileUnk + _xMiddleUnk];
            uint _otherHeight = (uint)DAT_TileMapState::instance.DefaultHeightLayer[iVar4 + _xMiddleUnk];
            _middleTileUnk = _middleTileUnk + _xMiddleUnk;
            _anotherTile = iVar4 + _xMiddleUnk;
            if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) != 0
                || (int)uVar5 > (int)(_otherHeight + 0x10)
                || (int)uVar5 < (int)(DAT_TileMapState::instance.DefaultHeightLayer[_anotherTile] - 0x10)
                || _blocked != 0) {
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xef;
                DAT_TileMapState::instance.PathLinkageLayer[_anotherTile]
                    = DAT_TileMapState::instance.PathLinkageLayer[_anotherTile] & 0xfe;
            } else {
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 0x10;
                DAT_TileMapState::instance.PathLinkageLayer[_anotherTile]
                    = DAT_TileMapState::instance.PathLinkageLayer[_anotherTile] | 1;
            }
            _blocked = _pl2 == 2;
            _middleTileUnk = DAT_ViewportRenderState::instance.translationMatrix[_rowBelow].addXgetTile;
            uVar5 = (uint)DAT_TileMapState::instance.DefaultHeightLayer[_middleTileUnk + _xMiddleUnk];
            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[_rowBelow + -1].addXgetTile + _xMiddleUnk;
            _middleTileUnk = _middleTileUnk + _xMiddleUnk;
            if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) != 0
                || (int)uVar5 > (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar4] + 0x10)
                || (int)uVar5 < (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar4] - 0x10)
                || _blocked != 0) {
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xfe;
                DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                    = DAT_TileMapState::instance.PathLinkageLayer[iVar4] & 0xef;
                return;
            }
            DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 1;
            DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar4] | 0x10;
            return;
        }

    }
}
}
