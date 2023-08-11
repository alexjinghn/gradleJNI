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

   void run(bool async);

 private:
   void runWorkload(long iter);
   void innerRun();
};

}