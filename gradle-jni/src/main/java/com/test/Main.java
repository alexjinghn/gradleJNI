package com.test;

public class Main {
    public static void main(String[] args) {
        System.out.println("java version: " + System.getProperty("java.version"));
        System.out.println("jni version: " + JniBridge.version());

//        JniLogger logger = new JniLogger();
//        JniWorker worker = JniWorker.createNewJniWorker();
//        worker.setLogger(logger);
//        worker.start();
//        worker.stop();
    }
}
