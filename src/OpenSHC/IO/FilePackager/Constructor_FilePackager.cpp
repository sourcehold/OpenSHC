#include "../FilePackager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D070
    FilePackager* FilePackager::Constructor_FilePackager()
    {
        this->packagerMapVersionNumUnk = 172;
        this->tempMem = NULL;
        this->CRASHES_saveUncompressedUnk = FALSE;
        this->loadAndSaveBarFunc = NULL;
        return this;
    }

}
}
