#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/EH_FUN_00599fb4.hpp"
#include "OpenSHC/Globals/LIB_00df37e0.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/vftable.hpp"

#include "HoldStrong_lib/stdLib/ios/ios_base.func.hpp"
#include "HoldStrong_lib/std/basic_ofstream<char,_struct_std::char_traits<char>_>.func.hpp"
#include "HoldStrong_lib/stdLib/ios/basic_streambuf<char,_struct_std::char_traits<char>_>.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479540
        void WindowAndDirectDraw::takeScreenshot(int param_1)
        {
            char cVar1;
            uint uVar2;
            StringObject* pSVar3;
            CharPointerArrayUnion* pCVar4;
            uint uVar5;
            char* pcVar6;
            char* pcVar7;
            ushort* _ptrPixelData;
            int _xIndex;
            int* unaff_FS_OFFSET;
            int _heightIndex;
            dword* _ios_base_child_PtrUnk;
            undefined1* local_8c4;
            uint local_8c0;
            BITMAPFILEHEADER _ptrBmpFileHeader;
            basic_ofstream<char, struct std::char_traits<char>> _ofstream;
            BITMAPINFOHEADER _ptrBitmapInfoHeader;
            StringObject local_7fc;
            char local_7e0[1000];
            char local_3f8[1000];
            uint local_10;
            int local_c;
            code* pcStack_8;
            int local_4;
            ushort _pixelData;
            int _width;
            local_4 = -1;
            pcStack_8 = HoldStrong_lib::EH_FUN_00599fb4::instance;
            local_c = *unaff_FS_OFFSET;
            local_10 = MSVC_SecurityCookie::instance ^ (uint)&_heightIndex;
            uVar2 = MSVC_SecurityCookie::instance ^ (uint)&stack0xfffff724;
            *unaff_FS_OFFSET = (int)&local_c;
            pSVar3 = MACRO_CALL_MEMBER(IO::ResourceManager_Func::paths_getDocumentsFolderString,
                DAT_ResourceManager::ptr)(&local_7fc, true);
            if (pSVar3->dataLength < 0x10) {
                pCVar4 = &pSVar3->data;
            } else {
                pCVar4 = (CharPointerArrayUnion*)(pSVar3->data).pCharArray;
            }
            pcVar6 = local_7e0;
            do {
                cVar1 = pCVar4->charArray[0];
                *pcVar6 = cVar1;
                pCVar4 = (CharPointerArrayUnion*)((int)pCVar4 + 1);
                pcVar6 = pcVar6 + 1;
            } while (cVar1 != '\0');
            if (0xf < local_7fc.dataLength) {
                MACRO_CALL(OS_Func::_free)(local_7fc.data.pCharArray);
            }
            if (param_1 == -1) {
                pcVar6 = (char*)((int)&local_7fc.dataLength + 3);
                do {
                    pcVar7 = pcVar6;
                    pcVar6 = pcVar7 + 1;
                } while (pcVar7[1] != '\0');
                strcpy(pcVar7 + 1, "screen_capture.bmp");
            } else {
                MACRO_CALL(OS_Func::_sprintf)(local_3f8, "screen_capture_%03d.bmp", param_1, uVar2);
                pcVar6 = local_3f8;
                do {
                    cVar1 = *pcVar6;
                    pcVar6 = pcVar6 + 1;
                } while (cVar1 != '\0');
                uVar2 = (int)pcVar6 - (int)local_3f8;
                pcVar6 = (char*)((int)&local_7fc.dataLength + 3);
                do {
                    pcVar7 = pcVar6 + 1;
                    pcVar6 = pcVar6 + 1;
                } while (*pcVar7 != '\0');
                pcVar7 = local_3f8;
                for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *(undefined4*)pcVar6 = *(undefined4*)pcVar7;
                    pcVar7 = pcVar7 + 4;
                    pcVar6 = pcVar6 + 4;
                }
                for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                    *pcVar6 = *pcVar7;
                    pcVar7 = pcVar7 + 1;
                    pcVar6 = pcVar6 + 1;
                }
            }
MACRO_CALL_MEMBER(HoldStrong_lib::std::basic_ofstream<char,_struct_std::char_traits<char>_>_Func::basic_ofstream<char,_struct_std::char_traits<char>_>, ()()basic_ofstream<char,_struct_std::char_traits<char>_> *)(&_ofstream,local_7e0,0x20,0x40,
1));
local_4 = 0;
if (!((&_ofstream.field_0x8)[(int)_ofstream.vftptr_0x0[1].~basic_ofstream<char, _struct_std::char_traits<char> _> _0]
        & 6)) {
    MACRO_CALL_MEMBER(
        UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurfaceComplete, this)();
    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
        14, '\0', &_ptrBmpFileHeader);
    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(2, "BM", &_ptrBmpFileHeader);
    _ptrBmpFileHeader.bfSize = this->numPixel_GameX_x_3_x_GameY_0x4c + 54;
    _ptrBmpFileHeader.bfOffBits = 54;
    uVar2 = 0;
    do {
        MACRO_CALL(OS_Func::basic_ofstream_write)(
            &_ofstream, (uint) * (byte*)((int)&_ptrBmpFileHeader.bfType + uVar2));
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0xe);
    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
        40, '\0', &_ptrBitmapInfoHeader);
    _ptrBitmapInfoHeader.biSize = 40;
    _ptrBitmapInfoHeader.biPlanes = 1;
    _ptrBitmapInfoHeader.biBitCount = 24;
    _ptrBitmapInfoHeader.biWidth = this->resolutionX;
    _ptrBitmapInfoHeader.biHeight = this->resolutionY;
    _ptrBitmapInfoHeader.biCompression = 0;
    _ptrBitmapInfoHeader.biSizeImage = this->numPixel_GameX_x_3_x_GameY_0x4c;
    uVar2 = 0;
    do {
        MACRO_CALL(OS_Func::basic_ofstream_write)(
            &_ofstream, (uint) * (byte*)((int)&_ptrBitmapInfoHeader.biSize + uVar2));
        uVar2 = uVar2 + 1;
        _width = this->resolutionX;
        _heightIndex = this->resolutionY;
    } while (uVar2 < 40);
    while (_heightIndex = _heightIndex + -1, -1 < _heightIndex) {
        _xIndex = 0;
        _ptrPixelData = this->surfacePointer_screenMenu + _width * _heightIndex;
        if (0 < _width) {
            do {
                _pixelData = *_ptrPixelData;
                local_8c0 = CONCAT31(local_8c0._1_3_, (char)_pixelData << 3);
                _ptrPixelData = _ptrPixelData + 1;
                MACRO_CALL(OS_Func::basic_ofstream_write)(&_ofstream, local_8c0);
                local_8c4 = (undefined1*)CONCAT31(local_8c4._1_3_, (char)((int)(uint)_pixelData >> 5) * '\x04');
                MACRO_CALL(OS_Func::basic_ofstream_write)(&_ofstream, (uint)((int)(local_8c4)));
                _ios_base_child_PtrUnk
                    = (dword*)CONCAT31(_ios_base_child_PtrUnk._1_3_, (char)((short)_pixelData >> 0xb) << 3);
                MACRO_CALL(OS_Func::basic_ofstream_write)(&_ofstream, (uint)((int)(_ios_base_child_PtrUnk)));
                _xIndex = _xIndex + 1;
                _width = this->resolutionX;
            } while (_xIndex < this->resolutionX);
        }
    }
    _ios_base_child_PtrUnk = &_ofstream.mbr_0x54;
    *(undefined***)(_ofstream.vftptr_0x0[1].~basic_ofstream<char, _struct_std::char_traits<char> _> _0
        + (int)&_ofstream.vftptr_0x0) = std::basic_ofstream<char, struct_std::char_traits<char> _>::vftable::instance;
    local_8c4 = &_ofstream.field_0x4;
    _ofstream._4_4_ = std::basic_filebuf<char, struct_std::char_traits<char> _>::vftable::instance;
    local_4 = 2;
    if (_ofstream._76_1_ != '\0') {
        if (_ofstream._80_4_) {
            MACRO_CALL_MEMBER(HoldStrong_lib::stdLib::ios::basic_streambuf<char, _struct_std::char_traits<char> _>
                                  _Func::meth_0x476680,
                (basic_streambuf<char, _struct_std::char_traits<char> _>*)local_8c4)();
            MACRO_CALL(OS_Func::_fclose)((FILE*)_ofstream._80_4_);
        }
        _ofstream._20_4_ = &_ofstream.field_0xc;
        _ofstream._24_4_ = &_ofstream.field_0x10;
        _ofstream._36_4_ = &_ofstream.field_0x1c;
        _ofstream._40_4_ = &_ofstream.field_0x20;
        _ofstream._52_4_ = &_ofstream.field_0x2c;
        _ofstream._56_4_ = &_ofstream.field_0x30;
        _ofstream._76_1_ = 0;
        _ofstream._69_1_ = 0;
        _ofstream._16_4_ = 0;
        _ofstream._32_4_ = 0;
        _ofstream._48_4_ = 0;
        _ofstream._12_4_ = 0;
        _ofstream._28_4_ = 0;
        _ofstream._44_4_ = 0;
        _ofstream._80_4_ = 0;
        _ofstream._72_4_ = LIB_00df37e0::instance;
        _ofstream._64_4_ = 0;
    }
    local_4 = CONCAT31(local_4._1_3_, 1);
MACRO_CALL_MEMBER(HoldStrong_lib::stdLib::ios::basic_streambuf<char,_struct_std::char_traits<char>_>_Func::meth_0x472680, (basic_streambuf<char,_struct_std::char_traits<char>_>*)&_ofstream.field_0x4)();
local_4 = -1;
*(undefined***)(_ofstream.vftptr_0x0[1].~basic_ofstream<char, _struct_std::char_traits<char> _> _0
    + (int)&_ofstream.vftptr_0x0) = std::basic_ostream<char, struct_std::char_traits<char> _>::vftable::instance;
} else {
    local_4 = -1;
MACRO_CALL_MEMBER(HoldStrong_lib::std::basic_ofstream<char,_struct_std::char_traits<char>_>_Func::meth_0x478920, (basic_ofstream<char,_struct_std::char_traits<char>_>*)&_ofstream.mbr_0x54)();
}
_ofstream.mbr_0x54 = (dword)std::ios_base::vftable::instance;
MACRO_CALL_MEMBER(HoldStrong_lib::stdLib::ios::ios_base_Func::_Ios_base_dtor, (ios_base*)&_ofstream.mbr_0x54)();
*unaff_FS_OFFSET = local_c;
;
return;
        }

    }
}
}
