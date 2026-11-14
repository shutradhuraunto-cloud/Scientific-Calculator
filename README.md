# Scientific + Normal Calculator in C

A modular, menu-driven **Scientific and Normal Calculator** built in C using industry-standard software engineering practices, defensive input validation, stateful angle-mode management, and persistent calculation history.

## Author
* **Aunto Chandro Bishawsharma**
* **GitHub Repository:** [Scientific-Calculator](https://github.com/shutradhuraunto-cloud/Scientific-Calculator)

---

## Features

### 1. Normal Calculator
* Addition (`+`), Subtraction (`-`), Multiplication (`*`), Division (`/`)
* Modulus (`%`), Percentage (`x% of y`), Power (`x^y`)

### 2. Scientific Calculator
* Square ($x^2$), Cube ($x^3$), Square Root ($\sqrt{x}$)
* Trigonometric Functions: $\sin(x)$, $\cos(x)$, $\tan(x)$
* Logarithmic Functions: $\log_{10}(x)$ and Natural Log $\ln(x)$
* Factorial ($x!$) up to $20!$ and Absolute Value ($|x|$)
* Direct Degree to Radian & Radian to Degree Converters

### 3. Additional Highlights
* **Degree & Radian Mode Toggle:** Dynamically switch between `DEG` and `RAD` modes.
* **Calculation History:** Stores history in a session array and permanently in `history.txt`.
* **Robust Error Handling:** Prevents crashes on invalid inputs, division by zero, negative square roots, and undefined tangents.

---

## Project Structure

* `calculator.h` - Function prototypes, macros, and shared declarations
* `main.c` - Application entry point, main menu, and input validation
* `normal.c` - Normal calculator operations
* `scientific.c` - Scientific calculator & Degree/Radian mode operations
* `history.c` - In-memory array & file-based calculation history

---

## How to Compile and Run

```bash
gcc main.c normal.c scientific.c history.c -o calculator.exe
.\calculator.exe
