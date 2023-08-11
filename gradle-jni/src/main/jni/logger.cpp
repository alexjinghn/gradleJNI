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

/**
 * Counterpart to {@link JniUtil::getJniEnv(JavaVM*, jboolean*)}
 *
 * Detachess the current thread from the JVM if it was previously
 * attached
 *
 * @param jvm (IN) A pointer to the JavaVM instance
 * @param attached (IN) JNI_TRUE if we previously had to attach the thread
 *     to the JavaVM to get the JNIEnv
 */
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

static jclass getJClass(JNIEnv* env) {
  jclass jclazz = env->FindClass("com/test/JniLogger");
  assert(jclazz != nullptr);
  return jclazz;
}

static jmethodID getLogMethodId(JNIEnv* env) {
  jclass jclazz = getJClass(env);
  if (jclazz == nullptr) {
    // exception occurred accessing class
    return nullptr;
  }

  static jmethodID mid = env->GetMethodID(
      jclazz, "log", "(JLjava/lang/String;)V");
  assert(mid != nullptr);
  return mid;
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

  m_jLogMethodId = getLogMethodId(env);
  Logv(1, "native logger initialized");
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

void Logger::Logv(long should_log, const char* msg) {

  // pass msg to java callback handler
  jboolean attached_thread = JNI_FALSE;
  JNIEnv* env = getJniEnv(&attached_thread);
  assert(env != nullptr);
  jstring jmsg = env->NewStringUTF(msg);
  if (jmsg == nullptr) {
    // unable to construct string
    if (env->ExceptionCheck()) {
      env->ExceptionDescribe();  // print out exception to stderr
    }
    releaseJniEnv(attached_thread);
    return;
  }

  if (env->ExceptionCheck()) {
    // exception thrown: OutOfMemoryError
    env->ExceptionDescribe();  // print out exception to stderr
    env->DeleteLocalRef(jmsg);
    releaseJniEnv(attached_thread);
    return;
  }

  env->CallVoidMethod(m_jcallback_obj, m_jLogMethodId, (jlong) should_log, jmsg);
  if (env->ExceptionCheck()) {
    // exception thrown
    env->ExceptionDescribe();  // print out exception to stderr
    env->DeleteLocalRef(jmsg);
    releaseJniEnv(attached_thread);
    return;
  }

  env->DeleteLocalRef(jmsg);
  releaseJniEnv(attached_thread);
}

void Logger::attach_then_detach() {
  jboolean attached_thread = JNI_FALSE;
  JNIEnv* env = getJniEnv(&attached_thread);
  assert(env != nullptr);
  releaseJniEnv(attached_thread);
}



JNIEnv* Logger::getJniEnv(jboolean* attached) const {
  return getJniEnvUtil(m_jvm, attached);
}

void Logger::releaseJniEnv(jboolean& attached) const {
  releaseJniEnvUtil(m_jvm, attached);
}

}
