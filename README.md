🎮 C and Raylib Game

A 2D platformer game built using C and the Raylib library. The game features custom sprites, game physics, collision detection, and more.
📋 Prerequisites

Make sure you have the following tools installed on your machine:

    C Compiler (e.g., gcc for Linux/Windows, clang for macOS)
    Raylib Library: Follow the instructions below to install Raylib based on your operating system.

🔧 Installation Instructions
1. Clone the Repository

First, clone the repository to your local machine:

bash

git clone https://github.com/yourusername/yourgame.git
cd yourgame

2. Install Raylib

Follow the instructions below based on your operating system:

    Linux

    bash

sudo apt install libraylib-dev

macOS

bash

    brew install raylib

    Windows
        Download the Raylib installer.
        Follow the setup instructions and include it in your system path.

For detailed installation instructions, visit the Raylib official documentation.
3. Compile the Game

Navigate to the project directory and compile the game using the following command:

bash

gcc -o mygame main.c -lraylib -lm -lpthread -ldl -lrt -lX11

This command links the necessary libraries and outputs an executable named mygame. Adjust the command if you are using a different operating system.
4. Run the Game

After compiling, run the game executable:

bash

./mygame

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

![Gameplay](resources/gameplayScreenshot.png)
