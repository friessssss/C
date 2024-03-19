#include <stdio.h>

typedef struct {
    // PID controller structure

    // Define Setpoint  
    double setpoint; // Desired setpoint

    // Define PID Gains
    double KP; // Proportional gain
    double KI; // Integral gain
    double KD; // Derivative gain

    // Define PID Output Limits
    double output_max; // Maximum output

    double prev_error; // Previous error for calculating derivative
    double integral; // Integral term for integral control

} PIDController;

void PIDController_Init(PIDController *pid, double setpoint, double KP, double KI, double KD, double output_max);
double PIDController_Update(PIDController *pid, double position);