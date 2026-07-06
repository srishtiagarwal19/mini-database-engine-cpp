# Mini Database Engine (C++)

A lightweight SQL-like database engine built from scratch in **C++** to understand the internal working of relational database systems.

The project is being developed incrementally, with each milestone introducing new database concepts such as SQL parsing, file-based storage, query execution, and indexing.

---

## 🚀 Features

### ✅ Implemented

* Interactive command-line interface (CLI)
* SQL command parsing
* `CREATE TABLE` statement parsing
* Table name extraction
* Column name extraction
* File-based table creation
* Metadata storage
* Duplicate table detection
* Case-insensitive SQL keyword parsing

### 🚧 Upcoming Features

* INSERT INTO
* SELECT queries
* WHERE clause
* UPDATE records
* DELETE records
* Multiple tables
* Hash Indexing
* Buffer Manager
* B+ Tree Index (Advanced)

---

## 📁 Project Structure

```text
MiniDB/
│
├── build/
│
├── data/
│
├── include/
│   ├── Parser.h
│   └── Storage.h
│
├── src/
│   ├── main.cpp
│   ├── Parser.cpp
│   └── Storage.cpp
│
└── README.md
```

---

## 🏗️ Architecture

```
            User
              │
              ▼
         MiniDB CLI
              │
              ▼
          SQL Parser
              │
              ▼
        Storage Engine
              │
              ▼
        File System (.tbl)
```

---

## ✅ Milestones

### Milestone 1

* Project setup
* Interactive CLI
* Basic command shell

### Milestone 2

* SQL command recognition
* Supports:

  * CREATE TABLE
  * INSERT
  * SELECT
  * UPDATE
  * DELETE

### Milestone 3

* Parse CREATE TABLE statements
* Extract table names
* Extract column names

### Milestone 4

* Implement Storage Engine
* Create `.tbl` files
* Store schema in `metadata.txt`
* Detect duplicate tables

### Milestone 5
- Added Database controller class
- Implemented INSERT INTO SQL parsing
- Added persistent record insertion into table files
- Added validation for table existence before inserting

---

## 🖥️ Example

### Input

```sql
CREATE TABLE Student(id,name,age)
```

### Output

```
Table created successfully.
```

Generated files

```
data/
│
├── Student.tbl
└── metadata.txt
```

---

## 🛠️ Technologies Used

* C++17
* Standard Template Library (STL)
* File Handling
* Object-Oriented Programming (OOP)
* VS Code
* MSYS2 MinGW-w64
* Git
* GitHub

---

## ⚙️ Build & Run

Compile:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o build/minidb.exe
```

Run:

```bash
./build/minidb.exe
```

Windows PowerShell:

```powershell
.\build\minidb.exe
```

---

## 🎯 Learning Objectives

This project is designed to understand how a relational database works internally by implementing:

* SQL Parsing
* Storage Engine
* File Management
* Query Execution
* Indexing
* Database Architecture
* System Design Concepts

---

## 📌 Future Enhancements

* INSERT INTO support
* SELECT with WHERE
* UPDATE
* DELETE
* Metadata Manager
* Hash Index
* B+ Tree Index
* Transactions
* Query Optimizer
* JOIN Operations

---

## 👩‍💻 Author

**Srishti Agarwal**
