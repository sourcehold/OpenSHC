#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CAA0
        void DirectionAlgorithmState::somethingWithProjectileDistance(int x, int y, int targetX, int targetY)
        {
            if (x > targetX) {
                this->distanceX = x - targetX;
            } else {
                this->distanceX = targetX - x;
            }
            if (y > targetY) {
                this->distanceY = y - targetY;
            } else {
                this->distanceY = targetY - y;
            }

            /* minor axis in percent of the major axis (an inlined percentage helper like computeHealthPercentage:
               100 when the major axis is 0) */
            int axisRatioPercent;
            if (this->distanceX >= this->distanceY) {
                int part = this->distanceY;
                int whole = this->distanceX;
                if (whole == 0) {
                    axisRatioPercent = 100;
                } else {
                    axisRatioPercent = part * 100 / whole;
                }
            } else {
                int part = this->distanceX;
                int whole = this->distanceY;
                if (whole == 0) {
                    axisRatioPercent = 100;
                } else {
                    axisRatioPercent = part * 100 / whole;
                }
            }
            if (this->distanceX >= this->distanceY) {
                if (x > targetX) {
                    if (y > targetY) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 72;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 73;
                        } else {
                            this->orientation = 74;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 72;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 71;
                        } else {
                            this->orientation = 70;
                        }
                    }
                } else {
                    if (y > targetY) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 64;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 63;
                        } else {
                            this->orientation = 62;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 64;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 65;
                        } else {
                            this->orientation = 66;
                        }
                    }
                }
            } else {
                if (y > targetY) {
                    if (x > targetX) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 60;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 75;
                        } else {
                            this->orientation = 74;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 60;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 61;
                        } else {
                            this->orientation = 62;
                        }
                    }
                } else {
                    if (x > targetX) {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 68;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 69;
                        } else {
                            this->orientation = 70;
                        }
                    } else {
                        if (axisRatioPercent <= 25) {
                            this->orientation = 68;
                        } else if (axisRatioPercent < 75) {
                            this->orientation = 67;
                        } else {
                            this->orientation = 66;
                        }
                    }
                }
            }

            if (this->distanceY + this->distanceX <= 0) {
                this->orientation = 76;
            }
        }

    }
}
}
