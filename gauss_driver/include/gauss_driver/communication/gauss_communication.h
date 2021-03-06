#ifndef GAUSS_COMMUNICATION_H
#define GAUSS_COMMUNICATION_H

#include <boost/shared_ptr.hpp>
#include <ros/ros.h>
#include <string>
#include <thread>
#include "std_msgs/String.h"

#include "gauss_driver/communication/dxl_communication.h"
#include "gauss_driver/communication/can_communication.h"

#include "gauss_driver/communication/communication_base.h"

#include "gauss_driver/change_hardware_version.h"
#include "common/common.h"

extern GaussLogger g_roslogger_pub; 
class GaussCommunication : public CommunicationBase {

    public:
   
        GaussCommunication(int hardware_version);
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

        // check hardware version (V1/V2)
        void checkHardwareVersionFromDxlMotors();

    private:

        int hardware_version;

        boost::shared_ptr<DxlCommunication> dxlComm;
        boost::shared_ptr<CanCommunication> canComm;
        
        bool can_enabled;
        bool dxl_enabled;

        double gauss_hw_check_connection_frequency;

        boost::shared_ptr<std::thread> hardware_connection_loop_thread;
        boost::shared_ptr<std::thread> can_connection_loop_thread;
        boost::shared_ptr<std::thread> dxl_connection_loop_thread;

        void manageHardwareConnectionLoop();
        void manageCanConnectionLoop();
        void manageDxlConnectionLoop();

        bool scanAndCheckMotors();

        // used when can or dxl is disabled
        double pos_can_disabled_v1[4] = { 0.0, 0.628, -1.4, 0.0 };
        double pos_dxl_disabled_v1[2] = { 0.0, 0.0 };

        double pos_can_disabled_v2[3] = { 0.0, 0.628, -1.4 };
        double pos_dxl_disabled_v2[3] = { 0.0, 0.0, 0.0 };

        // for new calibration request
        bool new_calibration_requested;

        bool gauss_comm_ok;
        bool can_comm_ok;
        bool dxl_comm_ok;
};


#endif

