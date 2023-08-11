#include "com_test_JniLogger.h"
#include "logger.h"
#include <memory>


JNIEXPORT jlong JNICALL Java_com_test_JniLogger_createNewLogger
  (JNIEnv * env, jobject jobj) {
  auto* sptr_logger = new std::shared_ptr<NATIVE_IMPL::Logger>(
      new NATIVE_IMPL::Logger(env, jobj));
  return static_cast<jlong>(reinterpret_cast<size_t>(sptr_logger));
}