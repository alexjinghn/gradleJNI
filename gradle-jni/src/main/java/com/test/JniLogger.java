package com.test;

import java.util.concurrent.atomic.AtomicLong;

public class JniLogger {
    protected long nativeHandle;

    public JniLogger() {
        nativeHandle = createNewLogger();
    }

    private native long createNewLogger();
}
