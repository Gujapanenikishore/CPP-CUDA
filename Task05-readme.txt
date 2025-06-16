===========================================
TASK 5: LOCK-FREE ATOMIC SMART POINTER (C++)
===========================================

OBJECTIVE:
----------
To implement a thread-safe, lock-free smart pointer using:
- Atomic reference counting (using std::atomic)
- No use of mutex or locking mechanisms
- Multi-threaded correctness and stress testing
- Benchmark against std::shared_ptr

-------------------------------------------
KEY CONCEPTS:
-------------
- Reference counting: tracks how many smart pointers share ownership
- Atomic operations: ensure thread-safe increments/decrements
- Lock-free design: improves performance in concurrent environments

-------------------------------------------
STRUCTURE:
----------

CLASS: AtomicSharedPtr<T>
--------------------------

Private Inner Struct: ControlBlock
- Holds:
  - T* ptr: pointer to managed object
  - atomic<size_t> refCount: number of references

Private Member:
- ControlBlock* block: pointer to the control block

Public Functions:

1. Constructor (T* ptr)
   - Creates new ControlBlock with refCount = 1

2. Copy Constructor
   - Increments reference count atomically

3. Copy Assignment
   - Releases old reference
   - Copies new block and increments its refCount

4. Destructor
   - Decrements refCount atomically
   - Deletes object and control block when count reaches zero

5. Dereference Operators:
   - operator-> and operator* to access the actual object

6. isValid()
   - Checks if smart pointer is pointing to a valid object

7. use_count()
   - Returns current reference count

Private Function: release()
- Called on destruction or assignment
- Atomically decrements count
- Deletes block if last owner

-------------------------------------------
STRUCT: TestData
-----------------
- Contains:
  - int value = 0
  - Constructor initializes it
  - doWork(): increments value by 1

-------------------------------------------
FUNCTION: stressTestAtomicSharedPtr()
-------------------------------------
Purpose:
- Test AtomicSharedPtr across multiple threads

Steps:
1. Create AtomicSharedPtr<TestData> shared(new TestData(42))
2. Launch 10 threads
3. Each thread copies the smart pointer and calls doWork() 100,000 times
4. Join all threads
5. Print:
   - Final value of shared object
   - Reference count
   - Time taken

Expected:
- Final value = 42 + 10 * 100000 = 1000001
- Ref count = 1 (only shared in main remains)

-------------------------------------------
FUNCTION: stressTestStdSharedPtr()
-----------------------------------
Purpose:
- Same logic as above but using std::shared_ptr

Used for comparison:
- Shows baseline behavior of standard smart pointers
- Verifies performance difference

-------------------------------------------
MAIN FUNCTION
-------------
- Calls both stress tests
- Shows performance output for each

-------------------------------------------
EXPECTED OUTPUT:
----------------

===== Lock-Free Atomic Shared Pointer Test =====
[AtomicSharedPtr] Final value: 1000001
[AtomicSharedPtr] Ref count: 1
[AtomicSharedPtr] Time: 134 ms

===== std::shared_ptr Baseline Test =====
[std::shared_ptr] Final value: 1000001
[std::shared_ptr] Use count: 1
[std::shared_ptr] Time: 150 ms

Note: Time varies based on system load and CPU performance.

-------------------------------------------
COMPILATION AND EXECUTION
--------------------------

To compile:
  g++ -std=c++17 Task5.cpp -o smart_ptr -pthread

To run:
  ./smart_ptr

-------------------------------------------
MODIFICATION OPTIONS
---------------------
- Change THREADS or ITERATIONS to scale the test
- Modify TestData::doWork() to simulate heavier load
- Try with different data types (e.g., string, double)
- Add more logs to monitor behavior

-------------------------------------------
ADVANTAGES OF AtomicSharedPtr
------------------------------
- No locks or mutex required
- Works efficiently in multi-threaded programs
- Memory-safe (deletes object only once)

-------------------------------------------
TOPICS DEMONSTRATED:
---------------------
- Smart pointers and ownership
- std::atomic and memory_order
- Thread creation and joining
- Stress testing concurrency
- Performance benchmarking

