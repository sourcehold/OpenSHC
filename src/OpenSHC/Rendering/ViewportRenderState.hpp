/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/ViewportRenderState.hpp'
*/

#pragma once

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Map/Floaters/Floater.hpp"
#include "OpenSHC/Map/Matrices/TranslationMatrixTriplet.hpp"
#include "OpenSHC/Rendering/UnitRenderHelpStructure.hpp"
#include "OpenSHC/Rendering/ViewportState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::IO::Graphics::GmIDInt;
    using OpenSHC::Map::Floaters::Floater;
    using OpenSHC::Map::Matrices::TranslationMatrixTriplet;
    using OpenSHC::Rendering::UnitRenderHelpStructure;
    using OpenSHC::Rendering::ViewportState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0019F008
    class ViewportRenderState {
    public:
        ViewportState viewportState; // 0x00000000 length: 180
        undefined4 DAT_skipped_isos; // 0x000000B4 length: 4
        undefined1 padding_0xb8[4]; // 0x000000B8 length: 4
        undefined4 DAT_MapEditorDisplayLayer; // 0x000000BC length: 4
        uchar DAT_BinaryTileMap400x400[160000]; // 0x000000C0 length: 160000
        short DAT_TileTranslationMatrix_YComponent[80400]; // 0x000271C0 length: 160800
        int field9_0x4e5e0; // 0x0004E5E0 length: 4
        undefined4 field10_0x4e5e4; // 0x0004E5E4 length: 4
        undefined4 field11_0x4e5e8; // 0x0004E5E8 length: 4
        undefined4 field12_0x4e5ec; // 0x0004E5EC length: 4
        undefined4 field13_0x4e5f0; // 0x0004E5F0 length: 4
        undefined4 field14_0x4e5f4; // 0x0004E5F4 length: 4
        undefined4 field15_0x4e5f8; // 0x0004E5F8 length: 4
        undefined4 field16_0x4e5fc; // 0x0004E5FC length: 4
        int screenPointToTileNumber[321602]; // 0x0004E600 length: 1286408
        undefined1 padding_0x188708[8]; // 0x00188708 length: 8
        int DAT_TileTranslationMatrix_X_offset_min_24; // 0x00188710 length: 4
        int field27_0x188714; // 0x00188714 length: 4
        int field28_0x188718; // 0x00188718 length: 4
        int DAT_TileTranslationMatrix_X_offset_min_12; // 0x0018871C length: 4
        TranslationMatrixTriplet translationMatrix[400]; // 0x00188720 length: 4800
        undefined4 translationResult1; // 0x001899E0 length: 4
        undefined4 translationTracker1; // 0x001899E4 length: 4
        undefined4 translationResult2; // 0x001899E8 length: 4
        Floater floatersArray[250]; // 0x001899EC length: 7000
        undefined4 availableFloaterIndex; // 0x0018B544 length: 4
        int landscapeAnimationRandomTileArray[45]; // 0x0018B548 length: 180
        byte landscapeAnimationValueArray[60]; // 0x0018B5FC length: 60
        int landscapeSeaWhiteCapsAnimationFrames[45]; // 0x0018B638 length: 180
        byte unused02[60]; // 0x0018B6EC length: 60
        undefined4 windowX; // 0x0018B728 length: 4
        undefined4 windowY; // 0x0018B72C length: 4
        undefined4 screenPixelWidth; // 0x0018B730 length: 4
        undefined4 screenPixelHeight; // 0x0018B734 length: 4
        undefined4 field44_0x18b738; // 0x0018B738 length: 4
        undefined4 interval_03_160; // 0x0018B73C length: 4
        undefined4 previousIntervalTime_03; // 0x0018B740 length: 4
        undefined4 interval_04_180; // 0x0018B744 length: 4
        undefined4 previousIntervalTime_04; // 0x0018B748 length: 4
        undefined4 interval_01_80; // 0x0018B74C length: 4
        undefined4 previousIntervalTime_01; // 0x0018B750 length: 4
        undefined4 interval_02_100; // 0x0018B754 length: 4
        undefined4 previousIntervalTime_02; // 0x0018B758 length: 4
        int unknownCounterUntil_0x20; // 0x0018B75C length: 4
        int unknownCounterUntil_0x24; // 0x0018B760 length: 4
        int field55_0x18b764; // 0x0018B764 length: 4
        int unknownCounterUntil_0x10; // 0x0018B768 length: 4
        int unknownCounterUntil_0x200; // 0x0018B76C length: 4
        undefined4 unitBatchedRenderCounterUntil6; // 0x0018B770 length: 4
        UnitRenderHelpStructure unitBatch1[500]; // 0x0018B774 length: 16000
        UnitRenderHelpStructure unitBatch2[500]; // 0x0018F5F4 length: 16000
        UnitRenderHelpStructure unitBatch3[500]; // 0x00193474 length: 16000
        UnitRenderHelpStructure unitBatch4[500]; // 0x001972F4 length: 16000
        UnitRenderHelpStructure unitBatch5[500]; // 0x0019B174 length: 16000
        undefined4 unitRender1; // 0x0019EFF4 length: 4
        undefined4 unitRender2; // 0x0019EFF8 length: 4
        undefined4 unitRender3; // 0x0019EFFC length: 4
        undefined4 unitRender4; // 0x0019F000 length: 4
        undefined4 unitRender5; // 0x0019F004 length: 4

    private:
        ViewportRenderState(ViewportRenderState const&);
        void operator=(ViewportRenderState const&);

        ViewportRenderState();
        ~ViewportRenderState();

    public:
        // Constructor
        ViewportRenderState* Constructor_ViewportRenderState();

        BOOLEnum xyAreValid(uint x, uint y);

        int translateXYToTile(int x, int y);

        int meth_0x4092e0(int param_1, int param_2);

        void setTileSystemMemoryLookupArrays();

        void tweakValidTilesToExcludeMapBorders();

        void resetBatchedRender();

        void FUN_004e2630(int param_1);

        void scheduleUnitForBatchedRendering(undefined4 unitIDOrStatus, undefined4 drawX, undefined4 drawY,
            undefined4 imageID, undefined4 blendStrength, undefined4 gmID, int param_7);

        void renderGmOverlayBuilding2(int param_1, int param_2, int param_3);

        void renderGmOverlayBuilding(int tileIndex, int xUnk, int yUnk, int param_4);

        void updateWaterAnimationFrames();

        void assignRandomTiles();

        void setViewportBasedOnMapSize();

        void setupMouseTileXY2();

        void setupMouseTileXY();

        void focusOnTile(int tile);

        void meth_0x4e5ed0(int param_1, int param_2);

        void meth_0x4e6340();

        void creataAFloatingLayerElement(GmIDInt gmID, int imageID, int imageX, int imageY, int tile, int variation);

        void renderDebugDataMousePointing(int x, int y, int width, int height);

        void setupViewport(
            undefined4 windowX, undefined4 windowY, undefined4 screenPixelWidth, undefined4 screenPixelHeight);

        void resetupViewport(int zoomUnk);

        void resetupViewportThunk();

        void renderUnits();

        void updateBuildingPreviewPosition(int mouseXScreenSpace, int mouseYScreenSpace);

        void meth_0x4e8c50();

        void meth_0x4e8c90();

        void focusOnCoordinate(int x, int y);

        void FUN_004e8cc0(int param_1, int param_2, int param_3, int param_4, int param_5);

        void renderMap();
    };

    static_assert_cpp98_obj(sizeof(ViewportRenderState) == 1699848, ViewportRenderState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(ViewportRenderState, false, Address::SHC_3BB0A8C1_0x021AEBD8) pDAT_ViewportRenderState;

} // namespace Rendering
} // namespace OpenSHC
