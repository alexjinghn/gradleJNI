package com.test;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("java version: " + System.getProperty("java.version"));
        System.out.println("jni version: " + JniWorker.version());
        long iteration = 1000;
        boolean async = false;
        if (args.length >0) {
            iteration = Long.parseLong(args[0]);
            async = args[1].equals("async");
        }
        JniLogger logger = new JniLogger();
        JniWorker worker = JniWorker.createNewJniWorker();
        worker.setLogger(logger);
        worker.setIteration(iteration);
        worker.run(async);
        System.out.println("number of ignored messages : " + logger.getIgnoredLogMessageCount());
        if (logger.getIgnoredLogMessageCount() != iteration) {
            System.out.println("Experiment failed!");
        }
    }
}
