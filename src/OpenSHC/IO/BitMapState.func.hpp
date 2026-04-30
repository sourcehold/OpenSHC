/**
  path: 'OpenSHC/IO/BitMapState.func.hpp'
*/

#include "OpenSHC/IO/BitMapState.hpp"
namespace OpenSHC {
namespace IO {
    namespace BitMapState_Func {

        MACRO_FUNCTION_RESOLVER(void (BitMapState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0046C5A0,
            &BitMapState::readBitmapFace)
        readBitmapFace;

        MACRO_FUNCTION_RESOLVER(void (BitMapState::*)(int), false, Address::SHC_3BB0A8C1_0x0046C680,
            &BitMapState::blitBitmap24BitToSurface565)
        blitBitmap24BitToSurface565;

        MACRO_FUNCTION_RESOLVER(void (BitMapState::*)(int), false, Address::SHC_3BB0A8C1_0x0046C7A0,
            &BitMapState::blitPalettedBitmapToSurface565)
        blitPalettedBitmapToSurface565;

        MACRO_FUNCTION_RESOLVER(
            void (BitMapState::*)(), false, Address::SHC_3BB0A8C1_0x0046C8D0, &BitMapState::copyBitmapToTextureBuffer)
        copyBitmapToTextureBuffer;

        MACRO_FUNCTION_RESOLVER(
            void (BitMapState::*)(), false, Address::SHC_3BB0A8C1_0x00472230, &BitMapState::setBMPFacesToMagenta)
        setBMPFacesToMagenta;

        MACRO_FUNCTION_RESOLVER(
            void (BitMapState::*)(), false, Address::SHC_3BB0A8C1_0x00472270, &BitMapState::loadBitmapHeader)
        loadBitmapHeader;

        MACRO_FUNCTION_RESOLVER(
            void (BitMapState::*)(void*), false, Address::SHC_3BB0A8C1_0x004723E0, &BitMapState::loadAndBlitBitmap)
        loadAndBlitBitmap;

        MACRO_FUNCTION_RESOLVER(
            void (BitMapState::*)(), false, Address::SHC_3BB0A8C1_0x004788A0, &BitMapState::loadFacesBMP)
        loadFacesBMP;

    } // namespace BitMapState_Func
} // namespace IO
} // namespace OpenSHC
