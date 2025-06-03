
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


---

## 🛠️ Build & Run Instructions

This project provides multiple ways to build and execute the AST-based C plagiarism detection tool, depending on your operating system.

---

### 🐧 Linux / WSL

#### ✅ Build using `Makefile` (recommended)

---

### 📦 Install Dependencies (Linux / WSL)

Before building, make sure required packages are installed:

```bash
sudo apt update && sudo apt install bison g++ make
```

This installs:

* `bison` – for generating the parser
* `g++` – for compiling C++ code
* `make` – for using the Makefile

---


```bash
make
```

To clean previous builds:

```bash
make clean
```

#### ✅ Build using `build.sh` script

```bash
bash build.sh
```

#### ▶️ Run the tool

After building, run:

```bash
./bin/detector_with_filtering.exe original.c --ast-cc-test suspected.c
```

---

### 🪟 Windows

#### ✅ Build using `build.bat`

Double-click `build.bat` in File Explorer, or run:

```cmd
build.bat
```

> ⚠️ Make sure `bison` and `g++` are available in your PATH. You can use MSYS2 or run the project via WSL.

#### ▶️ Run the tool

From the command prompt:

```cmd
bin\detector_with_filtering.exe original.c --ast-cc-test suspected.c
```

---

### 📂 Output

* Executables will be created in the `bin/` directory:

  * `detector_with_filtering.exe` – Main detector with filtering
  * `c_parser.exe` – Optional parser-only binary
  * 
---
