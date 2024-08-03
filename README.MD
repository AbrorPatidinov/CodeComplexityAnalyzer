# C Code Analyzer

This program analyzes C code files to calculate the cyclomatic complexity of individual functions. Cyclomatic complexity is a software metric used to indicate the complexity of a program. It is a quantitative measure of the number of linearly independent paths through a program's source code.

## How to Compile and Run

1. **Compile the code:**
   ```bash
   gcc your_program.c -o code_analyzer
   ./code_analyzer <your_c_file.c>

Replace <your_c_file.c> with the actual name of your C source code file.

Functionality
  Function Identification: The program identifies functions within the C code, even if they span multiple lines.
  Cyclomatic Complexity Calculation: For each identified function, the program calculates the cyclomatic complexity based 3.on the number of decision points (if, else, switch, for, while, etc.) and logical operators (&&, ||).
  
  Complexity Level Classification: Functions are categorized into three complexity levels:
  Low: Cyclomatic complexity <= 5
  
  Moderate: Cyclomatic complexity between 6 and 10
  High (Consider refactoring): Cyclomatic complexity > 10
  
  Output: The program provides a well-formatted output:
  Total lines of code in the analyzed file.
  
  Total number of functions detected.
  For each function:
  
  Function name
  Starting and ending line numbers
  
  Calculated cyclomatic complexity
  Assigned complexity level
  A visual representation of complexity using asterisks.

