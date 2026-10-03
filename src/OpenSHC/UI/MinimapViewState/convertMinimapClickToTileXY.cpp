#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B51A0
    void MinimapViewState::convertMinimapClickToTileXY(int* param_1, int* param_2)
    {
        short sVar1;
        int iVar2;
        int iVar3;
        if (this->field15_0x3c != 0) {
            iVar2 = DAT_MouseState::instance.screenSpaceY - this->y;
            iVar3 = 0;
            *param_1 = (((DAT_MouseState::instance.screenSpaceX - this->x) * this->oneOrTwo) / this->widthFactor + 6
                           + this->field5_0x14)
                * 0x20;
            iVar2 = ((this->oneOrTwo * iVar2) / this->heightFactor + this->field4_0x10) * 8;
            *param_2 = iVar2;
            if (DAT_TileMapState::instance.mapOrientation != 0) {
                if (DAT_TileMapState::instance.mapOrientation == 6) {
                    iVar3 = 0x13a10;
                } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                    iVar3 = 0x27420;
                } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                    iVar3 = 0x3ae30;
                }
            }
            iVar2 = DAT_ViewportRenderState::instance
                        .screenPointToTileNumber[((int)(*param_1 + (*param_1 >> 0x1f & 0x1fU)) >> 5)
                            + ((int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4) * 0x191 + iVar3 + -6];
            sVar1 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar2];
            *param_2 = (int)sVar1;
            *param_1 = iVar2 - DAT_ViewportRenderState::instance.translationMatrix[sVar1].addXgetTile;
        }
        *param_1 = -1;
        *param_2 = -1;
    }

}
}
