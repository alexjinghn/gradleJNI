#include <jni.h>
#include <memory>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "logger.h"

namespace NATIVE_IMPL {
class Worker {
 public:
   Worker();
   ~Worker();

   // pointer to the logger native object, will be set by Java_com_test_JniWorker_setLogger
   std::shared_ptr<Logger> info_log;

   // number of invocations, will be set by Java_com_test_JniWorker_setIteration
   long iteration;

   // starts the workload, will be started by Java_com_test_JniWorker_run
   // this method will start `innerRun()` on a separate thread and block waiting for its completion
   void run();

 private:
   // run targeted iterations of `runWorkload()` and print stats to stdout
   void innerRun();
   // logger workload
   void runWorkload();
};

}