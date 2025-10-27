#include "ViewportRenderState.h"
#include "ViewportRenderState.func.h"

#include "windowslib.h"

ViewportRenderState::ViewportRenderState() { ViewportRenderState_Func::_constructor_::call(this); }

// FUNCTION: STRONGHOLDCRUSADER 0x004e1fa0
ViewportRenderState* ViewportRenderState::_constructor_()
{
    int iVar1;
    int* piVar2;
    DWORD t;

    this->DAT_ViewportState.viewportX = 32;
    this->DAT_ViewportState.viewportY = 8;
    this->DAT_ViewportState.field4_0x10 = -1;

    t = timeGetTime();

    this->creationTime4 = t;
    this->creationTime3 = t;
    this->creationTime2 = t;
    this->creationTime = t;

    this->DAT_ViewportState.isZoomedOut = 0;
    this->DAT_MapEditorDisplayLayer = 0;
    this->field53_0x18b75c = 0;
    this->field57_0x18b76c = 0;
    this->field54_0x18b760 = 0;
    this->field55_0x18b764 = 0;
    this->field56_0x18b768 = 0;
    this->DAT_ViewportState.field37_0x94 = 0;
    this->value160 = 160;
    this->value180 = 180;
    this->value80 = 80;
    this->value100 = 100;
    this->unknownArray1Index = 1;
    piVar2 = this->unknownTileArray3;

    for (iVar1 = 45; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar2 = 0;
        piVar2 = piVar2 + 1;
    }
    return this;
}

// FUNCTION: STRONGHOLDCRUSADER 0x00401000
BOOL ViewportRenderState::xyAreValid(uint x, uint y)
{
    if (((x <= MAP_XY_LIMIT_INCLUSIVE) && (y <= MAP_XY_LIMIT_INCLUSIVE))
        && (this->DAT_BinaryTileMap400x400[y * MAP_XY_LIMIT + x] != '\0')) {
        return 1;
    }
    return 0;
}

// FUNCTION: STRONGHOLDCRUSADER 0x00401040
int ViewportRenderState::translateXYToTile(int x, int y) { return this->translationMatrix[y].addXgetTile + x; }

// FUNCTION: STRONGHOLDCRUSADER 0x004092e0
int ViewportRenderState::meth_0x4092e0(int param_1, int param_2)
{
    return param_1 - this->translationMatrix[param_2].addXgetTile;
}

// FUNCTION: STRONGHOLDCRUSADER 0x004e5dd0
void ViewportRenderState::setupMouseTileXY()
{
    this->DAT_ViewportState.mouseTileX = 0;
    this->DAT_ViewportState.mouseTileY = 0;
    while (this->DAT_ViewportState.mouseTileY < 400) {
        if (this->DAT_ViewportState.mouseAtomRefFloorTile
            < this->translationMatrix[this->DAT_ViewportState.mouseTileY + 1].firstTileOfRow)
            break;
        this->DAT_ViewportState.mouseTileY = this->DAT_ViewportState.mouseTileY + 1;
    };
    this->DAT_ViewportState.mouseTileX = this->translationMatrix[this->DAT_ViewportState.mouseTileY].distanceToCenter
        + (this->DAT_ViewportState.mouseAtomRefFloorTile
            - this->translationMatrix[this->DAT_ViewportState.mouseTileY].firstTileOfRow);
}

// FUNCTION: STRONGHOLDCRUSADER 0x004e5d80
void ViewportRenderState::setupMouseTileXY2()
{
    this->DAT_ViewportState.mouseTileX = 0;
    this->DAT_ViewportState.mouseTileY = 0;
    while (this->DAT_ViewportState.mouseTileY < 400) {
        if (this->DAT_ViewportState.mouseTile
            < this->translationMatrix[this->DAT_ViewportState.mouseTileY + 1].firstTileOfRow)
            break;
        this->DAT_ViewportState.mouseTileY = this->DAT_ViewportState.mouseTileY + 1;
    }
    this->DAT_ViewportState.mouseTileX = this->translationMatrix[this->DAT_ViewportState.mouseTileY].distanceToCenter
        + (this->DAT_ViewportState.mouseTile
            - this->translationMatrix[this->DAT_ViewportState.mouseTileY].firstTileOfRow);
}

// FUNCTION: STRONGHOLDCRUSADER 0x004e5a90
void ViewportRenderState::meth_0x4e5a90()
{
    DWORD DVar1;
    int* piVar2;
    int iVar3;

    DVar1 = timeGetTime();
    this->field55_0x18b764 = 0;
    if ((DVar1 - this->creationTime2) > this->value180) {
        this->field55_0x18b764 = 1;
        piVar2 = this->unknownArray2;
        iVar3 = 0x2d;
        this->creationTime2 = DVar1;
        do {
            *piVar2 = *piVar2 + 1;
            piVar2 = piVar2 + 1;
            iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
    }
    if ((DVar1 - this->creationTime3) > this->value80) {
        this->field56_0x18b768 = this->field56_0x18b768 + 1;
        this->creationTime3 = DVar1;
        if (0x10 <= this->field56_0x18b768) {
            this->field56_0x18b768 = 0;
        }
    }
    if ((int)(DVar1 - this->creationTime4) > this->value100) {
        this->field53_0x18b75c = this->field53_0x18b75c + 1;
        this->creationTime4 = DVar1;
        if (0x20 <= this->field53_0x18b75c) {
            this->field53_0x18b75c = 0;
        }
    }
    if ((int)(DVar1 - this->creationTime) > this->value160) {
        this->field54_0x18b760 = this->field54_0x18b760 + 1;
        if (0x24 <= this->field54_0x18b760) {
            this->field54_0x18b760 = 0;
        }
        this->field57_0x18b76c = this->field57_0x18b76c + 1;
        this->creationTime = DVar1;
        if (0x200 <= this->field57_0x18b76c) {
            this->field57_0x18b76c = 0;
        }
    }
}
