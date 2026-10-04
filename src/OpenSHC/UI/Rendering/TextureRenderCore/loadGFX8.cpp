#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::FileResourceType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00454700
        int TextureRenderCore::loadGFX8(char* gfx8Filename)
        {
            size_t _size;
            BOOLEnum _success;
            void* _destination;
            int _currentBufferFillSize;
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                IO::FRT_GFX8, (char const*)((int)(gfx8Filename)));
            _size = MACRO_CALL_MEMBER(
                IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            _currentBufferFillSize = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer;
            if (0x1167910 < (int)(_currentBufferFillSize + _size)) {
                return -1;
            }
            _destination = (void*)((int)this->gmAndGfxImageDataBuffer + _currentBufferFillSize);
            _success = MACRO_CALL_MEMBER(IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                DAT_ResourceManager::ptr)(_destination, _size);
            if (_success == FALSE) {
                return -1;
            }
            this->loadedGfxArray[this->totalLoadedGfx + 1].offsetInBuffer
                = this->loadedGfxArray[this->totalLoadedGfx].offsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            this->loadedGfxArray[this->totalLoadedGfx].width = *(int*)_destination;
            this->loadedGfxArray[this->totalLoadedGfx].height = *(int*)((int)_destination + 4);
            _currentBufferFillSize = this->totalLoadedGfx;
            this->totalLoadedGfx = this->totalLoadedGfx + 1;
            return _currentBufferFillSize;
        }

    }
}
}
