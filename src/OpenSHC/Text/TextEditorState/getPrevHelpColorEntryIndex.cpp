#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/HelpTextRelatedColorStruct.hpp"



#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace Text {

using OpenSHC::Text::HelpTextRelatedColorStruct;


/* 
  Returns param_1 - 1 if non-negative. If param_1 - 1 goes below 0, walks the field6_0x7a16c array
   forward to find the last entry with a non-null name and returns that index. Simple circular
   previous-index for the help colour/style entry array.
   
   renamed by: Claude Sonnet 4.6
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045DA40
int TextEditorState::getPrevHelpColorEntryIndex(int param_1)

{
int iVar1;
HelpTextRelatedColorStruct *pHVar2;

iVar1 = param_1 + -1;
if (iVar1 < 0) {
iVar1 = 0;
if (DAT_UserHelpDefinedData::instance.field6_0x7a16c[0].name_0x0 != (char *)0x0) {
pHVar2 = DAT_UserHelpDefinedData::instance.field6_0x7a16c;
do {
pHVar2 = pHVar2 + 1;
iVar1 = iVar1 + 1;
} while (pHVar2->name_0x0 != (char *)0x0);
}
iVar1 = iVar1 + -1;
}
return iVar1;
}


}
}