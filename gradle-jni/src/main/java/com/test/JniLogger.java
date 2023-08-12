package com.test;

import java.util.concurrent.atomic.AtomicLong;

public class JniLogger extends JniObject {
    private AtomicLong counter = new AtomicLong(0);

    public JniLogger() {
        nativeHandle = createNewLogger();
    }

    private native long createNewLogger();


    private void log(long shouldLog, String message) {
        if (shouldLog != 0) {
            System.out.println("NATIVE: " + message);
        } else {
            assert message.contains("test");
            counter.getAndIncrement();
        }
    }

    public long getIgnoredLogMessageCount() {
        return counter.get();
    }
}
