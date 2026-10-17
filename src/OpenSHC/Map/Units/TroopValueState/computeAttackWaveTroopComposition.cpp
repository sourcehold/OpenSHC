#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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
                } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen < 2) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                } else if (3 <= DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 2;
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                        = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + -1;
                }
                DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                    = (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 1;
                DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes
                    = (4 < DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) + 2;
                if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 1;
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 1;
                    if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore <= 0) {
                        DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 0;
                    }
                } else {
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 0;
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 0;
                }
                DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 2;
                if (DAT_TroopValueState::instance.attackInfo.laddermen < 3) {
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                        = DAT_TroopValueState::instance.attackInfo.laddermen;
                }
                DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes
                    = (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore);
            } else {
                if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 0x14) {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                    } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen < 2) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                    } else if (4 <= DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 3;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                            = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + -1;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 4;
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                        = (1 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 2;
                    DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes
                        = (6 < DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) + 3;
                    DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes
                        = (4 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 2;
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes
                        = (0 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 1;
                    if (DAT_TroopValueState::instance.attackInfo.laddermen < 5) {
                        DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                            = DAT_TroopValueState::instance.attackInfo.laddermen;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 1;
                } else if (DAT_TroopValueState::instance.attackInfo.attackTribeCount < 0x1e) {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                    } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen < 2) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                    } else if (4 <= DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 3;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                            = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + -1;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                        = (uint)(4 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen < 0xb) {
                        DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes
                            = (uint)(5 < DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) * 2 + 2;
                    }
                    if (DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore < 9) {
                        DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes
                            = (uint)(4 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) * 2 + 2;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 5;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes = 2;
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 5;
                    if (DAT_TroopValueState::instance.attackInfo.laddermen < 6) {
                        DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                            = DAT_TroopValueState::instance.attackInfo.laddermen;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes
                        = (4 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 1;
                } else {
                    if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen <= 0) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 0;
                    } else if (DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen < 2) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 1;
                    } else if (5 <= DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes = 4;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxWallScaleTribes
                            = DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen + -1;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                        = ((DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore < 6) - 1 & 3) + 2;
                    if (0xc < DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) {
                        DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes = 8;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxMoatAttackTribes
                            = (uint)(6 < DAT_TroopValueState::instance.attackInfo.spearmenAndMacemen) * 2 + 3;
                    }
                    if (0xa < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) {
                        DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes = 6;
                    } else {
                        DAT_TroopValueState::instance.attackInfo.maxPeopleAttackTribes
                            = (uint)(8 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) * 2 + 3;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxLadderTribes = 6;
                    DAT_TroopValueState::instance.attackInfo.maxGateAttackTribes
                        = (0 < DAT_TroopValueState::instance.attackInfo.pikemenSwordsmenAndMore) + 2;
                    if (DAT_TroopValueState::instance.attackInfo.laddermen < 7) {
                        DAT_TroopValueState::instance.attackInfo.maxLadderTribes
                            = DAT_TroopValueState::instance.attackInfo.laddermen;
                    }
                    DAT_TroopValueState::instance.attackInfo.maxTunnelerTribes = 2;
                }
            }
            DAT_TroopValueState::instance.attackInfo.maxEngineerTribes
                = DAT_TroopValueState::instance.attackInfo.engineers;
            DAT_TroopValueState::instance.attackInfo.maxLordAttackTribes = 3;
            if ((int)DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                < DAT_TroopValueState::instance.attackInfo.assassinTribeCount) {
                DAT_TroopValueState::instance.attackInfo.maxTownAttackTribes
                    = DAT_TroopValueState::instance.attackInfo.assassinTribeCount;
            }
        }

    }
}
}
