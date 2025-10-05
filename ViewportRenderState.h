#pragma once

#include "framework.h"
#include "common.h"
#include "ViewportRenderStateStruct.h"
#include "windowslib.h"


struct UnitRenderHelpStructure {
    int param_1;
    int param_2;
    int param_3;
    int param_4;
    int param_5;
    int param_6;
    int param_7;
    int param_8;
};


struct TranslationMatrixTriplet {
    int distanceToCenter; /* y distance to center */
    int firstTileOfRow; /* serialized tiles */
    int addXgetTile; /* tile - x */
};

class ViewportRenderState {
    public:
        // Do not declare virtual functions, it will shift all struct addresses by +4
        struct ViewportState DAT_ViewportState; /* imported */
        undefined4 DAT_skipped_isos;
        undefined field2_0xb8;
        undefined field3_0xb9;
        undefined field4_0xba;
        undefined field5_0xbb;
        undefined4 DAT_MapEditorDisplayLayer;
        uchar DAT_BinaryTileMap400x400[160000];
        short DAT_TileTranslationMatrix_YComponent[80400];
        int field9_0x4e5e0;
        undefined4 field10_0x4e5e4;
        undefined4 field11_0x4e5e8;
        undefined4 field12_0x4e5ec;
        undefined4 field13_0x4e5f0;
        undefined4 field14_0x4e5f4;
        undefined4 field15_0x4e5f8;
        undefined4 field16_0x4e5fc;
        int screenPointToTileNumber[321602];
        undefined field18_0x188708;
        undefined field19_0x188709;
        undefined field20_0x18870a;
        undefined field21_0x18870b;
        undefined field22_0x18870c;
        undefined field23_0x18870d;
        undefined field24_0x18870e;
        undefined field25_0x18870f;
        int DAT_TileTranslationMatrix_X_offset_min_24;
        int field27_0x188714;
        int field28_0x188718;
        int DAT_TileTranslationMatrix_X_offset_min_12;
        struct TranslationMatrixTriplet translationMatrix[400];
        undefined4 translationResult1;
        undefined4 translationTracker1;
        undefined4 translationResult2;
        int unknownArray1[250][7];
        undefined4 unknownArray1Index;
        int unknownTileArray3[45];
        byte unused1[60];
        int unknownArray2[45];
        byte unused02[60];
        undefined4 windowX;
        undefined4 windowY;
        undefined4 screenPixelWidth;
        undefined4 screenPixelHeight;
        undefined4 field44_0x18b738;
        undefined4 value160;
        undefined4 creationTime;
        undefined4 value180;
        undefined4 creationTime2;
        undefined4 value80;
        undefined4 creationTime3;
        undefined4 value100;
        undefined4 creationTime4;
        int field53_0x18b75c;
        int field54_0x18b760;
        int field55_0x18b764;
        int field56_0x18b768;
        int field57_0x18b76c;
        undefined4 unitRenderCounterUntil6;
        struct UnitRenderHelpStructure unitBatch1[500];
        struct UnitRenderHelpStructure unitBatch2[500];
        struct UnitRenderHelpStructure unitBatch3[500];
        struct UnitRenderHelpStructure unitBatch4[500];
        struct UnitRenderHelpStructure unitBatch5[500];
        undefined4 unitRender1;
        undefined4 unitRender2;
        undefined4 unitRender3;
        undefined4 unitRender4;
        undefined4 unitRender5;
        
    //FUNCTION: STRONGHOLDCRUSADER 0x004e1fa0
    ViewportRenderState() {
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
    }

    //FUNCTION: STRONGHOLDCRUSADER 0x00401000
    BOOL xyAreValid( uint x, uint y)
    {
        if (((x <= MAP_XY_LIMIT_INCLUSIVE) && (y <= MAP_XY_LIMIT_INCLUSIVE)) &&
            (this->DAT_BinaryTileMap400x400[y * MAP_XY_LIMIT + x] != '\0')) {
            return 1;
        }
        return 0;
    }

    // //FUNCTION: STRONGHOLDCRUSADER 0x00401040
    // int translateXYToTile(int x, int y)
    // {
    //     return this->translationMatrix[y].addXgetTile + x;
    // }

    // //FUNCTION: STRONGHOLDCRUSADER 0x004092e0
    // int meth_0x4092e0(int param_1, int param_2)
    // {
    //     return param_1 - this->translationMatrix[param_2].addXgetTile;
    // }

    // //FUNCTION: STRONGHOLDCRUSADER 0x004e5dd0
    // void setupMouseTileXY()
    // {
    //     this->DAT_ViewportState.mouseTileX = 0;
    //     this->DAT_ViewportState.mouseTileY = 0;
    //     while (this->DAT_ViewportState.mouseTileY < 400) {
    //         if (this->DAT_ViewportState.mouseAtomRefFloorTile <
    //             this->translationMatrix
    //             [this->DAT_ViewportState.mouseTileY + 1].firstTileOfRow) break;
    //         this->DAT_ViewportState.mouseTileY =
    //             this->DAT_ViewportState.mouseTileY + 1;
    //     } ;
    //     this->DAT_ViewportState.mouseTileX =
    //         this->translationMatrix
    //         [this->DAT_ViewportState.mouseTileY].distanceToCenter +
    //         (this->DAT_ViewportState.mouseAtomRefFloorTile -
    //             this->translationMatrix
    //             [this->DAT_ViewportState.mouseTileY].firstTileOfRow);
    // }

    // //FUNCTION: STRONGHOLDCRUSADER 0x004e5d80
    // void setupMouseTileXY2()
    // {
    //     this->DAT_ViewportState.mouseTileX = 0;
    //     this->DAT_ViewportState.mouseTileY = 0;
    //     while (this->DAT_ViewportState.mouseTileY < 400) {
    //         if (this->DAT_ViewportState.mouseTile <
    //             this->translationMatrix
    //             [this->DAT_ViewportState.mouseTileY + 1].firstTileOfRow) break;
    //         this->DAT_ViewportState.mouseTileY =
    //             this->DAT_ViewportState.mouseTileY + 1;
    //     } 
    //     this->DAT_ViewportState.mouseTileX =
    //         this->translationMatrix
    //         [this->DAT_ViewportState.mouseTileY].distanceToCenter +
    //         (this->DAT_ViewportState.mouseTile -
    //             this->translationMatrix
    //             [this->DAT_ViewportState.mouseTileY].firstTileOfRow);
    // }

    // //FUNCTION: STRONGHOLDCRUSADER 0x004e5a90
    // void meth_0x4e5a90()
    // {
    //     DWORD DVar1;
    //     int* piVar2;
    //     int iVar3;

    //     DVar1 = timeGetTime();
    //     this->field55_0x18b764 = 0;
    //     if ((DVar1 - this->creationTime2) > this->value180) {
    //         this->field55_0x18b764 = 1;
    //         piVar2 = this->unknownArray2;
    //         iVar3 = 0x2d;
    //         this->creationTime2 = DVar1;
    //         do {
    //             *piVar2 = *piVar2 + 1;
    //             piVar2 = piVar2 + 1;
    //             iVar3 = iVar3 + -1;
    //         } while (iVar3 != 0);
    //     }
    //     if ((DVar1 - this->creationTime3) > this->value80) {
    //         this->field56_0x18b768 = this->field56_0x18b768 + 1;
    //         this->creationTime3 = DVar1;
    //         if (0x10 <= this->field56_0x18b768) {
    //             this->field56_0x18b768 = 0;
    //         }
    //     }
    //     if ((int)(DVar1 - this->creationTime4) > this->value100) {
    //         this->field53_0x18b75c = this->field53_0x18b75c + 1;
    //         this->creationTime4 = DVar1;
    //         if (0x20 <= this->field53_0x18b75c) {
    //             this->field53_0x18b75c = 0;
    //         }
    //     }
    //     if ((int)(DVar1 - this->creationTime) > this->value160) {
    //         this->field54_0x18b760 = this->field54_0x18b760 + 1;
    //         if (0x24 <= this->field54_0x18b760) {
    //             this->field54_0x18b760 = 0;
    //         }
    //         this->field57_0x18b76c = this->field57_0x18b76c + 1;
    //         this->creationTime = DVar1;
    //         if (0x200 <= this->field57_0x18b76c) {
    //             this->field57_0x18b76c = 0;
    //         }
    //     }
    // }
};