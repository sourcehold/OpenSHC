#include "../BitMapState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004788A0
    void BitMapState::loadFacesBMP()
    {
        MACRO_CALL_MEMBER(ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            FRT_BMP, s_faces_bmp_005a6500);
        MACRO_CALL_MEMBER(BitMapState_Func::loadBitmapHeader, this)();

        unsigned char* surface = (unsigned char*)MACRO_CALL(OS_Func::_malloc)(this->stride16bit * this->high);
        MACRO_CALL_MEMBER(BitMapState_Func::loadAndBlitBitmap, this)(surface);
        int x = 7;
        for (int faceIndex = 0; faceIndex < 10; ++faceIndex) {
            MACRO_CALL_MEMBER(BitMapState_Func::readBitmapFace, this)(surface, x, 7, faceIndex);
            MACRO_CALL_MEMBER(BitMapState_Func::readBitmapFace, this)(surface, x, 81, faceIndex + 10);
            x += 71;
        }
        MACRO_CALL(OS_Func::_free_base)(surface);
    }

}
}
