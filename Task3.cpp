/*Task 3: Advanced Thread Pool with Task Scheduling (Individual)

Design a thread pool supporting priority-based task scheduling, dependencies between tasks, and error propagation.

Use std:: priority_queue, std::condition_variable, and std:: future effectively.

Demonstrate with examples clearly showing task priorities, dependencies, and exception handling.*/



#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <map>
#include <chrono>
#include <algorithm>  // ←  Add this to fix all_of error


using namespace std;

// Task wrapper with priority and dependencies
struct Task {
    int priority;
    function<void()> func;
    vector<shared_future<void>> dependencies;

    // For priority_queue ordering (max-heap, so higher priority comes first)
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

// Thread Pool class
class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    future<void> submit(function<void()> f, int priority = 0, vector<shared_future<void>> deps = {});

private:
    vector<thread> workers;
    priority_queue<Task> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop;

    void workerThread();
};

// Constructor: launches threads
ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back([this] { this->workerThread(); });
}

// Destructor: joins threads
ThreadPool::~ThreadPool() {
    {
        unique_lock<mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (thread &worker: workers)
        worker.join();
}

// Submit a task with priority and dependencies
future<void> ThreadPool::submit(function<void()> f, int priority, vector<shared_future<void>> deps) {
    auto task_promise = make_shared<promise<void>>();
    auto task_future = task_promise->get_future();

    Task task;
    task.priority = priority;
    task.dependencies = deps;
    task.func = [f, task_promise]() {
        try {
            f();
            task_promise->set_value();
        } catch (...) {
            task_promise->set_exception(current_exception());
        }
    };

    {
        unique_lock<mutex> lock(queue_mutex);
        tasks.push(task);
    }
    condition.notify_one();
    return task_future;
}

// Thread loop
void ThreadPool::workerThread() {
    while (true) {
        Task task;
        {
            unique_lock<mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty())
                return;

            // Wait if top task has unresolved dependencies
            task = tasks.top();
            bool ready = all_of(task.dependencies.begin(), task.dependencies.end(),
                                [](const shared_future<void>& f) {
                                    return f.wait_for(chrono::seconds(0)) == future_status::ready;
                                });

            if (!ready) {
                condition.wait_for(lock, chrono::milliseconds(10));
                continue;
            }

            tasks.pop();
        }
        task.func();
    }
}

// ------------------------
// Example usage
// ------------------------
int main() {
    ThreadPool pool(3);

    // Task A (low priority)
    auto futureA = pool.submit([] {
        cout << "Task A (priority 1) starting\n";
        this_thread::sleep_for(chrono::milliseconds(300));
        cout << "Task A done\n";
    }, 1);

    // Task B (high priority)
    auto futureB = pool.submit([] {
        cout << "Task B (priority 10) starting\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Task B done\n";
    }, 10);

    // Task C (depends on A and B)
    auto futureC = pool.submit([] {
        cout << "Task C (depends on A & B) starting\n";
        cout << "Task C done\n";
    }, 5, { futureA.share(), futureB.share() });

    // Task D (throws an exception)
    auto futureD = pool.submit([] {
        cout << "Task D (throws exception)\n";
        throw runtime_error("Error in Task D");
    }, 3);

    // Wait for all
    futureC.wait();
    try {
        futureD.get();
    } catch (const exception& e) {
        cout << "Caught exception from Task D: " << e.what() << endl;
    }

    cout << "Main done\n";
    return 0;
}


/*______
OUTPUT:

Task A (priority 1) starting
Task B (priority 10) starting
Task B done
Task A done
Task C (depends on A & B) starting
Task C done
Task D (throws exception)
Caught exception from Task D: Error in Task D
Main done  */