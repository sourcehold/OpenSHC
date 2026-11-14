// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../TextEditor.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextToken.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::Enums::HelpTextToken;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00462340
        void TextEditor::MenuItemActionHandler_TextEditor_Buttons(int param_1, ...)
        {
            WCHAR* pWVar2;
            int iVar4;
            int iVar5;
            int iVar6;
            BOOLEnum BVar7;
            int iVar9;
            switch (param_1) {
            case -1:
                iVar4 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                if (iVar4 >= 18) {
                    iVar4 -= 18;
                } else {
                    iVar4 = 0;
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar4;
                return;
            case -2:
                iVar5 = DAT_TextEditorState::instance.topVisibleLineIndex
                    - DAT_TextEditorState::instance.dialogContentHeight;
                iVar4 = DAT_TextEditorState::instance.helpContentScrollOffsetY;
                if (iVar4 < ((iVar5 <= 0) - 1 & iVar5) - 18) {
                    iVar4 += 18;
                    if (iVar4 <= ((iVar5 <= 0) - 1 & iVar5)) {
                        DAT_TextEditorState::instance.helpContentScrollOffsetY = iVar4;
                        return;
                    }
                }
                DAT_TextEditorState::instance.helpContentScrollOffsetY = (iVar5 <= 0) - 1 & iVar5;
                return;
            case -3:
                if (DAT_TextEditorState::instance.useAlternateHelpTab != 0) {
                    if (0 <= DAT_TextEditorState::instance.field_0x23964) {
                        DAT_TextEditorState::instance.activeHelpHotspotIndex
                            = DAT_TextEditorState::instance.field_0x23964;
                    }
                } else if (0 <= DAT_TextEditorState::instance.currentLinkId) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog,
                        DAT_TextEditorState::ptr)(DAT_TextEditorState::instance.currentLinkId);
                }
                break;
            case -4:
                if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::popHelpDialogStack, DAT_TextEditorState::ptr)();
                }
                break;
            case -5:
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog, DAT_TextEditorState::ptr)(-1);
                return;
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
                DAT_TextEditorState::instance.topVisibleLineIndex = -1;
                *DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory = L'\0';
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 3:
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    // "Select help file to load"
                    DAT_ResourceManager::ptr)(s_Select_help_file_to_load_005a5894);
                if (BVar7) {
                    if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openUnusedHelpTextEditorDialog,
                            DAT_TextEditorState::ptr)(iVar6);
                    }
                }
                break;
            case 4:
                if (DAT_TextEditorState::instance.customHelpTextLength != 0) {
                    strcpy(DAT_ResourceManager::instance.strFileTitle,
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[DAT_TextEditorState::instance.currentHelpSectionID]);
                    strcpy(DAT_ResourceManager::instance.strFile,
                        DAT_UserHelpDefinedData::instance
                            .HelpSections[DAT_TextEditorState::instance.currentHelpSectionID]);
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showSaveHelpFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7) {
                        if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::showOpenGfxFileDialog, DAT_ResourceManager::ptr)();
                if (BVar7) {
                    if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                        iVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_PIC);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                            DAT_TextEditorState::ptr)();
                        return;
                    }
                }
                break;
            case 6:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    // "Select help file to link to"
                    DAT_ResourceManager::ptr)(s_Select_help_file_to_link_to_005a5878);
                if (BVar7) {
                    if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                        iVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_LINK);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                            DAT_TextEditorState::ptr)();
                        return;
                    }
                }
                break;
            case 7:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDLINK);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\x05';
                iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDLINK);
                DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 8:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
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
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_CENTRE);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\a';
                iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_CENTRE);
                DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 10:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDCENTRE);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\b';
                iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_ENDCENTRE);
                DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 11:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_COLOUR);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\x03';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                    = L'\x01';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                    = (WCHAR)OpenSHC::Text::Enums::HTT_COLOUR;
                DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_COLOUR;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 12:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_SOUND);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\n';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1] = L'\v';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                    = (WCHAR)OpenSHC::Text::Enums::HTT_LINKCOLOUR;
                DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_LINKCOLOUR;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 13:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::showOpenSoundFileDialog, DAT_ResourceManager::ptr)();
                if (BVar7) {
                    if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                        iVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_STRING);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                            DAT_TextEditorState::ptr)();
                        return;
                    }
                }
                break;
            case 14:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                    DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_STRING);
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex] = L'\f';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1] = L'\0';
                DAT_TextEditorState::instance
                    .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                    = (WCHAR)OpenSHC::Text::Enums::HTT_STRING;
                DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_STRING;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 15:
                if (DAT_TextEditorState::instance.pendingTokenTypeToSkip != OpenSHC::Text::Enums::HTT_NONE) {
                    iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                        DAT_TextEditorState::ptr)(
                        (OpenSHC::Text::Enums::HelpTextToken)DAT_TextEditorState::instance.pendingTokenTypeToSkip);
                    DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                    DAT_TextEditorState::instance.pendingTokenTypeToSkip = OpenSHC::Text::Enums::HTT_NONE;
                }
                DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                DAT_ResourceManager::instance.strFile[0] = '\0';
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                    // "Select help file to include"
                    DAT_ResourceManager::ptr)(s_Select_help_file_to_include_005a585c);
                if (BVar7) {
                    if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
                        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                            DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::helpToken_insertSpaceForHelpTextToken,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_INCLUDE);
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex]
                            = L'\x0e';
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]
                            = (WCHAR)iVar6;
                        DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                            = L'\x0e';
                        iVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength,
                            DAT_TextEditorState::ptr)(OpenSHC::Text::Enums::HTT_INCLUDE);
                        DAT_TextEditorState::instance.activeHelpHotspotIndex += iVar6;
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText,
                            DAT_TextEditorState::ptr)();
                        return;
                    }
                }
                break;
            case 20:
                DAT_TextEditorState::instance.useWideHelpLayout ^= 1;
                if (DAT_TextEditorState::instance.useWideHelpLayout == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setHelpWindowBounds,
                        DAT_TextEditorState::ptr)(DAT_TextEditorState::instance.dialogX + 10,
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogY + 10)),
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogWidth - 40)),
                        (undefined4)((int)(DAT_TextEditorState::instance.dialogHeight - 45)));
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                DAT_TextEditorState::instance.dialogContentX = DAT_TextEditorState::instance.dialogX + 10;
                DAT_TextEditorState::instance.dialogContentY = DAT_TextEditorState::instance.dialogY + 10;
                DAT_TextEditorState::instance.dialogContentWidth = 664;
                DAT_TextEditorState::instance.dialogContentHeight = 291;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                return;
            case 32:
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 4:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                        // "Select help file to link to"
                        DAT_ResourceManager::ptr)(s_Select_help_file_to_link_to_005a5878);
                    if (BVar7) {
                        if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
                            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                                DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1] = (WCHAR)iVar6;
                        }
                    }
                    break;
                case 14:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::showOpenHelpFileDialog,
                        // "Select help file to include"
                        DAT_ResourceManager::ptr)(s_Select_help_file_to_include_005a585c);
                    if (BVar7) {
                        if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
                            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                                DAT_TextEditorState::ptr)(DAT_ResourceManager::instance.strFileTitle);
                            DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1] = (WCHAR)iVar6;
                        }
                    }
                case 1:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showOpenGfxFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7) {
                        if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                case 11:
                    DAT_ResourceManager::instance.strFileTitle[0] = '\0';
                    DAT_ResourceManager::instance.strFile[0] = '\0';
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::showOpenSoundFileDialog, DAT_ResourceManager::ptr)();
                    if (BVar7) {
                        if (strlen(DAT_ResourceManager::instance.strFileTitle) != 0) {
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
                }
                break;
            case 33:
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\0';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 2:
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getPrevHelpSectionID,
                        DAT_TextEditorState::ptr)((uint)(ushort)pWVar2[iVar6 + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 3:
                case 10:
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getPrevHelpColorEntryIndex,
                        DAT_TextEditorState::ptr)((uint)(ushort)pWVar2[iVar6 + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 12:
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    pWVar2[iVar6 + 1] = (WCHAR)((int)((ushort)pWVar2[iVar6 + 1] + 19) % 20);
                }
                break;
            case 0:
            case 16:
            case 17:
            case 18:
            case 19:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
                break;
            case 34:
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x01';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 2:
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getNextHelpSectionID,
                        DAT_TextEditorState::ptr)((uint)(ushort)pWVar2[iVar6 + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 3:
                case 10:
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getNextHelpColorEntryIndex,
                        DAT_TextEditorState::ptr)((uint)(ushort)pWVar2[iVar6 + 1]);
                    pWVar2[iVar6 + 1] = (WCHAR)iVar9;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                    return;
                case 12:
                    pWVar2 = DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory;
                    iVar6 = DAT_TextEditorState::instance.activeHelpHotspotIndex;
                    pWVar2[iVar6 + 1] = (WCHAR)((int)((ushort)pWVar2[iVar6 + 1] + 1) % 20);
                }
                break;
            case 35:
                if (DAT_TextEditorState::instance.field_0x23970 == 1) {
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x02';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                break;
            case 36:
                if (DAT_TextEditorState::instance.field_0x23970 == 1) {
                    DAT_TextEditorState::instance
                        .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                        = L'\x03';
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextEditorState_Func::initializeAndLayoutHelpText, DAT_TextEditorState::ptr)();
                }
                break;
            default:
                break;
            }
        }

    }
}
}
