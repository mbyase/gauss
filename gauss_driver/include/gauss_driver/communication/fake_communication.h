#ifndef FAKE_COMMUNICATION_H
#define FAKE_COMMUNICATION_H

#include <boost/shared_ptr.hpp>
#include <ros/ros.h>
#include <string>
#include <thread>

#include "gauss_driver/communication/communication_base.h"

#include "gauss_driver/dynamixel/dxl_motor_state.h" // for gripper enums

class FakeCommunication : public CommunicationBase {

    public:
        FakeCommunication(int hardware_version);
        int init();

        void manageHardwareConnection();
        bool isConnectionOk();

        void startHardwareControlLoop();
        void stopHardwareControlLoop();
        void resumeHardwareControlLoop();

        void getCurrentPosition(double pos[6]);
        
        void getHardwareStatus(bool *is_connection_ok, std::string &error_message,
                int *calibration_needed, bool *calibration_in_progress,
                std::vector<std::string> &motor_names, std::vector<std::string> &motor_types,
                std::vector<int32_t> &temperatures,
                std::vector<double> &voltages, std::vector<int32_t> &hw_errors);
        
        void getFirmwareVersions(std::vector<std::string> &motor_names,
                std::vector<std::string> &firmware_versions);
        
        void sendPositionToRobot(const double cmd[6]); 
        void activateLearningMode(bool activate);
        bool setLeds(std::vector<int> &leds, std::string &message);
        
        int allowMotorsCalibrationToStart(int mode);
        void requestNewCalibration();
        bool isCalibrationInProgress();
        
        // tools
        int pingAndSetDxlTool(uint8_t id, std::string name);
        
        int openGripper(uint8_t id, uint16_t open_position, uint16_t open_speed, uint16_t open_hold_torque);
        int closeGripper(uint8_t id, uint16_t close_position, uint16_t close_speed, uint16_t close_hold_torque, uint16_t close_max_torque);
        
        int pullAirVacuumPump(uint8_t id, uint16_t pull_air_position, uint16_t pull_air_hold_torque);
        int pushAirVacuumPump(uint8_t id, uint16_t push_air_position);
        
        // steppers
        void synchronizeMotors(bool begin_traj);

    private:

        int hardware_version;
        
        double echo_pos[6]; // just store cmd in this array, and echo position

};

#endif
