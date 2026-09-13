#include "../TextEditorState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // TODO: fix L-strings

    // TODO: See if stack object can be removed
    struct StackObject {
        BOOL bodyActive;
        int _filePointerIndex;
        BOOL headerActive;
        BOOL closeFile;
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F5B0
    void TextEditorState::parseHlp()
    {
        FILE* filePointer[4];
        int graphicIndexes[4][100];

        int const currentHelpSectionID = this->currentHelpSectionID;
        int textMemIndex = 0;

        StackObject sto;
        sto.headerActive = FALSE;
        sto.bodyActive = FALSE;
        sto._filePointerIndex = 0;

        int loadedGraphics[4];
        loadedGraphics[0] = 0;
        loadedGraphics[1] = 0;
        loadedGraphics[2] = 0;
        loadedGraphics[3] = 0;
        this->customHelpTextLength = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            40000, NULL, this->DAT_PointerToTemporaryTextMemory);
        filePointer[0] = MACRO_CALL_MEMBER(TextEditorState_Func::readCrusaderHelpHlp, this)(
            DAT_UserHelpDefinedData::instance.HelpSections[currentHelpSectionID]);
        if (!filePointer[0]) {
            return;
        }

        while (true) {
            sto.closeFile = FALSE;
            while (!sto.closeFile) {
                int _wchar = MACRO_CALL(OS_Func::_fgetwc)(filePointer[sto._filePointerIndex]);
                switch (_wchar) {
                case '\n':
                case '\r':
                    continue;

                case '<': {
                    wchar_t* hlpTag = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                        filePointer[sto._filePointerIndex]);
                    if (hlpTag) {
                        if (!MACRO_CALL(OS_Func::__wcsicmp)(L"header", hlpTag)) {
                            sto.headerActive = TRUE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"\\header", hlpTag)) {
                            sto.headerActive = FALSE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"body", hlpTag)) {
                            sto.bodyActive = TRUE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"\\body", hlpTag)) {
                            sto.bodyActive = FALSE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"loadpic", hlpTag)) {
                            if (sto.headerActive) {
                                wchar_t* resourceName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (resourceName) {
                                    char resourceNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(resourceNameChars, resourceName);
                                    // TODO: Wrong order of logic blocks
                                    if (!MACRO_CALL_MEMBER(
                                            UI::Rendering::TextureRenderCore_Func::checkGfxResourceExists,
                                            DAT_TextureRenderCoreObject::ptr)(resourceNameChars)
                                        || !MACRO_CALL(OS_Func::__stricmp)(resourceNameChars, "st99_dog_cage.tgx")) {
                                        graphicIndexes[sto._filePointerIndex][loadedGraphics[sto._filePointerIndex]++]
                                            = -1;
                                        continue;
                                    } else {
                                        graphicIndexes[sto._filePointerIndex][loadedGraphics[sto._filePointerIndex]++]
                                            = MACRO_CALL_MEMBER(TextEditorState_Func::findOrAddHelpGraphicName, this)(
                                                resourceNameChars);
                                        continue;
                                    }
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"pic", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* picId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (picId) {
                                    if (MACRO_CALL(OS_Func::__wtol)(picId) < loadedGraphics[sto._filePointerIndex]) {
                                        if (graphicIndexes[sto._filePointerIndex][MACRO_CALL(OS_Func::__wtol)(picId)]
                                            != -1) {
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_PIC;
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                = graphicIndexes[sto._filePointerIndex]
                                                                [MACRO_CALL(OS_Func::__wtol)(picId)];
                                            wchar_t* picPosition = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart,
                                                this)(filePointer[sto._filePointerIndex]);
                                            if (!picPosition) {
                                                sto.closeFile = TRUE;
                                            } else {
                                                if (!MACRO_CALL(OS_Func::__wcsicmp)(L"left", picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = HTT_PIC_LEFT;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"right", picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = HTT_PIC_RIGHT;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"centre", picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = HTT_PIC_CENTRE;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"here", picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = HTT_PIC_HERE;
                                                }
                                            }
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_PIC;
                                            continue;
                                        }
                                    }
                                    if (!MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                            filePointer[sto._filePointerIndex])) {
                                        sto.closeFile = TRUE;
                                    }
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"font", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* fontId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (fontId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_FONT;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(fontId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_FONT;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"colour", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* colorId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (colorId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_COLOUR;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(colorId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_COLOUR;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"linkcolour", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* linkColorId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (linkColorId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_LINKCOLOUR;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(linkColorId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_LINKCOLOUR;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"link", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* linkName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (linkName) {
                                    char linkNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(linkNameChars, linkName);
                                    int const helpSectionIndex = MACRO_CALL_MEMBER(
                                        TextEditorState_Func::findOrAddHelpSectionName, this)(linkNameChars);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_LINK;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = helpSectionIndex;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_LINK;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"\\link", hlpTag)) {
                            if (sto.bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_ENDLINK;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"newparagraph", hlpTag)) {
                            if (sto.bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_NEWPARAGRAPH;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"centre", hlpTag)) {
                            if (sto.bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_CENTRE;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"\\centre", hlpTag)) {
                            if (sto.bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_ENDCENTRE;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"sound", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* soundName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (soundName) {
                                    char soundNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(soundNameChars, soundName);
                                    int const soundIndex = MACRO_CALL_MEMBER(
                                        TextEditorState_Func::findOrAddSoundName, this)(soundNameChars);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_SOUND;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = soundIndex;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_SOUND;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"include", hlpTag)) {
                            if (sto.bodyActive) {
                                if (DAT_TextEditorState::instance.useAlternateHelpTab) {
                                    wchar_t* includeName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                        filePointer[sto._filePointerIndex]);
                                    if (includeName) {
                                        char includeNameChars[1000];
                                        MACRO_CALL_MEMBER(
                                            Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                            DAT_WideCharMultiByteState::ptr)(includeNameChars, includeName);
                                        int const helpSectionIndex = MACRO_CALL_MEMBER(
                                            TextEditorState_Func::findOrAddHelpSectionName, this)(includeNameChars);
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_INCLUDE;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = helpSectionIndex;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_INCLUDE;
                                        continue;
                                    }
                                } else {
                                    wchar_t* includeName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                        filePointer[sto._filePointerIndex]);
                                    if (includeName) {
                                        char includeNameChars[1000];
                                        MACRO_CALL_MEMBER(
                                            Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                            DAT_WideCharMultiByteState::ptr)(includeNameChars, includeName);
                                        int sectionId = MACRO_CALL_MEMBER(
                                            TextEditorState_Func::findOrAddHelpSectionName, this)(includeNameChars);
                                        ++sto._filePointerIndex;
                                        sto.bodyActive = FALSE;
                                        sto.headerActive = FALSE;
                                        loadedGraphics[sto._filePointerIndex] = 0;
                                        filePointer[sto._filePointerIndex]
                                            = MACRO_CALL_MEMBER(TextEditorState_Func::readCrusaderHelpHlp, this)(
                                                DAT_UserHelpDefinedData::instance.HelpSections[sectionId]);
                                        continue;
                                    }
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"string", hlpTag)) {
                            if (sto.bodyActive) {
                                wchar_t* stringId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[sto._filePointerIndex]);
                                if (stringId) {
                                    if (this->helpDialogVariant) {
                                        long const textIndex = MACRO_CALL(OS_Func::__wtol)(stringId);
                                        // TODO: wrong order of ptr access addition
                                        if (this->intArray1[textIndex]) {
                                            int i = 0;
                                            while (this->intArray1[textIndex][i]) {
                                                wchar_t const ch = this->intArray1[textIndex][i++];
                                                if (ch == L'\n') {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = HTT_NEWPARAGRAPH;
                                                } else if (ch >= L' ') {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = ch;
                                                }
                                            }
                                        }

                                    } else {
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_STRING;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                            = (short)MACRO_CALL(OS_Func::__wtol)(stringId);
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = HTT_STRING;
                                    }
                                    continue;
                                }
                            }
                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(L"\\section", hlpTag)) {
                            sto.closeFile = TRUE;
                            continue;
                        } else {
                            continue;
                        }
                    }

                    sto.closeFile = TRUE;
                    continue;
                }

                case L'\u2019': // ’
                    _wchar = L'`';
                    break;

                case L'\u201C': // “
                case L'\u201D': // ”
                    _wchar = L'"';
                    break;

                case WEOF:
                    sto.closeFile = TRUE;
                    continue;

                default:
                    break;
                }

                if (sto.bodyActive) {
                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = _wchar;
                }
            };

            MACRO_CALL(OS_Func::_fclose)(filePointer[sto._filePointerIndex]);
            sto.bodyActive = TRUE;
            sto.headerActive = FALSE;
            --sto._filePointerIndex;
            if (sto._filePointerIndex < 0) {
                this->customHelpTextLength = textMemIndex;
                return;
            }
        }
    }

}
}
