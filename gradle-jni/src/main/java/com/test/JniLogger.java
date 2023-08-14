package com.test;

/**
 * Java flyweight to native logger object
 */
public class JniLogger {
    protected long nativeHandle;

    public JniLogger() {
        nativeHandle = createNewLogger();
    }

    private native long createNewLogger();
}
