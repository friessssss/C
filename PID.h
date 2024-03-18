#include <stdio.h>

// Simulated system parameters
#define SIM_DT 0.1 // Simulation time step
#define SIM_MAX_TIME 10 // Maximum simulation time

typedef struct {
    // PID controller structure

    // Define Setpoint  
    double setpoint; // Desired setpoint

    // Define PID Gains
    double KP; // Proportional gain
    double KI; // Integral gain
    double KD; // Derivative gain

    // Define Integrator Limits
    double limMaxInt;

    double prev_error; // Previous error for calculating derivative
    double integral; // Integral term for integral control

} PIDController;

void PIDController_Init(PIDController *pid, double setpoint, double KP, double KI, double KD);
double PIDController_Update(PIDController *pid, double position);