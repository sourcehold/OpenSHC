#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"





namespace OpenSHC {
namespace Text {

using OpenSHC::DE::SHCDE::eTextSections;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004246B0
int TextManager::computeTextWidthForTextGroup(eTextSections textOffsetIndex,int textNumInGroup,int fontSize)

{
char *text;
int _width;

text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup);
_width = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, this)(text, fontSize);
return _width;
}


}
}