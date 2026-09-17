#include "OpenSHC/IO/FilePackager.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D090
    void FilePackager::copyFromOldToNewMapDirectory()
    {
        this->directory.filePayloadSize = this->oldDirectory.fileSizeWithoutDirectory;
        this->directory.sectionCount = this->oldDirectory.sectionCount;
        this->directory.magicNumOfFileType = this->oldDirectory.magicNumOfFileType;
        this->directory.emptyConst0 = this->oldDirectory.emptyConst0;
        this->directory.emptyConst1 = this->oldDirectory.emptyConst1;
        this->directory.emptyConst2 = this->oldDirectory.emptyConst2;
        this->directory.emptyConst3 = this->oldDirectory.emptyConst3;

        for (int i = 0; i < 100; ++i) {
            this->directory.uncompressedSize[i] = this->oldDirectory.uncompressedSize[i];
        }
        for (int i = 0; i < 100; ++i) {
            this->directory.compressedSize[i] = this->oldDirectory.compressedSize[i];
        }
        for (int i = 0; i < 100; ++i) {
            this->directory.id[i] = this->oldDirectory.id[i];
        }
        for (int i = 0; i < 100; ++i) {
            this->directory.isCompressed[i] = this->oldDirectory.isCompressed[i];
        }
        for (int i = 0; i < 100; ++i) {
            this->directory.offset[i] = this->oldDirectory.offset[i];
        }
    }

} // namespace IO
} // namespace OpenSHC
