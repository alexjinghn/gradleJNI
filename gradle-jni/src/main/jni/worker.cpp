#include "worker.h"
#include <string>
#include <chrono>
#include <vector>
#include <cmath>

namespace NATIVE_IMPL {


double calculateMean(const std::vector<long>& numbers) {
    long sum = 0;
    for (const long& num : numbers) {
        sum += num;
    }
    return static_cast<double>(sum) / numbers.size();
}

double calculateStandardDeviation(const std::vector<long>& numbers, double mean) {
    double sumSquaredDiffs = 0.0;
    for (const long& num : numbers) {
        double diff = num - mean;
        sumSquaredDiffs += diff * diff;
    }
    return std::sqrt(sumSquaredDiffs / numbers.size());
}

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

void Worker::runWorkload(long iter) {
  info_log->Logv(0, ("test" + std::to_string(iter)).c_str());
  return;
}

void Worker::run() {
    info_log->Logv(1, "running workload...");
    info_log->Logv(1, std::to_string(iteration).c_str());

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;
    using std::chrono::nanoseconds;

    std::vector<long> stats;
    auto start = high_resolution_clock::now();
    for (long i = 0; i < iteration; i ++) {
      auto t1 = high_resolution_clock::now();
      runWorkload(i);
      auto t2 = high_resolution_clock::now();
      auto ms_int = duration_cast<nanoseconds>(t2 - t1);
      stats.push_back(ms_int.count());
    }
    auto end = high_resolution_clock::now();
    auto total_duration = duration_cast<microseconds>(end - start);
    double mean = calculateMean(stats);

    // Calculate the standard deviation
    double standardDeviation = calculateStandardDeviation(stats, mean);

    info_log->Logv(1, ("Workload time taken (microseconds): " + std::to_string(total_duration.count())).c_str());
    info_log->Logv(1, ("Workload time taken mean (nanoseconds): " + std::to_string(mean)).c_str());
    info_log->Logv(1, ("Workload time taken sd (nanoseconds): " + std::to_string(standardDeviation)).c_str());
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
