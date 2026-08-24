#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuModal.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"



#include "OpenSHC/Globals/DAT_ModalMenuArrayPointerToStackTop.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::UI::MenuModal;
using OpenSHC::UI::Enums::MenuModalType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004A9EB0
MenuModal * MenuModalComposition::findModalMenu(MenuModalType menuModalID)

{
MenuModal *pMVar1;

pMVar1 = DAT_ModalMenuArrayPointerToStackTop::instance;
while( true ) {
if (pMVar1 == (MenuModal *)0x0) {
return (MenuModal *)0x0;
}
if (pMVar1->menuModalID == menuModalID) break;
pMVar1 = pMVar1->pointerToNextModalMenu;
}
return pMVar1;
}


}
}