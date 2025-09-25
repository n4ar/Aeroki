# Aeroki - คู่มือการใช้งาน

## Aeroki คืออะไร?
Aeroki เป็นภาษาโปรแกรมที่ใช้คำภาษาไทยในการเขียนโค้ด ทำขึ้นมาเพื่อให้คนไทยเข้าใจโลกการเขียนโปรแกรมได้ง่ายขึ้น มีความสามารถครบครันตั้งแต่ตัวแปรหลายชนิด คำสั่งเงื่อนไข ลูป ไปจนถึงการจัดการไฟล์

## การติดตั้งและใช้งาน

### คอมไพล์
```bash
gcc -o aeroki Aeroki.c main.c -lm
```

### วิธีรันโปรแกรม
```bash
./aeroki                    # เปิดโหมดพิมพ์คำสั่ง
./aeroki program.ark        # รันไฟล์โปรแกรม
```

## Language Features

### 1. Variable Types (ตัวแปรหลายประเภท)

#### Integer (จำนวนเต็ม)
```aeroki
ให้ x = 10
ให้ age = 25
```

#### Float (จำนวนทศนิยม)
```aeroki
ให้ pi = 3.14159
ให้ temperature = 36.5
```

#### String (ข้อความ)
```aeroki
ให้ name = "สมชาย"
ให้ message = "สวัสดีชาวโลก"
```

#### Boolean (ค่าความจริง)
```aeroki
ให้ is_ready = จริง
ให้ is_finished = เท็จ
```

### 2. Display & Calculation (การแสดงผลและคำนวณ)

#### Display Variables (แสดงค่าตัวแปร)
```aeroki
หา x                        # Display variable x
หา name                     # Display string variable
```

#### Arithmetic Operations (การคำนวณ)
```aeroki
หา x + y                    # Addition
หา x - y                    # Subtraction
หา x * y                    # Multiplication
หา x / y                    # Division
หา x % y                    # Modulo
```

#### Mathematical Functions (ฟังก์ชันคณิตศาสตร์)
```aeroki
หา รากที่สอง(25)            # Square root (Thai)
หา sqrt(16)                 # Square root (English)
หา สัมบูรณ์(-10)            # Absolute value (Thai)
หา abs(-42)                 # Absolute value (English)
หา ปัดขึ้น(3.14)            # Ceiling (Thai)
หา ceil(2.1)               # Ceiling (English)
หา ปัดลง(3.99)              # Floor (Thai)
หา floor(4.8)              # Floor (English)
หา sin(1.57)               # Sine
หา cos(0)                  # Cosine
หา tan(0.78)               # Tangent
หา log(10)                 # Natural logarithm
```

### 3. Print Statements (การแสดงผล)

#### Print Text (แสดงข้อความ)
```aeroki
แสดง "Hello World!"
แสดง "สวัสดีชาวโลก"
```

#### Print Variables (แสดงตัวแปร)
```aeroki
แสดง x
แสดง name
แสดง is_ready
```

### 4. Input (การรับค่า)

```aeroki
รับค่า username            # Get input for username
รับค่า number              # Get input for number
```

The system automatically detects the input type:
- Numbers become integers or floats
- "จริง"/"true" becomes boolean true
- "เท็จ"/"false" becomes boolean false
- Everything else becomes string

### 5. Conditional Statements (คำสั่งเงื่อนไข)

#### Basic If Statement (คำสั่งถ้า)
```aeroki
ถ้า x > 10 แล้ว แสดง "x is greater than 10"
ถ้า name เท่ากับ "สมชาย" แล้ว แสดง "Hello Somchai!"
ถ้า is_ready == จริง แล้ว แสดง "Ready to proceed"
```

#### Comparison Operators (ตัวดำเนินการเปรียบเทียบ)

**English Operators:**
- `==` : Equal to
- `!=` : Not equal to
- `<`  : Less than
- `>`  : Greater than
- `<=` : Less than or equal to
- `>=` : Greater than or equal to

**Thai Operators:**
- `เท่ากับ` : Equal to
- `ไม่เท่ากับ` : Not equal to
- `น้อยกว่า` : Less than
- `มากกว่า` : Greater than
- `น้อยกว่าหรือเท่ากับ` : Less than or equal to
- `มากกว่าหรือเท่ากับ` : Greater than or equal to

### 6. Loop Structures (การวนลูป)

#### For Loop (วนลูปแบบกำหนดช่วง)
```aeroki
วนลูป i จาก 1 ถึง 10 ทำ แสดง i
วนลูป counter จาก start ถึง end ทำ หา counter * 2
```

You can use:
- Numbers: `วนลูป i จาก 1 ถึง 5`
- Variables: `วนลูป i จาก start ถึง end`

### 7. File I/O Operations (การทำงานกับไฟล์)

#### Read from File (อ่านไฟล์)
```aeroki
อ่านไฟล์ "data.txt" ใส่ content
อ่านไฟล์ "numbers.txt" ใส่ data
```

#### Write to File (เขียนไฟล์)
```aeroki
เขียนไฟล์ "output.txt" จาก message
เขียนไฟล์ "result.txt" จาก calculation_result
```

### 8. Comments (หมายเหตุ)

```aeroki
# This is a single-line comment
// This is also a comment

# หมายเหตุภาษาไทย
// คอมเมนต์แบบนี้ก็ได้
```

### 9. Memory Management (การจัดการหน่วยความจำ)

#### Clear All Variables (ล้างตัวแปรทั้งหมด)
```aeroki
ล้าง                        # Clear all variables from memory
```

## Complete Example Programs

### Example 1: Basic Calculator
```aeroki
# เครื่องคิดเลขพื้นฐาน
แสดง "=== เครื่องคิดเลขพื้นฐาน ==="

# รับข้อมูลจากผู้ใช้
รับค่า num1
รับค่า num2

# คำนวณ
หา num1 + num2
หา num1 - num2
หา num1 * num2
หา num1 / num2

# แสดงฟังก์ชันคณิตศาสตร์
หา รากที่สอง(num1)
หา สัมบูรณ์(num1)
```

### Example 2: Grade Calculator
```aeroki
# คำนวณเกรด
แสดง "โปรแกรมคำนวณเกรด"

รับค่า score

ถ้า score >= 80 แล้ว แสดง "เกรด A"
ถ้า score >= 70 แล้ว แสดง "เกรด B"
ถ้า score >= 60 แล้ว แสดง "เกรด C"
ถ้า score >= 50 แล้ว แสดง "เกรด D"
```

### Example 3: Loop with Conditions
```aeroki
# วนลูปพร้อมเงื่อนไข
แสดง "ตัวเลขคู่จาก 1 ถึง 10:"

วนลูป i จาก 1 ถึง 10 ทำ ถ้า i % 2 เท่ากับ 0 แล้ว แสดง i
```

### Example 4: File Processing
```aeroki
# ประมวลผลไฟล์
ให้ user_data = "ชื่อ: สมชาย อายุ: 25"
ให้ numbers = 12345

# บันทึกข้อมูล
เขียนไฟล์ "user.txt" จาก user_data
เขียนไฟล์ "numbers.txt" จาก numbers

แสดง "บันทึกไฟล์เสร็จสิ้น"

# ล้างและอ่านข้อมูลใหม่
ล้าง
อ่านไฟล์ "user.txt" ใส่ loaded_data
อ่านไฟล์ "numbers.txt" ใส่ loaded_numbers

แสดง "ข้อมูลที่อ่านได้:"
หา loaded_data
หา loaded_numbers
```

## Shell Mode Commands

When running in interactive mode (`./aeroki`), you can use all commands interactively:

```
>>> ให้ x = 10
>>> หา x
10
>>> แสดง "สวัสดี"
สวัสดี
>>> ออก
```

## Error Handling

The interpreter provides Thai error messages:
- `ไม่พบตัวแปร: variable_name` - Variable not found
- `ตัวแปรเต็มแล้ว` - Too many variables
- `ไม่รู้จักคำสั่ง: command` - Unknown command
- `ไม่สามารถเปิดไฟล์ filename ได้` - Cannot open file
- `ไม่สามารถสร้างไฟล์ filename ได้` - Cannot create file

## Language Keywords Summary

### Commands (คำสั่ง)
- `ให้` - Variable assignment
- `หา` - Display/Calculate
- `รับค่า` - Input
- `แสดง` - Print
- `ถ้า...แล้ว` - If statement
- `วนลูป...จาก...ถึง...ทำ` - For loop
- `อ่านไฟล์...ใส่` - Read file
- `เขียนไฟล์...จาก` - Write file
- `ล้าง` - Clear memory
- `ออก` - Exit (shell mode)

### Values (ค่า)
- `จริง` - True
- `เท็จ` - False

### Math Functions (ฟังก์ชันคณิตศาสตร์)
- `รากที่สอง` - Square root
- `สัมบูรณ์` - Absolute value
- `ปัดขึ้น` - Ceiling
- `ปัดลง` - Floor

### Comparison Operators (ตัวเปรียบเทียบ)
- `เท่ากับ` - Equal to
- `ไม่เท่ากับ` - Not equal to
- `น้อยกว่า` - Less than
- `มากกว่า` - Greater than
- `น้อยกว่าหรือเท่ากับ` - Less than or equal to
- `มากกว่าหรือเท่ากับ` - Greater than or equal to

## Tips for Programming in Aeroki

1. **Variable Naming**: Use English variable names for better compatibility
2. **File Paths**: Use forward slashes (/) in file paths
3. **String Quotes**: Always use double quotes for strings
4. **Comments**: Use # or // for comments
5. **Testing**: Use the shell mode for quick testing
6. **Memory Management**: Use `ล้าง` to clear variables when needed

## Future Enhancements (Currently in Development)

- Array/List support with Thai syntax
- Custom function definitions
- Advanced loop structures (while loops)
- Logical operators (AND, OR, NOT)
- Error handling (try/catch)
- More built-in functions
- Advanced file operations

---

*Aeroki Programming Language - Making programming accessible in Thai*