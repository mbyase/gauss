#ifndef COMMUNICATION_BASE_H
#define COMMUNICATION_BASE_H

#include <stdint.h>
#include <string>
#include <vector>


class CommunicationBase {

    public:

        virtual int init() = 0;

        virtual void manageHardwareConnection() = 0;
        virtual bool isConnectionOk() = 0;

        virtual void startHardwareControlLoop() = 0;
        virtual void stopHardwareControlLoop() = 0;
        virtual void resumeHardwareControlLoop() = 0;

        virtual void getCurrentPosition(double pos[6]) = 0;
        
        virtual void getHardwareStatus(bool *is_connection_ok, std::string &error_message, 
                int *calibration_needed, bool *calibration_in_progress,
                std::vector<std::string> &motor_names, std::vector<std::string> &motor_types,
                std::vector<int32_t> &temperatures,
                std::vector<double> &voltages, std::vector<int32_t> &hw_errors) = 0;
        
        virtual void getFirmwareVersions(std::vector<std::string> &motor_names,
                std::vector<std::string> &firmware_versions) = 0;
        
        virtual void sendPositionToRobot(const double cmd[6]) = 0;
        virtual void activateLearningMode(bool activate) = 0;
        virtual bool setLeds(std::vector<int> &leds, std::string &message) = 0;

        virtual int allowMotorsCalibrationToStart(int mode) = 0;
        virtual void requestNewCalibration() = 0;
        virtual bool isCalibrationInProgress() = 0;

        // tools
        virtual int pingAndSetDxlTool(uint8_t id, std::string name) = 0;
        
        virtual int openGripper(uint8_t id, uint16_t open_position, uint16_t open_speed, uint16_t open_hold_torque) = 0;
        virtual int closeGripper(uint8_t id, uint16_t close_position, uint16_t close_speed, uint16_t close_hold_torque, uint16_t close_max_torque) = 0;

        virtual int pullAirVacuumPump(uint8_t id, uint16_t pull_air_position, uint16_t pull_air_hold_torque) = 0;
        virtual int pushAirVacuumPump(uint8_t id, uint16_t push_air_position) = 0;
        
        // steppers
        virtual void synchronizeMotors(bool begin_traj) = 0;

};

#endif
