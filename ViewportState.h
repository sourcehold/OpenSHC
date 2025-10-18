#pragma once

#include "common.h"

/* C++ Class updated via OOAanalyzer. */
struct ViewportState
{
    undefined4 field0_0x0;
    int mouseTileX;
    int mouseTileY;
    int mouseTile;
    int field4_0x10;
    undefined4 field5_0x14;
    undefined4 field6_0x18;
    int mouseRayBuildingID;
    undefined4 field8_0x20;
    int mouseRayEntityID;
    int mouseRayUnitID;
    undefined4 field11_0x2c;
    int mouseRayLastUnitID;
    undefined4 field13_0x34;
    undefined4 field14_0x38;
    undefined4 field15_0x3c;
    undefined4 field16_0x40;
    int somePitchDitchID;
    undefined4 field18_0x48;
    undefined4 field19_0x4c;
    undefined4 field20_0x50;
    undefined4 field21_0x54;
    undefined4 field22_0x58;
    undefined4 field23_0x5c;
    undefined4 field24_0x60;
    int mouseX;
    int mouseY;
    undefined4 field27_0x6c;
    int mouseAtomRefFloorTile;
    undefined4 ptrColor;
    int viewportX;            /* Unsigned Double-Word (ddw, 4-bytes) */
    int viewportY;            /* Unsigned Double-Word (ddw, 4-bytes) */
    int currentCameraOffsetX; /* Unsigned Double-Word (ddw, 4-bytes) */
    int currentCameraOffsetY; /* Unsigned Double-Word (ddw, 4-bytes) */
    int viewportHeight;       /* Unsigned Double-Word (ddw, 4-bytes) */
    int viewportWidth;        /* Unsigned Double-Word (ddw, 4-bytes) */
    int isZoomedOut;          /* Unsigned Double-Word (ddw, 4-bytes) */
    undefined4 field37_0x94;
    undefined4 field38_0x98;
    int tileCenterX;
    int tileCenterY;
    undefined4 someYOffset;
    undefined4 someXOffset;
    dword mbr_0xac; /* Unsigned Double-Word (ddw, 4-bytes) */
    dword mbr_0xb0; /* Unsigned Double-Word (ddw, 4-bytes) */
};
