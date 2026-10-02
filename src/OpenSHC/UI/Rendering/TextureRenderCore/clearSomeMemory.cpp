#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00c9a490.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00c9a510.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00d7d250.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0044CC30
        void TextureRenderCore::clearSomeMemory()
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(PTR_ARRAY_00c9a510::instance)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(PTR_ARRAY_00d7d250::instance)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(PTR_ARRAY_00c9a490::instance)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x80, '\0', (void*)((int)(PTR_ARRAY_Unknown_UnitGMHeights::instance)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                16896, '\0', (void*)((int)(DAT_BlendFilterArrays::instance)));
        }

    }
}
}
