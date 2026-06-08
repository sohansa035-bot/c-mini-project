# 🎨 2D Console Graphics Editor

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Environment](https://img.shields.io/badge/Environment-CLI-green.svg)
![License](https://img.shields.io/badge/License-MIT-orange.svg)

A lightweight, fully functional 2D text-based graphics editor developed in C. It enables users to create, manipulate, and save geometric shapes directly within a terminal interface. Built entirely from scratch using fundamental C concepts such as linked lists and manual rasterization math, this project demonstrates robust memory management and algorithm design.

---

## ✨ Features

- **Geometric Primitives**: Support for rendering **Lines**, **Rectangles**, **Circles**, and **Triangles**.
- **Dynamic Data Structures**: Utilizes Singly Linked Lists for O(1) shape insertion and infinite scalable canvas elements.
- **Persistent Storage**: Built-in file I/O operations automatically serialize and deserialize shapes to a local `shapes.txt` file.
- **Rasterization Engine**: Custom mathematical algorithms for pixel-perfect console rendering (Bresenham-like line approximation, Cartesian circle mapping).
- **Interactive CLI Menu**: A streamlined text interface allowing users to perform CRUD operations (Add, Edit, Delete, Show) on canvas shapes.

---

## 🛠️ Installation & Setup

### Prerequisites
- A standard C compiler (e.g., `gcc`, `clang`)
- A terminal or command prompt environment

### Compilation
Clone the repository and compile the source code using GCC:

```bash
git clone https://github.com/sohansa035-bot/c-mini-project.git
cd "c-mini-project"
gcc main.c -o graphics_editor
```

### Execution
Run the compiled binary:

```bash
# On Windows
graphics_editor.exe

# On Linux / macOS
./graphics_editor
```

---

## 💻 Usage Guide

Upon launching the application, you are presented with a main menu. Enter the corresponding number to execute a command:

```text
1.Add 2.Edit 3.Delete 4.Show 5.Exit
Choice: 
```

### Supported Operations

| Command | Description | Input Format Expected |
| :--- | :--- | :--- |
| **Add** | Creates a new shape on the canvas. | Select type (0-3), provide coordinates, provide label |
| **Edit** | Modifies the coordinates or properties of an existing shape. | Shape ID |
| **Delete**| Removes a shape from the canvas and frees memory. | Shape ID |
| **Show** | Renders all current shapes onto the 80x40 ASCII grid. | N/A |
| **Exit** | Saves all shapes to `shapes.txt` and safely exits. | N/A |

### Shape Input Formats
- **Line (0)**: `x1 y1 x2 y2`
- **Rectangle (1)**: `x1 y1 x2 y2` (top-left and bottom-right corners)
- **Circle (2)**: `cx cy radius` (center coordinates and radius length)
- **Triangle (3)**: `x1 y1 x2 y2 x3 y3` (coordinates for all three vertices)

---

## 🧠 Technical Architecture

- **Canvas Buffer**: Implemented as a 2D `char` array (`40x80`) serving as a frame buffer before rendering to standard output.
- **State Management**: The application state is preserved via a linked list (`struct Node`), where each node contains structural data (type, ID, label) and geometry data (`struct Point`).
- **Memory Safety**: Careful implementation of `malloc` and `free` ensures no memory leaks during the lifecycle of shape manipulation.

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
