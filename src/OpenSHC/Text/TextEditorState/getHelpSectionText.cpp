#include "OpenSHC/Text/TextEditorState.func.hpp"



#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {




/* 
  Walks the UserHelpDefinedData help section list to find the entry with ID matching param_1.
   Returns a pointer to its text_0x0 field if found, or null if param_1 is not present in the list.
   
   renamed by: Claude Sonnet 4.6
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045D9E0
char * TextEditorState::getHelpSectionText(int param_1)

{
int iVar1;
int iVar2;

iVar2 = 0;
iVar1 = DAT_UserHelpDefinedData::instance.field5_0x7a124[0].unknown_0x4;
while( true ) {
if (iVar1 == -1) {
return (char *)0x0;
}
if (iVar1 == param_1) break;
iVar1 = DAT_UserHelpDefinedData::instance.field5_0x7a124[iVar2 + 1].unknown_0x4;
iVar2 = iVar2 + 1;
}
return DAT_UserHelpDefinedData::instance.field5_0x7a124[iVar2].text_0x0;
}


}
}