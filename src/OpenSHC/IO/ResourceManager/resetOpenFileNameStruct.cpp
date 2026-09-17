#include "../ResourceManager.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471DF0
    void ResourceManager::resetOpenFileNameStruct()
    {
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->openFileNameA), '\0', &this->openFileNameA);
        this->openFileNameA.lStructSize = sizeof(this->openFileNameA);
        this->openFileNameA.hwndOwner = DAT_WindowAndDirectDraw::instance.windowHandle;
        this->openFileNameA.lpstrFile = this->strFile;
        this->openFileNameA.nMaxFile = 1000;
        this->openFileNameA.lpstrFileTitle = this->strFileTitle;
        this->openFileNameA.nMaxFileTitle = 1000;
        this->openFileNameA.Flags = OFN_NOCHANGEDIR;
    }

} // namespace IO
} // namespace OpenSHC
