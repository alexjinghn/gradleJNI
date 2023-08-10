package com.test;

public class JniWorker extends JniObject{

    private long nativeHandle;
    public JniWorker(long _nativeHandle) {
        nativeHandle = _nativeHandle;
    }

    public static JniWorker createNewJniWorker() {
        return new JniWorker(newJniWorker());
    }

    private static native long newJniWorker();


    private native void setLogger(long handle,
    long loggerHandle);
	public native void start();
    public native void stop();

    public void setLogger(JniLogger logger) {
        setLogger(nativeHandle, logger.nativeHandle);
    }


    @Override
    public void close() {
        throw new UnsupportedOperationException("Unimplemented method 'close'");
    }
}

