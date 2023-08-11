package com.test;

public abstract class JniObject  implements AutoCloseable {
    protected long nativeHandle;
    public abstract void close();
}
