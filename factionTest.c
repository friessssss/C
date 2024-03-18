#include <stdio.h>
#include "PID.h"

// Simulated system parameters
#define SIM_DT 0.1 // Simulation time step
#define SIM_MAX_TIME 10 // Maximum simulation time

// Initialize PID controller
void PIDController_Init(PIDController *pid, double setpoint, double KP, double KI, double KD) {
    pid->setpoint = setpoint;
    pid->prev_error = 0;
    pid->integral = 0;
    pid->KP = KP;
    pid->KI = KI;
    pid->KD = KD;
}

// Update PID controller
double PIDController_Update(PIDController *pid, double position) {
    double error = pid->setpoint - position;
    pid->integral += error * SIM_DT;
    double derivative = (error - pid->prev_error) / SIM_DT;
    double output = pid->KP * error + pid->KI * pid->integral + pid->KD * derivative;
    
    pid->prev_error = error;

    return output;
}


// Simulate the system
void SimulateSystem(PIDController *pid) {
    double position = 0; // Initial position
    double time = 0;

    while (time <= SIM_MAX_TIME) {
        double control_signal = PIDController_Update(pid, position);
        // Simulate system dynamics (simple integration)
        position += control_signal * SIM_DT;
        
        // Print current time and position
        printf("Time: %.2f, Position: %.2f\n", time, position);

        time += SIM_DT;
    }
}

int main() {
    PIDController pid;
    PIDController_Init(&pid, 10.0, 2, 0.1, 0.5); // Initialize PID controller with setpoint

    SimulateSystem(&pid);

    printf("Done!\n");

    return 0;
}
