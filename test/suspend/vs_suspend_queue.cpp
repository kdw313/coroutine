//
//  Author  : github.com/luncliff (luncliff@gmail.com)
//  License : CC BY 4.0
//
#include <CppUnitTest.h>

#include <thread>

#include <coroutine/return.h>
#include <coroutine/suspend_queue.h>
#include <coroutine/sync.h>

using namespace std;
using namespace std::literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class suspend_queue_test : public TestClass<suspend_queue_test>
{

    TEST_METHOD(suspend_queue_no_await)
    {
        suspend_queue sq{};

        // do nothing with this awaitable object
        auto aw = sq.wait();
        Assert::IsTrue(aw.await_ready() == false);
    }

    TEST_METHOD(suspend_queue_no_thread)
    {
        suspend_queue sq{};

        auto routine = [&sq](int& status) -> return_ignore {
            status = 1;
            co_await sq.wait();
            status = 2;
            co_await sq.wait();
            status = 3;
        };

        int status = 0;
        routine(status);
        Assert::IsTrue(status == 1);

        coroutine_task_t coro{};

        // we know there is a waiting coroutine
        Assert::IsTrue(sq.try_pop(coro));
        coro.resume();
        Assert::IsTrue(status == 2);

        Assert::IsTrue(sq.try_pop(coro));
        coro.resume();
        Assert::IsTrue(status == 3);
    }

    TEST_METHOD(suspend_queue_one_worker_thread)
    {
        suspend_queue sq{};

        // do work with 1 thread
        thread worker{[&sq]() {
            coroutine_task_t coro{};

            while (sq.try_pop(coro) == false)
                this_thread::sleep_for(1s);

            coro.resume();
        }};

        using thread_id_t = std::thread::id;

        auto routine = [&sq](thread_id_t& invoke_id,
                             thread_id_t& resume_id) -> return_ignore {
            invoke_id = this_thread::get_id();
            co_await sq.wait();
            resume_id = this_thread::get_id();
        };

        thread_id_t id1{}, id2{};
        routine(id1, id2);

        auto worker_id = worker.get_id();
        worker.join();
        Assert::IsTrue(id1 != id2);
        Assert::IsTrue(id1
                       == this_thread::get_id()); // invoke id == this thread
        Assert::IsTrue(id2 == worker_id);         // resume id == worker thread
    }

    TEST_METHOD(suspend_queue_multiple_worker_thread)
    {
        suspend_queue sq{};

        auto resume_only_one = [&sq]() {
            size_t retry_count = 5;
            coroutine_task_t coro{};

            while (sq.try_pop(coro) == false)
                if (retry_count--)
                    this_thread::sleep_for(500ms);
                else
                    Assert::Fail(L"failed to pop from suspend queue");

            coro.resume();
        };

        // do work with 3 thread
        // suspend_queue works in thread-safe manner
        thread w1{resume_only_one}, w2{resume_only_one}, w3{resume_only_one};

        auto routine = [&sq]() -> return_ignore {
            co_await sq.wait(); // just wait schedule
        };

        routine(); // spawn 3 (num of worker) coroutines
        routine();
        routine();

        // all workers must resumed their own tasks
        w1.join();
        w2.join();
        w3.join();
    }
};
