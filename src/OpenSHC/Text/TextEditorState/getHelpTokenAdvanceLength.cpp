#include "OpenSHC/Text/TextEditorState.func.hpp"





namespace OpenSHC {
namespace Text {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045F080
undefined4 TextEditorState::getHelpTokenAdvanceLength(undefined4 param_1)

{
switch(param_1) {
case 1:
return(undefined4)( 4);
case 2:
case 3:
case 4:
case 10:
case 0xb:
case 0xc:
case 0xe:
return(undefined4)( 3);
default:
return(undefined4)( 1);
}
}


}
}