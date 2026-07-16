# 📚 Virtual Library

<p align="center">

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge\&logo=qt\&logoColor=white)
![OOP](https://img.shields.io/badge/Object--Oriented-Programming-2E8B57?style=for-the-badge)
![Design Patterns](https://img.shields.io/badge/Design-Patterns-blue?style=for-the-badge)

</p>

---

## 📖 Overview

**Virtual Library** is a desktop application developed in C++ and Qt for managing a collection of multimedia items.

The application supports different media types, including audio files, videos, e-books and images. It provides tools for creating, editing, removing, searching, viewing and evaluating media items through a graphical interface.

The project focuses on object-oriented design, inheritance, polymorphism, separation of responsibilities and the practical use of common design patterns.

---

## ✨ Main Features

* Management of audio, video, e-book and image items
* Creation, editing and removal of media
* Search with multiple filters
* Type-specific validation
* Media scoring based on item attributes
* Undo and redo support
* JSON-based library persistence
* Qt Widgets graphical interface
* File and console logging
* Extensible object-oriented architecture

---

## 🧩 Supported Media Types

| Media type | Example attributes                                         |
| ---------- | ---------------------------------------------------------- |
| Audio      | Artist, album, genre, duration and audio properties        |
| Video      | Director, genre, duration, resolution and video properties |
| E-book     | Author, publisher, ISBN, language and page count           |
| Image      | Creator, category, resolution, bit depth and location      |

Common information is managed through an abstract media hierarchy, while each concrete type defines its own specialized attributes and behaviour.

---

## 🏗️ Architecture

The application follows an MVC-inspired organization, separating the domain model, application logic and graphical interface.

### Model

Contains the core application logic:

* media hierarchy
* library management
* builders and factories
* visitors
* searching and scoring
* validation
* JSON serialization
* logging

### Controller

Coordinates the interaction between the model and the graphical interface.

It manages operations such as media insertion, editing, removal, searching, persistence and undo/redo.

### View

Contains the Qt Widgets graphical interface and the components used to create, edit, search and display media items.

---

## 🧠 Design Patterns

| Pattern | Usage                                                                       |
| ------- | --------------------------------------------------------------------------- |
| Visitor | Type-specific operations such as validation, searching, scoring and display |
| Builder | Progressive construction and modification of media objects                  |
| Factory | Creation of the appropriate concrete media type                             |
| Command | Undo and redo for insert, edit and remove operations                        |

---

## 🛠️ Technologies

| Technology         | Purpose                                    |
| ------------------ | ------------------------------------------ |
| C++17              | Core application and object-oriented model |
| Qt Widgets         | Graphical user interface                   |
| qmake              | Project configuration and build system     |
| JSON               | Library persistence                        |
| STL smart pointers | Memory and ownership management            |

---

## 📂 Repository Structure

```text
.
├── README.md
├── docs/
│   └── Virtual Library Project Report.pdf
└── src/
    ├── Controller/
    ├── Model/
    │   ├── Builders/
    │   ├── Library/
    │   ├── Loggers/
    │   ├── Media/
    │   ├── Utilities/
    │   └── Visitors/
    ├── Resource/
    ├── View/
    ├── Virtual_Library.pro
    ├── example_library.json
    └── main.cpp
```

---

## 💾 Data Persistence

The application can save and load the multimedia library using JSON files.

Each media type implements its own serialization logic, while the library manages the complete collection.

An example library is included in:

```text
src/example_library.json
```

---

## ▶️ Building and Running

The simplest way to build the project is through **Qt Creator**:

1. Open `src/Virtual_Library.pro`.
2. Select a compatible Qt kit.
3. Configure the project.
4. Build and run the application.

Alternatively, from a terminal with Qt and `qmake` configured:

```bash
cd src
qmake Virtual_Library.pro
make
```

Depending on the compiler and operating system, the build command may instead be `mingw32-make` or `nmake`.

---

## 📄 Documentation

The complete project report is available in:

```text
docs/Virtual Library Project Report.pdf
```

The report describes the application requirements, class hierarchy, architecture, design patterns, persistence system and graphical interface.

The report is written in **Italian**, as the project was originally developed for an Italian university course.

---

## 🎓 Academic Context

This project was developed individually as part of an Object-Oriented Programming course.

Its goal was to design and implement a non-trivial C++ application using inheritance, polymorphism, abstract classes, dynamic binding, design patterns, safe resource management and a graphical user interface.

---

## 👨‍💻 Author

* Luca Artinian — [@ArtiLuca](https://github.com/ArtiLuca)
