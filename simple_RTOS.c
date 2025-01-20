// CANOVAS Benjamin - 5TS1
// Final assignement - Système d'exploitation temps-réel pour l'embarqué

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Task priorities */
#define TASK_PERIODIC_PRIORITY             (tskIDLE_PRIORITY + 1)
#define TASK_FAHRENHEIT_PRIORITY           (tskIDLE_PRIORITY + 2)
#define TASK_MULTIPLY_PRIORITY             (tskIDLE_PRIORITY + 3)
#define TASK_BINARY_SEARCH_PRIORITY        (tskIDLE_PRIORITY + 4)
#define TASK_KEYBOARD_MONITOR_PRIORITY     (tskIDLE_PRIORITY + 5)

/* Task periods (in ms) */
#define TASK_PERIODIC_DELAY_MS             pdMS_TO_TICKS(1000)
#define TASK_FAHRENHEIT_DELAY_MS           pdMS_TO_TICKS(700)
#define TASK_MULTIPLY_DELAY_MS             pdMS_TO_TICKS(750)
#define TASK_BINARY_SEARCH_DELAY_MS        pdMS_TO_TICKS(700)
#define TASK_KEYBOARD_MONITOR_DELAY_MS     pdMS_TO_TICKS(200)

/* Helper function to read a character without waiting for Enter */
char getChar() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* Task 1: Periodic task to print "Working" */
static void vTaskPeriodic(void *pvParameters) {
    for (;;) {
        printf("Working\n");
        vTaskDelay(TASK_PERIODIC_DELAY_MS);
    }
}

/* Task 2: Convert Fahrenheit to Celsius */
static void vTaskFahrenheit2Celsius(void *pvParameters) {
    const float fahrenheit = 98.6;
    for (;;) {
        float celsius = (fahrenheit - 32) * 5.0 / 9.0;
        printf("%.1f °F is %.1f °C\n", fahrenheit, celsius);
        vTaskDelay(TASK_FAHRENHEIT_DELAY_MS);
    }
}

/* Task 3: Multiply two large integers and print the result */
static void vTaskMultiply(void *pvParameters) {
    unsigned long int num1 = 12345678;
    unsigned long int num2 = 87654321;
    for (;;) {
        unsigned long int result = num1 * num2;
        printf("Multiplication Result: %lu\n", result);
        vTaskDelay(TASK_MULTIPLY_DELAY_MS);
    }
}

/* Task 4: Perform binary search on a fixed array */
static void binary_search(int target) {
    int array[50];
    for (int i = 0; i < 50; i++) {
        array[i] = i + 1;
    }
    int left = 0, right = 49;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == target) {
            printf("Found %d at position %d\n", target, mid);
            return;
        }
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Value %d not found\n", target);
}

static void vTaskBinarySearch(void *pvParameters) {
    int target = 25;  // Fixed search target
    for (;;) {
        binary_search(target);
        vTaskDelay(TASK_BINARY_SEARCH_DELAY_MS);
    }
}

/* Task 5: Monitor keyboard and handle 'RESET' logic */
static void vTaskKeyboardMonitor(void *pvParameters) {
    int resetState = 0;
    char key;

    for (;;) {
        key = getChar();
        if (key == '1') {
            resetState = 1;
            printf("RESET Detected: %d\n", resetState);
        } else {
            resetState = 0;
            printf("RESET State: %d\n", resetState);
        }
        vTaskDelay(TASK_KEYBOARD_MONITOR_DELAY_MS);
    }
}

/* Main function */
int main(void) {
    /* Initialize the console */
    printf("Starting FreeRTOS Scheduler...\n");

    /* Create tasks */
    xTaskCreate(vTaskPeriodic, "PeriodicTask", configMINIMAL_STACK_SIZE, NULL, TASK_PERIODIC_PRIORITY, NULL);
    xTaskCreate(vTaskFahrenheit2Celsius, "FahrenheitTask", configMINIMAL_STACK_SIZE, NULL, TASK_FAHRENHEIT_PRIORITY, NULL);
    xTaskCreate(vTaskMultiply, "MultiplyTask", configMINIMAL_STACK_SIZE, NULL, TASK_MULTIPLY_PRIORITY, NULL);
    xTaskCreate(vTaskBinarySearch, "BinarySearchTask", configMINIMAL_STACK_SIZE, NULL, TASK_BINARY_SEARCH_PRIORITY, NULL);
    xTaskCreate(vTaskKeyboardMonitor, "KeyboardMonitor", configMINIMAL_STACK_SIZE, NULL, TASK_KEYBOARD_MONITOR_PRIORITY, NULL);

    /* Start scheduler */
    vTaskStartScheduler();

    /* Loop infinitely if the scheduler fails */
    for (;;) {}

    return 0;
}
