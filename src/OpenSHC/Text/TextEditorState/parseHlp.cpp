#include "../TextEditorState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextPicturePositionToken.hpp"
#include "OpenSHC/wstring-literals.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F5B0
    void TextEditorState::parseHlp()
    {
        FILE* filePointer[4];
        int graphicIndexes[4][100];

        int const currentHelpSectionID = this->currentHelpSectionID;
        int textMemIndex = 0;

        BOOL headerActive = FALSE;
        BOOL bodyActive = FALSE;
        int _filePointerIndex = 0;

        int loadedGraphics[4] = { 0, 0, 0, 0 };
        this->customHelpTextLength = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            40000, NULL, this->DAT_PointerToTemporaryTextMemory);
        filePointer[0] = MACRO_CALL_MEMBER(TextEditorState_Func::readCrusaderHelpHlp, this)(
            DAT_UserHelpDefinedData::instance.HelpSections[currentHelpSectionID]);
        if (!filePointer[0]) {
            return;
        }

        while (_filePointerIndex >= 0) {
            BOOL closeFile = FALSE;
            while (!closeFile) {
                int _wchar = MACRO_CALL(OS_Func::_fgetwc)(filePointer[_filePointerIndex]);
                switch (_wchar) {
                case '\n':
                case '\r':
                    continue;

                case '<': {
                    wchar_t* hlpTag
                        = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(filePointer[_filePointerIndex]);
                    if (hlpTag) {
                        if (!MACRO_CALL(OS_Func::__wcsicmp)(u_header_005a5774, hlpTag)) {
                            headerActive = TRUE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u__header_005a5764, hlpTag)) {
                            headerActive = FALSE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_body_005a5758, hlpTag)) {
                            bodyActive = TRUE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u__body_005a574c, hlpTag)) {
                            bodyActive = FALSE;
                            continue;

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_loadpic_005a573c, hlpTag)) {
                            if (headerActive) {
                                wchar_t* resourceName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (resourceName) {
                                    char resourceNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(resourceNameChars, resourceName);

                                    bool validPic = true;
                                    if (!MACRO_CALL_MEMBER(
                                            UI::Rendering::TextureRenderCore_Func::checkGfxResourceExists,
                                            DAT_TextureRenderCoreObject::ptr)(resourceNameChars)) {
                                        validPic = false;
                                    } else if (!MACRO_CALL(OS_Func::__stricmp)(
                                                   resourceNameChars, s_st99_dog_cage_tgx_005a5728)) {
                                        validPic = false;
                                    }
                                    if (!validPic) {
                                        graphicIndexes[_filePointerIndex][loadedGraphics[_filePointerIndex]++] = -1;
                                    } else {
                                        graphicIndexes[_filePointerIndex][loadedGraphics[_filePointerIndex]++]
                                            = MACRO_CALL_MEMBER(TextEditorState_Func::findOrAddHelpGraphicName, this)(
                                                resourceNameChars);
                                    }
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_pic_005a5720, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* picId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (picId) {
                                    if (MACRO_CALL(OS_Func::__wtol)(picId) < loadedGraphics[_filePointerIndex]) {
                                        if (graphicIndexes[_filePointerIndex][MACRO_CALL(OS_Func::__wtol)(picId)]
                                            != -1) {
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_PIC;
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                = graphicIndexes[_filePointerIndex][MACRO_CALL(OS_Func::__wtol)(picId)];
                                            wchar_t* picPosition = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart,
                                                this)(filePointer[_filePointerIndex]);
                                            if (!picPosition) {
                                                closeFile = TRUE;
                                            } else {
                                                if (!MACRO_CALL(OS_Func::__wcsicmp)(u_left_005a5714, picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = Enums::HTPPT_LEFT;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_right_005a5708, picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = Enums::HTPPT_RIGHT;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_centre_005a56f8, picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = Enums::HTPPT_CENTRE;
                                                } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_here_005a56ec, picPosition)) {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = Enums::HTPPT_HERE;
                                                }
                                            }
                                            this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_PIC;
                                            continue;
                                        }
                                    }
                                    if (!MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                            filePointer[_filePointerIndex])) {
                                        closeFile = TRUE;
                                    }
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_font_005a56e0, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* fontId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (fontId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_FONT;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(fontId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_FONT;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_colour_005a56d0, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* colorId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (colorId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_COLOUR;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(colorId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_COLOUR;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_linkcolour_005a56b8, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* linkColorId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (linkColorId) {
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_LINKCOLOUR;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                        = (short)MACRO_CALL(OS_Func::__wtol)(linkColorId);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_LINKCOLOUR;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_link_005a56ac, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* linkName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (linkName) {
                                    char linkNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(linkNameChars, linkName);
                                    int const helpSectionIndex = MACRO_CALL_MEMBER(
                                        TextEditorState_Func::findOrAddHelpSectionName, this)(linkNameChars);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_LINK;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = helpSectionIndex;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_LINK;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u__link_005a56a0, hlpTag)) {
                            if (bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_ENDLINK;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_newparagraph_005a5684, hlpTag)) {
                            if (bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_NEWPARAGRAPH;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_centre_005a56f8, hlpTag)) {
                            if (bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_CENTRE;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u__centre_005a5674, hlpTag)) {
                            if (bodyActive) {
                                this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_ENDCENTRE;
                                continue;
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_sound_005a5668, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* soundName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (soundName) {
                                    char soundNameChars[1000];
                                    MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                        DAT_WideCharMultiByteState::ptr)(soundNameChars, soundName);
                                    int const soundIndex = MACRO_CALL_MEMBER(
                                        TextEditorState_Func::findOrAddSoundName, this)(soundNameChars);
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_SOUND;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = soundIndex;
                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_SOUND;
                                    continue;
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_include_005a5658, hlpTag)) {
                            if (bodyActive) {
                                if (DAT_TextEditorState::instance.useAlternateHelpTab) {
                                    wchar_t* includeName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                        filePointer[_filePointerIndex]);
                                    if (includeName) {
                                        char includeNameChars[1000];
                                        MACRO_CALL_MEMBER(
                                            Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                            DAT_WideCharMultiByteState::ptr)(includeNameChars, includeName);
                                        int const helpSectionIndex = MACRO_CALL_MEMBER(
                                            TextEditorState_Func::findOrAddHelpSectionName, this)(includeNameChars);
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_INCLUDE;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = helpSectionIndex;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_INCLUDE;
                                        continue;
                                    }
                                } else {
                                    wchar_t* includeName = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                        filePointer[_filePointerIndex]);
                                    if (includeName) {
                                        char includeNameChars[1000];
                                        MACRO_CALL_MEMBER(
                                            Util::WideCharMultiByteState_Func::wideCharToMultiByteComplete,
                                            DAT_WideCharMultiByteState::ptr)(includeNameChars, includeName);
                                        int sectionId = MACRO_CALL_MEMBER(
                                            TextEditorState_Func::findOrAddHelpSectionName, this)(includeNameChars);
                                        ++_filePointerIndex;
                                        bodyActive = FALSE;
                                        headerActive = FALSE;
                                        loadedGraphics[_filePointerIndex] = 0;
                                        filePointer[_filePointerIndex]
                                            = MACRO_CALL_MEMBER(TextEditorState_Func::readCrusaderHelpHlp, this)(
                                                DAT_UserHelpDefinedData::instance.HelpSections[sectionId]);
                                        continue;
                                    }
                                }
                            }

                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u_string_005a5648, hlpTag)) {
                            if (bodyActive) {
                                wchar_t* stringId = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(
                                    filePointer[_filePointerIndex]);
                                if (stringId) {
                                    if (this->helpDialogVariant) {
                                        long const textIndex = MACRO_CALL(OS_Func::__wtol)(stringId);

                                        if (this->intArray1[textIndex]) {
                                            int i = 0;
                                            // Mismatch: wrong order of ptr access addition
                                            while (this->intArray1[textIndex][i]) {
                                                wchar_t const ch = this->intArray1[textIndex][i++];
                                                if (ch == L'\n') {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                                        = Enums::HTT_NEWPARAGRAPH;
                                                } else if (ch >= L' ') {
                                                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = ch;
                                                }
                                            }
                                        }

                                    } else {
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_STRING;
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++]
                                            = (short)MACRO_CALL(OS_Func::__wtol)(stringId);
                                        this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = Enums::HTT_STRING;
                                    }
                                    continue;
                                }
                            }
                        } else if (!MACRO_CALL(OS_Func::__wcsicmp)(u__section_005a5634, hlpTag)) {
                            closeFile = TRUE;
                            continue;
                        } else {
                            continue;
                        }
                    }

                    closeFile = TRUE;
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
                    closeFile = TRUE;
                    continue;

                default:
                    break;
                }

                if (bodyActive) {
                    this->DAT_PointerToTemporaryTextMemory[textMemIndex++] = _wchar;
                }
            };

            MACRO_CALL(OS_Func::_fclose)(filePointer[_filePointerIndex]);
            bodyActive = TRUE;
            headerActive = FALSE;
            --_filePointerIndex;
        }
        this->customHelpTextLength = textMemIndex;
    }

}
}
