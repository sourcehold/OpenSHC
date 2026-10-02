#include "../Rendering.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95958.hpp"
#include "OpenSHC/Globals/INT_00b95ab8.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::FileResourceType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Rendering::Colors::BGR24;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004410D0
    void Rendering::DisplayMapDescriptionAndAllocatePlayersToSlots()
    {
        uint uVar1;
        char* _mapName;
        int _index;
        char* puVar1;
        char _mapResourceLoadName[1012];
        int _x;
        int _y;
        int _width;
        int _blendStrength;
        int _mode;
        char* _mapDescription;
        BGR24 _color;
        char _mapChar;
        uVar1 = MSVC_SecurityCookie::instance ^ (uint)_mapResourceLoadName;
        if (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
            < 0) {
            if (DAT_GameSynchronyState::instance.isHost != FALSE)
                goto LAB_00441251;
            _mapName = DAT_GameSynchronyState::instance.mapName;
            do {
                _mapChar = *_mapName;
                _mapName = _mapName + 1;
            } while (_mapChar != '\0');
            if (_mapName == DAT_GameSynchronyState::instance.mapName + 1)
                goto LAB_00441251;
        }
        _index = 0;
        do {
            _mapChar = DAT_GameSynchronyState::instance.mapName[_index];
            _mapResourceLoadName[_index + 4] = _mapChar;
            _index = _index + 1;
        } while (_mapChar != '\0');
        puVar1 = _mapResourceLoadName + 3;
        do {
            _mapName = puVar1;
            puVar1 = _mapName + 1;
        } while (_mapName[1] != '\0');
        strcpy(_mapName + 1, ".map");
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            OpenSHC::IO::FRT_MAPS, (char const*)((int)(_mapResourceLoadName + 4)));
        MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
        INT_00b95958::instance = 1;
        DAT_00b95b74::instance = 0;
        DAT_00b960f4::instance = 0xffffffed;
        if (DAT_GameCore::instance.mapDescUseStringTable == 0) {
            _mode = 1;
            _blendStrength = 0;
            _color = 0;
            _width = 345;
            _y = 0;
            _x = 0;
            _mapName = DAT_GameCore::instance.mapDescription;
        LAB_004411d1:
            DAT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(
                _mapName, _x, _y, _width, _color, _blendStrength, _mode);
        } else if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
            _mode = 1;
            _blendStrength = 0;
            _color = 0;
            _width = 0x159;
            _y = 0;
            _x = 0;
            _mapName = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.mapDescUseStringTableIndex);
            goto LAB_004411d1;
        }
        if ((DAT_GameSynchronyState::instance.isHost != FALSE)
            && ((INT_00b960b0::instance
                    != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                || (INT_00b95ab8::instance != 0)))) {
            DAT_GameSynchronyState::instance.playerPositionsArray[0] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[1] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[2] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[3] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[4] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[5] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[6] = -10;
            DAT_GameSynchronyState::instance.playerPositionsArray[7] = -10;
            _index = 1;
            INT_00b960b0::instance = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected;
            do {
                if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_index] != -1)
                    || (DAT_GameSynchronyState::instance.currentAIArray[_index] != 0)) {
                    MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(_index);
                }
                _index = _index + 1;
            } while (_index < 9);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
        }
    LAB_00441251:
        INT_00b95ab8::instance = 0;
        ;
    }

}
}
