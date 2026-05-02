/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/TextureRenderCore.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eGMInt.hpp"
#include "OpenSHC/IO/Graphics/GMFileHeaderColorpalette.hpp"
#include "OpenSHC/IO/Graphics/GfxRef.hpp"
#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/RGB15.hpp"
#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/Text/FontRenderTypeInt.hpp"
#include "OpenSHC/UI/Rendering/Range.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::DE::SHCDE::eGMInt;
        using OpenSHC::IO::Graphics::GfxRef;
        using OpenSHC::IO::Graphics::GMFileHeaderColorpalette;
        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Colors::RGB15;
        using OpenSHC::Rendering::Enums::RenderTargetInt;
        using OpenSHC::Text::FontRenderTypeInt;
        using OpenSHC::UI::Rendering::Range;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x0016D484
        class TextureRenderCore {
        public:
            dword bufferAllocStateUnk_0x0; // 0x00000000 length: 4
            RenderTargetInt drawBufferChoiceValue; // 0x00000004 length: 4
            RenderTargetInt currentRenderSurfaceIdentifierUnk_0x8; // 0x00000008 length: 4
            ushort* currentRenderSurface; // 0x0000000C length: 4
            dword mbr_0x10; // 0x00000010 length: 4
            undefined1 padding_0x14[24]; // 0x00000014 length: 24
            int field29_0x2c; // 0x0000002C length: 4
            undefined1 padding_0x30[20]; // 0x00000030 length: 20
            int gmSizeOfProcessedPictures_0x44; // 0x00000044 length: 4
            int gmNumberOfProcessedPictures; // 0x00000048 length: 4
            int gmFileID; // 0x0000004C length: 4
            BOOLEnum unknownSfxAndGmRelatedFlag; // 0x00000050 length: 4
            int isZoom2; // 0x00000054 length: 4
            Range mapGameSurfaceHeightRange; // 0x00000058 length: 8
            Range screenMenuSurfaceHeightRange; // 0x00000060 length: 8
            dword activeMenuTabIndex; // 0x00000068 length: 4
            dword mbr_0x6c; // 0x0000006C length: 4
            dword mbr_0x70; // 0x00000070 length: 4
            int gmProcessedImageDataBufferSize_0x74; // 0x00000074 length: 4
            void* gmProcessedImageData; // 0x00000078 length: 4
            int unknownMemSize_1_0x7c; // 0x0000007C length: 4
            void* unknownMemPtr_1_0x80; // 0x00000080 length: 4
            int unknownMemSize_2_0x84; // 0x00000084 length: 4
            void* address2; // 0x00000088 length: 4
            int gmAndGfxImageDataBufferSize_0x8c; // 0x0000008C length: 4
            void* gmAndGfxImageDataBuffer; // 0x00000090 length: 4
            void* bitmapsFaces_0x94; // 0x00000094 length: 4
            int field69_0x98; // 0x00000098 length: 4
            int field70_0x9c; // 0x0000009C length: 4
            int field71_0xa0; // 0x000000A0 length: 4
            int field72_0xa4; // 0x000000A4 length: 4
            int field73_0xa8; // 0x000000A8 length: 4
            int field74_0xac; // 0x000000AC length: 4
            int field75_0xb0; // 0x000000B0 length: 4
            int field76_0xb4; // 0x000000B4 length: 4
            int field77_0xb8; // 0x000000B8 length: 4
            int field78_0xbc; // 0x000000BC length: 4
            int field79_0xc0; // 0x000000C0 length: 4
            int field80_0xc4; // 0x000000C4 length: 4
            int field81_0xc8; // 0x000000C8 length: 4
            int field82_0xcc; // 0x000000CC length: 4
            int field83_0xd0; // 0x000000D0 length: 4
            int field84_0xd4; // 0x000000D4 length: 4
            int field85_0xd8; // 0x000000D8 length: 4
            int field86_0xdc; // 0x000000DC length: 4
            int field87_0xe0; // 0x000000E0 length: 4
            int unknownPlayerDependentRenderValue[9]; // 0x000000E4 length: 36
            int field89_0x108; // 0x00000108 length: 4
            int field90_0x10c; // 0x0000010C length: 4
            int field91_0x110; // 0x00000110 length: 4
            int field92_0x114; // 0x00000114 length: 4
            int field93_0x118; // 0x00000118 length: 4
            int field94_0x11c; // 0x0000011C length: 4
            int field95_0x120; // 0x00000120 length: 4
            int field96_0x124; // 0x00000124 length: 4
            int field97_0x128; // 0x00000128 length: 4
            int field98_0x12c; // 0x0000012C length: 4
            undefined1 padding_0x130[1004]; // 0x00000130 length: 1004
            GMFileHeaderColorpalette gmFileHeaderColorpaletteArray[240]; // 0x0000051C length: 1249920
            char gmFileNameArray_UNUSEDUnk_0x13179c[240][1001]; // 0x0013179C length: 240240
            GfxRef loadedGfxArray[100]; // 0x0016C20C length: 1600
            int totalLoadedGfx; // 0x0016C84C length: 4
            int backwardsLoadedGfxIndex_0x16C850; // 0x0016C850 length: 4
            RECT renderingRect_16c854; // 0x0016C854 length: 16
            Range mapSurfaceRangeTemporaryUnk_0x16c864; // 0x0016C864 length: 8
            undefined1 padding_0x16c86c[24]; // 0x0016C86C length: 24
            ushort campaignMapColorMapsUnk_0x16c886[6][256]; // 0x0016C884 length: 3072

        private:
            TextureRenderCore(TextureRenderCore const&);
            void operator=(TextureRenderCore const&);

            TextureRenderCore();
            ~TextureRenderCore();

        public:
            // Constructor
            TextureRenderCore* Constructor_TextureRenderCore(
                int processedImageDataBufferSize, int gmAndGfxImageDataBufferSize, int unknownMemSize);

            void Destructor_TextureRenderCore();

            void drawLoadingBarUnk(GmIDInt currentGmId, int barLengthUnk);

            void transformGmColorTableFromRGB555To565IfRequired(int gmID);

            void transformRawWithMarkerUnkToRGB555To565(int imageOffset, int imageSize);

            void transformTgxFromRGB555ToRGB565(ushort* tgxDataPtr, int tgxByteSize);

            void transformTileObjectToRGB565(int imageOffset);

            void transformRawToRGB555To565(int imageOffset, int imageSize);

            RGB15 transformBGR24ToScreenColor(BGR24 color);

            void clearSomeMemory();

            void setMapSurfaceHeightRange(int start, int end);

            void setMapSurfaceHeightRangeUnk();

            void temporarySaveMapSurfaceHeightRangeUnk();

            void restoreMapSurfaceHeightRangeFromTemporaryUnk();

            void setScreenMenuSurfaceHeightRange(int start, int end);

            void setScreenMenuSurfaceHeightRangeToResolution();

            void drawBitmapFace(int bitmapFaceIndex, int xPos, int yPos);

            void renderFacesSmallUnk(int facesIndex, int drawX, int drawY);

            void drawBitmapFaceWithBlendUnk(int bitmapFaceIndex, int xPos, int yPos, int colorOrBlendOrGammaUnk);

            void renderFunctionResponsibleForManyGameObjects(
                int drawX, int drawY, int imageWidth, int imageHeight, ushort* imageAddress);

            void renderInterfaceOrBuildingOccupationArea(
                int x, int y, int width, int height, ushort* imageDataPtr, int blendStrengthUnk);

            void renderBlendedBlackBox(int drawX, int drawY, int drawXEnd, int drawYEnd, int blendStrengthUnk);

            void renderGmWithPreparedAlphaMask(
                int x, int y, int width, int height, ushort* imageDataPtr, int blendStrength);

            void renderTgxWithColorUnk(
                int xPos, int yPos, int width, int height, ushort* imageSource, ushort fillColorUnk);

            void renderTgxWithColorAndBlendingUnk(int xPos, int yPos, int width, int height, ushort* imageSource,
                ushort fillColorUnk, int blendStrengthUnk);

            void renderUnitAnimationUnk(int xPosition, int yPosition, int width, int height, byte* imageAddress);

            void renderUnitAnimationWithBlendingUnk(
                int xPosition, int yPosition, int width, int height, byte* imageAddress, int blendStrengthUnk);

            int loadGfxFile(char* tgxFileName);

            int loadGFX8(char* gfx8Filename);

            int loadGfxAtBufferEnd(char* fileName);

            BOOLEnum FUN_004548d0(char* param_1);

            void renderLoadedGfx(int loadedGfxIndex, int xPos, int yPos);

            void setRenderingRectToGameResolution();

            void setRenderingRect(int xPos, int yPos, int width, int heigth);

            BOOLEnum checkIfGfxTgxStartsWithTransparentPixels(int gfxIndex);

            void renderGfxTgxWithBlending(int gfxIndex, int x, int y, int blendStrengthUnk);

            void drawTgxOnFlaggedSurface(int xPos, int yPos, int gfxWidth, int gfxHeight, ushort* tgxSourcePtr);

            void loadCampaignMapGfxUnk();

            void setMenuTabIndexUnk(int indexToSetToMinusOne);

            void setActiveMenuTabIndexToZero();

            void moveOverlappingMenuPartsToMapSurface();

            void transformUncompressedImageWithMarkerUnkToRGB565(int imageIndex);

            void transformTgxCompressedImageToRGB565(int imageIndex);

            void transformTilesetToRGB565(int imageIndex);

            void transformUncompressedImageToRGB565(int imageIndex);

            void renderGM(eGMInt gmID, int imageID, int drawX, int drawY);

            void renderGMWithBlending(GmIDInt GmID, int imageID, int drawX, int drawY, int blendStrengthUnk);

            void drawTgxGmOnFlaggedSurface(GmIDInt gmId, int imageIndexInGm, int xPos, int yPos);

            void renderTextChar(int xPos, int yPos, int imageId, FontRenderTypeInt renderType, int lineHeight,
                ushort fillColor, int blendStrength);

            void renderGMWithAlphaMask(
                GmIDInt gmID, int imageID, int xPos, int yPos, GmIDInt maskGmID, int alphaImageID, int blendStrength);

            void drawGfxOnFlaggedSurface(int gfxIndex, int xPos, int yPos);

            void adaptGmColorsToRGB565IfRequired(int gmID, int imageIndex);

            void loadGMFile(GmIDInt gmID, char* gmFileName);

            void loadGmFiles(char* fileNameArray);
        };

        static_assert_cpp98_obj(sizeof(TextureRenderCore) == 1496196, TextureRenderCore);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(TextureRenderCore, false, Address::SHC_3BB0A8C1_0x01FEA090) pDAT_TextureRenderCore;

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
