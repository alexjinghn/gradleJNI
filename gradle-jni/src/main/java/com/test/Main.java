package com.test;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("java version: " + System.getProperty("java.version"));
        System.out.println("jni version: " + JniWorker.version());
        long iteration = 1000;
        if (args.length >0) {
            iteration = Long.parseLong(args[0]);
        }
        JniLogger logger = new JniLogger();
        JniWorker worker = JniWorker.createNewJniWorker();
        worker.setLogger(logger);
        worker.setIteration(iteration);
        worker.run();
        System.out.println("number of ignored messages : " + logger.getIgnoredLogMessageCount());
//        worker.start();
//        Thread.sleep(2000);
//        worker.stop();
    }
}
