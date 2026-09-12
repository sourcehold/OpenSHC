#include "../TextEditorState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

    // TODO: Replace L strings with references from a file

    // FUNCTION: STRONGHOLDCRUSADER 0x0045DB40
    void TextEditorState::saveHelpFileToResource()
    {
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_HELP, DAT_UserHelpDefinedData::instance.HelpSections[this->currentHelpSectionID]);
        char const* const _Filename = MACRO_CALL_MEMBER(
            IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
        FILE* _File = MACRO_CALL(OS_Func::_fopen)(_Filename, s_wb_005a5510);
        if (!_File) {
            return;
        }
        wchar_t const utf16bom = L'\uFEFF';
        MACRO_CALL(OS_Func::_fwrite)((void*)&utf16bom, sizeof(wchar_t), 1, _File);

        MACRO_CALL(OS_Func::_fwprintf)(_File, L"<HEADER>\n");
        for (int i = 0; i < this->graphicFileCount; ++i) {
            MACRO_CALL(OS_Func::_fwprintf)(_File, L"<LOADPIC=\"%S\">\n", this->graphicFileNames[i]);
        }
        MACRO_CALL(OS_Func::_fwprintf)(_File, L"<\\HEADER>\n");
        MACRO_CALL(OS_Func::_fwprintf)(_File, L"<BODY>\n");

        for (int i = 0; this->DAT_PointerToTemporaryTextMemory[i];) {
            HelpTextToken const switchValue = (HelpTextToken)this->DAT_PointerToTemporaryTextMemory[i];
            i += 1;
            switch (switchValue) {
            case HTT_PIC:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<PIC %d,", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 1;
                switch ((HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[i]) {
                case HTT_PIC_LEFT:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, L"LEFT>");
                    i += 2;
                    break;
                case HTT_PIC_RIGHT:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, L"RIGHT>");
                    i += 2;
                    break;
                case HTT_PIC_CENTRE:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, L"CENTRE>");
                    i += 2;
                    break;
                case HTT_PIC_HERE:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, L"HERE>");
                default:
                    i += 2;
                    break;
                }
                break;
            case HTT_FONT:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<FONT %d>", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case HTT_COLOUR:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<COLOUR=%d>", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case HTT_LINKCOLOUR:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<LINKCOLOUR=%d>", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case HTT_LINK:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<LINK \"%S\">",
                    DAT_UserHelpDefinedData::instance.HelpSections[this->DAT_PointerToTemporaryTextMemory[i]]);
                i += 2;
                break;
            case HTT_INCLUDE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<INCLUDE \"%S\">",
                    DAT_UserHelpDefinedData::instance.HelpSections[this->DAT_PointerToTemporaryTextMemory[i]]);
                i += 2;
                break;
            case HTT_ENDLINK:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<\\LINK>");
                break;
            case HTT_NEWPARAGRAPH:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"\n<NEWPARAGRAPH>\n");
                break;
            case HTT_CENTRE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<CENTRE>");
                break;
            case HTT_ENDCENTRE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<\\CENTRE>");
                break;
            case HTT_SOUND:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<SOUND %d>", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case HTT_STRING:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"<STRING %d>", this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            default:
                MACRO_CALL(OS_Func::_fwprintf)(_File, L"%c", (wchar_t)switchValue);
                break;
            }
        }

        MACRO_CALL(OS_Func::_fwprintf)(_File, L"\n<\\BODY>\n");
        MACRO_CALL(OS_Func::_fclose)(_File);
    }

#undef MACRO_TEXT_ACCESS

}
}
