#include "../SoundSystem.func.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479c20
        int SoundSystem::meth_0x479c20(char* fileName)
        {
            if (!this->waveOutOpenUnk_0x8) {
                return -1;
            }
            this->soundFileDataPointerArray_0x122c[this->loadedSoundsCountAndIndex_0x316c] = AIL_file_read(fileName, 0);
            this->soundFileSizes_0x21cc[this->loadedSoundsCountAndIndex_0x316c] = AIL_file_size(fileName);
            if (!this->soundFileDataPointerArray_0x122c[this->loadedSoundsCountAndIndex_0x316c]) {
                return -1;
            }
            ++this->loadedSoundsCountAndIndex_0x316c;
            return this->loadedSoundsCountAndIndex_0x316c - 1;
        }

    }
}
}
