#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AB440
void UI::MenuModalRenderFunction_DisplayAiLordMessage(int x, int y, int width, int height)

{
    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playAiLordMessage, DAT_VideoBikQueue::ptr)(x, y);
}

}
