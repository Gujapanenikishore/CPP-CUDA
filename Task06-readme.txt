========================================================
TASK 6: CONCURRENT MULTI-QUEUE PRODUCER-CONSUMER SYSTEM
========================================================

OBJECTIVE:
----------
- Design a multi-threaded producer-consumer system.
- Use multiple task queues (1 per consumer).
- Implement work-stealing so idle consumers can steal tasks.
- Use mutex, condition_variable for thread synchronization.
- Measure performance and verify balanced task distribution.

--------------------------------------------------------
DESIGN OVERVIEW:
--------------------------------------------------------

1. There are multiple queues (NUM_QUEUES = 10), one for each consumer.
2. Producers distribute tasks randomly among queues.
3. Consumers:
   - First check their own queue
   - If empty, steal a task from the back of another queue
4. The system ensures all tasks are completed efficiently.

--------------------------------------------------------
KEY DATA STRUCTURES:
--------------------------------------------------------

STRUCT: Task
- Contains:
  - int id
  - function<void()> work (represents task logic)

STRUCT: TaskQueue
- Contains:
  - deque<Task> tasks: double-ended queue
  - mutex mtx: protects access
  - condition_variable cv: used to block/wake consumers

GLOBAL:
- vector<TaskQueue> queues(NUM_QUEUES): holds all queues
- atomic<int> completedTasks: counter to track how many tasks are done

--------------------------------------------------------
THREAD FUNCTIONS:
--------------------------------------------------------

PRODUCER:
---------
- Each producer creates a number of tasks.
- Each task is assigned to a random queue.
- Each task simulates work (sleep for 5 ms).
- Tasks are enqueued using enqueueTask().

CONSUMER:
---------
- Each consumer checks its own queue first.
- If empty, attempts to steal from the back of other queues.
- If no task is found:
   - It waits for 10ms using condition_variable.
   - Wakes up if a task is added or tasks are completed.
- Exits when completedTasks >= TOTAL_TASKS.

--------------------------------------------------------
FUNCTION: enqueueTask()
------------------------
- Locks a queue
- Adds a task to the back
- Notifies the consumer waiting on that queue

FUNCTION: tryGetTask()
------------------------
- First tries to pop from own queue (front)
- Then tries to steal from others (back)
- Returns true if task was acquired, false otherwise

--------------------------------------------------------
MAIN FUNCTION FLOW:
-------------------
1. Starts timer using high_resolution_clock
2. Launches producer threads
3. Launches consumer threads
4. Waits for all threads to finish using join()
5. Ends timer and reports elapsed time

--------------------------------------------------------
SAMPLE OUTPUT:
--------------
Starting concurrent multi-queue producer-consumer with work-stealing...
All tasks completed. Time: 312 ms

(Note: Actual time may vary based on CPU, OS, and load)

--------------------------------------------------------
CONFIGURABLE PARAMETERS:
-------------------------

- NUM_QUEUES: Number of task queues and consumers (default: 10)
- NUM_PRODUCERS: Number of producer threads (default: 1)
- TOTAL_TASKS: Total number of tasks to process (default: 1000)

--------------------------------------------------------
HOW TO COMPILE AND RUN:
------------------------

Compile:
  g++ -std=c++17 Task6.cpp -o worksteal -pthread

Run:
  ./worksteal

--------------------------------------------------------
MODIFICATIONS FOR TESTING:
----------------------------

- Change TOTAL_TASKS to 5000 or more to see scaling.
- Increase NUM_PRODUCERS to distribute task load.
- Add logging inside tryGetTask() to observe stealing.
- Increase or decrease task sleep time for benchmarking.

--------------------------------------------------------
ADVANTAGES OF THIS DESIGN:
---------------------------

- Scalable: each consumer owns a queue
- Efficient: idle threads can steal from others
- Balanced: reduces starvation by sharing workload
- Lock-efficient: minimal locking using condition_variable

--------------------------------------------------------
TOPICS COVERED:
----------------

- Multi-threading with std::thread
- Synchronization with std::mutex and std::condition_variable
- Atomic operations with std::atomic
- Work stealing algorithm
- Thread-safe task queues
- Real-time benchmarking using std::chrono

