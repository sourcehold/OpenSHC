#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Text {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045F580
undefined4 TextEditorState::loadAndParseHelpFile(FILE *param_1)

{
FILE *_File;

_File = (FILE *)MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::readCrusaderHelpHlp, this)((CHAR *)param_1);
if (_File != (FILE *)0x0) {
MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
if (this->helpSectionParseSucceeded != FALSE) {
return(undefined4)( 1);
}
}
return(undefined4)( 0);
}


}
}