/**
 * Project Name: Scientific-Calculator
 * File Name   : main.c
 * Phase       : Phase 5 & Phase 6 (History + Complete Error Handling)
 * Author      : Aunto Chandro Bishawsharma
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_HISTORY 100
#define MAX_RECORD_LEN 150
#define HISTORY_FILE "history.txt"

int isDegreeMode = 1;
char sessionHistory[MAX_HISTORY][MAX_RECORD_LEN];
int historyCount = 0;

// Function Prototypes
void displayMainMenu(void);
void toggleAngleMode(void);
const char* getAngleModeName(void);
void pauseExecution(void);
void clearScreen(void);
int getValidInt(const char *prompt, int *value);
int getValidDouble(const char *prompt, double *value);
int getValidLong(const char *prompt, long *value);

void historyMenu(void);
void displayHistoryMenu(void);
void addToHistory(const char *record);
void viewSessionHistory(void);
void viewPermanentHistory(void);
void clearAllHistory(void);

void normalCalculatorMenu(void);
void displayNormalMenu(void);
void performAddition(void);
void performSubtraction(void);
void performMultiplication(void);
void performDivision(void);
void performModulus(void);
void performPercentage(void);
void performPower(void);

void scientificCalculatorMenu(void);
void displayScientificMenu(void);
void performSquare(void);
void performCube(void);
void performSquareRoot(void);
void performSin(void);
void performCos(void);
void performTan(void);
void performLog10(void);
void performNaturalLog(void);
void performFactorial(void);
void performAbsoluteValue(void);
void convertDegToRad(void);
void convertRadToDeg(void);

int main(void) {
    int userChoice = -1;

    do {
        displayMainMenu();
        if (!getValidInt("Enter your choice (0-5): ", &userChoice)) {
            userChoice = -1;
            pauseExecution();
            continue;
        }

        switch (userChoice) {
            case 1:
                normalCalculatorMenu();
                break;
            case 2:
                scientificCalculatorMenu();
                break;
            case 3:
                toggleAngleMode();
                pauseExecution();
                break;
            case 4:
                historyMenu();
                break;
            case 5:
                clearScreen();
                printf("[INFO] Screen cleared successfully!\n");
                break;
            case 0:
                printf("\n==================================================\n");
                printf(" Thank you for using the Calculator. Goodbye!     \n");
                printf("==================================================\n");
                break;
            default:
                printf("\n[WARNING] Invalid choice! Please select between 0 and 5.\n");
                pauseExecution();
                break;
        }
    } while (userChoice != 0);

    return 0;
}

const char* getAngleModeName(void) {
    return isDegreeMode ? "DEGREE (DEG)" : "RADIAN (RAD)";
}

void toggleAngleMode(void) {
    isDegreeMode = !isDegreeMode;
    printf("\n[MODE CHANGED] Angle Mode is now set to: %s\n", getAngleModeName());
}

void displayMainMenu(void) {
    printf("\n==================================================\n");
    printf("       SCIENTIFIC + NORMAL CALCULATOR (v6.0)      \n");
    printf("       [Active Angle Mode: %-12s]          \n", getAngleModeName());
    printf("==================================================\n");
    printf("  [1] Normal Calculator      (+, -, *, /, %%, ^)  \n");
    printf("  [2] Scientific Calculator  (sin, cos, log, x!)  \n");
    printf("  [3] Switch Angle Mode      (DEG <-> RAD)        \n");
    printf("  [4] Calculation History    (View / Clear)       \n");
    printf("  [5] Clear Screen                                \n");
    printf("  [0] Exit Application                            \n");
    printf("--------------------------------------------------\n");
}

/* ================= HISTORY MODULE ================= */

void addToHistory(const char *record) {
    if (historyCount < MAX_HISTORY) {
        strncpy(sessionHistory[historyCount], record, MAX_RECORD_LEN - 1);
        sessionHistory[historyCount][MAX_RECORD_LEN - 1] = '\0';
        historyCount++;
    } else {
        int i;
        for (i = 1; i < MAX_HISTORY; i++) {
            strcpy(sessionHistory[i - 1], sessionHistory[i]);
        }
        strncpy(sessionHistory[MAX_HISTORY - 1], record, MAX_RECORD_LEN - 1);
        sessionHistory[MAX_HISTORY - 1][MAX_RECORD_LEN - 1] = '\0';
    }

    FILE *file = fopen(HISTORY_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", record);
        fclose(file);
    }
}

void displayHistoryMenu(void) {
    printf("\n--------------------------------------------------\n");
    printf("               CALCULATION HISTORY                \n");
    printf("--------------------------------------------------\n");
    printf("  [1] View Current Session History (Array)        \n");
    printf("  [2] View Permanent History       (history.txt)  \n");
    printf("  [3] Clear All History                           \n");
    printf("  [0] Back to Main Menu                           \n");
    printf("--------------------------------------------------\n");
}

void historyMenu(void) {
    int choice = -1;
    do {
        displayHistoryMenu();
        if (!getValidInt("Select an option (0-3): ", &choice)) {
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: viewSessionHistory(); break;
            case 2: viewPermanentHistory(); break;
            case 3: clearAllHistory(); break;
            case 0: printf("\n[INFO] Returning to Main Menu...\n"); break;
            default: printf("\n[WARNING] Invalid choice! Select between 0 and 3.\n"); break;
        }

        if (choice != 0) {
            printf("\nPress Enter to continue in History Menu...");
            getchar();
        }
    } while (choice != 0);
}

void viewSessionHistory(void) {
    int i;
    printf("\n--- [Current Session History (In-Memory Array)] ---\n");
    if (historyCount == 0) {
        printf("No calculations performed in this session yet.\n");
        return;
    }
    for (i = 0; i < historyCount; i++) {
        printf("  %2d. %s\n", i + 1, sessionHistory[i]);
    }
}

void viewPermanentHistory(void) {
    printf("\n--- [Permanent Calculation History (File: %s)] ---\n", HISTORY_FILE);
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        printf("No permanent history file found yet. Perform a calculation first!\n");
        return;
    }

    char line[MAX_RECORD_LEN];
    int lineNumber = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) > 0) {
            lineNumber++;
            printf("  %2d. %s\n", lineNumber, line);
        }
    }
    if (lineNumber == 0) {
        printf("History file is currently empty.\n");
    }
    fclose(file);
}

void clearAllHistory(void) {
    historyCount = 0;
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file != NULL) {
        fclose(file);
        printf("\n[SUCCESS] All Calculation History has been cleared!\n");
    } else {
        printf("\n[ERROR] Could not clear the history file!\n");
    }
}

/* ================= NORMAL CALCULATOR MODULE ================= */

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

/* ================= SCIENTIFIC CALCULATOR MODULE ================= */

void displayScientificMenu(void) {
    printf("\n--------------------------------------------------\n");
    printf("              SCIENTIFIC CALCULATOR               \n");
    printf("          [Current Mode: %-12s]            \n", getAngleModeName());
    printf("--------------------------------------------------\n");
    printf("  [1]  Square                  (x^2)              \n");
    printf("  [2]  Cube                    (x^3)              \n");
    printf("  [3]  Square Root             (sqrt(x))          \n");
    printf("  [4]  Power                   (x^y)              \n");
    printf("  [5]  Sine                    sin(x) [%s] \n", isDegreeMode ? "DEG" : "RAD");
    printf("  [6]  Cosine                  cos(x) [%s] \n", isDegreeMode ? "DEG" : "RAD");
    printf("  [7]  Tangent                 tan(x) [%s] \n", isDegreeMode ? "DEG" : "RAD");
    printf("  [8]  Log Base 10             log10(x)           \n");
    printf("  [9]  Natural Log             ln(x)              \n");
    printf("  [10] Factorial               (x!)   [0 to 20]   \n");
    printf("  [11] Absolute Value          |x|                \n");
    printf("  [12] Switch Angle Mode       (DEG <-> RAD)      \n");
    printf("  [13] Convert Degree -> Radian                   \n");
    printf("  [14] Convert Radian -> Degree                   \n");
    printf("  [0]  Back to Main Menu                          \n");
    printf("--------------------------------------------------\n");
}

void scientificCalculatorMenu(void) {
    int choice = -1;
    do {
        displayScientificMenu();
        if (!getValidInt("Select a scientific operation (0-14): ", &choice)) {
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:  performSquare(); break;
            case 2:  performCube(); break;
            case 3:  performSquareRoot(); break;
            case 4:  performPower(); break;
            case 5:  performSin(); break;
            case 6:  performCos(); break;
            case 7:  performTan(); break;
            case 8:  performLog10(); break;
            case 9:  performNaturalLog(); break;
            case 10: performFactorial(); break;
            case 11: performAbsoluteValue(); break;
            case 12: toggleAngleMode(); break;
            case 13: convertDegToRad(); break;
            case 14: convertRadToDeg(); break;
            case 0:  printf("\n[INFO] Returning to Main Menu...\n"); break;
            default: printf("\n[WARNING] Invalid choice! Select between 0 and 14.\n"); break;
        }

        if (choice != 0) {
            printf("\nPress Enter to continue in Scientific Calculator...");
            getchar();
        }
    } while (choice != 0);
}

void performSquare(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Square (x^2)] ---\n");
    if (!getValidDouble("Enter a number (x): ", &x)) return;

    double result = x * x;
    printf(">> Result: (%.4f)^2 = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] (%.4f)^2 = %.4f", x, result);
    addToHistory(record);
}

void performCube(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Cube (x^3)] ---\n");
    if (!getValidDouble("Enter a number (x): ", &x)) return;

    double result = x * x * x;
    printf(">> Result: (%.4f)^3 = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] (%.4f)^3 = %.4f", x, result);
    addToHistory(record);
}

void performSquareRoot(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Square Root (sqrt)] ---\n");
    if (!getValidDouble("Enter a non-negative number (x): ", &x)) return;

    if (x < 0.0) {
        printf("\n[MATH ERROR] Square root of a negative number is undefined!\n");
        return;
    }

    double result = sqrt(x);
    printf(">> Result: sqrt(%.4f) = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] sqrt(%.4f) = %.4f", x, result);
    addToHistory(record);
}

void performSin(void) {
    double inputAngle, radians;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Sine: sin(x) | Mode: %s] ---\n", getAngleModeName());

    if (isDegreeMode) {
        if (!getValidDouble("Enter angle in Degrees : ", &inputAngle)) return;
        radians = inputAngle * (M_PI / 180.0);
    } else {
        if (!getValidDouble("Enter angle in Radians : ", &inputAngle)) return;
        radians = inputAngle;
    }

    double result = sin(radians);
    if (fabs(result) < 1e-12) result = 0.0;

    printf(">> Result: sin(%.4f %s) = %.4f\n", inputAngle, isDegreeMode ? "deg" : "rad", result);
    snprintf(record, sizeof(record), "[Scientific] sin(%.4f %s) = %.4f",
             inputAngle, isDegreeMode ? "deg" : "rad", result);
    addToHistory(record);
}

void performCos(void) {
    double inputAngle, radians;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Cosine: cos(x) | Mode: %s] ---\n", getAngleModeName());

    if (isDegreeMode) {
        if (!getValidDouble("Enter angle in Degrees : ", &inputAngle)) return;
        radians = inputAngle * (M_PI / 180.0);
    } else {
        if (!getValidDouble("Enter angle in Radians : ", &inputAngle)) return;
        radians = inputAngle;
    }

    double result = cos(radians);
    if (fabs(result) < 1e-12) result = 0.0;

    printf(">> Result: cos(%.4f %s) = %.4f\n", inputAngle, isDegreeMode ? "deg" : "rad", result);
    snprintf(record, sizeof(record), "[Scientific] cos(%.4f %s) = %.4f",
             inputAngle, isDegreeMode ? "deg" : "rad", result);
    addToHistory(record);
}

void performTan(void) {
    double inputAngle, radians;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Tangent: tan(x) | Mode: %s] ---\n", getAngleModeName());

    if (isDegreeMode) {
        if (!getValidDouble("Enter angle in Degrees : ", &inputAngle)) return;
        radians = inputAngle * (M_PI / 180.0);
    } else {
        if (!getValidDouble("Enter angle in Radians : ", &inputAngle)) return;
        radians = inputAngle;
    }

    if (fabs(cos(radians)) < 1e-12) {
        printf("\n[MATH ERROR] tan(%.4f %s) is undefined (Division by zero)!\n",
               inputAngle, isDegreeMode ? "deg" : "rad");
        return;
    }

    double result = tan(radians);
    if (fabs(result) < 1e-12) result = 0.0;

    printf(">> Result: tan(%.4f %s) = %.4f\n", inputAngle, isDegreeMode ? "deg" : "rad", result);
    snprintf(record, sizeof(record), "[Scientific] tan(%.4f %s) = %.4f",
             inputAngle, isDegreeMode ? "deg" : "rad", result);
    addToHistory(record);
}

void performLog10(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Logarithm Base 10: log10(x)] ---\n");
    if (!getValidDouble("Enter a positive number (x > 0): ", &x)) return;

    if (x <= 0.0) {
        printf("\n[MATH ERROR] Logarithm of zero or negative number is undefined!\n");
        return;
    }

    double result = log10(x);
    printf(">> Result: log10(%.4f) = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] log10(%.4f) = %.4f", x, result);
    addToHistory(record);
}

void performNaturalLog(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Natural Logarithm: ln(x)] ---\n");
    if (!getValidDouble("Enter a positive number (x > 0): ", &x)) return;

    if (x <= 0.0) {
        printf("\n[MATH ERROR] Natural log of zero or negative number is undefined!\n");
        return;
    }

    double result = log(x);
    printf(">> Result: ln(%.4f) = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] ln(%.4f) = %.4f", x, result);
    addToHistory(record);
}

void performFactorial(void) {
    long n;
    long i;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Factorial (x!)] ---\n");
    if (!getValidLong("Enter a whole number (0 to 20): ", &n)) return;

    if (n < 0) {
        printf("\n[MATH ERROR] Factorial of a negative number is undefined!\n");
        return;
    }
    if (n > 20) {
        printf("\n[OVERFLOW ERROR] Maximum supported value is 20!\n");
        return;
    }

    double fact = 1.0;
    for (i = 1; i <= n; i++) {
        fact *= (double)i;
    }

    printf(">> Result: %ld! = %.0f\n", n, fact);
    snprintf(record, sizeof(record), "[Scientific] %ld! = %.0f", n, fact);
    addToHistory(record);
}

void performAbsoluteValue(void) {
    double x;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Absolute Value |x|] ---\n");
    if (!getValidDouble("Enter any number (x): ", &x)) return;

    double result = fabs(x);
    printf(">> Result: |%.4f| = %.4f\n", x, result);
    snprintf(record, sizeof(record), "[Scientific] |%.4f| = %.4f", x, result);
    addToHistory(record);
}

void convertDegToRad(void) {
    double deg;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Degree to Radian Converter] ---\n");
    if (!getValidDouble("Enter angle in Degrees: ", &deg)) return;

    double rad = deg * (M_PI / 180.0);
    printf(">> Result: %.4f deg = %.6f rad\n", deg, rad);
    snprintf(record, sizeof(record), "[Convert] %.4f deg = %.6f rad", deg, rad);
    addToHistory(record);
}

void convertRadToDeg(void) {
    double rad;
    char record[MAX_RECORD_LEN];
    printf("\n--- [Radian to Degree Converter] ---\n");
    if (!getValidDouble("Enter angle in Radians: ", &rad)) return;

    double deg = rad * (180.0 / M_PI);
    printf(">> Result: %.6f rad = %.4f deg\n", rad, deg);
    snprintf(record, sizeof(record), "[Convert] %.6f rad = %.4f deg", rad, deg);
    addToHistory(record);
}

/* ================= STRICT INPUT VALIDATION ================= */

int getValidInt(const char *prompt, int *value) {
    char buffer[100];
    char *endptr;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    char *start = buffer;
    while (isspace((unsigned char)*start)) start++;

    if (*start == '\0') {
        printf("\n[INPUT ERROR] Input cannot be empty! Please enter a number.\n");
        return 0;
    }

    errno = 0;
    long parsed = strtol(start, &endptr, 10);
    while (isspace((unsigned char)*endptr)) endptr++;

    if (endptr == start || *endptr != '\0' || errno == ERANGE) {
        printf("\n[INPUT ERROR] Invalid integer input! Do not mix letters or symbols.\n");
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int getValidDouble(const char *prompt, double *value) {
    char buffer[100];
    char *endptr;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    char *start = buffer;
    while (isspace((unsigned char)*start)) start++;

    if (*start == '\0') {
        printf("\n[INPUT ERROR] Input cannot be empty! Operation cancelled.\n");
        return 0;
    }

    errno = 0;
    double parsed = strtod(start, &endptr);
    while (isspace((unsigned char)*endptr)) endptr++;

    if (endptr == start || *endptr != '\0' || errno == ERANGE || isnan(parsed) || isinf(parsed)) {
        printf("\n[INPUT ERROR] Invalid numeric value! Please enter a valid number.\n");
        return 0;
    }

    *value = parsed;
    return 1;
}

int getValidLong(const char *prompt, long *value) {
    char buffer[100];
    char *endptr;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    char *start = buffer;
    while (isspace((unsigned char)*start)) start++;

    if (*start == '\0') {
        printf("\n[INPUT ERROR] Input cannot be empty! Operation cancelled.\n");
        return 0;
    }

    errno = 0;
    long parsed = strtol(start, &endptr, 10);
    while (isspace((unsigned char)*endptr)) endptr++;

    if (endptr == start || *endptr != '\0' || errno == ERANGE) {
        printf("\n[INPUT ERROR] Whole integer required! Decimals or letters not allowed.\n");
        return 0;
    }

    *value = parsed;
    return 1;
}

void pauseExecution(void) {
    printf("\nPress Enter to return to the Main Menu...");
    getchar();
}

void clearScreen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}