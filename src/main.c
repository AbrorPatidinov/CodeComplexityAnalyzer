#include "../includes/dependecies.h"

#define MAX_LINE_LENGTH 1000
#define MAX_FUNCTIONS 1000
#define new_line printf("\n")

typedef struct {
    char name[100];
    int start_line;
    int end_line;
    int cyclomatic_complexity;
} Function;

Function functions[MAX_FUNCTIONS];
int function_count = 0;

int calculate_cyclomatic_complexity(FILE *file, int start_line, int end_line) {
    char line[MAX_LINE_LENGTH];
    int complexity = 1;
    
    fseek(file, 0, SEEK_SET);
    for (int i = 1; i <= end_line; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        if (i < start_line) continue;
        
        if (strstr(line, "if") || strstr(line, "for") || strstr(line, "while") ||
            strstr(line, "case") || strstr(line, "&&") || strstr(line, "||") ||
            strstr(line, "?"))
            complexity++;
    }
    
    return complexity;
}

int is_function_declaration(const char *line) {
    return (strstr(line, "(") && strstr(line, ")") && !strstr(line, ";") &&
            !strstr(line, "typedef") && !strstr(line, "#define"));
}

void extract_function_name(const char *line, char *name) {
    const char *start = line;
    while (*start && !isalpha(*start)) start++;
    const char *end = strchr(start, '(');
    if (end) {
        while (end > start && !isalpha(*(end-1))) end--;
        strncpy(name, start, end - start);
        name[end - start] = '\0';
    } else {
        strcpy(name, "unknown");
    }
}

void analyze_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int in_function = 0;
    int brace_count = 0;
    char current_function[100] = "";
    
    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;
        
        if (!in_function && is_function_declaration(line)) {
            in_function = 1;
            brace_count = 0;
            extract_function_name(line, current_function);
            functions[function_count].start_line = line_count;
            strncpy(functions[function_count].name, current_function, sizeof(functions[function_count].name));
            printf("Function detected: %s at line %d\n", current_function, line_count);
        }
        
        if (in_function || strchr(line, '{')) {
            if (strchr(line, '{')) brace_count++;
            if (strchr(line, '}')) brace_count--;
            
            if (brace_count == 0 && in_function) {
                in_function = 0;
                functions[function_count].end_line = line_count;
                functions[function_count].cyclomatic_complexity = 
                    calculate_cyclomatic_complexity(file, functions[function_count].start_line, functions[function_count].end_line);
                printf("Function ended: %s at line %d\n", functions[function_count].name, line_count);
                function_count++;
            }
        }
    }
    
    printf("\nFile: %s\n", filename);
    printf("Total lines of code: %d\n", line_count);
    printf("Number of functions: %d\n\n", function_count);
    
    printf("Function Complexity Analysis:\n");
    printf("------------------------------\n");
    for (int i = 0; i < function_count; i++) {
        printf("Function: %s\n", functions[i].name);
        printf("  Lines: %d-%d\n", functions[i].start_line, functions[i].end_line);
        printf("  Cyclomatic Complexity: %d\n", functions[i].cyclomatic_complexity);
        printf("  Complexity Level: ");
        if (functions[i].cyclomatic_complexity <= 5) printf("Low\n");
        else if (functions[i].cyclomatic_complexity <= 10) printf("Moderate\n");
        else printf("High (Consider refactoring)\n");
        printf("\n");
    }
    
    printf("Complexity Visualization:\n");
    printf("-------------------------\n");
    for (int i = 0; i < function_count; i++) {
        printf("%-20s ", functions[i].name);
        for (int j = 0; j < functions[i].cyclomatic_complexity; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);  
        return 1;
    }

    // File analysis
    analyze_file(argv[1]);

    return EXIT_SUCCESS;
}