/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_test_JniWorker */

#ifndef _Included_com_test_JniWorker
#define _Included_com_test_JniWorker
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_test_JniWorker
 * Method:    newJniWorker
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_test_JniWorker_newJniWorker
  (JNIEnv *, jclass);

/*
 * Class:     com_test_JniWorker
 * Method:    setLogger
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_test_JniWorker_setLogger
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     com_test_JniWorker
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_test_JniWorker_start
  (JNIEnv *, jobject);

/*
 * Class:     com_test_JniWorker
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_test_JniWorker_stop
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
