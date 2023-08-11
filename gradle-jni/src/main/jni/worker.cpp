#include "worker.h"
#include <string>
#include <chrono>

namespace NATIVE_IMPL {

Worker::Worker(): stopFlag(false) {
}

Worker::~Worker() {
}

void Worker::threadFunction() {
  while (!stopFlag.load()) {
    // Your thread's work here
    std::cout << "Thread is running..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Thread stopped." << std::endl;
}

void Worker::runWorkload() {
  for (long i = 0; i < iteration ; i++) {
    info_log->Logv(0, ("test" + std::to_string(i)).c_str());
  }
  return;
}

void Worker::run() {
    info_log->Logv(1, "running workload...");
    info_log->Logv(1, std::to_string(iteration).c_str());

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    auto t1 = high_resolution_clock::now();
    runWorkload();
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<microseconds>(t2 - t1);

    info_log->Logv(1, ("Workload time taken (microseconds): " + std::to_string(ms_int.count())).c_str());
    return;
}

void Worker::start() {
    info_log->Logv(1, "work started");
    info_log->Logv(1, std::to_string(iteration).c_str());
//    if (!isRunning()) {
//      stopFlag.store(false);
//      myThread = std::thread(&Worker::threadFunction, this);
//    }
    return;
}

void Worker::stop() {
//    if (isRunning()) {
//      stopFlag.store(true);
//      if (myThread.joinable()) {
//        try {
//          myThread.join();
//        } catch (const std::system_error& e) {
//          // Handle exceptions that might occur during thread termination
//          std::cerr << "Error while stopping thread: " << e.what() << std::endl;
//        }
//      }
//    }
    info_log->Logv(1, "work stopped");
    return;
}
}
