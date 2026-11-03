// disable deprecation warnings for strcpy, strcat and sprintf
#pragma warning(disable : 4996)

#include "../WindowAndDirectDraw.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

#include <fstream>

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00479540
        void WindowAndDirectDraw::takeScreenshot(int screenshotNumber)
        {
            char path[1000];
            // NOTE: Requires direct, non-resolved call due to copy elision.
            strcpy(path, DAT_ResourceManager::ptr->paths_getDocumentsFolderString(true).c_str());
            if (screenshotNumber == -1) {
                strcat(path, S_SCREEN_CAPTURE_BMP_005A6538);
            } else {
                char fileName[1000];
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(fileName, S_SCREEN_CAPTURE__03D_BMP_005A6520, screenshotNumber);
                strcat(path, fileName);
            }

            // NOTE: the original writes through its own statically linked VC8 std::ofstream. The bytes go through the
            // game's own operator<<(ostream&, char), OS::basic_ofstream_write (0x004791B0); the stream object is our
            // library's std::ofstream, which has the same VC8 layout.
            std::ofstream file(path, std::ios::binary);
            if (file.fail())
                return;

            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurfaceComplete, this)();

            BITMAPFILEHEADER fileHeader;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(fileHeader), '\0', &fileHeader);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                2, (void*)DAT_BMP_MAGICVALUE, &fileHeader);
            fileHeader.bfSize
                = this->numPixel_GameX_x_3_x_GameY_0x4c + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
            fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
            for (uint i = 0; i < sizeof(fileHeader); i++) {
                MACRO_CALL(OpenSHC::OS_Func::basic_ofstream_write)(&file, ((char*)&fileHeader)[i]);
            }

            BITMAPINFOHEADER infoHeader;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(infoHeader), '\0', &infoHeader);
            infoHeader.biSize = sizeof(infoHeader);
            infoHeader.biPlanes = 1;
            infoHeader.biBitCount = 24;
            infoHeader.biWidth = this->resolutionX;
            infoHeader.biHeight = this->resolutionY;
            infoHeader.biCompression = BI_RGB;
            infoHeader.biSizeImage = this->numPixel_GameX_x_3_x_GameY_0x4c;
            for (uint i = 0; i < sizeof(infoHeader); i++) {
                MACRO_CALL(OpenSHC::OS_Func::basic_ofstream_write)(&file, ((char*)&infoHeader)[i]);
            }

            // RGB565 rows, bottom-up, written as BGR24. The walking pointer and the named char locals are both
            // load-bearing: row[x] cost 10 points and passing the expressions directly cost 6 (quick_diff).
            for (int y = this->resolutionY - 1; y >= 0; y--) {
                ushort* pixelPtr = this->surfacePointer_screenMenu + this->resolutionX * y;
                for (int x = 0; x < this->resolutionX; x++) {
                    int const pixel = *pixelPtr++;
                    char const blue = (char)pixel << 3;
                    MACRO_CALL(OpenSHC::OS_Func::basic_ofstream_write)(&file, blue);
                    char const green = (char)(pixel >> 5) * 4;
                    MACRO_CALL(OpenSHC::OS_Func::basic_ofstream_write)(&file, green);
                    char const red = (char)((short)pixel >> 11) << 3;
                    MACRO_CALL(OpenSHC::OS_Func::basic_ofstream_write)(&file, red);
                }
            }
        }

    }
}
}
