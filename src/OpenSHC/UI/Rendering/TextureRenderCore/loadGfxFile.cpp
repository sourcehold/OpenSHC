#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00454620
        int TextureRenderCore::loadGfxFile(char const* tgxFileName)
        {
            size_t _size;
            BOOLEnum _loadSuccessful;
            void* _tgxLoadLocation;
            int _currentBufferSize;
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GFX, tgxFileName);
            _size = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            _currentBufferSize = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer;
            if (0x1167910 < (int)(_currentBufferSize + _size)) {
                return -1;
            }
            _tgxLoadLocation = (void*)((int)this->gmAndGfxImageDataBuffer + _currentBufferSize);
            _loadSuccessful = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                DAT_ResourceManager::ptr)(_tgxLoadLocation, _size);
            if (_loadSuccessful == FALSE) {
                return -1;
            }
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                    (ushort*)((int)_tgxLoadLocation + 8),
                    DAT_ResourceManager::instance.loadPositionInCurrentResource + -8);
            }
            this->loadedGfxArray[this->totalLoadedGfx + 1].offsetInBuffer
                = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            this->loadedGfxArray[this->totalLoadedGfx].width = *(int*)_tgxLoadLocation;
            this->loadedGfxArray[this->totalLoadedGfx].height = *(int*)((int)_tgxLoadLocation + 4);
            this->totalLoadedGfx = this->totalLoadedGfx + 1;
            return this->totalLoadedGfx + -1;
        }

    }
}
}
