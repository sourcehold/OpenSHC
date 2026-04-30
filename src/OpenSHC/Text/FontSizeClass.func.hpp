/**
  path: 'OpenSHC/Text/FontSizeClass.func.hpp'
*/

#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/FontRenderTypeInt.hpp"
#include "OpenSHC/Text/FontSizeClass.hpp"
namespace OpenSHC {
namespace Text {
    namespace FontSizeClass_Func {

        using OpenSHC::IO::Graphics::GmIDInt;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::FontRenderTypeInt;

        MACRO_FUNCTION_RESOLVER(void (FontSizeClass::*)(GmIDInt, int, FontRenderTypeInt, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00469A30, &FontSizeClass::setupFontSizeClassObject)
        setupFontSizeClassObject;

        MACRO_FUNCTION_RESOLVER(
            int (FontSizeClass::*)(char*, int), false, Address::SHC_3BB0A8C1_0x00469A70, &FontSizeClass::getWidthOfText)
        getWidthOfText;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(char*, int, char*, int, int*), false,
            Address::SHC_3BB0A8C1_0x00469B90, &FontSizeClass::getWordStartingFromPos)
        getWordStartingFromPos;

        MACRO_FUNCTION_RESOLVER(
            void (FontSizeClass::*)(char*, int), false, Address::SHC_3BB0A8C1_0x00469C40, &FontSizeClass::meth_0x469c40)
        meth_0x469c40;

        MACRO_FUNCTION_RESOLVER(
            int (FontSizeClass::*)(byte), false, Address::SHC_3BB0A8C1_0x00469E10, &FontSizeClass::getCharWidthUnk)
        getCharWidthUnk;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(LPWSTR, int), false, Address::SHC_3BB0A8C1_0x00471610,
            &FontSizeClass::getWidthOfWideText)
        getWidthOfWideText;

        MACRO_FUNCTION_RESOLVER(
            dword (FontSizeClass::*)(WCHAR), false, Address::SHC_3BB0A8C1_0x00471670, &FontSizeClass::meth_0x471670)
        meth_0x471670;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(char*, int, int, int, BGR24, int), false,
            Address::SHC_3BB0A8C1_0x00472D60, &FontSizeClass::renderText)
        renderText;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(char*, int, int, int, BGR24, int, int), false,
            Address::SHC_3BB0A8C1_0x00472EF0, &FontSizeClass::renderMultilineTextUnk)
        renderMultilineTextUnk;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(LPWSTR, int, int, int, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00473300, &FontSizeClass::renderMultilineWideTextUnk)
        renderMultilineWideTextUnk;

        MACRO_FUNCTION_RESOLVER(void (FontSizeClass::*)(int, int, int, int, BGR24), false,
            Address::SHC_3BB0A8C1_0x004733A0, &FontSizeClass::renderSomeSpecificTextUnk)
        renderSomeSpecificTextUnk;

        MACRO_FUNCTION_RESOLVER(int (FontSizeClass::*)(char, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00473640, &FontSizeClass::renderCharUnk)
        renderCharUnk;

        MACRO_FUNCTION_RESOLVER(void (FontSizeClass::*)(LPWSTR, int, int, int, BGR24, int), false,
            Address::SHC_3BB0A8C1_0x004737B0, &FontSizeClass::renderWideText)
        renderWideText;

        MACRO_FUNCTION_RESOLVER(void (FontSizeClass::*)(undefined4, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00473830, &FontSizeClass::meth_0x473830)
        meth_0x473830;

    } // namespace FontSizeClass_Func
} // namespace Text
} // namespace OpenSHC
