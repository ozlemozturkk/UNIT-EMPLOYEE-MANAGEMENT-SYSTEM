# 👥 Unit & Employee Management System

A **C-based employee and organizational unit management system** designed to store, organize, and manage information about employees and the units they belong to.

The project focuses on building a structured management application in C while applying core programming concepts such as **data structures, modular programming, memory management, and file organization**.

## 📌 About the Project

The Unit & Employee Management System models a simple organizational structure where employees are associated with different units.

The system provides functionality for managing employee and unit information while keeping the code separated into different source and header files.

Rather than implementing the entire application in a single file, the project follows a **modular C programming approach**, separating function declarations, implementations, and the main program flow.

## ✨ Features

* 👤 Employee information management
* 🏢 Organizational unit management
* 🔗 Association between employees and units
* ➕ Adding employee and unit records
* ✏️ Updating stored information
* 🔍 Viewing and searching records
* 📂 Structured data management
* 💾 File-based data handling
* 🧩 Modular source code organization

## 🏢 System Structure

The application is based on two main entities:

### 👤 Employee

Stores information related to employees and allows employee records to be managed within the system.

### 🏢 Unit

Represents organizational units and provides a structure for grouping and managing employees.

This relationship allows employee information to be organized according to the unit they belong to.

## 🛠️ Technologies & Concepts

* 🇨 **C Programming**
* 🧱 **Structures (`struct`)**
* 👉 **Pointers**
* 🧠 **Dynamic Memory Management**
* 📂 **File Operations**
* 🧩 **Modular Programming**
* 📄 **Header Files**
* 🛠️ **Makefile**
* 🔧 **Git & GitHub**

## 🧩 Project Structure

```text
UNIT-EMPLOYEE-MANAGEMENT-SYSTEM/
│
├── main.c        # Main program flow
├── Proje1.c      # Function implementations
├── Proje1.h      # Structures and function declarations
├── Makefile      # Build configuration
├── .gitignore
└── .gitattributes
```

The separation between `.c` and `.h` files keeps the project easier to organize and maintain.

## ⚙️ How It Works

The program manages information about employees and organizational units through a menu-driven structure.

User operations are processed by functions defined in the project modules, while the main program coordinates the overall application flow.

The project also demonstrates how related data can be represented and managed using C data structures.

## 🚀 Running the Project

### Requirements

* GCC or another compatible C compiler
* `make`

### Build

```bash
make
```

### Run

After compilation, run the generated executable:

```bash
./<executable_name>
```

> The executable name depends on the configuration in the Makefile.

## 💡 About This Project

This project gave me the opportunity to move beyond small standalone C programs and build a more structured application composed of multiple source files.

Working with employee and unit data provided practical experience with **structs, pointers, memory management, file operations, and modular program design**. Using a Makefile also helped organize the compilation process as the project grew beyond a single source file.




