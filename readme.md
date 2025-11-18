# RGame

**RGame** is an abstraction layer built on top of the [raylib](https://raylib.com) library to simplify and standardize video game programming. It provides a collection of utilities, classes, structs, and templates that streamline the development process, making it easier to create games and interactive applications.

---

## Table of Contents

- [Dependencies](#dependencies)
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [UI System](#ui-system)
- [Contributing](#contributing)
- [License](#license)

---

## Dependencies

- [raylib](https://raylib.com): A simple and easy-to-use game programming library, used as the foundation of RGame.

RGame is designed to work with **raylib** version X.X or newer. If you don't have it installed, follow the instructions on [raylib's website](https://raylib.com) to set it up.

---

## Overview

RGame aims to simplify the game development process by providing:

- **UI Elements**: A range of UI components (e.g., Buttons, Panels, Labels) for building interactive user interfaces.
- **GameObject System**: A flexible, component-based architecture for managing in-game entities.
- **Scene Management**: Tools for organizing and managing scenes, transitions, and state updates.

By abstracting common patterns and structures, RGame allows developers to focus more on gameplay and less on boilerplate code.

---

## Features

- **Cross-Platform**: Works on Windows, macOS, Linux, and other platforms supported by raylib. Mobile platforms are currently unsuported.
- **UI System**: Easily create buttons, labels, and panels with customizable styles.
- **Flexible Scene Management**: Organize game objects into scenes and easily switch between them.
- **Open Source**: RGame is open-source and contributions are welcome.

---

## Installation

To get started with RGame, follow these steps:

### 1. Clone the Repository

```bash
git clone https://github.com/leodct/rgame.git
cd rgame
```

### 2. Install Dependencies

rgame relies on [raylib](https://raylib.com), which must be installed on your system.

- On **Windows**: Follow the raylib installation instructions on their [GitHub page](https://github.com/raysan5/raylib) or [raylib website](https://raylib.com).
- On **macOS**: You can use `brew` to install raylib:

  brew install raylib

- On **Linux** (Ubuntu):

  sudo apt-get install libraylib-dev

Once raylib is installed, you're ready to start building with RGame!

---

## UI System

The UI system includes a range of pre-built components to help you create user interfaces easily:

- **UIElement**: Base class for all UI elements.
- **Button**: Interactive button component that handles mouse input.
- **Label**: Text element that can be positioned and styled.
- **Panel**: A container that can hold other UI elements.
- **ImageDisplay**: Displays an image as a UI element.
- **VariableDisplay**: A special label that can display a variable's value and update it in real-time.

## Contributing

We welcome contributions to RGame! If you want to help improve this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix (`git checkout -b feature-name`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-name`).
5. Open a Pull Request with a description of your changes.

Before submitting a PR, make sure your code passes the tests and follows the project's coding conventions.

### Reporting Issues

If you encounter any bugs or have feature requests, please open an issue in the [GitHub repository](https://github.com/yourusername/RGame/issues).

## License

RGame is open-source software released under the [MIT License](LICENSE).

## Acknowledgements

- **Raylib**: This project uses [Raylib](https://github.com/raysan5/raylib), an excellent and easy-to-use game development library, as the foundation for graphics and input handling.
- **Contributors**: Special thanks to all the contributors who have helped improve RGame.
- **Community**: Thanks to the developers and users who provide valuable feedback and suggestions!
