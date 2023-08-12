#include "com_test_JniWorker.h"
#include "worker.h"
#include <memory>

JNIEXPORT jint JNICALL Java_com_test_JniWorker_version
  (JNIEnv *, jclass) {
    return 4;
}

JNIEXPORT jlong JNICALL Java_com_test_JniWorker_newJniWorker
  (JNIEnv *, jclass) {
  auto* sptr_logger = new std::shared_ptr<NATIVE_IMPL::Worker>(
      new NATIVE_IMPL::Worker());

  return static_cast<jlong>(reinterpret_cast<size_t>(sptr_logger));
}

JNIEXPORT void JNICALL Java_com_test_JniWorker_setLogger
  (JNIEnv * env, jobject jobj, jlong worker_handle, jlong logger_handle) {
  std::shared_ptr<NATIVE_IMPL::Logger>* pLogger =
      reinterpret_cast<std::shared_ptr<NATIVE_IMPL::Logger>*>(
          logger_handle);
  reinterpret_cast<NATIVE_IMPL::Worker*>(worker_handle)->info_log = *pLogger;
  return;
}

JNIEXPORT void JNICALL Java_com_test_JniWorker_setIteration
  (JNIEnv * env, jobject jobj, jlong worker_handle, jlong iteration) {
  reinterpret_cast<NATIVE_IMPL::Worker*>(worker_handle)->iteration = iteration;
  return;
}

JNIEXPORT void JNICALL Java_com_test_JniWorker_run
  (JNIEnv * env, jobject jobj, jlong worker_handle) {
  reinterpret_cast<NATIVE_IMPL::Worker*>(worker_handle)->run();
  return;
}
