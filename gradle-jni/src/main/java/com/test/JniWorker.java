package com.test;

public class JniWorker extends JniObject{
    static {
        NativeLibrary.load();
    }

    public JniWorker(long _nativeHandle) {
        nativeHandle = _nativeHandle;
    }

    public static JniWorker createNewJniWorker() {
        return new JniWorker(newJniWorker());
    }

    private static native long newJniWorker();
    private native void setLogger(long handle, long loggerHandle);

    private native void setIteration(long handle, long iteration);

    private native void run(long handle, long async);
	private native void start(long handle);
    private native void stop(long handle);

    public static native int version();

    public void setLogger(JniLogger logger) {
        setLogger(nativeHandle, logger.nativeHandle);
    }
    public void setIteration(long iteration) {
        setIteration(nativeHandle, iteration);
    }

    public void run(boolean async) {
        if (async) {
            run(nativeHandle, 1);
        } else {
            run(nativeHandle, 0);
        }
    }

    public void start() {
        start(nativeHandle);
    }

    public void stop() {
        stop(nativeHandle);
    }

    @Override
    public void close() {
        throw new UnsupportedOperationException("Unimplemented method 'close'");
    }
}

