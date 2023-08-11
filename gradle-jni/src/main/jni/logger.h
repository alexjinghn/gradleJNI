#include <jni.h>

namespace NATIVE_IMPL {

class Logger {
 public:
  Logger(JNIEnv* env, jobject jcallback_obj);
  ~Logger();

  const jobject& GetJavaObject() const { return m_jcallback_obj; }
  void Logv(long should_log, const char* msg);
  void attach_then_detach();

 protected:
  JavaVM* m_jvm;
  jobject m_jcallback_obj;
  JNIEnv* getJniEnv(jboolean* attached) const;
  void releaseJniEnv(jboolean& attached) const;

  jmethodID m_jLogMethodId;
};

}