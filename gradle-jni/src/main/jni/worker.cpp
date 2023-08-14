#include "worker.h"
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>

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

long calculatePercentile(const std::vector<long>& data, double percentTile) {
    std::vector<long> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    int p99Index = static_cast<int>(std::ceil(percentTile * sortedData.size())) - 1;

    return sortedData[p99Index];
}

Worker::Worker() {
}

Worker::~Worker() {
}

void Worker::run() {
    std::thread t(&Worker::innerRun, this);
    t.join();
    return;
}

void Worker::innerRun() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;
    using std::chrono::nanoseconds;

    std::vector<long> stats;
    std::cout << "start running workload...." << std::endl;
    auto start = high_resolution_clock::now();
    for (long i = 0; i < iteration; i ++) {
      auto t1 = high_resolution_clock::now();
      runWorkload();
      auto t2 = high_resolution_clock::now();
      auto ms_int = duration_cast<nanoseconds>(t2 - t1);
      stats.push_back(ms_int.count());
    }
    auto end = high_resolution_clock::now();
    std::cout << "finished running workload, calculating stats" << std::endl;

    auto total_duration = duration_cast<microseconds>(end - start);
    double mean = calculateMean(stats);

    // Calculate the standard deviation
    double standardDeviation = calculateStandardDeviation(stats, mean);

    long p999Value = calculatePercentile(stats, 0.999);
    long p99Value = calculatePercentile(stats, 0.99);
    long p95Value = calculatePercentile(stats, 0.95);
    long p90Value = calculatePercentile(stats, 0.9);

    std::cout << "Workload time taken (microseconds): " + std::to_string(total_duration.count()) << std::endl;
    std::cout << "Workload time taken mean (nanoseconds): " + std::to_string(mean) << std::endl;
    std::cout << "Workload time taken sd (nanoseconds): " + std::to_string(standardDeviation) << std::endl;
    std::cout << "Workload time taken p999 (nanoseconds): " + std::to_string(p999Value) << std::endl;
    std::cout << "Workload time taken p99 (nanoseconds): " + std::to_string(p99Value) << std::endl;
    std::cout << "Workload time taken p95 (nanoseconds): " + std::to_string(p95Value) << std::endl;
    std::cout << "Workload time taken p90 (nanoseconds): " + std::to_string(p90Value) << std::endl;
}

void Worker::runWorkload() {
  info_log->attach_then_detach();
  return;
}
}
