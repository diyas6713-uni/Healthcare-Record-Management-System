## Healthcare Record Management System (C)
A console-based healthcare record management system developed in C using file-based storage.

## Problem Statement
Managing healthcare records manually is inefficient and prone to errors.
This project provides a simple digital solution to manage patient, doctor,
treatment, and billing records in a structured manner.

## Features
- Add, update, and delete patient records
- Manage doctor details and specializations
- Assign doctors to patients
- Maintain treatment history
- Generate billing information
- Search and filter records
- View basic statistics

## Tech Stack
- Language: C
- Storage: File-based (.txt)
- Compiler: GCC

## Project Structure
src/             - Source code  
docs/            - Project report and documentation  
architecture/    - Flowchart and ER diagram  
assets/          - Screenshots  
sample-data/     - Sample data files  

## How to Run
1. Clone the repository
2. Go to the src folder
3. Compile:
   gcc healthcare.c -o healthcare
4. Run:
   ./healthcare

## System Design
- Flowchart: architecture/Flowchart.txt
- ER Diagram: architecture/ER Diagram.txt

## Screenshots
Screenshots of the application interface are available in the assets/screenshots folder.

## Limitations
- File-based storage instead of database
- No authentication or encryption
- Console-based, single-user application
- Developed for academic purposes

## Future Scope
- Database integration
- User authentication
- GUI-based interface
- Enhanced security features

## Author
Diya Singhal
