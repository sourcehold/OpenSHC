#include "../TextManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/WindowsHelper/Enums/CodePage.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473870
    void TextManager::loadCRTex()
    {
        this->codePage = WindowsHelper::Enums::CP_WINDOWS_1252;
        this->field_0x14 = 1;
        this->helpTextLinkActive = FALSE;
        this->textSurfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
        this->field_0x1348 = 0;
        int file = MACRO_CALL(OS_Func::_ucrt_open)("cr.tex", _O_BINARY, 0);
        if (file == -1) {
            return;
        }
        MACRO_CALL(OS_Func::_ucrt_read)(file, this->textOffsets, sizeof(this->textOffsets));
        LPWSTR wideText = (LPWSTR)MACRO_CALL(OS_Func::_malloc)(702000);
        MACRO_CALL(OS_Func::_ucrt_read)(file, wideText, 702000);
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
            DAT_WideCharMultiByteState::ptr)(this->textStart, wideText, 351000);
        this->alternativeCodePageUsedUnk = FALSE;
        this->gameLanguage = GL_ENGLISH;
        if (MACRO_CALL(OS_Func::__stricmp)("polish",
                MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->codePage = WindowsHelper::Enums::CP_WINDOWS_1250;
            this->alternativeCodePageUsedUnk = TRUE;
            MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                DAT_WideCharMultiByteState::ptr)(this->textStart, wideText, 351000);
            this->gameLanguage = GL_POLISH;
        } else if (MACRO_CALL(OS_Func::__stricmp)("english",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_ENGLISH;
        } else if (MACRO_CALL(OS_Func::__stricmp)("american",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_AMERICAN;
        } else if (MACRO_CALL(OS_Func::__stricmp)("german",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_GERMAN;
        } else if (MACRO_CALL(OS_Func::__stricmp)("french",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_FRENCH;
        } else if (MACRO_CALL(OS_Func::__stricmp)("italian",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_ITALIAN;
        } else if (MACRO_CALL(OS_Func::__stricmp)("SPANISH",
                       MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(
                           DE::SHCDE::TEXT_LANGUAGE, 0))
            == 0) {
            this->gameLanguage = GL_SPANISH;
        }
        MACRO_CALL(OS_Func::_ucrt_close)(file);
        this->field_0x1348 = 1;
        this->field_0x24 = 0;
        this->field_0x28 = 0;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->field_0x1334), 0, this->field_0x1334);
        MACRO_CALL_MEMBER(TextManager_Func::resetTextClipRange, this)();
        this->field_0x34 = 0;
    }

}
}
