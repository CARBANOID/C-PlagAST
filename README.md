Sure! Here’s the optimized `README.md` content for your `C-PlagAST` project in **copyable format**:

---

````
# 🔍 C-PlagAST: AST-CC Based Plagiarism Detection Tool for C Code

**C-PlagAST** is an advanced plagiarism detection tool built for C programs. It uses the **AST-CC** (Abstract Syntax Tree – Consistent Comparison) algorithm to detect structural similarity in code — even after formatting changes, variable renaming, or code reordering. Ideal for academic environments, it delivers accurate, structure-aware plagiarism analysis beyond basic text matching.

![GitHub repo size](https://img.shields.io/github/repo-size/CARBANOID/C-PlagAST)
![GitHub stars](https://img.shields.io/github/stars/CARBANOID/C-PlagAST?style=social)
![GitHub license](https://img.shields.io/github/license/CARBANOID/C-PlagAST)

---

## ✨ Features

- ⚙️ **AST-Based Structural Code Comparison**
- 🔄 Normalization techniques:
  - Dead/unreachable code removal
  - Declaration/function reordering
  - Prototype elimination
- 📊 Confusion matrix & accuracy reporting
- 📁 Batch file comparison support
- 🧪 Ideal for detecting academic plagiarism in C code

---

## 🛠️ Build & Run Instructions

Supports **Linux**, **WSL**, and **Windows** environments.

<details>
<summary>🐧 Linux / WSL</summary>

### 📦 Install Dependencies

```bash
sudo apt update && sudo apt install bison g++ make
````

### 🔧 Build

```bash
make         # Recommended
# or
bash build.sh
```

### 🧪 Run the Tool

```bash
./bin/detector_with_filtering.exe original.c --ast-cc-test suspected1.c suspected2.c
```

To print the Normalized AST:

```bash
./bin/detector_with_filtering.exe --printAST test1.c test2.c
```

</details>

<details>
<summary>🪟 Windows</summary>

### 🔧 Build

Run `build.bat` in File Explorer or Command Prompt:

```bat
.\build.bat
```

> ⚠️ Ensure `bison` and `g++` are in PATH (use MSYS2 or WSL if needed)

### 🧪 Run the Tool

```bat
bin\detector_with_filtering.exe original.c --ast-cc-test suspected1.c suspected2.c
```

To print normalized AST:

```bat
bin\detector_with_filtering.exe --printAST test1.c test2.c
```

</details>

---

## 📂 Output Structure

* 🔹 `bin/` — Compiled executables

  * `detector_with_filtering.exe` — Main detector
  * `c_parser.exe` — Optional standalone parser
* 🔹 `build/` — Intermediate parser files (`parser.cpp`, `parser.hpp`)

---

## 📌 Example Usage

```bash
./bin/detector_with_filtering.exe original.c --ast-cc-test suspect1.c suspect2.c
```

---

## 🙋‍♂️ Author

**Sushant Negi**
CARBANOID
📍 India
🧑‍💻 BTech CSE (6th Semester)
🔗 GitHub: [CARBANOID](https://github.com/CARBANOID)

---

## 🏷️ Keywords

`plagiarism detection` · `AST-CC` · `C language` · `abstract syntax tree` · `academic integrity` · `code normalization` · `source code similarity` · `C plagiarism checker`
---
