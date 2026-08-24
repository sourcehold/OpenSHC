#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"



#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_CopyOfScenarioGold.hpp"

namespace OpenSHC {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004BEC10
void UI::MenuView_EditScenario_Prepare()

{
DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("frontend_builder2.tgx");
MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::updateEventYearsAndCommitBuildingAvailability, DAT_MapPropertiesState::ptr)();
DAT_CopyOfScenarioGold::instance = (int)DAT_GameState::instance.mapAndTime.scenarioGold;
return;
}


}