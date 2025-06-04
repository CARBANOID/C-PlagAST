
---

### 📄 **Project Title:**

**C-PlagAST: AST-CC Based Plagiarism Detection Tool for C Code**

---

### 📝 **Project Description:**

**C-PlagAST** is an advanced plagiarism detection tool specifically designed for analyzing C source code. It leverages the **AST-CC (Abstract Syntax Tree – Consistent Comparison)** algorithm to identify structural similarities between code files, making it robust against superficial changes such as variable renaming, formatting variations, and reordering of functions or declarations.

Unlike traditional text-based comparison tools, C-PlagAST parses source code into **abstract syntax trees**, applies a series of **normalization techniques** (such as dead code elimination, function and declaration reordering, and prototype removal), and then generates structural hashes or similarity scores to evaluate the likelihood of plagiarism.

This tool is intended for use in academic and professional environments where accurate and structure-aware code plagiarism detection is essential.

---

### 🔍 **Key Features:**

* AST-based structural comparison of C programs
* Supports normalization techniques:

  * Dead code and unreachable code removal
  * Declaration and function reordering
  * Prototype elimination
* Confusion matrix and accuracy reporting
* CLI-based execution with support for batch testing
* Ideal for academic plagiarism detection in C programming assignments

---

## 🛠️ Build & Run Instructions

This project supports multiple build options for Linux, WSL, and Windows.

---

### 🐧 Linux / WSL

---

### 📦 Install Dependencies

Before building, make sure required packages are installed:

```bash
sudo apt update && sudo apt install bison g++ make
```

This installs:

* `bison` – for generating the parser
* `g++` – for compiling C++ code
* `make` – for using the Makefile

---

To clean previous builds:

```bash
make clean
```

#### ✅ Build using `Makefile` (recommended)

```bash
make
```
or 
---
#### ✅ Build using `build.sh`

```bash
bash build.sh
```

#### ▶️ Run the Tool

To check for plagiarism:

```bash
./bin/detector_with_filtering.exe original.c --ast-cc-test suspected1.c suspected2.c suspected3.c
```
The plagiarism will be checked by comparing the added files after the --ast-cc-test flag against original.c .

To print the **Normalized AST** for debugging:

```bash
./bin/detector_with_filtering.exe --printAST test1.c test2.c test3.c
```

---

### 🪟 Windows

#### ✅ Build using `build.bat`

Run in File Explorer or via Command Prompt:

```cmd
.\build.bat
```

> ⚠️ Ensure `bison` and `g++` are available in your `PATH`. Use MSYS2 or WSL if necessary.

#### ▶️ Run the Tool

To check for plagiarism:

```cmd
bin\detector_with_filtering.exe original.c --ast-cc-test suspected1.c suspected2.c suspected3.c
```
The plagiarism will be checked by comparing the added files after the --ast-cc-test flag against original.c .

To print the **normalized AST**:

```cmd
bin\detector_with_filtering.exe --printAST test1.c test2.c test3.c
```

---

### 📂 Output

* Executables will be generated in the `bin/` directory:

  * `detector_with_filtering.exe` – Main detector with normalization and filtering
  * `c_parser.exe` – Optional standalone parser binary

---
