#include <jni.h>

namespace NATIVE_IMPL {

class Logger {
 public:
  Logger(JNIEnv* env, jobject jcallback_obj);
  ~Logger();

  // attach the current thread to the JVM then detach immediately
  void attach_then_detach();

 protected:
  JavaVM* m_jvm;
  jobject m_jcallback_obj;

  // attach
  JNIEnv* getJniEnv(jboolean* attached) const;

  // detach
  void releaseJniEnv(jboolean& attached) const;
};

}