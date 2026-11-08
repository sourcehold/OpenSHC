#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00420BF0
        void BuildingsState::upgradeBuildingsForMapVersion(
            int receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
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
            if (receivedMapVersion < 103) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
            }
            if (receivedMapVersion < 116) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageLayerForAllBuildings,
                    DAT_BuildingsState::ptr)();
            }
            if (receivedMapVersion < 119) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingFlag1)();
            }
            if (receivedMapVersion < 121) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField1)();
            }
            if (receivedMapVersion < 130) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetDairyCheeseToZero)();
            }
            if (receivedMapVersion < 133) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeTowerLogicLayer)();
            }
            if (receivedMapVersion < 140) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetHovelBuildOrder)();
            }
            if (receivedMapVersion < 143) {
                MACRO_CALL(OpenSHC::Map::Version_Func::SetBuildingsEmployeeCountToValue)();
            }
            if (receivedMapVersion < 146) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField2)();
            }
            if (receivedMapVersion < 149) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeSolitaryMapBuildingField3)();
            }
            if (receivedMapVersion < 150) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeLogicAndDisplayLayerForDairyFarms)();
            }
            if (receivedMapVersion < 151) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeDestroyDrawbridgesInFirst10Buildings)();
            }
            if (receivedMapVersion < 152) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradePitchDitchBuildingIntoPitchDitchObject)();
            }
            if (receivedMapVersion < 156) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeBuildingField4)();
            }
            if (receivedMapVersion < 161) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeClearBuildings1000AndHigher)();
            }
            if (receivedMapVersion < 167) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeKnightsAndStables)();
            }
            if (receivedMapVersion < 172) {
                MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeOutpostField)();
            }
        }

    }
}
}
