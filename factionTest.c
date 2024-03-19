#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PID.h"

// Simulated system parameters
#define SIM_DT 0.001 // Simulation time step
#define SIM_MAX_TIME 10 // Maximum simulation time
#define MAX_INTEGRAL_TERM 0.01 // Maximum integral term
#define MAX_ERROR 100 // Maximum error

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

    if (error > MAX_ERROR)
        error = MAX_ERROR;
    else if (error < -MAX_ERROR)
        error = -MAX_ERROR;

    // Anti-windup: Limit integral term
    if (pid->integral > MAX_INTEGRAL_TERM)
        pid->integral = MAX_INTEGRAL_TERM;
    else if (pid->integral < -MAX_INTEGRAL_TERM)
        pid->integral = -MAX_INTEGRAL_TERM;

    // double derivative = (error - pid->prev_error) / SIM_DT;

    double derivative;
    if (pid->integral > MAX_INTEGRAL_TERM || pid->integral < -MAX_INTEGRAL_TERM) {
        // If integral term is saturated, scale down derivative term
        derivative = 0; // or any other appropriate value
    } else {
        derivative = (error - pid->prev_error) / SIM_DT;
    }

    double output = pid->KP * error + pid->KI * pid->integral + pid->KD * derivative;
    
    pid->prev_error = error;

    return output;
}


// Simulate the system
void SimulateSystem(PIDController *pid) {
    double position = 0; // Initial position
    double time = 0;     // Initial time

    FILE *f = fopen("time-position-signal.csv", "w+");

    while (time <= SIM_MAX_TIME) {

        double control_signal = PIDController_Update(pid, position);

        // Simulate system dynamics (simple integration)
        position += control_signal * SIM_DT;
        
        // Print current time and position
        printf("Time: %.2f, Position: %.2f, Setpoint: %.2f, Signal: %2f\n", time, position, pid->setpoint, control_signal);

        time += SIM_DT;

        // Write Time, Position, Signal, and Setpoint
        fprintf(f, "%f,%f,%f,%f\n", time, position, control_signal, pid->setpoint);

    }
}

// Ask User for Setpoint, KP, KI, KD
double UserInput(char *prompt) {
    double input = -1;
    while (input < 0) {
        printf("Enter the %s: ", prompt);
        scanf("%lf", &input);
        if (input < 0) {
            printf("Invalid input. Please enter a positive number.\n");
        }
    }
    return input;
}

int main() {

    // Initialize PID controller

    PIDController pid;
    
    // Ask User for Setpoint, KP, KI, KD

    double setpoint, KP, KI, KD;

    setpoint = UserInput("Setpoint");
    KP = UserInput("KP");
    KI = UserInput("KI");
    KD = UserInput("KD");

    // Initialize PID controller with setpoint, KP, KI, KD

    PIDController_Init(&pid, setpoint, KP, KI, KD); 

    SimulateSystem(&pid);

    printf("Done!\n");

    return 0;
}
