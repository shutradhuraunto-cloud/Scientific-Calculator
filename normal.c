/**
 * Project Name: Scientific-Calculator
 * File Name   : normal.c
 * Author      : Aunto Chandro Bishawsharma
 * Description : Implements all Normal Calculator operations (+, -, *, /, %,
 *               Percentage, Power).
 */

#include "calculator.h"

void displayNormalMenu(void) {
    printf("\n--------------------------------------------------\n");
    printf("                NORMAL CALCULATOR                 \n");
    printf("--------------------------------------------------\n");
    printf("  [1] Addition        (+)                         \n");
    printf("  [2] Subtraction     (-)                         \n");
    printf("  [3] Multiplication  (*)                         \n");
    printf("  [4] Division        (/)                         \n");
    printf("  [5] Modulus         (%%) [Integers Only]        \n");
    printf("  [6] Percentage      (x%% of y)                  \n");
    printf("  [7] Power           (x^y)                       \n");
    printf("  [0] Back to Main Menu                           \n");
    printf("--------------------------------------------------\n");
}

void normalCalculatorMenu(void) {
    int choice = -1;
    do {
        displayNormalMenu();
        if (!getValidInt("Select an operation (0-7): ", &choice)) {
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: performAddition(); break;
            case 2: performSubtraction(); break;
            case 3: performMultiplication(); break;
            case 4: performDivision(); break;
            case 5: performModulus(); break;
            case 6: performPercentage(); break;
            case 7: performPower(); break;
            case 0: printf("\n[INFO] Returning to Main Menu...\n"); break;
            default: printf("\n[WARNING] Invalid operation! Choose between 0 and 7.\n"); break;
        }

        if (choice != 0) {
            printf("\nPress Enter to continue in Normal Calculator...");
            getchar();
        }
    } while (choice != 0);
}

void performAddition(void) {
    double num1, num2;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Addition (+)] ---\n");
    if (!getValidDouble("Enter first number  : ", &num1)) return;
    if (!getValidDouble("Enter second number : ", &num2)) return;

    double result = num1 + num2;
    printf(">> Result: %.4f + %.4f = %.4f\n", num1, num2, result);
    snprintf(record, sizeof(record), "[Normal] %.4f + %.4f = %.4f", num1, num2, result);
    addToHistory(record);
}

void performSubtraction(void) {
    double num1, num2;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Subtraction (-)] ---\n");
    if (!getValidDouble("Enter first number  : ", &num1)) return;
    if (!getValidDouble("Enter second number : ", &num2)) return;

    double result = num1 - num2;
    printf(">> Result: %.4f - %.4f = %.4f\n", num1, num2, result);
    snprintf(record, sizeof(record), "[Normal] %.4f - %.4f = %.4f", num1, num2, result);
    addToHistory(record);
}

void performMultiplication(void) {
    double num1, num2;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Multiplication (*)] ---\n");
    if (!getValidDouble("Enter first number  : ", &num1)) return;
    if (!getValidDouble("Enter second number : ", &num2)) return;

    double result = num1 * num2;
    printf(">> Result: %.4f * %.4f = %.4f\n", num1, num2, result);
    snprintf(record, sizeof(record), "[Normal] %.4f * %.4f = %.4f", num1, num2, result);
    addToHistory(record);
}

void performDivision(void) {
    double num1, num2;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Division (/)] ---\n");
    if (!getValidDouble("Enter dividend (top number)   : ", &num1)) return;
    if (!getValidDouble("Enter divisor (bottom number) : ", &num2)) return;

    if (fabs(num2) < 1e-15) {
        printf("\n[MATH ERROR] Division by zero is undefined!\n");
        return;
    }

    double result = num1 / num2;
    printf(">> Result: %.4f / %.4f = %.4f\n", num1, num2, result);
    snprintf(record, sizeof(record), "[Normal] %.4f / %.4f = %.4f", num1, num2, result);
    addToHistory(record);
}

void performModulus(void) {
    long num1, num2;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Modulus (%%)] ---\n");
    if (!getValidLong("Enter first integer  : ", &num1)) return;
    if (!getValidLong("Enter second integer : ", &num2)) return;

    if (num2 == 0) {
        printf("\n[MATH ERROR] Modulus by zero is undefined!\n");
        return;
    }

    long result = num1 % num2;
    printf(">> Result: %ld %% %ld = %ld\n", num1, num2, result);
    snprintf(record, sizeof(record), "[Normal] %ld %% %ld = %ld", num1, num2, result);
    addToHistory(record);
}

void performPercentage(void) {
    double total, percent;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Percentage (%%)] ---\n");
    if (!getValidDouble("Enter total value (e.g., 500)     : ", &total)) return;
    if (!getValidDouble("Enter percentage (e.g., 20 for 20%%): ", &percent)) return;

    double result = (total * percent) / 100.0;
    printf(">> Result: %.2f%% of %.4f = %.4f\n", percent, total, result);
    snprintf(record, sizeof(record), "[Normal] %.2f%% of %.4f = %.4f", percent, total, result);
    addToHistory(record);
}

void performPower(void) {
    double base, exponent;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Power (x^y)] ---\n");
    if (!getValidDouble("Enter base (x)     : ", &base)) return;
    if (!getValidDouble("Enter exponent (y) : ", &exponent)) return;

    if (base == 0.0 && exponent < 0.0) {
        printf("\n[MATH ERROR] Zero cannot be raised to a negative power!\n");
        return;
    }
    if (base < 0.0 && floor(exponent) != exponent) {
        printf("\n[MATH ERROR] Negative base with fractional exponent is complex!\n");
        return;
    }

    double result = pow(base, exponent);
    if (isinf(result)) {
        printf("\n[OVERFLOW ERROR] Result is too large (Infinity)!\n");
        return;
    }

    printf(">> Result: (%.4f) ^ (%.4f) = %.4f\n", base, exponent, result);
    snprintf(record, sizeof(record), "[Power] (%.4f)^(%.4f) = %.4f", base, exponent, result);
    addToHistory(record);
}