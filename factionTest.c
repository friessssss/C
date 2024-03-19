#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PID.h"

// Simulated system parameters
#define SIM_DT 0.001 // Simulation time step
#define SIM_MAX_TIME 10 // Maximum simulation time
#define MAX_INTEGRAL_TERM 0.1 // Maximum integral term

// Initialize PID controller
void PIDController_Init(PIDController *pid, double setpoint, double KP, double KI, double KD, double output_max) {
    pid->setpoint = setpoint;
    pid->prev_error = 0;
    pid->integral = 0;
    pid->KP = KP;
    pid->KI = KI;
    pid->KD = KD;
    pid->output_max = output_max;;
}

// Update PID controller
// Inputs: PID controller, current position
// Output: Control signal
// Calculate control signal based on current position, setpoint, and PID gains
// Integral Gain is Saturated to prevent windup
// Output is limited to output_max and -output_max in order to prevent actuator saturation

double PIDController_Update(PIDController *pid, double position) {
    double error = pid->setpoint - position;
    pid->integral += error * SIM_DT;

    // Anti-windup: Limit integral term
    if (pid->integral > MAX_INTEGRAL_TERM)
        pid->integral = MAX_INTEGRAL_TERM;
    else if (pid->integral < -MAX_INTEGRAL_TERM)
        pid->integral = -MAX_INTEGRAL_TERM;

    double derivative = (error - pid->prev_error) / SIM_DT;

    double output = pid->KP * error + pid->KI * pid->integral + pid->KD * derivative;

    if (output > pid->output_max)
        output = pid->output_max;
    else if (output < -pid->output_max)
        output = -pid->output_max;
    
    pid->prev_error = error;

    return output;
}


// Simulate the system
// Inputs: PID controller
// Simulate the system dynamics and print the time, position, and control signal
// Write the time, position, control signal, and setpoint to a file
// Starting at t=0 and position=0, simulate the system to t=SIM_MAX_TIME with time step SIM_DT

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

        // Write Time, Position, Signal, and Setpoint
        fprintf(f, "%f,%f,%f,%f\n", time, position, control_signal, pid->setpoint);

        time += SIM_DT;

    }
}

// Ask User for Setpoint, KP, KI, KD
// Inputs: Prompt
// Output: User input
// Prompt the user to enter a positive number

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
    
    // Ask User for Setpoint, KP, KI, KD, Output Max
    double setpoint, KP, KI, KD, output_max, output_min;
    setpoint = UserInput("Setpoint");
    KP = UserInput("KP");
    KI = UserInput("KI");
    KD = UserInput("KD");
    output_max = UserInput("Output Max");

    // Initialize PID controller with setpoint, KP, KI, KD, output_max, output_min
    PIDController_Init(&pid, setpoint, KP, KI, KD, output_max); 


    // Simulate the system
    SimulateSystem(&pid);

    printf("Done!\n");

    return 0;
}
