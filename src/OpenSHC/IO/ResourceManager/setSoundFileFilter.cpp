#include "../ResourceManager.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C4B0
    void ResourceManager::setSoundFileFilter()

    {
        this->openFileNameA.lpstrFilter = DAT_TextInputDefinedData::instance.field27_0x728;
        this->openFileNameA.nFilterIndex = 1;
        this->openFileNameA.lpstrDefExt = DAT_TextInputDefinedData::instance.field27_0x728;
        this->openFileNameA.lpstrInitialDir = s_fx__005a5a2c;
    }

} // namespace IO
} // namespace OpenSHC
