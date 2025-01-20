# IPSA_In513_RTOS
Depository for the final assignement of Embedded Systems.


# Final Assignment - Real-Time Operating System (RTOS) and Scheduling

## Project Overview

This project involves two main components:

1. **Task Scheduling Analysis**: Implements an EDF (Earliest Deadline First) algorithm for scheduling tasks and checking their schedulability.
2. **RTOS Implementation with FreeRTOS**: Implements a real-time operating system with FreeRTOS to handle multiple periodic tasks.

## Files

### 1. `scheduling_analysis.py` - Task Scheduling Analysis (EDF Algorithm)

This Python script analyzes the schedulability of a given task set using the EDF algorithm.

**Features**:
- **Schedulability Check**: Verifies whether the task set is schedulable under EDF by calculating the total utilization and comparing it to 1.
- **EDF Scheduling Simulation**: Simulates the task scheduling and generates a timeline to ensure deadlines are met.
- **Output**: Provides the scheduling timeline and verifies if deadlines are met or missed.

**Usage**:
- The script takes a set of tasks, each with a computation time and period.
- It checks if the task set is schedulable and generates the schedule accordingly.

---

### 2. `simple_RTOS.c` - FreeRTOS RTOS Implementation

This C program uses FreeRTOS to implement a real-time operating system (RTOS) handling five periodic tasks.

**Tasks**:
- **Task 1**: Periodically prints "Working" to indicate the system is running.
- **Task 2**: Converts Fahrenheit to Celsius.
- **Task 3**: Multiplies two large numbers and prints the result.
- **Task 4**: Performs binary search on a fixed array of 50 elements.
- **Task 5**: Monitors the keyboard for the "RESET" input and handles the state transition.

**Features**:
- **FreeRTOS Integration**: Utilizes FreeRTOS API for task creation, scheduling, and delays.
- **Task Priorities**: Tasks are assigned different priorities for scheduling.
- **Input Handling**: Task 5 monitors user input and handles state transitions.

**Usage**:
- Compile and run on a FreeRTOS-supported embedded system.
- Tasks will execute based on the defined periods, demonstrating real-time scheduling.

---

