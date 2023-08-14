package com.test;

/**
 * Java flyweight to native worker object
 */
public class JniWorker {
    static {
        NativeLibrary.load();
    }

    protected long nativeHandle;

    public JniWorker(long _nativeHandle) {
        nativeHandle = _nativeHandle;
    }

    public static JniWorker createNewJniWorker() {
        return new JniWorker(newJniWorker());
    }

    public void setLogger(JniLogger logger) {
        setLogger(nativeHandle, logger.nativeHandle);
    }
    public void setIteration(long iteration) {
        setIteration(nativeHandle, iteration);
    }

    public void run() {
        run(nativeHandle);
    }

    private static native long newJniWorker();
    private native void setLogger(long handle, long loggerHandle);
    private native void setIteration(long handle, long iteration);
    private native void run(long handle);
    public static native int version();
}

