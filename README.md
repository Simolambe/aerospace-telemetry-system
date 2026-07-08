# Mini Telemetry System

A lightweight aerospace telemetry simulator written in C.

## Overview

This project simulates a basic flight telemetry communication system. A sender application generates realistic aircraft telemetry
data and transmits packets through UDP, while a receiver application listens for incoming packets and displays the received information.

## Features

* UDP communication between sender and receiver
* Real-time telemetry transmission
* Simulated flight parameters:

  * Temperature
  * Pressure
  * Roll, pitch and yaw angles
  * Airspeed
  * Altitude
* Lightweight C implementation using POSIX sockets

## Technologies

* C
* UDP sockets
* Linux / WSL environment
* GCC compiler

## How to run

Compile the receiver:
gcc receiver.c -o receiver

Compile the sender:
gcc sender.c telemetry.c -o sender

Run the receiver first:
./receiver

Then start the sender:
./sender
./sender
```
