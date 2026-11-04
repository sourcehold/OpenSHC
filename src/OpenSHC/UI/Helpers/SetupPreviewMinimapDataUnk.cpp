// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../Helpers.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00493050
    void Helpers::SetupPreviewMinimapDataUnk()
    {
        int const listIndex = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
            + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
        if (listIndex == -1 || DAT_MenuTextInputState::instance.previewedListIndex == listIndex) {
            return;
        }
        DAT_MenuTextInputState::instance.previewedListIndex = listIndex;
        // The original copies the name and appends the extension inline, so the macros are used here.
        char fileName[1008]; // the size of the original's buffer
        strcpy(fileName,
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex, DAT_ResourceManager::ptr)(
                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[listIndex]));
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
            // ".tmp"
            strcat(fileName, S__TMP_005A75A8);
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                IO::FRT_MAPS, fileName);
        } else if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_CUSTOM_SCENARIOS) {
            // saved games; custom scenarios (.map) come last, as in the original
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                || DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                // ".sav"
                strcat(fileName, S__SAV_005A75A0);
            } else {
                // ".msv"
                strcat(fileName, S__MSV_005A7498);
            }
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                IO::FRT_UNKNOWN, fileName);
        } else {
            // ".map"
            strcat(fileName, S__MAP_005A2294);
            MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                IO::FRT_MAPS, fileName);
        }
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
    }

}
}
