#include "Aeroki.h"

#define MAX_VARIABLES 100
#define MAX_FUNCTIONS 50
#define MAX_LINE_LENGTH 1024

// Global variables
Variable variables[MAX_VARIABLES];
Function functions[MAX_FUNCTIONS];
int var_count = 0;
int func_count = 0;

// === Utility Functions ===
void ltrim(char *str) {
    int index = 0;
    while (str[index] == ' ' || str[index] == '\t') index++;
    if (index > 0) {
        int i = 0;
        while (str[index]) str[i++] = str[index++];
        str[i] = '\0';
    }
}

void rtrim(char *str) {
    int index = strlen(str) - 1;
    while (index >= 0 && (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')) {
        str[index--] = '\0';
    }
}

void trim(char *str) {
    ltrim(str);
    rtrim(str);
}

bool is_number(const char *str) {
    if (!str || !*str) return false;
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

bool is_float(const char *str) {
    if (!str || !*str) return false;
    char *endptr;
    strtod(str, &endptr);
    return *endptr == '\0';
}

// === Variable Management ===
Variable* get_variable_ptr(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

int get_int_variable(const char *name) {
    Variable *var = get_variable_ptr(name);
    if (!var) {
        fprintf(stderr, "ไม่พบตัวแปร: %s\n", name);
        return 0;
    }
    if (var->type == TYPE_INT) return var->value.int_val;
    if (var->type == TYPE_FLOAT) return (int)var->value.float_val;
    if (var->type == TYPE_BOOLEAN) return var->value.bool_val ? 1 : 0;
    return 0;
}

double get_float_variable(const char *name) {
    Variable *var = get_variable_ptr(name);
    if (!var) {
        fprintf(stderr, "ไม่พบตัวแปร: %s\n", name);
        return 0.0;
    }
    if (var->type == TYPE_FLOAT) return var->value.float_val;
    if (var->type == TYPE_INT) return (double)var->value.int_val;
    return 0.0;
}

char* get_string_variable(const char *name) {
    Variable *var = get_variable_ptr(name);
    if (!var) {
        fprintf(stderr, "ไม่พบตัวแปร: %s\n", name);
        return "";
    }
    if (var->type == TYPE_STRING) return var->value.string_val;
    return "";
}

bool get_bool_variable(const char *name) {
    Variable *var = get_variable_ptr(name);
    if (!var) {
        fprintf(stderr, "ไม่พบตัวแปร: %s\n", name);
        return false;
    }
    if (var->type == TYPE_BOOLEAN) return var->value.bool_val;
    if (var->type == TYPE_INT) return var->value.int_val != 0;
    return false;
}

void set_int_variable(const char *name, int value) {
    Variable *var = get_variable_ptr(name);
    if (var) {
        var->type = TYPE_INT;
        var->value.int_val = value;
        return;
    }
    
    if (var_count < MAX_VARIABLES) {
        strcpy(variables[var_count].name, name);
        variables[var_count].type = TYPE_INT;
        variables[var_count].value.int_val = value;
        var_count++;
    } else {
        fprintf(stderr, "ตัวแปรเต็มแล้ว\n");
    }
}

void set_float_variable(const char *name, double value) {
    Variable *var = get_variable_ptr(name);
    if (var) {
        var->type = TYPE_FLOAT;
        var->value.float_val = value;
        return;
    }
    
    if (var_count < MAX_VARIABLES) {
        strcpy(variables[var_count].name, name);
        variables[var_count].type = TYPE_FLOAT;
        variables[var_count].value.float_val = value;
        var_count++;
    } else {
        fprintf(stderr, "ตัวแปรเต็มแล้ว\n");
    }
}

void set_string_variable(const char *name, const char *value) {
    Variable *var = get_variable_ptr(name);
    if (var) {
        var->type = TYPE_STRING;
        strcpy(var->value.string_val, value);
        return;
    }
    
    if (var_count < MAX_VARIABLES) {
        strcpy(variables[var_count].name, name);
        variables[var_count].type = TYPE_STRING;
        strcpy(variables[var_count].value.string_val, value);
        var_count++;
    } else {
        fprintf(stderr, "ตัวแปรเต็มแล้ว\n");
    }
}

void set_bool_variable(const char *name, bool value) {
    Variable *var = get_variable_ptr(name);
    if (var) {
        var->type = TYPE_BOOLEAN;
        var->value.bool_val = value;
        return;
    }
    
    if (var_count < MAX_VARIABLES) {
        strcpy(variables[var_count].name, name);
        variables[var_count].type = TYPE_BOOLEAN;
        variables[var_count].value.bool_val = value;
        var_count++;
    } else {
        fprintf(stderr, "ตัวแปรเต็มแล้ว\n");
    }
}

void clear_memory() {
    var_count = 0;
    func_count = 0;
    printf("ล้างหน่วยความจำแล้ว (Memory cleared)\n");
}

// === Math Functions ===
double math_function(const char *func, double val) {
    if (strcmp(func, "sin") == 0) return sin(val);
    if (strcmp(func, "cos") == 0) return cos(val);
    if (strcmp(func, "tan") == 0) return tan(val);
    if (strcmp(func, "sqrt") == 0 || strcmp(func, "รากที่สอง") == 0) return sqrt(val);
    if (strcmp(func, "log") == 0) return log(val);
    if (strcmp(func, "abs") == 0 || strcmp(func, "สัมบูรณ์") == 0) return fabs(val);
    if (strcmp(func, "floor") == 0 || strcmp(func, "ปัดลง") == 0) return floor(val);
    if (strcmp(func, "ceil") == 0 || strcmp(func, "ปัดขึ้น") == 0) return ceil(val);
    return val;
}

// === String Functions ===
char* string_function(const char *func, const char *str) {
    static char result[256];
    strcpy(result, str);
    
    if (strcmp(func, "uppercase") == 0 || strcmp(func, "ตัวใหญ่") == 0) {
        for (int i = 0; result[i]; i++) {
            result[i] = toupper(result[i]);
        }
    } else if (strcmp(func, "lowercase") == 0 || strcmp(func, "ตัวเล็ก") == 0) {
        for (int i = 0; result[i]; i++) {
            result[i] = tolower(result[i]);
        }
    }
    
    return result;
}

// === Comparison Functions ===
int compare_values(const char *left, const char *op, const char *right) {
    // Try to parse as numbers first
    if (is_number(left) && is_number(right)) {
        int l = atoi(left);
        int r = atoi(right);
        
        if (strcmp(op, "==") == 0 || strcmp(op, "เท่ากับ") == 0) return l == r;
        if (strcmp(op, "!=") == 0 || strcmp(op, "ไม่เท่ากับ") == 0) return l != r;
        if (strcmp(op, "<") == 0 || strcmp(op, "น้อยกว่า") == 0) return l < r;
        if (strcmp(op, ">") == 0 || strcmp(op, "มากกว่า") == 0) return l > r;
        if (strcmp(op, "<=") == 0 || strcmp(op, "น้อยกว่าหรือเท่ากับ") == 0) return l <= r;
        if (strcmp(op, ">=") == 0 || strcmp(op, "มากกว่าหรือเท่ากับ") == 0) return l >= r;
    } else {
        // String comparison
        int cmp = strcmp(left, right);
        if (strcmp(op, "==") == 0 || strcmp(op, "เท่ากับ") == 0) return cmp == 0;
        if (strcmp(op, "!=") == 0 || strcmp(op, "ไม่เท่ากับ") == 0) return cmp != 0;
        if (strcmp(op, "<") == 0 || strcmp(op, "น้อยกว่า") == 0) return cmp < 0;
        if (strcmp(op, ">") == 0 || strcmp(op, "มากกว่า") == 0) return cmp > 0;
        if (strcmp(op, "<=") == 0 || strcmp(op, "น้อยกว่าหรือเท่ากับ") == 0) return cmp <= 0;
        if (strcmp(op, ">=") == 0 || strcmp(op, "มากกว่าหรือเท่ากับ") == 0) return cmp >= 0;
    }
    return 0;
}

bool evaluate_condition(const char *condition) {
    char left[64], op[16], right[64];
    
    // Handle variable names in condition
    if (sscanf(condition, "%s %s %s", left, op, right) == 3) {
        char left_val[64], right_val[64];
        
        // Get actual values for variables
        Variable *left_var = get_variable_ptr(left);
        if (left_var) {
            if (left_var->type == TYPE_INT) {
                snprintf(left_val, sizeof(left_val), "%d", left_var->value.int_val);
            } else if (left_var->type == TYPE_STRING) {
                strcpy(left_val, left_var->value.string_val);
            } else if (left_var->type == TYPE_BOOLEAN) {
                strcpy(left_val, left_var->value.bool_val ? "จริง" : "เท็จ");
            }
        } else {
            strcpy(left_val, left);
        }
        
        Variable *right_var = get_variable_ptr(right);
        if (right_var) {
            if (right_var->type == TYPE_INT) {
                snprintf(right_val, sizeof(right_val), "%d", right_var->value.int_val);
            } else if (right_var->type == TYPE_STRING) {
                strcpy(right_val, right_var->value.string_val);
            } else if (right_var->type == TYPE_BOOLEAN) {
                strcpy(right_val, right_var->value.bool_val ? "จริง" : "เท็จ");
            }
        } else {
            strcpy(right_val, right);
        }
        
        return compare_values(left_val, op, right_val);
    }
    return false;
}

// === Command Handlers ===

// Enhanced variable assignment with type detection
void handle_hai(char *line) {
    char varname[32];
    char value_str[256];
    
    // Integer assignment: ให้ x = 10
    int int_value;
    if (sscanf(line, "ให้ %s = %d", varname, &int_value) == 2) {
        set_int_variable(varname, int_value);
        return;
    }
    
    // Float assignment: ให้ x = 10.5
    double float_value;
    if (sscanf(line, "ให้ %s = %lf", varname, &float_value) == 2) {
        set_float_variable(varname, float_value);
        return;
    }
    
    // String assignment: ให้ x = "hello"
    if (sscanf(line, "ให้ %s = \"%[^\"]\"", varname, value_str) == 2) {
        set_string_variable(varname, value_str);
        return;
    }
    
    // Boolean assignment: ให้ x = จริง/เท็จ
    if (sscanf(line, "ให้ %s = %s", varname, value_str) == 2) {
        if (strcmp(value_str, "จริง") == 0 || strcmp(value_str, "true") == 0) {
            set_bool_variable(varname, true);
        } else if (strcmp(value_str, "เท็จ") == 0 || strcmp(value_str, "false") == 0) {
            set_bool_variable(varname, false);
        }
        return;
    }
}

// Enhanced display and calculation
void handle_ha(char *line) {
    char left[32], right[32], func[32];
    char op;
    double val;
    
    // Math functions: หา sin(x) or หา รากที่สอง(25)
    if (sscanf(line, "หา %[^(](%lf)", func, &val) == 2) {
        double result = math_function(func, val);
        printf("%.2f\n", result);
        return;
    }
    
    // Math functions with variables: หา sin(x)
    if (sscanf(line, "หา %[^(](%[^)])", func, left) == 2) {
        Variable *var = get_variable_ptr(left);
        if (var && (var->type == TYPE_INT || var->type == TYPE_FLOAT)) {
            double val = (var->type == TYPE_INT) ? var->value.int_val : var->value.float_val;
            double result = math_function(func, val);
            printf("%.2f\n", result);
            return;
        }
    }
    
    // Arithmetic operations: หา x + y
    if (sscanf(line, "หา %s %c %s", left, &op, right) == 3) {
        Variable *left_var = get_variable_ptr(left);
        Variable *right_var = get_variable_ptr(right);
        
        if (left_var && right_var) {
            if (left_var->type == TYPE_INT && right_var->type == TYPE_INT) {
                int a = left_var->value.int_val;
                int b = right_var->value.int_val;
                int result = 0;
                
                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = (b != 0) ? a / b : 0; break;
                    case '%': result = (b != 0) ? a % b : 0; break;
                    default: return;
                }
                printf("%d\n", result);
                return;
            } else {
                // Handle float operations
                double a = (left_var->type == TYPE_INT) ? left_var->value.int_val : left_var->value.float_val;
                double b = (right_var->type == TYPE_INT) ? right_var->value.int_val : right_var->value.float_val;
                double result = 0;
                
                switch (op) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/': result = (b != 0) ? a / b : 0; break;
                    default: return;
                }
                printf("%.2f\n", result);
                return;
            }
        }
    }
    
    // Display single variable: หา x
    char varname[32];
    if (sscanf(line, "หา %s", varname) == 1) {
        Variable *var = get_variable_ptr(varname);
        if (var) {
            switch (var->type) {
                case TYPE_INT:
                    printf("%d\n", var->value.int_val);
                    break;
                case TYPE_FLOAT:
                    printf("%.2f\n", var->value.float_val);
                    break;
                case TYPE_STRING:
                    printf("%s\n", var->value.string_val);
                    break;
                case TYPE_BOOLEAN:
                    printf("%s\n", var->value.bool_val ? "จริง" : "เท็จ");
                    break;
            }
        } else {
            fprintf(stderr, "ไม่พบตัวแปร: %s\n", varname);
        }
    }
}

// Enhanced input handling
void handle_rubka(char *line) {
    char varname[32];
    if (sscanf(line, "รับค่า %s", varname) == 1) {
        char input[256];
        printf("กรอกค่า %s: ", varname);
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            trim(input);
            
            // Try to determine type
            if (is_number(input)) {
                set_int_variable(varname, atoi(input));
            } else if (is_float(input)) {
                set_float_variable(varname, atof(input));
            } else if (strcmp(input, "จริง") == 0 || strcmp(input, "true") == 0) {
                set_bool_variable(varname, true);
            } else if (strcmp(input, "เท็จ") == 0 || strcmp(input, "false") == 0) {
                set_bool_variable(varname, false);
            } else {
                set_string_variable(varname, input);
            }
        }
    }
}

// Print statement: แสดง "hello world" or แสดง x
void handle_print(char *line) {
    char text[256], varname[32];
    
    // Print string literal: แสดง "hello"
    if (sscanf(line, "แสดง \"%[^\"]\"", text) == 1) {
        printf("%s\n", text);
        return;
    }
    
    // Print variable: แสดง x
    if (sscanf(line, "แสดง %s", varname) == 1) {
        Variable *var = get_variable_ptr(varname);
        if (var) {
            switch (var->type) {
                case TYPE_INT:
                    printf("%d\n", var->value.int_val);
                    break;
                case TYPE_FLOAT:
                    printf("%.2f\n", var->value.float_val);
                    break;
                case TYPE_STRING:
                    printf("%s\n", var->value.string_val);
                    break;
                case TYPE_BOOLEAN:
                    printf("%s\n", var->value.bool_val ? "จริง" : "เท็จ");
                    break;
            }
        } else {
            fprintf(stderr, "ไม่พบตัวแปร: %s\n", varname);
        }
    }
}

// Conditional statements: ถ้า x > 5 แล้ว แสดง "big"
void handle_tha(char *line) {
    char condition[128], action[128];
    
    if (sscanf(line, "ถ้า %[^แ] แล้ว %[^\n]", condition, action) == 2) {
        trim(condition);
        trim(action);
        
        if (evaluate_condition(condition)) {
            // Execute the action
            if (strncmp(action, "แสดง", 12) == 0) {
                handle_print(action);
            } else if (strncmp(action, "ให้", 6) == 0) {
                handle_hai(action);
            } else if (strncmp(action, "หา", 6) == 0) {
                handle_ha(action);
            }
        }
    }
}

// Comments: // this is a comment or # this is a comment
void handle_comment(char *line) {
    // Comments are ignored in processing
    return;
}

// Simple loop: วนลูป i จาก 1 ถึง 5 ทำ แสดง i
void handle_loop(char *line) {
    char varname[32], start_str[32], end_str[32], action[256];
    int start, end;
    
    if (sscanf(line, "วนลูป %s จาก %s ถึง %s ทำ %[^\n]", varname, start_str, end_str, action) == 4) {
        start = is_number(start_str) ? atoi(start_str) : get_int_variable(start_str);
        end = is_number(end_str) ? atoi(end_str) : get_int_variable(end_str);
        
        for (int i = start; i <= end; i++) {
            set_int_variable(varname, i);
            
            // Execute action
            if (strncmp(action, "แสดง", 12) == 0) {
                handle_print(action);
            } else if (strncmp(action, "ให้", 6) == 0) {
                handle_hai(action);
            } else if (strncmp(action, "หา", 6) == 0) {
                handle_ha(action);
            }
        }
    }
}

// File I/O placeholder
void handle_file_io(char *line) {
    char filename[128], varname[32];
    
    // Read from file: อ่านไฟล์ "data.txt" ใส่ x
    if (sscanf(line, "อ่านไฟล์ \"%[^\"]\" ใส่ %s", filename, varname) == 2) {
        FILE *file = fopen(filename, "r");
        if (file) {
            char buffer[256];
            if (fgets(buffer, sizeof(buffer), file)) {
                trim(buffer);
                set_string_variable(varname, buffer);
                printf("อ่านไฟล์ %s เสร็จแล้ว\n", filename);
            }
            fclose(file);
        } else {
            fprintf(stderr, "ไม่สามารถเปิดไฟล์ %s ได้\n", filename);
        }
    }
    
    // Write to file: เขียนไฟล์ "output.txt" จาก x
    if (sscanf(line, "เขียนไฟล์ \"%[^\"]\" จาก %s", filename, varname) == 2) {
        Variable *var = get_variable_ptr(varname);
        if (var) {
            FILE *file = fopen(filename, "w");
            if (file) {
                switch (var->type) {
                    case TYPE_INT:
                        fprintf(file, "%d", var->value.int_val);
                        break;
                    case TYPE_FLOAT:
                        fprintf(file, "%.2f", var->value.float_val);
                        break;
                    case TYPE_STRING:
                        fprintf(file, "%s", var->value.string_val);
                        break;
                    case TYPE_BOOLEAN:
                        fprintf(file, "%s", var->value.bool_val ? "จริง" : "เท็จ");
                        break;
                }
                fclose(file);
                printf("เขียนไฟล์ %s เสร็จแล้ว\n", filename);
            } else {
                fprintf(stderr, "ไม่สามารถสร้างไฟล์ %s ได้\n", filename);
            }
        }
    }
}

// Function definition placeholder
void handle_function_def(char *line) {
    // Placeholder for function definitions
    printf("การสร้างฟังก์ชันยังไม่สนับสนุน\n");
}

void handle_function_call(char *line) {
    // Placeholder for function calls
    printf("การเรียกฟังก์ชันยังไม่สนับสนุน\n");
}

// Help command: ช่วย or help
void handle_help(char *line) {
    printf("\n=== คู่มือการใช้งาน Aeroki Programming Language ===\n\n");
    
    printf("📝 คำสั่งพื้นฐาน (Basic Commands):\n");
    printf("   ให้ x = 10                  # กำหนดค่าตัวแปร (Variable assignment)\n");
    printf("   หา x                        # แสดงค่าตัวแปร (Display variable)\n");
    printf("   รับค่า name                 # รับค่าจากผู้ใช้ (Get input)\n");
    printf("   แสดง \"ข้อความ\"              # แสดงข้อความ (Print text)\n");
    printf("   ล้าง                       # ล้างหน่วยความจำ (Clear memory)\n\n");
    
    printf("🧮 การคำนวณ (Calculations):\n");
    printf("   หา x + y                    # บวก (Addition)\n");
    printf("   หา x - y                    # ลบ (Subtraction)\n");
    printf("   หา x * y                    # คูณ (Multiplication)\n");
    printf("   หา x / y                    # หาร (Division)\n");
    printf("   หา x %% y                    # หาเศษ (Modulo)\n\n");
    
    printf("📊 ชนิดข้อมูล (Data Types):\n");
    printf("   ให้ x = 42                  # จำนวนเต็ม (Integer)\n");
    printf("   ให้ pi = 3.14               # จำนวนทศนิยม (Float)\n");
    printf("   ให้ name = \"Aeroki\"         # ข้อความ (String)\n");
    printf("   ให้ flag = จริง              # ค่าความจริง (Boolean: จริง/เท็จ)\n\n");
    
    printf("🔢 ฟังก์ชันคณิตศาสตร์ (Math Functions):\n");
    printf("   หา รากที่สอง(25)            # รากที่สอง (Square root)\n");
    printf("   หา สัมบูรณ์(-10)            # ค่าสัมบูรณ์ (Absolute value)\n");
    printf("   หา ปัดขึ้น(3.14)            # ปัดขึ้น (Ceiling)\n");
    printf("   หา ปัดลง(3.99)              # ปัดลง (Floor)\n");
    printf("   หา sin(1.57)                # ไซน์ (Sine)\n");
    printf("   หา cos(0)                   # โคไซน์ (Cosine)\n\n");
    
    printf("🔀 คำสั่งเงื่อนไข (Conditionals):\n");
    printf("   ถ้า x > 10 แล้ว แสดง \"big\"   # เงื่อนไข if-then\n");
    printf("   ตัวเปรียบเทียบ: ==, !=, <, >, <=, >=\n");
    printf("   ภาษาไทย: เท่ากับ, ไม่เท่ากับ, น้อยกว่า, มากกว่า\n\n");
    
    printf("🔄 การวนลูป (Loops):\n");
    printf("   วนลูป i จาก 1 ถึง 10 ทำ แสดง i\n");
    printf("   วนลูป counter จาก start ถึง end ทำ หา counter * 2\n\n");
    
    printf("📁 การทำงานกับไฟล์ (File I/O):\n");
    printf("   อ่านไฟล์ \"data.txt\" ใส่ content\n");
    printf("   เขียนไฟล์ \"output.txt\" จาก message\n\n");
    
    printf("📝 หมายเหตุ (Comments):\n");
    printf("   # หมายเหตุแบบนี้\n");
    printf("   // หรือแบบนี้ก็ได้\n\n");
    
    printf("🎯 ตัวอย่างโปรแกรม (Examples):\n");
    printf("   ให้ age = 20\n");
    printf("   ถ้า age >= 18 แล้ว แสดง \"ผู้ใหญ่\"\n");
    printf("   วนลูป i จาก 1 ถึง 5 ทำ หา i * i\n\n");
    
    printf("🚪 การออกจากโปรแกรม:\n");
    printf("   ออก                        # ออกจากโหมด Shell\n\n");
    
    printf("💡 เคล็ดลับ (Tips):\n");
    printf("   - ใช้ชื่อตัวแปรภาษาอังกฤษเพื่อความเข้ากันได้\n");
    printf("   - ข้อความต้องใส่เครื่องหมาย \"\" คู่\n");
    printf("   - ใช้ ช่วย หรือ help เพื่อดูคำสั่งนี้อีกครั้ง\n\n");
    
    printf("📚 เอกสารเพิ่มเติม:\n");
    printf("   README.md - คู่มือเริ่มต้น\n");
    printf("   AEROKI_GUIDE.md - คู่มือฉบับสมบูรณ์\n");
    printf("   QUICK_REFERENCE.md - คำสั่งอ้างอิงด่วน\n\n");
    
    printf("=== Aeroki Programming Language - โปรแกรมด้วยภาษาไทย ===\n\n");
}

// === Core Interpreter Functions ===

void process_line(char *line) {
    trim(line);
    
    // Skip empty lines
    if (strlen(line) == 0) return;
    
    // Handle comments
    if (line[0] == '#' || (line[0] == '/' && line[1] == '/')) {
        return;
    }
    
    // Command routing
    if (strncmp(line, "ให้", 6) == 0) {
        handle_hai(line);
    } else if (strncmp(line, "หา", 6) == 0) {
        handle_ha(line);
    } else if (strncmp(line, "รับค่า", 12) == 0) {
        handle_rubka(line);
    } else if (strncmp(line, "แสดง", 12) == 0) {
        handle_print(line);
    } else if (strncmp(line, "ถ้า", 6) == 0) {
        handle_tha(line);
    } else if (strncmp(line, "วนลูป", 15) == 0) {
        handle_loop(line);
    } else if (strncmp(line, "อ่านไฟล์", 18) == 0 || strncmp(line, "เขียนไฟล์", 18) == 0) {
        handle_file_io(line);
    } else if (strcmp(line, "ล้าง") == 0) {
        clear_memory();
    } else if (strcmp(line, "ช่วย") == 0 || strcmp(line, "help") == 0) {
        handle_help(line);
    } else if (line[0] != '\0') {
        printf("ไม่รู้จักคำสั่ง: %s\n", line);
        printf("พิมพ์ 'ช่วย' หรือ 'help' เพื่อดูคำสั่งที่มี\n");
    }
}

void __Ark_Interpreted(FILE *__src_file) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), __src_file)) {
        line[strcspn(line, "\n")] = '\0';
        process_line(line);
    }
}

void __Ark_Shell() {
    char line[MAX_LINE_LENGTH];
    
    printf("Aeroki Shell Mode (พิมพ์ 'ออก' เพื่อออก)\n");
    printf("คำสั่งที่รองรับ: ให้, หา, รับค่า, แสดง, ถ้า, วนลูป, อ่านไฟล์, เขียนไฟล์, ล้าง\n");
    printf("ตัวอย่าง: ให้ x = 10, หา x + 5, แสดง \"สวัสดี\"\n");
    printf("พิมพ์ 'ช่วย' หรือ 'help' เพื่อดูคู่มือคำสั่ง\n\n");
    
    while (1) {
        printf(">>> ");
        fflush(stdout);
        
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        line[strcspn(line, "\n")] = '\0';
        trim(line);
        
        if (strcmp(line, "ออก") == 0) break;
        
        process_line(line);
    }
    
    printf("ออกจากโหมดเชลล์แล้ว\n");
}