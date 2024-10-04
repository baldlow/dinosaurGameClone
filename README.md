🎮 C and Raylib Game

A 2D platformer game built using C and the Raylib library. The game features custom sprites, game physics, collision detection, and more.
📋 Table of Contents

    Prerequisites
    Installation Instructions
    How to Play
    Troubleshooting
    Project Structure
    Screenshots
    Contribution
    License
    Contact

📋 Prerequisites

Make sure you have the following tools installed on your machine:

    C Compiler (e.g., gcc for Linux/Windows, clang for macOS)
    Raylib Library: Follow the instructions below to install Raylib based on your operating system.

🔧 Installation Instructions

    Clone the Repository

git clone https://github.com/baldlow/dinosaurGameClone.git
cd dinosaurGameClone

    Install Raylib

Follow the instructions below based on your operating system:

    Linux

    sudo apt install libraylib-dev

macOS

brew install raylib

    Windows
        Download the Raylib installer.
        Follow the setup instructions and include it in your system path.
        For detailed installation instructions, visit the Raylib official documentation.

    Compile the Game

Navigate to the project directory and compile the game using the following command:

gcc -o dinosaurGameClone main.c -lraylib -lm -lpthread -ldl -lrt -lX11

This command links the necessary libraries and outputs an executable named dinosaurGameClone. Adjust the command if you are using a different operating system.

    Run the Game

After compiling, run the game executable:

./dinosaurGameClone

🕹️ How to Play

    Arrow Keys: Move your character left or right.
    Spacebar: Jump.
    R: Restart the level.
    Esc: Quit the game.

Avoid obstacles, collect items, and reach the goal to complete each level!
💡 Troubleshooting

    If you encounter errors during compilation, make sure that Raylib is correctly installed and the compiler can locate its header files and libraries.
    Ensure your compiler supports C99 or later standards.
    Check for typos or incorrect file paths if you get errors like file not found.

📂 Project Structure

Here's a quick look at the structure of the project:

.
├── README.md          # Project documentation
├── main.c             # Main game source code
├── resources/         # Game assets (sprites, sounds, etc.)

✨ Screenshots

🤝 Contribution

Contributions are welcome! Please follow these steps:

    Fork the repository.
    Create a new branch (git checkout -b feature-branch).
    Make your changes.
    Commit your changes (git commit -m 'Add some feature').
    Push to the branch (git push origin feature-branch).
    Open a pull request.

📜 License

This project is licensed under the MIT License. See the LICENSE file for details.
