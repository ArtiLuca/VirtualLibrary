# 📚 Virtual Library

<p align="center">

![C++](https://img.shields.io/badge/C++17-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge\&logo=qt\&logoColor=white)
![OOP](https://img.shields.io/badge/Object--Oriented-Programming-2E8B57?style=for-the-badge)
![Design Patterns](https://img.shields.io/badge/Design-Patterns-blue?style=for-the-badge)
![University Project](https://img.shields.io/badge/University-Project-blue?style=for-the-badge)

</p>

---

## 📖 Overview

**Virtual Library** is a C++17 and Qt desktop application for managing a multimedia library.

The application allows users to create, edit, remove, search and view different types of media items, including audio files, videos, e-books and images.

The project focuses on object-oriented programming principles such as inheritance, polymorphism, abstraction, separation of responsibilities and extensibility.
It also applies several design patterns to organize the creation, manipulation and analysis of media objects.

---

## ✨ Main Features

* Management of multiple media types
* Creation, editing and removal of media items
* Search functionality with multiple filters
* Type-specific validation
* Media scoring based on item attributes
* Undo and redo support
* JSON-based save/load functionality
* Qt Widgets graphical user interface
* File and console logging
* Extensible object-oriented architecture

---

## 🧩 Supported Media Types

| Media Type | Example Attributes                                                  |
| ---------- | ------------------------------------------------------------------- |
| Audio      | Artist, album, genre, duration and audio-specific properties        |
| Video      | Director, genre, duration, resolution and video-specific properties |
| E-book     | Author, publisher, ISBN, language and page count                    |
| Image      | Creator, category, resolution, bit depth and location               |

Common attributes are handled through an abstract media hierarchy, while each concrete media type defines its own specialized data and behaviour.

---

## 🏗️ Architecture

The application follows an MVC-inspired organization, separating the domain model, application logic and graphical interface.

### Model

The model contains the core logic of the application, including:

* media hierarchy
* library management
* builders and factories
* visitors
* validation
* searching and scoring
* JSON serialization
* logging

### Controller

The controller coordinates the interaction between the model and the graphical interface.

It manages operations such as media insertion, editing, removal, searching, persistence and undo/redo.

### View

The view contains the Qt Widgets graphical interface and the components used to create, edit, search and display media items.

---

## 🧠 Design Patterns

| Pattern | Usage                                                                       |
| ------- | --------------------------------------------------------------------------- |
| Visitor | Type-specific operations such as validation, searching, scoring and display |
| Builder | Progressive construction and modification of media objects                  |
| Factory | Creation of the appropriate concrete media type                             |
| Command | Undo and redo support for insert, edit and remove operations                |

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

Each media type implements its own serialization logic, while the library manages the complete media collection.

An example library file is included in:

```text
src/example_library.json
```

---

## ▶️ Building and Running

The simplest way to build and run the project is through **Qt Creator**:

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

Depending on the compiler and operating system, the build command may instead be:

```bash
mingw32-make
```

or:

```bash
nmake
```

---

## 📄 Documentation

The complete project report is available in:

```text
docs/Virtual Library Project Report.pdf
```

The report is written in **Italian**, as the project was originally developed for an Italian university course.

It describes the application requirements, class hierarchy, architecture, design patterns, persistence system, graphical interface and implementation choices.

---

## 🎓 Academic Context

This project was developed individually as part of an Object-Oriented Programming course at the **University of Padua**.

The goal was to design and implement a non-trivial C++ desktop application using inheritance, polymorphism, abstract classes, dynamic binding, design patterns, safe resource management and a graphical user interface.

---

## 👨‍💻 Author

* Luca Artinian — [@ArtiLuca](https://github.com/ArtiLuca)
