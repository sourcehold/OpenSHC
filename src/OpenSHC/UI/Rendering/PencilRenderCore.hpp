/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Rendering/PencilRenderCore.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevelInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTargetInt;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevelInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000042
        class PencilRenderCore {
        public:
            ushort otherColorUnk_0x0; // 0x00000000 length: 2
            undefined1 padding_0x2[2]; // 0x00000002 length: 2
            ushort* surfacePtr; // 0x00000004 length: 4
            dword horizontalByteSize; // 0x00000008 length: 4
            RenderTargetInt surfaceTarget; // 0x0000000C length: 4
            dword currentX; // 0x00000010 length: 4
            dword currentY; // 0x00000014 length: 4
            dword field8_0x18; // 0x00000018 length: 4
            dword field9_0x1c; // 0x0000001C length: 4
            dword moveDirectionXUnk_0x20; // 0x00000020 length: 4
            dword moveDirectionYUnk_0x24; // 0x00000024 length: 4
            int currentWidth_0x28; // 0x00000028 length: 4
            int currentHeight_0x2c; // 0x0000002C length: 4
            dword drawStartX; // 0x00000030 length: 4
            dword drawStartY; // 0x00000034 length: 4
            dword drawEndX; // 0x00000038 length: 4
            dword drawEndY; // 0x0000003C length: 4
            ushort drawColor; // 0x00000040 length: 2

        private:
            PencilRenderCore(PencilRenderCore const&);
            void operator=(PencilRenderCore const&);

            PencilRenderCore();
            ~PencilRenderCore();

        public:
            void setupPencilSurface();

            BOOLEnum setupPencil(int left, int top, int right, int bottom, ushort color);

            void drawHorizontalLine();

            void drawVerticalLine();

            void dimHorizontalLine();

            void drawCurrentPixel();

            void drawPixelPattern4x4(int drawX, int drawY);

            void drawHeaderBanner(int xPos, int yPos, int width, int unusedUnk);

            void drawScrollbar(
                uint xPos, int yPos, int height, int thumbYPos, BOOLEnum isDragged, int thumbHeight, int blendStrength);

            void renderUpDownButtonUnk(int isDownButtonUnk, int blendStrengthUnk);

            void drawTableCellBackground(BOOLEnum isSelected, int indexToGetStripes, int blendStrength);

            void drawColorBox(int left, int top, int right, int bottom, ushort color);

            void drawBoxWithRoundedEdgesAndColor(
                int left, int top, int right, int bottom, ushort color, RoundedBoxEdgeRoundingLevelInt roundingLevel);

            void drawBlendedBlackBox(int left, int top, int right, int bottom, int blendStrengh);

            void dimBox(int left, int top, int right, int bottom);

            void drawBoxWithRoundedEdges(
                int left, int top, int right, int bottom, RoundedBoxEdgeRoundingLevelInt roundingLevel);

            void drawBorderBox(int left, int top, int right, int bottom, ushort color);

            void drawDiagonalHeigherThanWideUnk();

            void drawDiagonalWiderThanHighUnk();

            void drawPixelPattern4x4OverWholeScreen();

            void drawBorderedBoxWithBlendedBackground(int xPos, int yPos, int width, int height);

            void drawBorderedBoxWithCustomBlendedBackground(
                int xPos, int yPos, int width, int height, int blendStrength);

            void drawLine(int x1, int y1, int x2, int y2, ushort color);

            void drawHeaderTextBanner(int textGroupIndex, int textNumInGroup, int xPos, int yPos, int width);
        };

        static_assert_cpp98_obj(sizeof(PencilRenderCore) == 66, PencilRenderCore);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(PencilRenderCore, false, Address::SHC_3BB0A8C1_0x0191D720) pDAT_PencilRenderCore;

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
