#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455C60
        void TextureRenderCore::loadGmFiles(char* fileNameArray)
        {
            int _currentLoadingBarStatus;
            int _lengthToCompare;
            char* _currentGmFilename;
            int _currentGmIndex;
            char* _endOfFilenameArray;
            bool bVar1;
            bool _reachedFilenameArrayEnd;
            char* _endOfFilenameArray2;
            /*
              Count gm files for the loading bar?
             */
            _currentLoadingBarStatus = 0;
            _currentGmFilename = fileNameArray;
            do {
                _currentLoadingBarStatus = _currentLoadingBarStatus + 1;
                _lengthToCompare = 5;
                bVar1 = true;
                _endOfFilenameArray2 = _currentGmFilename;
                _endOfFilenameArray = "null";
                do {
                    if (_lengthToCompare == 0)
                        break;
                    _lengthToCompare = _lengthToCompare + -1;
                    bVar1 = *_endOfFilenameArray2 == *_endOfFilenameArray;
                    _endOfFilenameArray2 = _endOfFilenameArray2 + 1;
                    _endOfFilenameArray = _endOfFilenameArray + 1;
                } while (bVar1);
                if (bVar1)
                    goto LAB_00455c95;
                _currentGmFilename = _currentGmFilename + 1000;
            } while (_currentLoadingBarStatus < 240);
            _currentLoadingBarStatus = _currentLoadingBarStatus + 1;
        LAB_00455c95:
            /*
              Start Actual loading
             */
            DAT_LoadingBarProgress::instance = _currentLoadingBarStatus;
            _currentGmIndex = 0;
            this->gmNumberOfProcessedPictures = 1;
            this->gmFileID = 1;
            this->gmSizeOfProcessedPictures_0x44 = 0;
            do {
                _currentGmIndex = _currentGmIndex + 1;
                _lengthToCompare = 5;
                _reachedFilenameArrayEnd = true;
                _currentGmFilename = fileNameArray;
                _endOfFilenameArray2 = "null";
                do {
                    if (_lengthToCompare == 0)
                        break;
                    _lengthToCompare = _lengthToCompare + -1;
                    _reachedFilenameArrayEnd = *_currentGmFilename == *_endOfFilenameArray2;
                    _currentGmFilename = _currentGmFilename + 1;
                    _endOfFilenameArray2 = _endOfFilenameArray2 + 1;
                } while (_reachedFilenameArrayEnd);
                if (_reachedFilenameArrayEnd)
                    break;
                GMTotalPicturesProcessed::instance[this->gmFileID] = this->gmNumberOfProcessedPictures;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGMFile, this)(
                    (IO::Graphics::GmID)(this->gmFileID), fileNameArray);
                fileNameArray = fileNameArray + 1000;
                this->gmNumberOfProcessedPictures = this->gmNumberOfProcessedPictures
                    + this->gmFileHeaderColorpaletteArray[this->gmFileID].numberOfPicturesInFile;
                this->gmFileID = this->gmFileID + 1;
            } while (_currentGmIndex < 240);
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadCampaignMapGfxUnk, this)();
            DAT_TextManagerObject::instance.sizeOfOneFontSet_0x3c
                = this->gmFileHeaderColorpaletteArray[0x57].numberOfPicturesInFile / 5;
        }

    }
}
}
