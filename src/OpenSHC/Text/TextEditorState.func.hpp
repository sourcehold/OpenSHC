/**
  path: 'OpenSHC/Text/TextEditorState.func.hpp'
*/

#include "OpenSHC/Text/TextEditorState.hpp"

#include "mbstring.h"
#include "winnt.h"
namespace OpenSHC {
namespace Text {
    namespace TextEditorState_Func {

        // Constructor

        MACRO_FUNCTION_RESOLVER(TextEditorState* (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F130,
            &TextEditorState::Constructor_TextEditorState)
        Constructor_TextEditorState;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4, undefined4, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x0045D080, &TextEditorState::setHelpWindowBounds)
        setHelpWindowBounds;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D0C0,
            &TextEditorState::resetHelpStateFields)
        resetHelpStateFields;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D140,
            &TextEditorState::findHelpSectionIndexByName)
        findHelpSectionIndexByName;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D1A0,
            &TextEditorState::findOrAddHelpSectionName)
        findOrAddHelpSectionName;

        MACRO_FUNCTION_RESOLVER(
            WCHAR (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045D200, &TextEditorState::parseHLPPart)
        parseHLPPart;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D370,
            &TextEditorState::loadHelpSectionGraphics)
        loadHelpSectionGraphics;

        MACRO_FUNCTION_RESOLVER(undefined* (TextEditorState::*)(int*), false, Address::SHC_3BB0A8C1_0x0045D3C0,
            &TextEditorState::getWideCharPointer)
        getWideCharPointer;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D430,
            &TextEditorState::renderHelpImageHotspots)
        renderHelpImageHotspots;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D690,
            &TextEditorState::bltTextToScreenIfNeedBe)
        bltTextToScreenIfNeedBe;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0045D6C0,
            &TextEditorState::drawBorderStyle0x20)
        drawBorderStyle0x20;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045D740,
            &TextEditorState::drawHelpWindowBackground)
        drawHelpWindowBackground;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D890,
            &TextEditorState::findHelpGraphicIndexByName)
        findHelpGraphicIndexByName;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045D8F0,
            &TextEditorState::findOrAddHelpGraphicName)
        findOrAddHelpGraphicName;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D950,
            &TextEditorState::getNextHelpSectionID)
        getNextHelpSectionID;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D990,
            &TextEditorState::getPrevHelpSectionID)
        getPrevHelpSectionID;

        MACRO_FUNCTION_RESOLVER(char* (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045D9E0,
            &TextEditorState::getHelpSectionText)
        getHelpSectionText;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045DA20,
            &TextEditorState::getNextHelpColorEntryIndex)
        getNextHelpColorEntryIndex;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045DA40,
            &TextEditorState::getPrevHelpColorEntryIndex)
        getPrevHelpColorEntryIndex;

        MACRO_FUNCTION_RESOLVER(int (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DA80,
            &TextEditorState::findSoundIndexByName)
        findSoundIndexByName;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*), false, Address::SHC_3BB0A8C1_0x0045DAE0,
            &TextEditorState::findOrAddSoundName)
        findOrAddSoundName;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045DB40,
            &TextEditorState::saveHelpFileToResource)
        saveHelpFileToResource;

        MACRO_FUNCTION_RESOLVER(undefined4 (TextEditorState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0045F080,
            &TextEditorState::getHelpTokenAdvanceLength)
        getHelpTokenAdvanceLength;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x0045F0D0,
            &TextEditorState::insertHelpTextToken)
        insertHelpTextToken;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F240,
            &TextEditorState::closeHelpDialogAndReturnToMenu)
        closeHelpDialogAndReturnToMenu;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(LPCSTR), false, Address::SHC_3BB0A8C1_0x0045F470,
            &TextEditorState::readCrusaderHelpHlp)
        readCrusaderHelpHlp;

        MACRO_FUNCTION_RESOLVER(undefined4 (TextEditorState::*)(FILE*), false, Address::SHC_3BB0A8C1_0x0045F580,
            &TextEditorState::loadAndParseHelpFile)
        loadAndParseHelpFile;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x0045F5B0, &TextEditorState::parseHlp)
        parseHlp;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x0045FDC0,
            &TextEditorState::processHelpRichTextTokens)
        processHelpRichTextTokens;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004613E0,
            &TextEditorState::setTextRenderingLogic)
        setTextRenderingLogic;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004614D0,
            &TextEditorState::initializeAndLayoutHelpText)
        initializeAndLayoutHelpText;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00461550,
            &TextEditorState::renderHelpDialogIfOpen)
        renderHelpDialogIfOpen;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x004619D0,
            &TextEditorState::loadAndLayoutHelpContent)
        loadAndLayoutHelpContent;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461A20,
            &TextEditorState::openBuildingHelpDialog)
        openBuildingHelpDialog;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461B90,
            &TextEditorState::openInGameHelpDialog)
        openInGameHelpDialog;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461CF0,
            &TextEditorState::openScenarioHelpDialog)
        openScenarioHelpDialog;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461E50,
            &TextEditorState::openCreditsScrollDialog)
        openCreditsScrollDialog;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00461F90,
            &TextEditorState::openMapDescriptionEditorDialog)
        openMapDescriptionEditorDialog;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(char*, undefined4), false, Address::SHC_3BB0A8C1_0x004620F0,
            &TextEditorState::setCustomHelpText)
        setCustomHelpText;

        MACRO_FUNCTION_RESOLVER(
            void (TextEditorState::*)(), false, Address::SHC_3BB0A8C1_0x00462150, &TextEditorState::popHelpDialogStack)
        popHelpDialogStack;

        MACRO_FUNCTION_RESOLVER(void (TextEditorState::*)(int), false, Address::SHC_3BB0A8C1_0x00462190,
            &TextEditorState::openUnusedHelpTextEditorDialog)
        openUnusedHelpTextEditorDialog;

    } // namespace TextEditorState_Func
} // namespace Text
} // namespace OpenSHC
