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

   std::shared_ptr<Logger> info_log;
   long iteration;

   void run();
   void start();
   void stop();

   bool isRunning() const {
     return myThread.joinable();
   }

 private:
   std::atomic<bool> stopFlag;
   std::thread myThread;

   void threadFunction();

   void runWorkload(long iter);
};

}