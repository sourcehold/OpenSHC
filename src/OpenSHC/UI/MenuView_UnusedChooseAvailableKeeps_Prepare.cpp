#include "OpenSHC/UI.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0042FAA0
void UI::MenuView_UnusedChooseAvailableKeeps_Prepare()

{
DAT_GameCore::instance.mapU2MiddleBytes[0] = 1;
DAT_GameCore::instance.mapU2MiddleBytes[1] = 1;
DAT_GameCore::instance.mapU2MiddleBytes[2] = 1;
DAT_GameCore::instance.mapU2MiddleBytes[3] = 1;
DAT_GameCore::instance.mapU2MiddleBytes[4] = 1;
return;
}


}