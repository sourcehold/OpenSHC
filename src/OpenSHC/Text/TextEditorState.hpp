/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Text/TextEditorState.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "mbstring.h"
#include "winnt.h"

namespace OpenSHC {
namespace Text {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00023974
    class TextEditorState {
    public:
        pointer DAT_PointerToTemporaryTextMemory; // 0x00000000 length: 4
        undefined4 customHelpTextLength; // 0x00000004 length: 4
        undefined4 isDialogStateInitialized; // 0x00000008 length: 4
        undefined4 helpDialogVariant; // 0x0000000C length: 4
        undefined4 useInGameHelpHandler; // 0x00000010 length: 4
        undefined4 savedMenuViewType; // 0x00000014 length: 4
        undefined4 savedActiveMenuTab; // 0x00000018 length: 4
        undefined4 savedMenuFlag; // 0x0000001C length: 4
        BOOLEnum pendingCreditsFadeBorder; // 0x00000020 length: 4
        BOOLEnum helpSectionParseSucceeded; // 0x00000024 length: 4
        undefined4 currentHelpSectionID; // 0x00000028 length: 4
        undefined4 helpSectionHistoryStack[30]; // 0x0000002C length: 120
        undefined4 counter; // 0x000000A4 length: 4
        undefined4 helpContentScrollOffsetY; // 0x000000A8 length: 4
        undefined4 topVisibleLineIndex; // 0x000000AC length: 4
        undefined4 dialogX; // 0x000000B0 length: 4
        undefined4 dialogY; // 0x000000B4 length: 4
        undefined4 dialogWidth; // 0x000000B8 length: 4
        undefined4 dialogHeight; // 0x000000BC length: 4
        undefined4 dialogContentX; // 0x000000C0 length: 4
        undefined4 dialogContentY; // 0x000000C4 length: 4
        undefined4 dialogContentHeight; // 0x000000C8 length: 4
        undefined4 dialogContentWidth; // 0x000000CC length: 4
        undefined4 helpContentScrollX; // 0x000000D0 length: 4
        undefined4 helpContentScrollY; // 0x000000D4 length: 4
        undefined4 activeHelpHotspotIndex; // 0x000000D8 length: 4
        undefined4 helpDialogSubMode; // 0x000000DC length: 4
        undefined4 useAlternateHelpTab; // 0x000000E0 length: 4
        undefined4 isCustomTextMode; // 0x000000E4 length: 4
        undefined4 useWideHelpLayout; // 0x000000E8 length: 4
        undefined4 pendingTokenTypeToSkip; // 0x000000EC length: 4
        undefined4 isTextHelpDialogMode; // 0x000000F0 length: 4
        char* customHelpTextPointer; // 0x000000F4 length: 4
        undefined4 isCustomHelpTextWide; // 0x000000F8 length: 4
        undefined4 customHelpTextBufferSize; // 0x000000FC length: 4
        undefined4 customTextMaxLength; // 0x00000100 length: 4
        char soundFileNames[5][1000]; // 0x00000104 length: 5000
        byte soundFilePlayedFlags[5]; // 0x0000148C length: 5
        undefined1 padding_0x1491[3]; // 0x00001491 length: 3
        undefined4 soundFileCount; // 0x00001494 length: 4
        char graphicFileNames[20][1000]; // 0x00001498 length: 20000
        undefined4 graphicFileCount; // 0x000062B8 length: 4
        short lineLayoutTable[60000]; // 0x000062BC length: 120000
        int imageHotspotCount; // 0x0002377C length: 4
        short imageHotspotTable[50][4]; // 0x00023780 length: 400
        int intArray1[25]; // 0x00023910 length: 100

    private:
        TextEditorState(TextEditorState const&);
        void operator=(TextEditorState const&);

    public:
        TextEditorState() {};
        ~TextEditorState() {};

        // Constructor
        TextEditorState* Constructor_TextEditorState();

        void setHelpWindowBounds(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);

        void resetHelpStateFields();

        int findHelpSectionIndexByName(char* param_1);

        int findOrAddHelpSectionName(char* param_1);

        WCHAR parseHLPPart(FILE* filePointer);

        void loadHelpSectionGraphics();

        undefined* getWideCharPointer(int* param_1);

        void renderHelpImageHotspots();

        void bltTextToScreenIfNeedBe();

        void drawBorderStyle0x20(int param_1, int param_2, int param_3, int param_4);

        void drawHelpWindowBackground();

        int findHelpGraphicIndexByName(char* param_1);

        void findOrAddHelpGraphicName(char* param_1);

        int getNextHelpSectionID(int param_1);

        int getPrevHelpSectionID(int param_1);

        char* getHelpSectionText(int param_1);

        int getNextHelpColorEntryIndex(int param_1);

        int getPrevHelpColorEntryIndex(int param_1);

        int findSoundIndexByName(char* param_1);

        void findOrAddSoundName(char* param_1);

        void saveHelpFileToResource();

        undefined4 getHelpTokenAdvanceLength(undefined4 param_1);

        void insertHelpTextToken(undefined4 param_1);

        void closeHelpDialogAndReturnToMenu();

        void readCrusaderHelpHlp(LPCSTR param_1);

        undefined4 loadAndParseHelpFile(FILE* param_1);

        void parseHlp();

        void processHelpRichTextTokens(int param_1);

        void setTextRenderingLogic();

        void initializeAndLayoutHelpText();

        void renderHelpDialogIfOpen();

        void loadAndLayoutHelpContent();

        void openBuildingHelpDialog(int param_1);

        void openInGameHelpDialog(int param_1);

        void openScenarioHelpDialog(int param_1);

        void openCreditsScrollDialog(int param_1);

        void openMapDescriptionEditorDialog(int param_1);

        void setCustomHelpText(char* param_1, undefined4 param_2);

        void popHelpDialogStack();

        void openUnusedHelpTextEditorDialog(int param_1);
    };

    static_assert_cpp98_obj(sizeof(TextEditorState) == 145780, TextEditorState);

#pragma pack(pop)

} // namespace Text
} // namespace OpenSHC
