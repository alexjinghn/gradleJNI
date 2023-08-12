#include "logger.h"
#include <assert.h>
#include <iostream>

namespace NATIVE_IMPL {

static JNIEnv* getJniEnvUtil(JavaVM* jvm, jboolean* attached) {
  assert(jvm != nullptr);
  JNIEnv* env;
  const jint env_rs =
      jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
  if (env_rs == JNI_OK) {
    // current thread is already attached, return the JNIEnv
    *attached = JNI_FALSE;
    return env;
  } else if (env_rs == JNI_EDETACHED) {
    // current thread is not attached, attempt to attach
    const jint rs_attach =
        jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), NULL);
    if (rs_attach == JNI_OK) {
      *attached = JNI_TRUE;
      return env;
    } else {
      // error, could not attach the thread
      std::cerr << "JniUtil::getJniEnv - Fatal: could not attach current "
                   "thread to JVM!"
                << std::endl;
      return nullptr;
    }
  } else if (env_rs == JNI_EVERSION) {
    // error, JDK does not support JNI_VERSION_1_6+
    std::cerr
        << "JniUtil::getJniEnv - Fatal: JDK does not support JNI_VERSION_1_6"
        << std::endl;
    return nullptr;
  } else {
    std::cerr << "JniUtil::getJniEnv - Fatal: Unknown error: env_rs="
              << env_rs << std::endl;
    return nullptr;
  }
}

static void releaseJniEnvUtil(JavaVM* jvm, jboolean& attached) {
  assert(jvm != nullptr);
  if (attached == JNI_TRUE) {
    const jint rs_detach = jvm->DetachCurrentThread();
    assert(rs_detach == JNI_OK);
    if (rs_detach != JNI_OK) {
      std::cerr << "JniUtil::getJniEnv - Warn: Unable to detach current "
                   "thread from JVM!"
                << std::endl;
    }
  }
}

Logger::Logger(JNIEnv* env, jobject jcallback_obj) {
  // Note: jcallback_obj may be accessed by multiple threads,
  // so we ref the jvm not the env
  const jint rs = env->GetJavaVM(&m_jvm);
  if (rs != JNI_OK) {
    // exception thrown
    return;
  }

  // Note: we may want to access the Java callback object instance
  // across multiple method calls, so we create a global ref
  assert(jcallback_obj != nullptr);
  m_jcallback_obj = env->NewGlobalRef(jcallback_obj);
  if (jcallback_obj == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }
}

Logger::~Logger() {
  jboolean attached_thread = JNI_FALSE;
  JNIEnv* env = getJniEnv(&attached_thread);
  assert(env != nullptr);

  if (m_jcallback_obj != nullptr) {
    env->DeleteGlobalRef(m_jcallback_obj);
  }

  releaseJniEnv(attached_thread);
}

JNIEnv* Logger::getJniEnv(jboolean* attached) const {
  return getJniEnvUtil(m_jvm, attached);
}

void Logger::releaseJniEnv(jboolean& attached) const {
  releaseJniEnvUtil(m_jvm, attached);
}

void Logger::attach_then_detach() {
  jboolean attached_thread = JNI_FALSE;
  JNIEnv* env = getJniEnv(&attached_thread);
  assert(env != nullptr);
  releaseJniEnv(attached_thread);
}

}
