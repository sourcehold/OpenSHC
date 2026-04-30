/**
  path: 'OpenSHC/UI/Rendering/PencilRenderCore.func.hpp'
*/

#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevelInt.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {
        namespace PencilRenderCore_Func {

            using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevelInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00468C50,
                &PencilRenderCore::setupPencilSurface)
            setupPencilSurface;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PencilRenderCore::*)(int, int, int, int, ushort), false,
                Address::SHC_3BB0A8C1_0x00468C80, &PencilRenderCore::setupPencil)
            setupPencil;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00468DE0,
                &PencilRenderCore::drawHorizontalLine)
            drawHorizontalLine;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00468E40,
                &PencilRenderCore::drawVerticalLine)
            drawVerticalLine;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00468EA0,
                &PencilRenderCore::dimHorizontalLine)
            dimHorizontalLine;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00468F20,
                &PencilRenderCore::drawCurrentPixel)
            drawCurrentPixel;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x00468F70,
                &PencilRenderCore::drawPixelPattern4x4)
            drawPixelPattern4x4;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00468FE0, &PencilRenderCore::drawHeaderBanner)
            drawHeaderBanner;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(uint, int, int, int, BOOLEnum, int, int), false,
                Address::SHC_3BB0A8C1_0x004690E0, &PencilRenderCore::drawScrollbar)
            drawScrollbar;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int), false, Address::SHC_3BB0A8C1_0x00469290,
                &PencilRenderCore::renderUpDownButtonUnk)
            renderUpDownButtonUnk;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(BOOLEnum, int, int), false,
                Address::SHC_3BB0A8C1_0x004692E0, &PencilRenderCore::drawTableCellBackground)
            drawTableCellBackground;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, ushort), false,
                Address::SHC_3BB0A8C1_0x00470E90, &PencilRenderCore::drawColorBox)
            drawColorBox;

            MACRO_FUNCTION_RESOLVER(
                void (PencilRenderCore::*)(int, int, int, int, ushort, RoundedBoxEdgeRoundingLevelInt), false,
                Address::SHC_3BB0A8C1_0x00470EE0, &PencilRenderCore::drawBoxWithRoundedEdgesAndColor)
            drawBoxWithRoundedEdgesAndColor;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00471000, &PencilRenderCore::drawBlendedBlackBox)
            drawBlendedBlackBox;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00471050, &PencilRenderCore::dimBox)
            dimBox;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, RoundedBoxEdgeRoundingLevelInt),
                false, Address::SHC_3BB0A8C1_0x004710A0, &PencilRenderCore::drawBoxWithRoundedEdges)
            drawBoxWithRoundedEdges;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, ushort), false,
                Address::SHC_3BB0A8C1_0x004711B0, &PencilRenderCore::drawBorderBox)
            drawBorderBox;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00471220,
                &PencilRenderCore::drawDiagonalHeigherThanWideUnk)
            drawDiagonalHeigherThanWideUnk;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x00471280,
                &PencilRenderCore::drawDiagonalWiderThanHighUnk)
            drawDiagonalWiderThanHighUnk;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(), false, Address::SHC_3BB0A8C1_0x004712E0,
                &PencilRenderCore::drawPixelPattern4x4OverWholeScreen)
            drawPixelPattern4x4OverWholeScreen;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00471340, &PencilRenderCore::drawBorderedBoxWithBlendedBackground)
            drawBorderedBoxWithBlendedBackground;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00471440, &PencilRenderCore::drawBorderedBoxWithCustomBlendedBackground)
            drawBorderedBoxWithCustomBlendedBackground;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, ushort), false,
                Address::SHC_3BB0A8C1_0x00472B20, &PencilRenderCore::drawLine)
            drawLine;

            MACRO_FUNCTION_RESOLVER(void (PencilRenderCore::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00475CC0, &PencilRenderCore::drawHeaderTextBanner)
            drawHeaderTextBanner;

        } // namespace PencilRenderCore_Func
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
