#include <jni.h>

namespace NATIVE_IMPL {

class Logger {
 public:
  Logger(JNIEnv* env, jobject jcallback_obj);
  ~Logger();

  void attach_then_detach();

 protected:
  JavaVM* m_jvm;
  jobject m_jcallback_obj;
  JNIEnv* getJniEnv(jboolean* attached) const;
  void releaseJniEnv(jboolean& attached) const;
};

}