# Blackjack Simulation 🃏

A command-line Blackjack game simulation.

## About The Project
This is my first C++ project. I developed this game primarily to learn the fundamentals of C++ and to get hands-on practice with Object-Oriented Programming (OOP) principles. 

## Features
* Classic Blackjack gameplay loop (Hit, Stand).
* Dealer logic (e.g., dealer hits until reaching 17).
* Dynamic card drawing and score calculation.
* Clean command-line interface.

## OOP Architecture
The game is built using a structured Object-Oriented approach to ensure modularity and readable code:
* **Card & Deck:** Manages the properties of individual cards and the logic for shuffling and drawing from a deck.
* **Player & Dealer:** Represents the participants, managing their hands and current scores.
* **Design Choices:** The codebase emphasizes clean class design, including the clear separation of constructor functions from static functions within the class implementations.

## Getting Started

### Prerequisites
To compile and run this project, you will need a C++ compiler installed on your system (such as GCC/G++ or MSVC).

### Compilation and Execution
If you are using a terminal with `g++`, you can compile the game by navigating to the project directory and running:

```bash
g++ -o blackjack main.cpp