#include "../TextEditorState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/string-literals.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F470
    FILE* TextEditorState::readCrusaderHelpHlp(LPCSTR searchedPart)
    {
        this->helpSectionParseSucceeded = FALSE;

        WCHAR searchedPartWide[200];
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharacter, DAT_WideCharMultiByteState::ptr)(
            searchedPartWide, searchedPart);
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_HELP, s_crusader_help_hlp_005a5620);

        char const* const _Filename = MACRO_CALL_MEMBER(
            IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        FILE* _File = MACRO_CALL(OS_Func::_fopen)(_Filename, s_rb_005a4e18);
        if (_File) {
            MACRO_CALL(OS_Func::_fseek)(_File, 2, FILE_BEGIN); // Skip BOM?

            int wideChar;
            while (true) {
                wideChar = MACRO_CALL(OS_Func::_fgetwc)(_File);
                if (wideChar != L'<') {
                    if (wideChar == WEOF) {
                        return _File;
                    }
                    continue;
                }
                wchar_t* hlpPart = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(_File);
                if (!hlpPart || MACRO_CALL(OS_Func::__wcsicmp)(u_section_005a5610, hlpPart)) {
                    continue;
                }
                wchar_t* sectionHlpPart = MACRO_CALL_MEMBER(TextEditorState_Func::parseHLPPart, this)(_File);
                if (!sectionHlpPart || MACRO_CALL(OS_Func::__wcsicmp)(searchedPartWide, sectionHlpPart)) {
                    continue;
                }
                break;
            };

            do {
                wideChar = MACRO_CALL(OS_Func::_fgetwc)(_File);
                if (wideChar == L'>') {
                    this->helpSectionParseSucceeded = TRUE;
                    break;
                }
            } while (wideChar != WEOF);
        }

        return _File;
    }

}
}
