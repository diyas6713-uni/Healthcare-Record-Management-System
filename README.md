## Healthcare Record Management System (C)
A console-based healthcare record management system developed in C using file-based storage.

## Problem Statement
Managing healthcare records manually is inefficient and prone to errors.
This project provides a simple digital solution to manage patient, doctor,
treatment, and billing records in a structured manner.

## Features
- Add, view, update, and delete patient records  
- Add and manage doctor records  
- Assign doctors to patients  
- Record patient treatments  
- Generate and store billing information  
- Persistent data storage using text files  
- Simple and user-friendly console interface 

## Tech Stack
- Language: C
- Storage: File-based (.txt)
- Compiler: GCC
- Concepts Used:
  - File Handling
  - Structures
  - Functions
  - Menu-driven Programming

## Project Structure
src/             - Source code  
docs/            - Project report and documentation  
architecture/    - Flowchart and ER diagram  
assets/          - Screenshots  
sample-data/     - Sample data files  

## System Design
- Flowchart: architecture/Flowchart.txt
- ER Diagram: architecture/ER Diagram.txt

## How to Run
1. Clone the repository
2. Go to the src folder
3. Compile:
   gcc healthcare.c -o healthcare
4. Run:
   ./healthcare

## Program Overview

After running the program, a menu will appear with options such as:

- Patient Module
- Doctor Module
- Billing Module
- Search and Filters
- Exit

Users can select options by entering the corresponding number.

## Screenshots
Screenshots of the application interface are available in the assets/screenshots folder.

## Limitations
- File-based storage instead of database
- No authentication or encryption
- Console-based, single-user application
- Developed for academic purposes

## Learning Outcomes

- Practical understanding of file handling in C  
- Experience with structured and modular programming  
- Implementation of real-world record management logic  
- Improved problem-solving and debugging skills  

## Future Scope
- Database integration - SQLite/MySQL
- User login/authentication
- Improved input validation and error handling
- GUI-based interface
- Enhanced security features

## Author
Diya Singhal

## GitHub Profile: 
https://github.com/diyas6713-uni

## License

This project is developed for **educational purposes only**.