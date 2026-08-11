# Dining Philosophers

A Linux System Programming project that demonstrates the classic **Dining Philosophers Problem** using **Linux processes** and **System V Semaphores**.

## 📌 Description

The program creates five philosopher processes using `fork()`.

Each philosopher repeatedly:

1. Thinks
2. Becomes hungry
3. Picks up two forks
4. Eats
5. Releases the forks

System V semaphores are used to synchronize access to the forks and prevent multiple philosophers from using the same fork simultaneously.

The program uses different fork acquisition orders for even and odd numbered philosophers to avoid deadlock.

## 🛠️ Technologies Used

- C Programming
- Linux System Programming
- Process Creation using `fork()`
- System V IPC
- System V Semaphores
- Inter-Process Synchronization

## 📂 Project Structure

```text
Dining-Philosophers/
│
├── main.c
├── header.h
└── README.md
```

### `main.c`

Contains the main application logic.

It handles:

- Creating philosopher processes
- Initializing semaphores
- Philosopher execution
- Fork acquisition and release
- Process synchronization
- Semaphore cleanup

### `header.h`

Contains:

- Required system header files
- Number of philosophers
- Number of meals
- System V semaphore union
- Global semaphore declaration

## 🔧 Configuration

The number of philosophers and meals can be configured in `header.h`.

```c
#define PHILOSOPHER_COUNT 5
#define TOTAL_MEALS 4
```

By default:

- **5 philosophers**
- **5 forks**
- **4 meals per philosopher**

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
```

Example:

```bash
git clone https://github.com/username/dining-philosophers.git
```

### 2. Enter the Project Directory

```bash
cd dining-philosophers
```

### 3. Compile the Program

Use GCC:

```bash
gcc main.c -o dining_philosophers
```

### 4. Run the Program

```bash
./dining_philosophers
```

## 📤 Sample Output

```text
Philosopher 0 is thinking.
Philosopher 0 is hungry.
Philosopher 0 took left fork 0.
Philosopher 0 took right fork 1.
Philosopher 0 is eating.

Philosopher 1 is thinking.
Philosopher 1 is hungry.
Philosopher 1 took right fork 2.
Philosopher 1 took left fork 1.
Philosopher 1 is eating.
```

The exact order of messages may vary because the philosopher processes execute concurrently.

## 🔐 Synchronization

Each fork is represented by a System V semaphore.

A semaphore value of:

```text
1 → Fork is available
0 → Fork is currently being used
```

The program uses:

```c
semop()
```

to acquire and release forks.

### Fork Acquisition

```text
Semaphore -1
```

The philosopher acquires the fork.

### Fork Release

```text
Semaphore +1
```

The philosopher releases the fork.

## 🔄 Program Flow

```text
Start
  │
  ▼
Create Semaphores
  │
  ▼
Initialize Forks
  │
  ▼
Create Philosopher Processes
  │
  ▼
Think
  │
  ▼
Hungry
  │
  ▼
Acquire Forks
  │
  ▼
Eat
  │
  ▼
Release Forks
  │
  ▼
Repeat
  │
  ▼
Finish Meals
  │
  ▼
Wait for Child Processes
  │
  ▼
Remove Semaphores
  │
  ▼
Exit
```

## 🧹 Cleanup

After all philosopher processes finish their meals, the parent process waits for the child processes and removes the System V semaphore set using:

```c
semctl(semaphore_id, 0, IPC_RMID);
```

This prevents unused IPC resources from remaining in the system.

## 🎯 Concepts Demonstrated

This project demonstrates:

- Process creation
- Parent and child processes
- Inter-process synchronization
- System V IPC
- Semaphores
- Critical section management
- Resource sharing
- Deadlock avoidance
- Process termination and cleanup

## 📚 Requirements

A Linux-based environment with:

- GCC compiler
- Standard C libraries
- System V IPC support

Ubuntu/Debian users can install GCC using:

```bash
sudo apt update
sudo apt install gcc
```

## 👨‍💻 Author

**Ajinkya Killedar**

Linux System Programming Project
