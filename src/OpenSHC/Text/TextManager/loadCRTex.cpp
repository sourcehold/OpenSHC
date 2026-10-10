#include "../TextManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/CodePage.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

#include <fcntl.h>

namespace OpenSHC {
namespace Text {

    using DE::SHCDE::eTextSections;
    using Rendering::Enums::RenderTarget;
    using Text::GameLanguage;
    using WindowsHelper::Enums::BOOLEnum;
    using WindowsHelper::Enums::CodePage;

    // FUNCTION: STRONGHOLDCRUSADER 0x00473870
    void TextManager::loadCRTex()
    {
        WCHAR* _lpWideCharStr;
        int _languageCompareResult;
        char* _langStr;
        this->codePage = WindowsHelper::Enums::CP_WINDOWS_1252;
        this->field5_0x14 = 1;
        this->field6_0x18 = 0;
        this->textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
        this->field27_0x1348 = 0;
        int _fileDescriptor = MACRO_CALL(OS_Func::_ucrt_open)("cr.tex", _O_BINARY, 0);
        if (_fileDescriptor != -1) {
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, (void*)((int)(this->textOffsets)), (size_t)((int)(1040)));
            _lpWideCharStr = (WCHAR*)MACRO_CALL(OS_Func::_malloc)(702000);
            MACRO_CALL(OS_Func::_ucrt_read)(_fileDescriptor, (void*)((int)(_lpWideCharStr)), (size_t)((int)(702000)));
            MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                DAT_WideCharMultiByteState::ptr)(this->textStart, _lpWideCharStr, (int)(351000));
            this->alternativeCodePageUsedUnk = FALSE;
            this->gameLanguage = Text::GL_ENGLISH;
            /*
              language
             */
            _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                DE::SHCDE::TEXT_LANGUAGE, 0);
            _languageCompareResult = MACRO_CALL(OS_Func::__stricmp)("polish", (char const*)((int)(_langStr)));
            if (!_languageCompareResult) {
                this->codePage = WindowsHelper::Enums::CP_WINDOWS_1250;
                this->alternativeCodePageUsedUnk = TRUE;
                MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(this->textStart, _lpWideCharStr, (int)(351000));
                this->gameLanguage = Text::GL_POLISH;
            } else {
                _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                    DE::SHCDE::TEXT_LANGUAGE, 0);
                _languageCompareResult = MACRO_CALL(OS_Func::__stricmp)("english", (char const*)((int)(_langStr)));
                if (!_languageCompareResult) {
                    this->gameLanguage = Text::GL_ENGLISH;
                } else {
                    _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                        DE::SHCDE::TEXT_LANGUAGE, 0);
                    _languageCompareResult = MACRO_CALL(OS_Func::__stricmp)("american", (char const*)((int)(_langStr)));
                    if (!_languageCompareResult) {
                        this->gameLanguage = Text::GL_AMERICAN;
                    } else {
                        _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                            DE::SHCDE::TEXT_LANGUAGE, 0);
                        _languageCompareResult
                            = MACRO_CALL(OS_Func::__stricmp)("german", (char const*)((int)(_langStr)));
                        if (!_languageCompareResult) {
                            this->gameLanguage = Text::GL_GERMAN;
                        } else {
                            _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                                DE::SHCDE::TEXT_LANGUAGE, 0);
                            _languageCompareResult
                                = MACRO_CALL(OS_Func::__stricmp)("french", (char const*)((int)(_langStr)));
                            if (!_languageCompareResult) {
                                this->gameLanguage = Text::GL_FRENCH;
                            } else {
                                _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    this)(DE::SHCDE::TEXT_LANGUAGE, 0);
                                _languageCompareResult
                                    = MACRO_CALL(OS_Func::__stricmp)("italian", (char const*)((int)(_langStr)));
                                if (!_languageCompareResult) {
                                    this->gameLanguage = Text::GL_ITALIAN;
                                } else {
                                    _langStr = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        this)(DE::SHCDE::TEXT_LANGUAGE, 0);
                                    _languageCompareResult
                                        = MACRO_CALL(OS_Func::__stricmp)("SPANISH", (char const*)((int)(_langStr)));
                                    if (!_languageCompareResult) {
                                        this->gameLanguage = Text::GL_SPANISH;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            MACRO_CALL(OS_Func::_ucrt_close)(_fileDescriptor);
            this->field27_0x1348 = 1;
            this->field9_0x24 = 0;
            this->field10_0x28 = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                20, '\0', (void*)((int)(this->field26_0x1334)));
            MACRO_CALL_MEMBER(Text::TextManager_Func::resetTextClipRange, this)();
            this->field13_0x34 = 0;
        }
        return;
    }

}
}
