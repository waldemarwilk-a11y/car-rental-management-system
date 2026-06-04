# Car Rental Management System (C++)

A console-based vehicle rental management application developed in **C++** using **Object-Oriented Programming (OOP)** principles and file-based data persistence.

The project simulates a simplified car rental company system where administrators can manage vehicles and customers, while clients can browse available vehicles, rent cars, and generate rental invoices.

---

## Features

### Administrator Panel

* Administrator registration and authentication
* Add new vehicles to the system
* Display the complete vehicle inventory
* Search vehicles by ID
* Modify vehicle information
* Remove vehicles from the database
* View registered customer accounts

### Customer Panel

* Customer registration and login
* Browse available and unavailable vehicles
* Rent vehicles by ID
* Vehicle availability tracking
* Automatic invoice generation
* Rental cost calculation

### Data Persistence

Application data is stored locally using file handling (`fstream`), allowing information to persist between application launches without requiring a database.

Stored data includes:

* Vehicle inventory
* Customer accounts
* Administrator accounts

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* File Handling (`fstream`)
* Console-Based User Interface
* Visual Studio 2022

---

## Screenshots

### Main Menu

Application entry point providing login and registration options for administrators and customers.

<img width="574" height="273" alt="Zrzut ekranu 2026-06-04 220116" src="https://github.com/user-attachments/assets/cd8bc1e1-d8d8-481c-8b1f-40cea0e6402d" />

---

### Administrator Panel

Administrative dashboard used for vehicle and customer management.

<img width="550" height="261" alt="Zrzut ekranu 2026-06-04 204805" src="https://github.com/user-attachments/assets/09ee4874-b6c4-46b4-b2df-7cf532c47edb" />

---

### Vehicle Inventory

Complete vehicle inventory displayed for management purposes.

<img width="536" height="259" alt="Zrzut ekranu 2026-06-04 205217" src="https://github.com/user-attachments/assets/2bfc5d06-2c37-4a42-abe6-d14a703c66de" />

---

### Customer Vehicle Browser

List of available and unavailable vehicles displayed before the rental process.

<img width="553" height="566" alt="Zrzut ekranu 2026-06-04 205831" src="https://github.com/user-attachments/assets/5b363bab-f40c-47f5-b6ad-fb3d9bb2cd8e" />

---

### Rental Invoice

Invoice automatically generated after a successful rental transaction.

<img width="587" height="250" alt="Zrzut ekranu 2026-06-04 211325" src="https://github.com/user-attachments/assets/25ee90c0-2d84-4b2e-a9aa-550f1dad1709" />

---

## Project Structure

```text
CarRentalManagementSystem/
│
├── README.md
├── .gitignore
├── CarRentalManagementSystem.sln
│
└── CarRentalManagementSystem/
    ├── main.cpp
    ├── Login.h
    ├── Klient.h
    ├── Pracownik.h
    ├── Samochod.h
    ├── Samochod.cpp
    ├── CarRentalManagementSystem.vcxproj
    └── CarRentalManagementSystem.vcxproj.filters
```

---

## Main Components

### Login

Responsible for user authentication and account management.

### Klient (Customer)

Provides customer functionality such as:

* account registration
* user login
* browsing vehicles
* renting vehicles
* invoice generation

### Pracownik (Administrator)

Provides administrative functionality such as:

* vehicle management
* customer management
* vehicle searching
* vehicle modification
* vehicle removal

### Samochod (Vehicle)

Represents vehicle information, including:

* vehicle model
* unique ID
* rental availability status

---

## Learning Outcomes

This project allowed me to practice:

* Object-Oriented Programming in C++
* Class design and encapsulation
* File input/output operations
* Authentication systems
* Persistent data storage
* Console application development
* Menu-driven application architecture

---

## Future Improvements

Potential future enhancements include:

* Database integration (SQLite / MySQL)
* Vehicle return functionality
* Rental history tracking
* Vehicle categories and filtering
* Improved validation and error handling
* Graphical User Interface (GUI)

---

## Build & Run

### Requirements

* Visual Studio 2022
* MSVC v143 Toolset
* Windows SDK

### Build Steps

1. Open `CarRentalManagementSystem.sln`
2. Select **Debug x64** or **Release x64**
3. Build the solution
4. Run the application

---

## Author

Portfolio project developed to demonstrate practical C++ programming skills, object-oriented design principles, file handling, and console application development.
