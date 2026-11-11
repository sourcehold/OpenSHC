#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00c9a490.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"
#include "OpenSHC/Globals/TGX_RepeatRunHandlers.hpp"
#include "OpenSHC/Globals/TGX_StreamRunHandlers.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044CC30
        void TextureRenderCore::clearSomeMemory()
        {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(TGX_RepeatRunHandlers::instance), '\0', TGX_RepeatRunHandlers::instance);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(TGX_StreamRunHandlers::instance), '\0', TGX_StreamRunHandlers::instance);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(PTR_ARRAY_00c9a490::instance), '\0', PTR_ARRAY_00c9a490::instance);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(PTR_ARRAY_Unknown_UnitGMHeights::instance), '\0', PTR_ARRAY_Unknown_UnitGMHeights::instance);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_BlendFilterArrays::instance), '\0', &DAT_BlendFilterArrays::instance);
        }

    }
}
}
