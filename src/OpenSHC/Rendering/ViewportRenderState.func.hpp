/**
  path: 'OpenSHC/Rendering/ViewportRenderState.func.hpp'
*/

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Rendering {
    namespace ViewportRenderState_Func {

        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (ViewportRenderState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x00401000,
            &ViewportRenderState::xyAreValid)
        xyAreValid;

        MACRO_FUNCTION_RESOLVER(int (ViewportRenderState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00401040,
            &ViewportRenderState::translateXYToTile)
        translateXYToTile;

        MACRO_FUNCTION_RESOLVER(int (ViewportRenderState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004092E0,
            &ViewportRenderState::tileIndexToColumn)
        tileIndexToColumn;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E2050,
            &ViewportRenderState::setTileSystemMemoryLookupArrays)
        setTileSystemMemoryLookupArrays;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E25A0,
            &ViewportRenderState::tweakValidTilesToExcludeMapBorders)
        tweakValidTilesToExcludeMapBorders;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E2600,
            &ViewportRenderState::resetBatchedRender)
        resetBatchedRender;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int), false, Address::SHC_3BB0A8C1_0x004E2630,
            &ViewportRenderState::renderAssassinClimbOverlay)
        renderAssassinClimbOverlay;

        MACRO_FUNCTION_RESOLVER(
            void (ViewportRenderState::*)(undefined4, undefined4, undefined4, undefined4, undefined4, undefined4, int),
            false, Address::SHC_3BB0A8C1_0x004E26D0, &ViewportRenderState::scheduleUnitForBatchedRendering)
        scheduleUnitForBatchedRendering;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004E2AD0,
            &ViewportRenderState::renderGmOverlayBuilding2)
        renderGmOverlayBuilding2;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004E3980, &ViewportRenderState::renderGmOverlayBuilding)
        renderGmOverlayBuilding;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E5A90,
            &ViewportRenderState::updateWaterAnimationFrames)
        updateWaterAnimationFrames;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E5B80,
            &ViewportRenderState::assignRandomTiles)
        assignRandomTiles;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E5C00,
            &ViewportRenderState::setViewportBasedOnMapSize)
        setViewportBasedOnMapSize;

        MACRO_FUNCTION_RESOLVER(undefined (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E5D80,
            &ViewportRenderState::setupMouseTileXY2)
        setupMouseTileXY2;

        MACRO_FUNCTION_RESOLVER(undefined (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E5DD0,
            &ViewportRenderState::setupMouseTileXY)
        setupMouseTileXY;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int), false, Address::SHC_3BB0A8C1_0x004E5E20,
            &ViewportRenderState::focusOnTile)
        focusOnTile;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004E5ED0,
            &ViewportRenderState::computeHoveredTileWithHeight)
        computeHoveredTileWithHeight;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E6340,
            &ViewportRenderState::clearAllFloaters)
        clearAllFloaters;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(GmIDInt, int, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004E63A0, &ViewportRenderState::creataAFloatingLayerElement)
        creataAFloatingLayerElement;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004E64D0, &ViewportRenderState::renderDebugDataMousePointing)
        renderDebugDataMousePointing;

        MACRO_FUNCTION_RESOLVER(undefined (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E66F0,
            &ViewportRenderState::setupViewport)
        setupViewport;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int), false, Address::SHC_3BB0A8C1_0x004E7770,
            &ViewportRenderState::resetupViewport)
        resetupViewport;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E7800,
            &ViewportRenderState::resetupViewportThunk)
        resetupViewportThunk;

        MACRO_FUNCTION_RESOLVER(
            void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E7810, &ViewportRenderState::renderUnits)
        renderUnits;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004E8430,
            &ViewportRenderState::updateBuildingPreviewPosition)
        updateBuildingPreviewPosition;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E8C50,
            &ViewportRenderState::centerBuildingPreview)
        centerBuildingPreview;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E8C90,
            &ViewportRenderState::focusOnSavedTile)
        focusOnSavedTile;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004E8CA0,
            &ViewportRenderState::focusOnCoordinate)
        focusOnCoordinate;

        MACRO_FUNCTION_RESOLVER(void (ViewportRenderState::*)(int, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004E8CC0, &ViewportRenderState::addFloatingDisplayElement)
        addFloatingDisplayElement;

        MACRO_FUNCTION_RESOLVER(
            void (ViewportRenderState::*)(), false, Address::SHC_3BB0A8C1_0x004E8CF0, &ViewportRenderState::renderMap)
        renderMap;

    } // namespace ViewportRenderState_Func
} // namespace Rendering
} // namespace OpenSHC
