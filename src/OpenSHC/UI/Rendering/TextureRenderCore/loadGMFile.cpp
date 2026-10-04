#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmImageType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PictureNumToGmIDArray_UNUSED.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/IO/Graphics/ImageHeader.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::FileResourceType;
        using IO::Graphics::GmImageType;
        using WindowsHelper::Enums::BOOLEnum;
        using IO::Graphics::ImageHeader;

        // FUNCTION: STRONGHOLDCRUSADER 0x004559B0
        void TextureRenderCore::loadGMFile(GmID gmID, char* gmFileName)
        {
            char (*shortFileName_00)[1001];
            short sVar1;
            BOOLEnum BVar2;
            BOOL BVar3;
            char* _soonPointerToLastCharInGMFileName;
            ImageHeader* _shiftedHeaderPtr;
            int iVar4;
            int _currentImageOffset;
            int _currentlyProcessedPictures;
            int _currentTotalImagesSize;
            tagMSG local_1c;
            char* shortFileName;
            char currentCharInGMFile;
            BVar3 = PeekMessageA(&local_1c, (HWND__*)0x0, 0, 0, 0);
            if (BVar3 != 0) {
                BVar3 = GetMessageA(&local_1c, (HWND__*)0x0, 0, 0);
                if (BVar3 != 0) {
                    TranslateMessage(&local_1c);
                    DispatchMessageA(&local_1c);
                }
            }
            BVar2 = this->unknownSfxAndGmRelatedFlag;
            _currentTotalImagesSize = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                5208, '\0', (void*)((int)(this->gmFileHeaderColorpaletteArray + gmID)));
            shortFileName_00 = this->gmFileNameArray_UNUSEDUnk_0x13179c + gmID;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                1000, '\0', (void*)((int)(shortFileName_00)));
            _soonPointerToLastCharInGMFileName = gmFileName;
            do {
                currentCharInGMFile = *_soonPointerToLastCharInGMFileName;
                _soonPointerToLastCharInGMFileName = _soonPointerToLastCharInGMFileName + 1;
            } while (currentCharInGMFile != '\0');
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                (int)_soonPointerToLastCharInGMFileName - (int)(gmFileName + 1), (void*)((int)(gmFileName)),
                (void*)((int)(shortFileName_00)));
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                IO::FRT_GM, (char const*)((int)(*shortFileName_00)));
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::readFirstPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(this->gmFileHeaderColorpaletteArray + gmID, (int)((int)(5208)), "gm1");
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(DAT_GMImageOffsets::instance + this->gmNumberOfProcessedPictures,
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile * 4, "gm1");
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(DAT_GMImageSizes::instance + this->gmNumberOfProcessedPictures,
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile * 4, "gm1");
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(DAT_GMImageHeaders::instance.imh + this->gmNumberOfProcessedPictures,
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile << 4, "gm1");
            MACRO_CALL_MEMBER(
                IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory, DAT_ResourceManager::ptr)(
                this->gmAndGfxImageDataBuffer, this->gmFileHeaderColorpaletteArray[gmID].dataSize, "gm1");
            if (this->gmFileHeaderColorpaletteArray[gmID].ImageType == IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(
                    UI::Rendering::TextureRenderCore_Func::transformGmColorTableFromRGB555To565IfRequired,
                    this)(gmID);
            }
            _currentImageOffset = DAT_GMImageOffsets::instance[this->gmNumberOfProcessedPictures];
            if (this->gmNumberOfProcessedPictures < this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile
                    + this->gmNumberOfProcessedPictures) {
                _shiftedHeaderPtr = &DAT_GMImageHeaders::instance.imh[this->gmNumberOfProcessedPictures];
                _currentlyProcessedPictures = this->gmNumberOfProcessedPictures;
                /*
                  For every picture in gm file
                 */
                do {
                    DAT_PictureNumToGmIDArray_UNUSED::instance[_currentlyProcessedPictures] = gmID;
                    if (BVar2 == FALSE) {
                        if ((_shiftedHeaderPtr->animatedColor & 4) == 0)
                            goto LAB_00455bc5;
                    LAB_00455ba2:
                        /*
                          Points in offset array? -TheRedDaemon
                         */
                        iVar4 = DAT_GMImageSizes::instance[_currentlyProcessedPictures + 115999];
                    LAB_00455ba9:
                        sVar1 = _shiftedHeaderPtr->alternativeImageIndexUnk;
                        DAT_GMImageOffsets::instance[_currentlyProcessedPictures] = iVar4;
                        DAT_GMImageSizes::instance[_currentlyProcessedPictures]
                            = DAT_GMImageSizes::instance[sVar1 + _currentlyProcessedPictures];
                    } else {
                        if (_shiftedHeaderPtr->animatedColor != 0) {
                            if ((_shiftedHeaderPtr->animatedColor & 4) != 0)
                                goto LAB_00455ba2;
                            iVar4 = DAT_GMImageOffsets::instance[_shiftedHeaderPtr->alternativeImageIndexUnk
                                + _currentlyProcessedPictures];
                            goto LAB_00455ba9;
                        }
                    LAB_00455bc5:
                        /*
                          copy current image data into proccessed array
                         */
                        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                            DAT_GMImageSizes::instance[_currentlyProcessedPictures],
                            (void*)((int)(((int)this->gmAndGfxImageDataBuffer
                                + DAT_GMImageOffsets::instance[_currentlyProcessedPictures]))),
                            (void*)((int)(((int)this->gmProcessedImageData + _currentImageOffset
                                + this->gmSizeOfProcessedPictures_0x44))));
                        DAT_GMImageOffsets::instance[_currentlyProcessedPictures]
                            = this->gmSizeOfProcessedPictures_0x44 + _currentImageOffset;
                        /*
                          update indices
                         */
                        _currentTotalImagesSize
                            = _currentTotalImagesSize + DAT_GMImageSizes::instance[_currentlyProcessedPictures];
                        _currentImageOffset
                            = _currentImageOffset + DAT_GMImageSizes::instance[_currentlyProcessedPictures];
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::adaptGmColorsToRGB565IfRequired, this)(
                            gmID, _currentlyProcessedPictures);
                    }
                    _currentlyProcessedPictures = _currentlyProcessedPictures + 1;
                    _shiftedHeaderPtr = _shiftedHeaderPtr + 8;
                } while (_currentlyProcessedPictures < this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile
                        + this->gmNumberOfProcessedPictures);
            }
            this->gmSizeOfProcessedPictures_0x44 = this->gmSizeOfProcessedPictures_0x44 + _currentTotalImagesSize;
            /*
              Update loading bar
             */
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::drawLoadingBarUnk, this)(
                gmID, (int)((int)(DAT_LoadingBarProgress::instance + 0xb4)));
        }

    }
}
}
