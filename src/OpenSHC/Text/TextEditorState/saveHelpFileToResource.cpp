#include "../TextEditorState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/Enums/HelpTextPicturePositionToken.hpp"
#include "OpenSHC/string-literals.hpp"
#include "OpenSHC/wstring-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

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

        MACRO_CALL(OS_Func::_fwprintf)(_File, u__HEADER__005a54fc);
        for (int i = 0; i < this->graphicFileCount; ++i) {
            MACRO_CALL(OS_Func::_fwprintf)(_File, u__LOADPIC_S__005a54dc, this->graphicFileNames[i]);
        }
        MACRO_CALL(OS_Func::_fwprintf)(_File, u__HEADER__005a54c4);
        MACRO_CALL(OS_Func::_fwprintf)(_File, u__BODY__005a54b4);

        for (int i = 0; this->DAT_PointerToTemporaryTextMemory[i];) {
            HelpTextToken const switchValue = (HelpTextToken)this->DAT_PointerToTemporaryTextMemory[i];
            i += 1;
            switch (switchValue) {
            case Enums::HTT_PIC:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__PIC__d__005a54a0, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 1;
                switch ((Enums::HelpTextPicturePositionToken)this->DAT_PointerToTemporaryTextMemory[i]) {
                case Enums::HTPPT_LEFT:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, u_LEFT__005a5494);
                    i += 2;
                    break;
                case Enums::HTPPT_RIGHT:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, u_RIGHT__005a5484);
                    i += 2;
                    break;
                case Enums::HTPPT_CENTRE:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, u_CENTRE__005a5474);
                    i += 2;
                    break;
                case Enums::HTPPT_HERE:
                    MACRO_CALL(OS_Func::_fwprintf)(_File, u_HERE__005a5468);
                default:
                    i += 2;
                    break;
                }
                break;
            case Enums::HTT_FONT:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__FONT__d__005a5454, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case Enums::HTT_COLOUR:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__COLOUR_d__005a543c, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case Enums::HTT_LINKCOLOUR:
                MACRO_CALL(OS_Func::_fwprintf)(
                    _File, u__LINKCOLOUR_d__005a541c, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case Enums::HTT_LINK:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__LINK__S__005a5404,
                    DAT_UserHelpDefinedData::instance.HelpSections[this->DAT_PointerToTemporaryTextMemory[i]]);
                i += 2;
                break;
            case Enums::HTT_INCLUDE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__INCLUDE__S__005a53e4,
                    DAT_UserHelpDefinedData::instance.HelpSections[this->DAT_PointerToTemporaryTextMemory[i]]);
                i += 2;
                break;
            case Enums::HTT_ENDLINK:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__LINK__005a53d4);
                break;
            case Enums::HTT_NEWPARAGRAPH:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__NEWPARAGRAPH__005a53b0);
                break;
            case Enums::HTT_CENTRE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__CENTRE__005a539c);
                break;
            case Enums::HTT_ENDCENTRE:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__CENTRE__005a5388);
                break;
            case Enums::HTT_SOUND:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__SOUND__d__005a5370, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            case Enums::HTT_STRING:
                MACRO_CALL(OS_Func::_fwprintf)(
                    _File, u__STRING__d__005a5358, this->DAT_PointerToTemporaryTextMemory[i]);
                i += 2;
                break;
            default:
                MACRO_CALL(OS_Func::_fwprintf)(_File, u__c_005a5350, (wchar_t)switchValue);
                break;
            }
        }

        MACRO_CALL(OS_Func::_fwprintf)(_File, u__BODY__005a533c);
        MACRO_CALL(OS_Func::_fclose)(_File);
    }

#undef MACRO_TEXT_ACCESS

}
}
