#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_SkirmishLobbySetupStructureLongMapName.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486AD0
    void Version::UpgradeOldSection1124()
    {
        SEC_SkirmishLobbySetupStructure::instance.mapu4int2
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapu4int2;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0x4
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0x4;
        strcpy(SEC_SkirmishLobbySetupStructure::instance.mapName,
            DAT_SkirmishLobbySetupStructureLongMapName::instance.mapName);
        for (int i = 0; i < 9; ++i) {
            SEC_SkirmishLobbySetupStructure::instance.roundTableOrderArray[i]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.roundTableOrderArray[i];
            SEC_SkirmishLobbySetupStructure::instance.playerGroupArray[i]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerGroupArray[i];
            SEC_SkirmishLobbySetupStructure::instance.currentAIArray[i]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAIArray[i];
            SEC_SkirmishLobbySetupStructure::instance.aiVariationArray[i]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.aiVariationArray[i];
        }
        // The eight slot positions are copied as two dwords
        *(int*)&SEC_SkirmishLobbySetupStructure::instance.slot1Position
            = *(int*)&DAT_SkirmishLobbySetupStructureLongMapName::instance.slot1Position;
        *(int*)&SEC_SkirmishLobbySetupStructure::instance.slot5Position
            = *(int*)&DAT_SkirmishLobbySetupStructureLongMapName::instance.slot5Position;
        SEC_SkirmishLobbySetupStructure::instance.currentPlayerSlotID
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentPlayerSlotID;
        SEC_SkirmishLobbySetupStructure::instance.currentAdvantageBalance
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAdvantageBalance;
        SEC_SkirmishLobbySetupStructure::instance.currentAdvantageGroup
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.currentAdvantageGroup;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0x80
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0x80;
        for (int i = 0; i < 9; ++i) {
            SEC_SkirmishLobbySetupStructure::instance.playerLordTypeArray[i]
                = DAT_SkirmishLobbySetupStructureLongMapName::instance.playerLordTypeArray[i];
        }
        SEC_SkirmishLobbySetupStructure::instance.mbr_0xf0
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0xf0;
        SEC_SkirmishLobbySetupStructure::instance.selectedLordType
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.selectedLordType;
        SEC_SkirmishLobbySetupStructure::instance.popularity
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.popularity;
        SEC_SkirmishLobbySetupStructure::instance.mapSelectionRelativeSelected
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapSelectionRelativeSelected;
        SEC_SkirmishLobbySetupStructure::instance.mapSelectionScrollOffset
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mapSelectionScrollOffset;
        SEC_SkirmishLobbySetupStructure::instance.mbr_0xfc
            = DAT_SkirmishLobbySetupStructureLongMapName::instance.mbr_0xfc;
    }

}
}
