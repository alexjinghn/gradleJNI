package com.test;

public class JniLogger extends JniObject {

    public long nativeHandle;

    public JniLogger() {
        nativeHandle = createNewLogger();
    }

    private native long createNewLogger();

    @Override
    public void close() {
        throw new UnsupportedOperationException("Unimplemented method 'close'");
    }
}
