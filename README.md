# cFSM Framework - c Finite State Machine Framework

## Overview
Plain c Finite State Machine Framework library for using in the host devices, and is suitable for all embedded devices(RTOS, Linux, etc.).

## Supported FSM types

Flat state machine example

![cfsm](/cFSM.svg)

## Licensing
[cFSM](https://github.com/Junbo-Zheng/cFSM) is licensed under the Apache license, check the [LICENSE](./LICENSE) file.

## Getting Started
Clone the repo, install dependencies, and serve:
```bash
git clone git@github.com:Junbo-Zheng/cFSM.git
sudo apt-get install -y cmake gcc ninja-build
```

## Build on Ubuntu22.04
```bash
cmake -S . -Bbuild -GNinja
cmake --build build -j20
./build/simple
```

## Simple Run
```bash
➜  /home/mi/local/c_fsm git:(master) ✗ ./build/simple
turn to low_entry
initial state: low
--------------------------------------------------
processing state: 0, event: 1, state name: low
low_callback with event: 1
exiting from low_exit
turn to mid_entry
--------------------------------------------------
processing state: 1, event: 2, state name: mid
mid_callback with event: 2
exiting from mid_exit
turn to high_entry
--------------------------------------------------
processing state: 2, event: 3, state name: high
high_callback with event: 3
state out of bounds, resetting to low state and exit
```

## Contribute
Anyone is welcome to contribute. Simply fork this repository, make your changes in an own branch and create a pull-request for your change. Please do only one change per pull-request.

You found a bug? Please fill out an issue and include any data to reproduce the bug.
