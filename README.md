# 2D Console Graphics Editor

A simple, text-based 2D graphics editor written in C. This project allows users to draw, edit, delete, and view basic geometric shapes directly in the console.

## Features

- **Shapes Supported**: Line, Rectangle, Circle, Triangle.
- **Canvas**: Renders shapes onto a 40x80 text grid using ASCII characters.
- **Linked Lists**: Utilizes singly linked lists for dynamic memory management of the drawn shapes.
- **File I/O**: Automatically saves your drawings to `shapes.txt` upon exit and loads them when the program starts.
- **Interactive Menu**: Simple text-based user interface to add, edit, delete, and show shapes.

## Compilation and Execution

To compile the project, use GCC:

```bash
gcc main.c -o graphics_editor
```

To run the compiled program:

```bash
./graphics_editor
```

## Usage

When running the program, you will be presented with a menu:
`1.Add 2.Edit 3.Delete 4.Show 5.Exit`

Select an option by entering the corresponding number:
- **Add**: Choose a shape type and provide the coordinates/radius.
- **Edit**: Modify the coordinates or radius of an existing shape by its ID.
- **Delete**: Remove a shape from the canvas by its ID.
- **Show**: Render all current shapes onto the console canvas.
- **Exit**: Save all shapes to `shapes.txt` and terminate the program.

## Requirements

- Standard C library
