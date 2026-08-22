#include "../ResourceManager.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C480
    void ResourceManager::setHelpFileFilter()
    {
        this->openFileNameA.lpstrFilter = DAT_TextInputDefinedData::instance.field23_0x71c;
        this->openFileNameA.nFilterIndex = 1;
        this->openFileNameA.lpstrDefExt = DAT_TextInputDefinedData::instance.field23_0x71c;
        this->openFileNameA.lpstrInitialDir = s_help__005a5a24;
    }

} // namespace IO
} // namespace OpenSHC
