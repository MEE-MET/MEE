#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>


namespace tp
{

struct TaskQueue
{
    std::queue<std::function<void()>> m_tasks;
    std::mutex                        m_mutex;
    std::atomic<uint32_t>             m_remaining_tasks = 0;

    /**
     * @brief Add a task to the queue
     * 
     * @tparam TCallback callback type
     * @param callback callback to add
     */
    template<typename TCallback>
    void addTask(TCallback&& callback)
    {
        std::lock_guard<std::mutex> lock_guard{m_mutex};
        m_tasks.push(std::forward<TCallback>(callback));
        m_remaining_tasks++;
    }

    /**
     * @brief Get a task from the queue
     * 
     * @param target_callback callback to fill
     */
    void getTask(std::function<void()>& target_callback)
    {
        {
            std::lock_guard<std::mutex> lock_guard{m_mutex};
            if (m_tasks.empty()) {
                return;
            }
            target_callback = std::move(m_tasks.front());
            m_tasks.pop();
        }
    }

    /**
     * @brief Wait for a task to be available
     */
    static void wait()
    {
        std::this_thread::yield();
    }

    /**
     * @brief Wait for all tasks to be completed
     */
    void waitForCompletion() const
    {
        while (m_remaining_tasks > 0) {
            wait();
        }
    }

    /**
     * @brief Notify that a task has been completed
     */
    void workDone()
    {
        m_remaining_tasks--;
    }
};

struct Worker
{
    uint32_t              m_id      = 0;
    std::thread           m_thread;
    std::function<void()> m_task    = nullptr;
    bool                  m_running = true;
    TaskQueue*            m_queue   = nullptr;

    Worker() = default;

    /**
     * @brief Construct a new Worker object
     * 
     * @param queue task queue
     * @param id worker id
     */
    Worker(TaskQueue& queue, uint32_t id)
        : m_id{id}
        , m_queue{&queue}
    {
        m_thread = std::thread([this](){
            run();
        });
    }

    /**
     * @brief Run the worker
     */
    void run()
    {
        while (m_running) {
            m_queue->getTask(m_task);
            if (m_task == nullptr) {
                TaskQueue::wait();
            } else {
                m_task();
                m_queue->workDone();
                m_task = nullptr;
            }
        }
    }

    /**
     * @brief Stop the worker
     */
    void stop()
    {
        m_running = false;
        m_thread.join();
    }
};

struct ThreadPool
{
    uint32_t            m_thread_count = 0;
    TaskQueue           m_queue;
    std::vector<Worker> m_workers;

    /**
     * @brief Construct a new Thread Pool object
     * 
     * @param thread_count number of threads
     */
    explicit
    ThreadPool(uint32_t thread_count)
        : m_thread_count{thread_count}
    {
        m_workers.reserve(thread_count);
        for (uint32_t i{thread_count}; i--;) {
            m_workers.emplace_back(m_queue, static_cast<uint32_t>(m_workers.size()));
        }
    }

    /**
     * @brief Destroy the Thread Pool object
     */
    virtual ~ThreadPool()
    {
        for (Worker& worker : m_workers) {
            worker.stop();
        }
    }

    /**
     * @brief Add a task to the queue
     * 
     * @tparam TCallback callback type
     * @param callback callback to add
     */
    template<typename TCallback>
    void addTask(TCallback&& callback)
    {
        m_queue.addTask(std::forward<TCallback>(callback));
    }

    /**
     * @brief Wait for all tasks to be completed
     */
    void waitForCompletion() const
    {
        m_queue.waitForCompletion();
    }

    /**
     * @brief Dispatch a task to the workers
     * 
     * @tparam TCallback callback type
     * @param callback callback to dispatch
     */
    template<typename TCallback>
    void dispatch(uint32_t element_count, TCallback&& callback)
    {
        const uint32_t batch_size = element_count / m_thread_count;
        for (uint32_t i{0}; i < m_thread_count; ++i) {
            const uint32_t start = batch_size * i;
            const uint32_t end   = start + batch_size;
            addTask([start, end, &callback](){ callback(start, end); });
        }

        if (batch_size * m_thread_count < element_count) {
            const uint32_t start = batch_size * m_thread_count;
            callback(start, element_count);
        }

        waitForCompletion();
    }
};

}
