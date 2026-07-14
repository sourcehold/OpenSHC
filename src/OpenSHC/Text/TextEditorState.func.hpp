/**
  path: 'OpenSHC/Text/TextEditorState.func.hpp'
*/

#include "OpenSHC/Text/TextEditorState.hpp"

#include "mbstring.h"
#include "winnt.h"
namespace OpenSHC {
namespace Text {
    namespace TextEditorState_Func {

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4, undefined4, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x0045D080, &TextEditorState::setTextEditorFields)
        setTextEditorFields;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D0C0,
            &TextEditorState::resetTextEditorHandles)
        resetTextEditorHandles;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D140,
            &TextEditorState::findHelpSectionIndex)
        findHelpSectionIndex;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D1A0,
            &TextEditorState::findOrAddHelpSection)
        findOrAddHelpSection;

        MACRO_FUNCTION_RESOLVER(
            WCHAR (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045D200, &TextEditorState::parseHLPPart)
        parseHLPPart;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D370,
            &TextEditorState::loadTextEditorGfxResources)
        loadTextEditorGfxResources;

        MACRO_FUNCTION_RESOLVER(undefined* (TextEditorState::*)(int*), false, Address::SHC_3BB0A8C1_0x0045D3C0,
            &TextEditorState::getWideCharPointer)
        getWideCharPointer;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D430,
            &TextEditorState::drawTextEditorGfxItems)
        drawTextEditorGfxItems;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D690,
            &TextEditorState::bltTextToScreenIfNeedBe)
        bltTextToScreenIfNeedBe;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0045D6C0,
            &TextEditorState::drawBorderStyle0x20)
        drawBorderStyle0x20;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D740,
            &TextEditorState::drawTextEditorBackground)
        drawTextEditorBackground;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D890,
            &TextEditorState::findTextEditorGfxIndex)
        findTextEditorGfxIndex;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D8F0,
            &TextEditorState::findOrAddTextEditorGfx)
        findOrAddTextEditorGfx;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D950, &TextEditorState::getNextHelpPageId)
        getNextHelpPageId;

        MACRO_FUNCTION_RESOLVER(
            int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D990, &TextEditorState::getPrevHelpPageId)
        getPrevHelpPageId;

        MACRO_FUNCTION_RESOLVER(
            char* (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D9E0, &TextEditorState::getHelpPageText)
        getHelpPageText;

        MACRO_FUNCTION_RESOLVER(undefined (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045DA20,
            &TextEditorState::getNextHelpEntryIndex)
        getNextHelpEntryIndex;

        MACRO_FUNCTION_RESOLVER(undefined (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045DA40,
            &TextEditorState::getPrevHelpEntryIndex)
        getPrevHelpEntryIndex;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DA80,
            &TextEditorState::findTextEditorString1Index)
        findTextEditorString1Index;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DAE0,
            &TextEditorState::findOrAddTextEditorString1)
        findOrAddTextEditorString1;

        MACRO_FUNCTION_RESOLVER(undefined (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F080,
            &TextEditorState::getTextTokenSlotCount)
        getTextTokenSlotCount;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0045F0D0,
            &TextEditorState::insertTextTokenSlots)
        insertTextTokenSlots;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F240,
            &TextEditorState::someKindOfTextEscape)
        someKindOfTextEscape;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(LPCSTR), false, Address::SHC_3BB0A8C1_0x0045F470,
            &TextEditorState::readCrusaderHelpHlp)
        readCrusaderHelpHlp;

        MACRO_FUNCTION_RESOLVER(undefined4 (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045F580,
            &TextEditorState::loadCrusaderHelpFile)
        loadCrusaderHelpFile;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F5B0, &TextEditorState::parseHlp)
        parseHlp;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045FDC0, &TextEditorState::layoutHelpText)
        layoutHelpText;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004613E0,
            &TextEditorState::setTextRenderingLogic)
        setTextRenderingLogic;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004614D0,
            &TextEditorState::rebuildHelpTextLayout)
        rebuildHelpTextLayout;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00461550, &TextEditorState::renderTextEditor)
        renderTextEditor;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004619D0,
            &TextEditorState::loadAndLayoutHelpContent)
        loadAndLayoutHelpContent;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461A20,
            &TextEditorState::openBuildingHelpText)
        openBuildingHelpText;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461B90,
            &TextEditorState::openInGameHelpText)
        openInGameHelpText;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461CF0,
            &TextEditorState::openScenarioHelpText)
        openScenarioHelpText;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461E50,
            &TextEditorState::openCreditsScroll)
        openCreditsScroll;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461F90,
            &TextEditorState::openMapDescriptionEditor)
        openMapDescriptionEditor;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*, undefined4), false, Address::SHC_3BB0A8C1_0x004620F0,
            &TextEditorState::displayRawText)
        displayRawText;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00462150, &TextEditorState::goBackInHelpHistory)
        goBackInHelpHistory;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00462190,
            &TextEditorState::openHelpTextEditor)
        openHelpTextEditor;

    } // namespace TextEditorState_Func
} // namespace Text
} // namespace OpenSHC
