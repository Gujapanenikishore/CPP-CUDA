#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <vector>
#include <memory>
#include <chrono>

// Struct to represent a task with priority
struct TaskItem {
    int priority;
    std::function<void()> func;

    bool operator<(const TaskItem& other) const {
        return priority < other.priority; // Higher priority = earlier execution
    }
};

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    TaskItem task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop || !taskQueue.empty();
                        });

                        if (stop && taskQueue.empty())
                            return;

                        task = taskQueue.top();
                        taskQueue.pop();
                    }
                    try {
                        task.func(); // May throw, will be captured by packaged_task
                    } catch (...) {
                        std::cerr << "[ThreadPool] Unhandled exception in task.\n";
                    }
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& t : workers)
            t.join();
    }

    // Submit with optional priority and dependency
    template <class Func>
    std::future<void> submit(Func&& f, int priority = 0, std::shared_future<void> dependency = {}) {
        using TaskType = std::packaged_task<void()>;
        auto taskPtr = std::make_shared<TaskType>(std::forward<Func>(f));
        std::future<void> fut = taskPtr->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            taskQueue.emplace(TaskItem{
                priority,
                [taskPtr, dep = std::move(dependency)]() mutable {
                    if (dep.valid()) dep.get();  // Wait for dependency
                    (*taskPtr)();                // Run task (will capture exceptions)
                }
            });
        }
        condition.notify_one();
        return fut;
    }

private:
    std::vector<std::thread> workers;
    std::priority_queue<TaskItem> taskQueue;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// === Demonstration code ===
void runExample() {
    ThreadPool pool(3);

    // T1: Low priority (1)
    auto t1 = pool.submit([] {
        std::cout << "[T1] Low priority (1)\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }, 1);

    // T2: High priority (10)
    auto t2 = pool.submit([] {
        std::cout << "[T2] High priority (10)\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }, 10);

    // T3: Medium priority (5), depends on T1
    auto dep1 = t1.share(); // shared_future allows multiple dependencies
    auto t3 = pool.submit([] {
        std::cout << "[T3] Medium priority (5), depends on T1\n";
    }, 5, dep1);

    // T4: Throws exception
    auto t4 = pool.submit([] {
        std::cout << "[T4] Throws an exception\n";
        throw std::runtime_error("Intentional error!");
    }, 7);

    // T5: Depends on T3
    auto t5 = pool.submit([] {
        std::cout << "[T5] Depends on T3\n";
    }, 3, t3.share());

    // Wait for all to finish and catch exceptions
    try {
        t1.get();
        t2.get();
        t3.get();
        t4.get(); // This will throw
    } catch (const std::exception& ex) {
        std::cerr << "[Main] Caught exception from T4: " << ex.what() << "\n";
    }

    t5.get(); // Wait for final task
}

int main() {
    runExample();
    return 0;
}
