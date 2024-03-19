
# README

The purpose of this project was to design a PID Controller in C while retaining MISRA C Compliance

## Usage

The program asks for a user input using 'scanf()' which allows input through the terminal. On MacOS, this is a bit more complex and needs a prepared launch.json file to operate properly in VSCode.

The program outputs a CSV file named 'time-position-signal.csv' which includes Time, Position, Signal, and the Setpoint of the system. This file gets overwritten each runtime so if need, rename the file after a simulation.

In order to graph the response, run the factionPlot.py


