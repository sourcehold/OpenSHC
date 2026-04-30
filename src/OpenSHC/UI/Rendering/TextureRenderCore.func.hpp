/**
  path: 'OpenSHC/UI/Rendering/TextureRenderCore.func.hpp'
*/

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/RGB15.hpp"
#include "OpenSHC/Text/FontRenderTypeInt.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/_SHCDE/eGMInt.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {
        namespace TextureRenderCore_Func {

            using OpenSHC::_SHCDE::eGMInt;
            using OpenSHC::IO::Graphics::GmIDInt;
            using OpenSHC::Rendering::Colors::BGR24;
            using OpenSHC::Rendering::Colors::RGB15;
            using OpenSHC::Text::FontRenderTypeInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044C7E0,
                &TextureRenderCore::Destructor_TextureRenderCore)
            Destructor_TextureRenderCore;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(GmIDInt, int), false, Address::SHC_3BB0A8C1_0x0044C850,
                &TextureRenderCore::drawLoadingBarUnk)
            drawLoadingBarUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x0044C8F0,
                &TextureRenderCore::transformGmColorTableFromRGB555To565IfRequired)
            transformGmColorTableFromRGB555To565IfRequired;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x0044C940,
                &TextureRenderCore::transformRawWithMarkerUnkToRGB555To565)
            transformRawWithMarkerUnkToRGB555To565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(ushort*, int), false, Address::SHC_3BB0A8C1_0x0044C9C0,
                &TextureRenderCore::transformTgxFromRGB555ToRGB565)
            transformTgxFromRGB555ToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x0044CAE0,
                &TextureRenderCore::transformTileObjectToRGB565)
            transformTileObjectToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x0044CB60,
                &TextureRenderCore::transformRawToRGB555To565)
            transformRawToRGB555To565;

            MACRO_FUNCTION_RESOLVER(RGB15 (TextureRenderCore::*)(BGR24), false, Address::SHC_3BB0A8C1_0x0044CBE0,
                &TextureRenderCore::transformBGR24ToScreenColor)
            transformBGR24ToScreenColor;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044CC30,
                &TextureRenderCore::clearSomeMemory)
            clearSomeMemory;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x0044CCA0,
                &TextureRenderCore::setMapSurfaceHeightRange)
            setMapSurfaceHeightRange;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044CCC0,
                &TextureRenderCore::setMapSurfaceHeightRangeUnk)
            setMapSurfaceHeightRangeUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044CCD0,
                &TextureRenderCore::temporarySaveMapSurfaceHeightRangeUnk)
            temporarySaveMapSurfaceHeightRangeUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044CCF0,
                &TextureRenderCore::restoreMapSurfaceHeightRangeFromTemporaryUnk)
            restoreMapSurfaceHeightRangeFromTemporaryUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x0044CD10,
                &TextureRenderCore::setScreenMenuSurfaceHeightRange)
            setScreenMenuSurfaceHeightRange;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x0044CD30,
                &TextureRenderCore::setScreenMenuSurfaceHeightRangeToResolution)
            setScreenMenuSurfaceHeightRangeToResolution;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0044CD40,
                &TextureRenderCore::drawBitmapFace)
            drawBitmapFace;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0044CE00,
                &TextureRenderCore::renderFacesSmallUnk)
            renderFacesSmallUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0044CEB0, &TextureRenderCore::drawBitmapFaceWithBlendUnk)
            drawBitmapFaceWithBlendUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*), false,
                Address::SHC_3BB0A8C1_0x0044D3D0, &TextureRenderCore::renderFunctionResponsibleForManyGameObjects)
            renderFunctionResponsibleForManyGameObjects;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*, int), false,
                Address::SHC_3BB0A8C1_0x0044E630, &TextureRenderCore::renderInterfaceOrBuildingOccupationArea)
            renderInterfaceOrBuildingOccupationArea;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0044F020, &TextureRenderCore::renderBlendedBlackBox)
            renderBlendedBlackBox;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*, int), false,
                Address::SHC_3BB0A8C1_0x0044F170, &TextureRenderCore::renderGmWithPreparedAlphaMask)
            renderGmWithPreparedAlphaMask;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*, ushort), false,
                Address::SHC_3BB0A8C1_0x0044F6F0, &TextureRenderCore::renderTgxWithColorUnk)
            renderTgxWithColorUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*, ushort, int), false,
                Address::SHC_3BB0A8C1_0x0044F850, &TextureRenderCore::renderTgxWithColorAndBlendingUnk)
            renderTgxWithColorAndBlendingUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, byte*), false,
                Address::SHC_3BB0A8C1_0x0044FBF0, &TextureRenderCore::renderUnitAnimationUnk)
            renderUnitAnimationUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, byte*, int), false,
                Address::SHC_3BB0A8C1_0x00451E00, &TextureRenderCore::renderUnitAnimationWithBlendingUnk)
            renderUnitAnimationWithBlendingUnk;

            MACRO_FUNCTION_RESOLVER(int (TextureRenderCore::*)(char*), false, Address::SHC_3BB0A8C1_0x00454620,
                &TextureRenderCore::loadGfxFile)
            loadGfxFile;

            MACRO_FUNCTION_RESOLVER(int (TextureRenderCore::*)(char*), false, Address::SHC_3BB0A8C1_0x00454700,
                &TextureRenderCore::loadGFX8)
            loadGFX8;

            MACRO_FUNCTION_RESOLVER(int (TextureRenderCore::*)(char*), false, Address::SHC_3BB0A8C1_0x004547C0,
                &TextureRenderCore::loadGfxAtBufferEnd)
            loadGfxAtBufferEnd;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TextureRenderCore::*)(char*), false, Address::SHC_3BB0A8C1_0x004548D0,
                &TextureRenderCore::FUN_004548d0)
            FUN_004548d0;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00454900,
                &TextureRenderCore::renderLoadedGfx)
            renderLoadedGfx;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00454960,
                &TextureRenderCore::setRenderingRectToGameResolution)
            setRenderingRectToGameResolution;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00454990, &TextureRenderCore::setRenderingRect)
            setRenderingRect;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x004549C0,
                &TextureRenderCore::checkIfGfxTgxStartsWithTransparentPixels)
            checkIfGfxTgxStartsWithTransparentPixels;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004549F0, &TextureRenderCore::renderGfxTgxWithBlending)
            renderGfxTgxWithBlending;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, int, ushort*), false,
                Address::SHC_3BB0A8C1_0x00454A60, &TextureRenderCore::drawTgxOnFlaggedSurface)
            drawTgxOnFlaggedSurface;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00454CB0,
                &TextureRenderCore::loadCampaignMapGfxUnk)
            loadCampaignMapGfxUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x00454EE0,
                &TextureRenderCore::setMenuTabIndexUnk)
            setMenuTabIndexUnk;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00454EF0,
                &TextureRenderCore::setActiveMenuTabIndexToZero)
            setActiveMenuTabIndexToZero;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00454F00,
                &TextureRenderCore::moveOverlappingMenuPartsToMapSurface)
            moveOverlappingMenuPartsToMapSurface;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x00455250,
                &TextureRenderCore::transformUncompressedImageWithMarkerUnkToRGB565)
            transformUncompressedImageWithMarkerUnkToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x00455270,
                &TextureRenderCore::transformTgxCompressedImageToRGB565)
            transformTgxCompressedImageToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x00455290,
                &TextureRenderCore::transformTilesetToRGB565)
            transformTilesetToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int), false, Address::SHC_3BB0A8C1_0x004552E0,
                &TextureRenderCore::transformUncompressedImageToRGB565)
            transformUncompressedImageToRGB565;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(eGMInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00455300, &TextureRenderCore::renderGM)
            renderGM;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(GmIDInt, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00455390, &TextureRenderCore::renderGMWithBlending)
            renderGMWithBlending;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(GmIDInt, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004554A0, &TextureRenderCore::drawTgxGmOnFlaggedSurface)
            drawTgxGmOnFlaggedSurface;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int, FontRenderTypeInt, int, ushort, int),
                false, Address::SHC_3BB0A8C1_0x00455540, &TextureRenderCore::renderTextChar)
            renderTextChar;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(GmIDInt, int, int, int, GmIDInt, int, int), false,
                Address::SHC_3BB0A8C1_0x004557B0, &TextureRenderCore::renderGMWithAlphaMask)
            renderGMWithAlphaMask;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004558E0,
                &TextureRenderCore::drawGfxOnFlaggedSurface)
            drawGfxOnFlaggedSurface;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x00455930,
                &TextureRenderCore::adaptGmColorsToRGB565IfRequired)
            adaptGmColorsToRGB565IfRequired;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(GmIDInt, char*), false,
                Address::SHC_3BB0A8C1_0x004559B0, &TextureRenderCore::loadGMFile)
            loadGMFile;

            MACRO_FUNCTION_RESOLVER(void (TextureRenderCore::*)(char*), false, Address::SHC_3BB0A8C1_0x00455C60,
                &TextureRenderCore::loadGmFiles)
            loadGmFiles;

        } // namespace TextureRenderCore_Func
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
