# Philosophers: A Concurrency Challenge with Threads and Mutexes

## Overview

The **Philosophers** project is a deep dive into multithreaded programming and synchronization, implemented entirely in C. It simulates the classical "Dining Philosophers Problem," where philosophers alternately think, eat, and sleep, sharing limited resources (forks) without causing deadlocks or race conditions.

This project showcases my ability to design concurrent systems, manage shared resources safely using mutexes, and ensure robust behavior under strict timing constraints. It also demonstrates my attention to detail in handling edge cases and writing efficient, standards-compliant code.

---

## Features

### 1. Core Functionality

- **Thread-Based Simulation:**
  - Each philosopher is implemented as a thread.
  - Philosophers alternate between thinking, eating, and sleeping.

- **Resource Sharing:**
  - Forks (shared resources) are protected using mutexes to prevent data races.
  - Only one philosopher can hold a fork at a time.

- **Simulation Termination:**
  - Stops when a philosopher dies due to starvation.
  - Optionally stops when all philosophers have eaten a specified number of times.

### 2. Logging

- Precise logs capture the state of each philosopher:
  ```
  [timestamp_in_ms] X has taken a fork
  [timestamp_in_ms] X is eating
  [timestamp_in_ms] X is sleeping
  [timestamp_in_ms] X is thinking
  [timestamp_in_ms] X died
  ```
  - `timestamp_in_ms`: Current time in milliseconds.
  - `X`: Philosopher ID.

- Logs are thread-safe and prevent overlapping or corruption.

### 3. Timing and Performance

- **Real-Time Constraints:**
  - Death detection occurs within 10ms of a philosopher starving.
  - Accurate sleep, eat, and think durations using `gettimeofday` and `usleep`.

- **Optimized for Efficiency:**
  - Minimal overhead in thread synchronization.

---

## Technical Highlights

### 1. Synchronization

- Used **pthread mutexes** to prevent simultaneous access to shared resources (forks).
- Implemented a fair locking mechanism to avoid deadlocks.
- Ensured thread-safe logging for consistent output.

### 2. Timing Management

- Used `gettimeofday` to measure precise elapsed time.
- Combined with `usleep` to implement accurate delays for eating, sleeping, and thinking.

### 3. Robustness

- Avoided **race conditions** by carefully locking and unlocking shared resources.
- Prevented **deadlocks** using a strategy to manage fork acquisition.
- Ensured compliance with the "no global variables" rule, encapsulating all shared data within structures.

### 4. Modular Code

- Clean and maintainable code adhering to strict coding standards.
- Separate files for core logic, utilities, and synchronization mechanisms.

---

## Challenges and Solutions

### 1. **Deadlock Prevention**
- **Challenge:** Philosophers could end up waiting indefinitely for forks.
- **Solution:** Implemented a strategy where philosophers pick up forks in a specific order, avoiding circular waiting.

### 2. **Precise Timing**
- **Challenge:** Ensuring that actions like eating and sleeping respect the specified durations.
- **Solution:** Used `gettimeofday` for high-resolution timing and calculated deltas to ensure accuracy.

### 3. **Thread Synchronization**
- **Challenge:** Preventing race conditions when philosophers access shared resources.
- **Solution:** Protected fork states and shared data using mutexes, ensuring atomic operations.

### 4. **Handling Edge Cases**
- **Challenge:** Managing scenarios like a single philosopher with one fork.
- **Solution:** Wrote custom logic to handle such edge cases gracefully.

---

## How to Use

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd philo
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the simulation:
   ```bash
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
   Example:
   ```bash
   ./philo 5 800 200 200 5
   ```

4. Clean up build files:
   ```bash
   make fclean
   ```

---

## Future Improvements

- **Enhanced Debugging:** Add verbose logging options for deeper insight into thread behavior.
- **Visualization:** Create a graphical representation of the simulation.
- **Performance Optimization:** Explore alternatives to mutexes, like spinlocks, for better performance under certain conditions.

---

## Why This Project Matters

This project is a testament to my skills in:

- **Multithreaded Programming:** Designing concurrent systems that are deadlock-free and race-condition-safe.
- **Resource Management:** Efficiently managing shared resources in a constrained environment.
- **C Programming Expertise:** Writing clean, maintainable, and high-performance code in C.

The **Philosophers** project represents a real-world scenario where resource contention and timing precision are critical, making it an excellent demonstration of my problem-solving abilities and technical expertise.

---

## Conclusion

The **Philosophers** project is more than just an academic exercise; it is a practical demonstration of advanced programming concepts in concurrency and synchronization. It reflects my ability to tackle complex challenges with precision and efficiency. I invite you to explore the codebase and witness these principles in action.
