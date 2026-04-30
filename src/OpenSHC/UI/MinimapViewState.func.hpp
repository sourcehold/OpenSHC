/**
  path: 'OpenSHC/UI/MinimapViewState.func.hpp'
*/

#include "OpenSHC/UI/MinimapViewState.hpp"
namespace OpenSHC {
namespace UI {
    namespace MinimapViewState_Func {

        MACRO_FUNCTION_RESOLVER(
            void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B5110, &MinimapViewState::FUN_004b5110)
        FUN_004b5110;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int*, int*), false, Address::SHC_3BB0A8C1_0x004B51A0,
            &MinimapViewState::meth_0x4b51a0)
        meth_0x4b51a0;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004B5280,
            &MinimapViewState::renderMinimapPreview)
        renderMinimapPreview;

        MACRO_FUNCTION_RESOLVER(
            void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B5300, &MinimapViewState::meth_0x4b5300)
        meth_0x4b5300;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(uint, int, int, uint, int), false,
            Address::SHC_3BB0A8C1_0x004B5330, &MinimapViewState::FUN_004b5330)
        FUN_004b5330;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(uint, int, int, int, uint), false,
            Address::SHC_3BB0A8C1_0x004B58D0, &MinimapViewState::setTileColorsUnk)
        setTileColorsUnk;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(uint, int, int), false, Address::SHC_3BB0A8C1_0x004B5F70,
            &MinimapViewState::meth_0x4b5f70)
        meth_0x4b5f70;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B61F0,
            &MinimapViewState::generateMinimapImage)
        generateMinimapImage;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B6320,
            &MinimapViewState::createMapPreviewMiniMap_ConvertColorsUnk)
        createMapPreviewMiniMap_ConvertColorsUnk;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004B6430,
            &MinimapViewState::setSpawnMoment)
        setSpawnMoment;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B6480,
            &MinimapViewState::clearOldSpawnMoment)
        clearOldSpawnMoment;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(uint, int), false, Address::SHC_3BB0A8C1_0x004B6640,
            &MinimapViewState::setMapPropertyDependingOnMapSize)
        setMapPropertyDependingOnMapSize;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, uint), false, Address::SHC_3BB0A8C1_0x004B6680,
            &MinimapViewState::setTileColorsDependingOnMapSize)
        setTileColorsDependingOnMapSize;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int, int, int, uint, int, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004B66C0, &MinimapViewState::drawMinimap)
        drawMinimap;

        MACRO_FUNCTION_RESOLVER(
            void (MinimapViewState::*)(), false, Address::SHC_3BB0A8C1_0x004B7300, &MinimapViewState::renderMinimapMain)
        renderMinimapMain;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x004B7460,
            &MinimapViewState::renderMinimapLandscaping)
        renderMinimapLandscaping;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x004B7530,
            &MinimapViewState::renderMinimapEditor)
        renderMinimapEditor;

        MACRO_FUNCTION_RESOLVER(void (MinimapViewState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x004B7600,
            &MinimapViewState::renderMiniMapForSaving)
        renderMiniMapForSaving;

    } // namespace MinimapViewState_Func
} // namespace UI
} // namespace OpenSHC
