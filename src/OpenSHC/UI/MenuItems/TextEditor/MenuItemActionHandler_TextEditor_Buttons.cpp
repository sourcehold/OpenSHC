#include "../TextEditor.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextToken.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::Enums::HelpTextToken;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00462340
        void TextEditor::MenuItemActionHandler_TextEditor_Buttons(int param_1, ...)
        {
            char cVar1;
            WCHAR* pWVar2;
            uint uVar3;
            char (*pacVar4)[1000];
            char (*pacVar5)[1000];
            int iVar6;
            BOOLEnum BVar7;
            char* pcVar8;
            int iVar9;
            undefined4 uVar10;
            HelpTextToken token;
            iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
            pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
            switch (param_1) {
            case 0:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
            case 0x1e:
            case 0x1f:
                break;
            case 1:
                DAT_TextEditorState::instance.helpDialogSubMode
                    = (uint)(DAT_TextEditorState::instance.helpDialogSubMode == 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 2:
                DAT_TextEditorState::instance.customHelpTextLength = 0;
                DAT_TextEditorState::instance.graphicFileCount = 0;
                DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                DAT_TextEditorState::instance.topVisibleLineIndex = 0xffffffff;
                *DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory = L'\0';
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 3:
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    DAT_ResourceManager::ptr)("Select help file to load");
                if (BVar7 != FALSE) {
                    pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                    do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog,
                            DAT_TextEditorState::ptr)(iVar6);
                    }
                }
                break;
            case 4:
                if (DAT_TextEditorState::instance.customHelpTextLength != 0) {
                    pacVar5 = DAT_UserHelpDefinedData::instance.HelpSections
                        + DAT_TextEditorState::instance.currentHelpSectionID;
                    pacVar4 = pacVar5;
                    do {
                        cVar1 = (*pacVar4)[0];
                        *(char*)((int)pacVar4 + (0x11bf521 - (int)pacVar5)) = cVar1;
                        pacVar4 = (char (*)[1000])(*pacVar4 + 1);
                    } while (cVar1 != '\0');
                    iVar6 = 0x11bf138 - (int)pacVar5;
                    do {
                        cVar1 = (*pacVar5)[0];
                        *(char*)((int)pacVar5 + iVar6) = cVar1;
                        pacVar5 = (char (*)[1000])(*pacVar5 + 1);
                    } while (cVar1 != '\0');
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showSaveHelpFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7 != FALSE) {
                        pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                        do {
                            cVar1 = *pcVar8;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                            DAT_TextEditorState::instance.currentHelpSectionID
                                = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                                    DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::saveHelpFileToResource,
                                DAT_TextEditorState::ptr)();
                        }
                    }
                }
                break;
            case 5:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::showOpenGfxFileDialog, DAT_ResourceManager::ptr)();
                if (BVar7 != FALSE) {
                    pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                    do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpGraphicName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::loadHelpSectionGraphics, DAT_TextEditorState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_PIC);
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = L'\x01';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                            = (WCHAR)iVar6;
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                            = L'\0';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 3]
                            = L'\x01';
                        token = OpenSHC::Text::Enums::HTT_PIC;
                        goto LAB_0046264e;
                    }
                }
                break;
            case 6:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    DAT_ResourceManager::ptr)("Select help file to link to");
                if (BVar7 != FALSE) {
                    pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                    do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_LINK);
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = L'\x04';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                            = (WCHAR)iVar6;
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                            = L'\x04';
                        token = OpenSHC::Text::Enums::HTT_LINK;
                        goto LAB_0046264e;
                    }
                }
                break;
            case 7:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDLINK);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\x05';
                token = OpenSHC::Text::Enums::HTT_ENDLINK;
                goto LAB_0046264e;
            case 8:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_FONT);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\x02';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                    = L'\x11';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                    = L'\x02';
                DAT_TextEditorState::instance.pendingTokenTypeToSkip = 2;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 9:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_CENTRE);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\a';
                token = OpenSHC::Text::Enums::HTT_CENTRE;
                goto LAB_0046264e;
            case 10:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDCENTRE);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\b';
                token = OpenSHC::Text::Enums::HTT_ENDCENTRE;
            LAB_0046264e:
                iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                    DAT_TextEditorState::ptr)(token);
                DAT_TextEditorState::instance.activeHelpHotspotIndex
                    = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 0xb:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                uVar10 = 3;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_COLOUR);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\x03';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                    = L'\x01';
                goto LAB_004628ba;
            case 0xc:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                uVar10 = 10;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_SOUND);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\n';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1] = L'\v';
                goto LAB_004628ba;
            case 0xd:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::showOpenSoundFileDialog, DAT_ResourceManager::ptr)();
                if (BVar7 != FALSE) {
                    pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                    do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddSoundName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_STRING);
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = L'\v';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                            = (WCHAR)iVar6;
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                            = L'\v';
                        token = OpenSHC::Text::Enums::HTT_STRING;
                        goto LAB_0046264e;
                    }
                }
                break;
            case 0xe:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                uVar10 = 0xc;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)((OpenSHC::Text::Enums::HelpTextToken)(OpenSHC::Text::Enums::HTT_ENDCENTRE
                    | OpenSHC::Text::Enums::HTT_LINK));
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\f';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1] = L'\0';
            LAB_004628ba:
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                    = (WCHAR)uVar10;
                DAT_TextEditorState::instance.pendingTokenTypeToSkip = uVar10;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 0xf:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != ((HelpTextToken)0)) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.activeHelpHotspotIndex + iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = ((HelpTextToken)0);
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    DAT_ResourceManager::ptr)("Select help file to include");
                if (BVar7 != FALSE) {
                    pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                    do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                            DAT_TextEditorState::ptr)(
                            (OpenSHC::Text::Enums::HelpTextToken)(OpenSHC::Text::Enums::HTT_ENDCENTRE
                                | OpenSHC::Text::Enums::HTT_NEWPARAGRAPH));
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = L'\x0e';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                            = (WCHAR)iVar6;
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                            = L'\x0e';
                        token = (OpenSHC::Text::Enums::HelpTextToken)(OpenSHC::Text::Enums::HTT_ENDCENTRE
                            | OpenSHC::Text::Enums::HTT_NEWPARAGRAPH);
                        goto LAB_0046264e;
                    }
                }
                break;
            case 0x14:
                DAT_TextEditorState::instance.useWideHelpLayout = DAT_TextEditorState::instance.useWideHelpLayout ^ 1;
                if (DAT_TextEditorState::instance.useWideHelpLayout == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setHelpWindowBounds,
                        DAT_TextEditorState::ptr)(DAT_TextEditorState::instance.dialogX + 10,
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogY + 10)),
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogWidth + -0x28)),
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogHeight + -0x2d)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                DAT_TextEditorState::instance.dialogContentX = DAT_TextEditorState::instance.dialogX + 10;
                DAT_TextEditorState::instance.dialogContentY = DAT_TextEditorState::instance.dialogY + 10;
                DAT_TextEditorState::instance.dialogContentWidth = 0x298;
                DAT_TextEditorState::instance.dialogContentHeight = 0x123;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 0x20:
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showOpenGfxFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7 != FALSE) {
                        pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                        do {
                            cVar1 = *pcVar8;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpGraphicName,
                                DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1] = (WCHAR)iVar6;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadHelpSectionGraphics,
                                DAT_TextEditorState::ptr)();
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                                DAT_TextEditorState::ptr)();
                        }
                    }
                    break;
                case 4:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                        DAT_ResourceManager::ptr)("Select help file to link to");
                    if (BVar7 != FALSE) {
                        pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                        do {
                            cVar1 = *pcVar8;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                    LAB_00462c09:
                        if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                                DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1] = (WCHAR)iVar6;
                        }
                    }
                    break;
                case 0xb:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showOpenSoundFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7 != FALSE) {
                        pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                        do {
                            cVar1 = *pcVar8;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        if (pcVar8 != DAT_ResourceManager::instance.strFileTitle + 1) {
                            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddSoundName,
                                DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1] = (WCHAR)iVar6;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                                DAT_TextEditorState::ptr)();
                        }
                    }
                    break;
                case 0xe:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                        DAT_ResourceManager::ptr)("Select help file to include");
                    if (BVar7 != FALSE) {
                        pcVar8 = DAT_ResourceManager::instance.strFileTitle;
                        do {
                            cVar1 = *pcVar8;
                            pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                        goto LAB_00462c09;
                    }
                }
                break;
            case 0x21:
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\0';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 2:
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getPrevHelpSectionID,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 3:
                case 10:
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getPrevHelpColorEntryIndex,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 0xc:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                        = (WCHAR)((ulonglong)((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                                  [DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                                      + 0x13)
                            % 0x14);
                }
                break;
            case 0x22:
                switch (DAT_TextEditorState::instance.field52_0x23970) {
                case 1:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x01';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 2:
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getNextHelpSectionID,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 3:
                case 10:
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getNextHelpColorEntryIndex,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 0xc:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                        = (WCHAR)((ulonglong)((ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                                  [DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                                      + 1)
                            % 0x14);
                }
                break;
            case 0x23:
                if (DAT_TextEditorState::instance.field52_0x23970 == 1) {
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x02';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                break;
            case 0x24:
                if (DAT_TextEditorState::instance.field52_0x23970 == 1) {
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x03';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                break;
            case -5:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog, DAT_TextEditorState::ptr)(-1);
                return;
            case -4:
                if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::popHelpDialogStack, DAT_TextEditorState::ptr)();
                }
                break;
            case -3:
                if (DAT_TextEditorState::instance.useAlternateHelpTab == 0) {
                    if (-1 < DAT_TextEditorState::instance.field50_0x23968) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog,
                            DAT_TextEditorState::ptr)(DAT_TextEditorState::instance.field50_0x23968);
                    }
                } else if (-1 < DAT_TextEditorState::instance.field49_0x23964) {
                    DAT_TextEditorState::instance.activeHelpHotspotIndex
                        = DAT_TextEditorState::instance.field49_0x23964;
                }
                break;
            case -2:
                uVar3 = DAT_TextEditorState::instance.topVisibleLineIndex
                    - DAT_TextEditorState::instance.dialogContentHeight;
                if (((int)((((int)uVar3 < 1) - 1 & uVar3) - 0x12)
                        <= (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)
                    || (DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + 0x12,
                        (int)(((int)uVar3 < 1) - 1 & uVar3)
                            < (int)DAT_TextEditorState::instance.helpContentScrollOffsetY)) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY = ((int)uVar3 < 1) - 1 & uVar3;
                }
                return;
            case -1:
                if (0x11 < (int)DAT_TextEditorState::instance.helpContentScrollOffsetY) {
                    DAT_TextEditorState::instance.helpContentScrollOffsetY
                        = DAT_TextEditorState::instance.helpContentScrollOffsetY + -0x12;
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = 0;
                return;
            default:
                break;
            }
        }

    }
}
}
