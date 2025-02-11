# Philosophers - The Dining Philosophers Problem

Welcome to the **Philosophers** project! In this challenge, you will dive into the world of **multithreading** and **mutexes**, simulating a group of philosophers sitting at a table, thinking, eating, and avoiding starvation.

## 📌 Features
- 🧵 **Multi-threading**: Each philosopher is managed as a separate thread.
- 🍴 **Mutex Locks**: Ensuring proper fork handling.
- ⏳ **Time Management**: Tracking eating, thinking, and sleeping cycles.

---
## 📂 Project Structure
```plaintext
├── philo/          # Mandatory part
├── includes/       # Header files
├── src/            # Source files
├── Makefile        # Compilation script
└── README.md       # Project documentation
```
---
## ⚡ Installation & Execution
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/philosophers.git
   cd philosophers
   ```
2. Compile the project:
   ```sh
   make -C philo
   ```
3. Run the simulation:
   ```sh
   ./philo 5 800 200 200
   ```
   **Arguments:**
   - `number_of_philosophers`
   - `time_to_die`
   - `time_to_eat`
   - `time_to_sleep`
   - *(Optional)* `number_of_times_each_philosopher_must_eat`

---
## 📜 Simulation Rules
1. A philosopher **must pick up both forks** to eat.
2. Philosophers alternate between **thinking, eating, and sleeping**.
3. A philosopher **dies if they do not eat within the time_to_die limit**.
4. The simulation stops if all philosophers eat the required number of times.

---
## 📢 Contributions
Contributions are welcome! Feel free to submit issues or pull requests.

---
## 📄 License
This project is licensed under the **MIT License**.

🔗 *Happy coding and good luck!*

 
