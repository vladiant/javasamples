#ifndef NATIVE_CLASS_H
#define NATIVE_CLASS_H

#include <cstdio>
#include <thread>
#include <atomic>
#include <unistd.h>

class NativeClass {
public:
    class Listener {
    public:
        virtual void print(const char* str) = 0;
        virtual ~Listener() {}
    };

private:
    std::atomic<bool> started{false};
    Listener* listener = nullptr;
    std::thread workerThread;

    static void worker(NativeClass* nc) {
        while (nc->started) {
            if (nc->listener != nullptr) {
                nc->listener->print("From native");
            }
            sleep(1);
        }
    }

public:
    NativeClass() {}

    ~NativeClass() {
        started = false;
        if (workerThread.joinable()) {
            workerThread.join();
        }
        if (listener != nullptr) {
            delete listener;
            listener = nullptr;
        }
    }

    void setListener(Listener* listener) {
        if (this->listener != nullptr) {
            delete this->listener;
        }
        this->listener = listener;
    }

    void scan() {
        started = true;
        workerThread = std::thread(worker, this);
        workerThread.join();
        started = false;
    }

    void stop() {
        started = false;
    }
};

#endif // NATIVE_CLASS_H
