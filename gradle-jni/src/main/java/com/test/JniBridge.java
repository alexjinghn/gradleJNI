package com.test;

public class JniBridge {

    static {
        NativeLibrary.load();
    }

    public static native int version();

    public static native int build();

    public static native long[] nativeCalculateSquares(long[] values, int numValue);


}