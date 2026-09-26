#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00420BF0
        void BuildingsState::upgradeBuildingsForMapVersion(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            MACRO_CALL(OpenSHC::Map::Version_Func::SetUndamagedBuildingHealthToValue)();
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingProperties1)(receivedMapVersion);
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeFirst9Buildings)();
            MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeKillingPitField)();
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::rebuildTileLogicLayerForGatesAndWalls, this)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::rebuildTileLogicLayerForKeeps, this)();
            this->pathLinkageKeepWasUpdatedUnk = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageForGatesKeepsSiegeTowers, this)();
            if (receivedMapVersion == packagerMapVersion) {
                return;
            }

            // Upgrades of maps saved with older versions
            if ((int)receivedMapVersion < 103) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
            }
            if ((int)receivedMapVersion < 116) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
                    DAT_BuildingsState::ptr)();
            }
            if ((int)receivedMapVersion < 119) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
            }
            if ((int)receivedMapVersion < 121) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField1)();
            }
            if ((int)receivedMapVersion < 130) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetDairyCheeseToZero)();
            }
            if ((int)receivedMapVersion < 133) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeTowerLogicLayer)();
            }
            if ((int)receivedMapVersion < 140) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetHovelBuildOrder)();
            }
            if ((int)receivedMapVersion < 143) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetBuildingsEmployeeCountToValue)();
            }
            if ((int)receivedMapVersion < 146) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField2)();
            }
            if ((int)receivedMapVersion < 149) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeSolitaryMapBuildingField3)();
            }
            if ((int)receivedMapVersion < 150) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeLogicAndDisplayLayerForDairyFarms)();
            }
            if ((int)receivedMapVersion < 151) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeDestroyDrawbridgesInFirst10Buildings)();
            }
            if ((int)receivedMapVersion < 152) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradePitchDitchBuildingIntoPitchDitchObject)();
            }
            if ((int)receivedMapVersion < 156) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField4)();
            }
            if ((int)receivedMapVersion < 161) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeClearBuildings1000AndHigher)();
            }
            if ((int)receivedMapVersion < 167) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeKnightsAndStables)();
            }
            if ((int)receivedMapVersion < 172) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeOutpostField)();
            }
        }

    }
}
}
