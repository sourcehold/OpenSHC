#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519310
        void TroopValueState::computeAttackWaveTroopComposition()
        {
            if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 6) {
                DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                    = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen;
                DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 1;
                DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 1;
                DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 1;
                DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 1;
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 0;
                DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 0;
                DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 10) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 3) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 4) {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 0;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 0;
                }
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 2;
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 2) {
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore != 0) {
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 1;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 0;
                }
                DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 20) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 4) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 4;
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 1) {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 6) {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 3;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 4) {
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 1;
                DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 30) {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 4) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 10) {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 5) {
                        DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 4;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 2;
                    }
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 6;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 8) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 5;
                } else if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 2;
                }
                DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 2;
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 5;
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 5) {
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 4) {
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 1;
                }
                DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            } else {
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 1) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen >= 5) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 4;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen - 1;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 5) {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 12) {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 8;
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen > 6) {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 3;
                }
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 10) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 6;
                } else if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 8) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 5;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 3;
                }
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 6;
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore > 0) {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 3;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 2;
                }
                if (DAT_TroopValueState::instance.attackInfo.laddermen <= 6) {
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 2;
                DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                    = DAT_TroopValueState::instance.attackInfo.engineers;
            }
            if (DAT_TroopValueState::instance.attackInfo.assassinTribeCount
                > DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes) {
                DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                    = DAT_TroopValueState::instance.attackInfo.assassinTribeCount;
            }
            DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes = 3;
        }

    }
}
}
