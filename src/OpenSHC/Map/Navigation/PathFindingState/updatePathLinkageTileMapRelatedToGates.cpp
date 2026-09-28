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
            byte* pbVar1;
            int iVar2;
            int iVar3;
            int _anotherTile;
            int iVar4;
            int _middleTileUnk;
            uint uVar5;
            int _xMiddleUnk;
            int _offset;
            int _pl2;
            uint _widthOrHeight;
            _middleTileUnk = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            _widthOrHeight = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation != 80) {
                _xMiddleUnk = _middleTileUnk + (int)_widthOrHeight / 2;
                iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                _pl2 = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
                _middleTileUnk = DAT_ViewportRenderState::instance.translationMatrix[iVar3 + -1].addXgetTile;
                iVar4 = DAT_ViewportRenderState::instance.translationMatrix[iVar3].addXgetTile;
                uVar5 = (uint) * (byte*)(_middleTileUnk + 0x1d46648 + _xMiddleUnk);
                _middleTileUnk = _middleTileUnk + _xMiddleUnk;
                _anotherTile = iVar4 + _xMiddleUnk;
                if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) == 0
                    && uVar5 <= *(byte*)(iVar4 + 0x1d46648 + _xMiddleUnk) + 0x10
                    && (int)(DAT_TileMapState::instance.DefaultHeightLayer[_anotherTile] - 0x10) <= (int)uVar5
                    && _pl2 != 2) {
                    DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                        = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 0x10;
                    DAT_TileMapState::instance.PathLinkageLayer[_anotherTile]
                        = DAT_TileMapState::instance.PathLinkageLayer[_anotherTile] | 1;
                } else {
                    DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                        = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xef;
                    DAT_TileMapState::instance.PathLinkageLayer[_anotherTile]
                        = DAT_TileMapState::instance.PathLinkageLayer[_anotherTile] & 0xfe;
                }
                _middleTileUnk
                    = DAT_ViewportRenderState::instance.translationMatrix[_widthOrHeight + iVar3].addXgetTile;
                uVar5 = (uint) * (byte*)(_middleTileUnk + 0x1d46648 + _xMiddleUnk);
                _middleTileUnk = _middleTileUnk + _xMiddleUnk;
                iVar4 = DAT_ViewportRenderState::instance.translationMatrix[_widthOrHeight + iVar3 + -1].addXgetTile
                    + _xMiddleUnk;
                if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) == 0
                    && uVar5 <= DAT_TileMapState::instance.DefaultHeightLayer[iVar4] + 0x10
                    && (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar4] - 0x10) <= (int)uVar5 && _pl2 != 2) {
                    DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                        = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 1;
                    DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                        = DAT_TileMapState::instance.PathLinkageLayer[iVar4] | 0x10;
                    return;
                }
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xfe;
                DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                    = DAT_TileMapState::instance.PathLinkageLayer[iVar4] & 0xef;
                return;
            }
            _pl2 = DAT_BuildingsState::instance.buildings[buildingID].pathLinkageRelated2;
            iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y + (int)_widthOrHeight / 2;
            iVar2 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile;
            iVar3 = iVar2 + -1 + _middleTileUnk;
            if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk + iVar2 + -1] & 0x4a5014b1U) == 0
                && (uint)(byte)DAT_TileMapState::instance.EntityLayerLT25[iVar3 + 0x13a10]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar3 + 1] + 0x10
                && (int)(DAT_TileMapState::instance.DefaultHeightLayer[iVar3 + 1] - 0x10)
                    <= (int)(uint)(byte)DAT_TileMapState::instance.EntityLayerLT25[iVar3 + 0x13a10]
                && _pl2 != 2) {
                pbVar1 = (byte*)((int)DAT_TileMapState::instance.PathConnectionLayer + iVar3 + 0x27420);
                *pbVar1 = *pbVar1 | 4;
                DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                    = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] | 0x40;
            } else {
                pbVar1 = (byte*)((int)DAT_TileMapState::instance.PathConnectionLayer + iVar3 + 0x27420);
                *pbVar1 = *pbVar1 & 0xfb;
                DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                    = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] & 0xbf;
            }
            _middleTileUnk = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + _widthOrHeight
                + _middleTileUnk;
            if ((DAT_TileMapState::instance.LogicLayer[_middleTileUnk] & 0x4a5014b1U) == 0
                && (uint)DAT_TileMapState::instance.HeightLayer[_middleTileUnk]
                    <= DAT_TileMapState::instance.HeightLayer[_middleTileUnk + 0x13a0f] + 0x10
                && (int)(DAT_TileMapState::instance.HeightLayer[_middleTileUnk + 0x13a0f] - 0x10)
                    <= (int)(uint)DAT_TileMapState::instance.HeightLayer[_middleTileUnk]
                && _pl2 != 2) {
                DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                    = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] | 0x40;
                pbVar1 = (byte*)((int)DAT_TileMapState::instance.PathConnectionLayer + _middleTileUnk + 0x2741f);
                *pbVar1 = *pbVar1 | 4;
                return;
            }
            DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk]
                = DAT_TileMapState::instance.PathLinkageLayer[_middleTileUnk] & 0xbf;
            pbVar1 = (byte*)((int)DAT_TileMapState::instance.PathConnectionLayer + _middleTileUnk + 0x2741f);
            *pbVar1 = *pbVar1 & 0xfb;
            return;
        }

    }
}
}
