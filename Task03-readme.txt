====================================================
TASK 3: ADVANCED THREAD POOL WITH TASK SCHEDULING
====================================================

OBJECTIVE:
----------
Implement a C++ ThreadPool that:
- Supports priority-based task scheduling
- Supports task dependencies
- Propagates exceptions from tasks
- Uses standard threading tools:
  std::thread, std::mutex, std::condition_variable, std::future

KEY FEATURES:
-------------
1. Priority queue (std::priority_queue) to manage task priority
2. Each task may have dependencies (shared_future list)
3. Uses condition variables to notify worker threads
4. Exception-safe via std::promise and std::future

------------------------------------------
STRUCTURE AND LOGIC EXPLANATION
------------------------------------------

STRUCT: Task
------------
- Represents one unit of work in the thread pool
- Contains:
  - priority (int): higher value means higher priority
  - func: actual task to execute
  - dependencies: other tasks this one depends on

- operator< is overloaded for use in priority_queue:
  - Higher priority tasks come first (max-heap behavior)

CLASS: ThreadPool
-----------------
- Manages threads and task execution
- Contains:
  - vector<thread> workers
  - priority_queue<Task> tasks
  - std::mutex and std::condition_variable for safe coordination
  - bool stop to signal shutdown

CONSTRUCTOR
-----------
- Starts a specified number of threads (e.g., 3)
- Each thread runs workerThread()

DESTRUCTOR
----------
- Sets stop = true
- Notifies all worker threads
- Waits (joins) for threads to finish

submit()
--------
- Accepts:
  - function to execute
  - task priority
  - optional list of dependencies (as shared_futures)
- Wraps the task in a lambda that sets promise value or exception
- Pushes task into the priority queue
- Notifies a worker thread

workerThread()
--------------
- Waits for tasks using condition_variable
- Always takes the highest-priority task
- Skips task if dependencies are not yet ready
- Executes task when ready
- Handles both normal and exceptional execution

------------------------------------------
EXAMPLE USAGE: main()
------------------------------------------

1. Task A - low priority (1), takes 300ms
2. Task B - high priority (10), takes 100ms
3. Task C - medium priority (5), depends on A and B
4. Task D - throws an exception (used to test error propagation)

futureC.wait()     - waits until task C is complete
futureD.get()      - triggers and catches exception from task D

------------------------------------------
EXPECTED OUTPUT:
------------------------------------------

Task A (priority 1) starting
Task B (priority 10) starting
Task B done
Task A done
Task C (depends on A & B) starting
Task C done
Task D (throws exception)
Caught exception from Task D: Error in Task D
Main done

Explanation:
- Task B executes first due to higher priority
- Task C waits until both A and B complete
- Task D throws an error, caught using future

------------------------------------------
HOW TO COMPILE AND RUN:
------------------------------------------

Compile:
  g++ -std=c++17 Task3.cpp -o threadpool -pthread

Run:
  ./threadpool

------------------------------------------
HOW TO MODIFY FOR DEMO:
------------------------------------------

- Change priorities in main() to see different execution order
- Add more dependencies (futureX.share()) to Task C
- Replace task body with different print or sleep durations
- Trigger and catch new exception types in Task D

------------------------------------------
KEY CONCEPTS IMPLEMENTED:
------------------------------------------

- Thread creation and management (std::thread)
- Synchronization using mutex and condition_variable
- Priority-based scheduling using std::priority_queue
- Task dependency using std::shared_future
- Exception propagation using std::promise / std::future
- Thread-safe task queue handling
- Clean shutdown and join on destructor

