#pragma once

#include "ViewportRenderStateStruct.h"
#include "common.h"
#include "framework.h"

struct UnitRenderHelpStructure
{
    int param_1;
    int param_2;
    int param_3;
    int param_4;
    int param_5;
    int param_6;
    int param_7;
    int param_8;
};

struct TranslationMatrixTriplet
{
    int distanceToCenter; /* y distance to center */
    int firstTileOfRow;   /* serialized tiles */
    int addXgetTile;      /* tile - x */
};

class ViewportRenderState
{
  public:
    // Do not declare virtual functions, it will shift all struct addresses by +4
    struct ViewportState DAT_ViewportState; /* imported */
    undefined4 DAT_skipped_isos;
    undefined field2_0xb8;
    undefined field3_0xb9;
    undefined field4_0xba;
    undefined field5_0xbb;
    undefined4 DAT_MapEditorDisplayLayer;
    uchar DAT_BinaryTileMap400x400[MAP_XY_LIMIT * MAP_XY_LIMIT];
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

    // FUNCTION: STRONGHOLDCRUSADER 0x004e1fa0
    ViewportRenderState();

    // FUNCTION: STRONGHOLDCRUSADER 0x00401000
    BOOL xyAreValid(uint x, uint y);

    // FUNCTION: STRONGHOLDCRUSADER 0x00401040
    int translateXYToTile(int x, int y);

    // FUNCTION: STRONGHOLDCRUSADER 0x004092e0
    int meth_0x4092e0(int param_1, int param_2);

    // FUNCTION: STRONGHOLDCRUSADER 0x004e5dd0
    void setupMouseTileXY();

    // FUNCTION: STRONGHOLDCRUSADER 0x004e5d80
    void setupMouseTileXY2();

    // FUNCTION: STRONGHOLDCRUSADER 0x004e5a90
    void meth_0x4e5a90();
};
