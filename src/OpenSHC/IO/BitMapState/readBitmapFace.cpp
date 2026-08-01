#include "../BitMapState.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace IO {

    // Structure seems a bit weird? If the parameters are truly "x" and "y", then the surface seems to be of short,
    // making the face 66x64, but the loop structure manages these in a different size. Maybe optimization? Was unable
    // to produce it, though.

    int const FACE_SIZE = 66 * 16 * 8;

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C5A0
    void BitMapState::readBitmapFace(unsigned char* surface, int x, int y, int faceIndex)
    {
        unsigned char (*copySurface)[16][8] = (unsigned char (*)[16][8])MACRO_CALL(OS_Func::_malloc)(FACE_SIZE);
        unsigned char* copySurfaceOrigin = (unsigned char*)copySurface;

        unsigned int stride16bit = this->stride16bit;
        for (int i = 0; i < 66; ++i) {

            unsigned char (*faceLine)[8] = (unsigned char (*)[8])(surface + i * stride16bit + x * 2 + stride16bit * y);

            for (int j = 0; j < 16; ++j) {
                for (int k = 0; k < 8; ++k) {
                    copySurface[i][j][k] = faceLine[j][k];
                }
            }
        }
        DAT_TextureRenderCoreObject::instance.field69_0x98[faceIndex] = FACE_SIZE;
        MACRO_CALL(OS_Func::_memcpy)(
            (void*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + faceIndex * FACE_SIZE),
            copySurfaceOrigin, FACE_SIZE);
        MACRO_CALL(OS_Func::_free_base)(copySurfaceOrigin);
    }

}
}
