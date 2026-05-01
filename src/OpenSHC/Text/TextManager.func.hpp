/**
  path: 'OpenSHC/Text/TextManager.func.hpp'
*/

#include "OpenSHC/DE/SHCDE/eTextSectionsInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignmentInt.hpp"
#include "OpenSHC/Text/TextManager.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace Text {
    namespace TextManager_Func {

        using OpenSHC::DE::SHCDE::eTextSectionsInt;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignmentInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(char*, int, int, TextAlignmentInt, uint, uint, int, BOOLEnum),
            false, Address::SHC_3BB0A8C1_0x00424320, &TextManager::renderInGameText)
        renderInGameText;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(char*, int, int, TextAlignmentInt, BGR24, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00424360, &TextManager::renderTextToScreen2)
        renderTextToScreen2;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(eTextSectionsInt, int, int, int, TextAlignmentInt, uint, uint, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00424390, &TextManager::renderText)
        renderText;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(eTextSectionsInt, int, int, int, TextAlignmentInt, uint, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x004243E0, &TextManager::renderText2)
        renderText2;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(eTextSectionsInt, int, int, int, TextAlignmentInt, uint, uint, int, BOOLEnum, int),
            false, Address::SHC_3BB0A8C1_0x00424420, &TextManager::renderInGameText2)
        renderInGameText2;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(eTextSectionsInt, int, int, int, TextAlignmentInt, uint, int, BOOLEnum, int), false,
            Address::SHC_3BB0A8C1_0x00424470, &TextManager::renderTextFromTextGroup)
        renderTextFromTextGroup;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(eTextSectionsInt, int, int, int), false,
            Address::SHC_3BB0A8C1_0x004244C0, &TextManager::renderMultilineText2)
        renderMultilineText2;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(eTextSectionsInt, int, int, int, int, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00424500, &TextManager::renderMultilineTextUnk)
        renderMultilineTextUnk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(eTextSectionsInt, int, int, int, int, uint, int), false,
            Address::SHC_3BB0A8C1_0x00424540, &TextManager::renderMultilineText2Unk)
        renderMultilineText2Unk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(eTextSectionsInt, int, int, int, int, uint, uint, int, int),
            false, Address::SHC_3BB0A8C1_0x00424580, &TextManager::renderMultilineText3Unk)
        renderMultilineText3Unk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(eTextSectionsInt, int, int, int, int, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x004245D0, &TextManager::renderMultilineText4Unk)
        renderMultilineText4Unk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, uint, uint, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00424620, &TextManager::renderNumber)
        renderNumber;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, uint, int, BOOL), false,
            Address::SHC_3BB0A8C1_0x00424650, &TextManager::renderLeftAlignedNumberToScreen)
        renderLeftAlignedNumberToScreen;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, TextAlignmentInt, uint, int, BOOLEnum), false,
            Address::SHC_3BB0A8C1_0x00424680, &TextManager::renderNumberToScreen)
        renderNumberToScreen;

        MACRO_FUNCTION_RESOLVER(int (TextManager::*)(eTextSectionsInt, int, int), false,
            Address::SHC_3BB0A8C1_0x004246B0, &TextManager::computeTextWidthForTextGroup)
        computeTextWidthForTextGroup;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(), false, Address::SHC_3BB0A8C1_0x00469E70, &TextManager::setupFontSizeClassObjects)
        setupFontSizeClassObjects;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(dword, dword), false, Address::SHC_3BB0A8C1_0x00469F20, &TextManager::meth_0x469f20)
        meth_0x469f20;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(), false, Address::SHC_3BB0A8C1_0x00469F40, &TextManager::meth_0x469f40)
        meth_0x469f40;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(char*, int, int), false, Address::SHC_3BB0A8C1_0x00469F50, &TextManager::trimText)
        trimText;

        MACRO_FUNCTION_RESOLVER(int (TextManager::*)(char*, int, int), false, Address::SHC_3BB0A8C1_0x00469F70,
            &TextManager::getTextWidthTillCursorUnk)
        getTextWidthTillCursorUnk;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(int), false, Address::SHC_3BB0A8C1_0x00469FA0, &TextManager::fillIntegerTextBuffer)
        fillIntegerTextBuffer;

        MACRO_FUNCTION_RESOLVER(char* (TextManager::*)(eTextSectionsInt, int), false, Address::SHC_3BB0A8C1_0x0046A050,
            &TextManager::getTextStringInGroupAtOffset)
        getTextStringInGroupAtOffset;

        MACRO_FUNCTION_RESOLVER(int (TextManager::*)(int, int, int, int, int, int, BOOL), false,
            Address::SHC_3BB0A8C1_0x0046A2C0, &TextManager::renderPartOfNumberUnk)
        renderPartOfNumberUnk;

        MACRO_FUNCTION_RESOLVER(
            int (TextManager::*)(int, int), false, Address::SHC_3BB0A8C1_0x0046A4D0, &TextManager::FUN_0046a4d0)
        FUN_0046a4d0;

        MACRO_FUNCTION_RESOLVER(
            int (TextManager::*)(char, int), false, Address::SHC_3BB0A8C1_0x0046A720, &TextManager::getCharWidth)
        getCharWidth;

        MACRO_FUNCTION_RESOLVER(
            int (TextManager::*)(char*, int), false, Address::SHC_3BB0A8C1_0x00471690, &TextManager::computeTextWidth)
        computeTextWidth;

        MACRO_FUNCTION_RESOLVER(
            int (TextManager::*)(int, int), false, Address::SHC_3BB0A8C1_0x004716D0, &TextManager::meth_0x4716d0)
        meth_0x4716d0;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(), false, Address::SHC_3BB0A8C1_0x00473870, &TextManager::loadCRTex)
        loadCRTex;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(char*, int, int, int, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00473A70, &TextManager::renderMultilineText5Unk)
        renderMultilineText5Unk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(char*, int, int, int, uint, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00473AC0, &TextManager::renderMultilineText6Unk)
        renderMultilineText6Unk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(LPWSTR, int, int, int, uint, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00473B50, &TextManager::renderMultilineWideTextUnk)
        renderMultilineWideTextUnk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, int, uint, int), false,
            Address::SHC_3BB0A8C1_0x00473BE0, &TextManager::renderSomeSpecificTextUnk)
        renderSomeSpecificTextUnk;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(char*, int, int, TextAlignmentInt, BGR24, int, BOOLEnum, int),
            false, Address::SHC_3BB0A8C1_0x00474250, &TextManager::renderTextToScreen)
        renderTextToScreen;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(LPWSTR, int, int, TextAlignmentInt, uint, int, BOOL, int), false,
            Address::SHC_3BB0A8C1_0x004742F0, &TextManager::renderWideText)
        renderWideText;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, TextAlignmentInt, uint, uint, int, BOOLEnum, int),
            false, Address::SHC_3BB0A8C1_0x00474390, &TextManager::renderNumber2)
        renderNumber2;

        MACRO_FUNCTION_RESOLVER(void (TextManager::*)(int, int, int, TextAlignmentInt, uint, int, BOOLEnum, int), false,
            Address::SHC_3BB0A8C1_0x00474430, &TextManager::renderNumberToScreen2)
        renderNumberToScreen2;

        MACRO_FUNCTION_RESOLVER(
            void (TextManager::*)(char*, int, int, TextAlignmentInt, uint, uint, int, BOOLEnum, int), false,
            Address::SHC_3BB0A8C1_0x00475E00, &TextManager::renderInGameTextWithShadow)
        renderInGameTextWithShadow;

    } // namespace TextManager_Func
} // namespace Text
} // namespace OpenSHC
