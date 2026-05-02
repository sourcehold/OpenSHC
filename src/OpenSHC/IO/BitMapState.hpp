/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/BitMapState.hpp'
*/

#pragma once

#include "wingdi.h"

namespace OpenSHC {
namespace IO {

#pragma pack(push, 1)

    // SIZE: 0x00000480
    class BitMapState {
    public:
        dword mbr_0x0; // 0x00000000 length: 4
        dword mbr_0x4; // 0x00000004 length: 4
        dword total; // 0x00000008 length: 4
        dword high; // 0x0000000C length: 4
        dword size; // 0x00000010 length: 4
        dword biBitCount; // 0x00000014 length: 4
        dword mbr_0x18; // 0x00000018 length: 4
        byte palette[1024]; // 0x0000001C length: 1024
        dword paletteSize; // 0x0000041C length: 4
        dword paletteStart; // 0x00000420 length: 4
        dword step2; // 0x00000424 length: 4
        dword step; // 0x00000428 length: 4
        dword stride32bit; // 0x0000042C length: 4
        dword stride24bit; // 0x00000430 length: 4
        dword stride16bit; // 0x00000434 length: 4
        dword stride8bit; // 0x00000438 length: 4
        BITMAPFILEHEADER bitmapFileHeader; // 0x0000043C length: 14
        undefined1 padding_0x44a[2]; // 0x0000044A length: 2
        BITMAPINFOHEADER bitmapInfoHeader; // 0x0000044C length: 40
        dword address; // 0x00000474 length: 4
        void* surface; // 0x00000478 length: 4
        dword mbr_0x47c; // 0x0000047C length: 4

    private:
        BitMapState(BitMapState const&);
        void operator=(BitMapState const&);

        BitMapState();
        ~BitMapState();

    public:
        // Constructor
        BitMapState* Constructor_BitMapState();

        void readBitmapFace(int param_1, int param_2, int param_3, int faceIndex);

        void blitBitmap24BitToSurface565(int addExtra);

        void blitPalettedBitmapToSurface565(int param_1);

        void copyBitmapToTextureBuffer();

        void setBMPFacesToMagenta();

        void loadBitmapHeader();

        void loadAndBlitBitmap(void* surface);

        void loadFacesBMP();
    };

    static_assert_cpp98_obj(sizeof(BitMapState) == 1152, BitMapState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(BitMapState, false, Address::SHC_3BB0A8C1_0x011BECB0) pDAT_BitMapState;

} // namespace IO
} // namespace OpenSHC
