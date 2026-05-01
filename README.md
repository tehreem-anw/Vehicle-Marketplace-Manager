# PakWheels-CLI: Vehicle Marketplace System

A robust C++ command-line application designed to simulate a vehicle buying and selling ecosystem, inspired by platforms like PakWheels. This project serves as a practical implementation of fundamental **Object-Oriented Programming (OOP)** principles to manage complex user-listing interactions.

The system facilitates a complete marketplace lifecycle—from user registration and vehicle ad creation to administrative oversight and listing management.

---

### 🚀 Key Features

* **User Account Management:** Separate modules for Buyers and Sellers with secure attribute handling.
* **Dynamic Ad Listings:** Support for various vehicle types with specific attributes (Model, Year, Price, Mileage).
* **Search & Filter Engine:** Capability to browse available listings based on specific vehicle criteria.
* **Admin Dashboard:** High-level oversight for managing user accounts and moderating active advertisements.

---

### 💻 Technical Architecture

This version of the project focuses on the structural relationships between objects, ensuring a scalable and organized codebase:

* **Composition:** Used to build the `Vehicle` entity from specific parts (e.g., an `Engine` and `Category` components).
* **Association:** Manages the link between a `Seller` and their multiple `Ad` listings.
* **Aggregation:** The `Marketplace` class acts as a container for `User` and `Listing` objects, maintaining the system's state without strictly owning the lifecycle of every entity.
* **Encapsulation:** Strict use of private attributes and public getters/setters to protect the integrity of user data and pricing information.

---

### 🛠️ Built With

* **Language:** C++
* **Concepts:** Object-Oriented Design (Composition, Association, Aggregation)
* **Environment:** VS Code / Dev C++
* **Version Control:** Git & GitHub
