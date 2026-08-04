#include "../BitMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace IO {

    int const FACE_SIZE = 66 * 64 * 2;

    // FUNCTION: STRONGHOLDCRUSADER 0x00472230
    void BitMapState::setBMPFacesToMagenta()
    {
        for (int faceIndex = 20; faceIndex < 28; ++faceIndex) {
            MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(FACE_SIZE,
                COL_MAGENTA::instance.shortValue,
                ((unsigned char (*)[FACE_SIZE])DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94)[faceIndex]);
        }
    }

}
}
