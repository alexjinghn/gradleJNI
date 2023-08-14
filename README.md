# Demo project for JNI attachCurrentThead/detachCurrentThread regression

This is a demo project to show that attachCurrentThead/detachCurrentThread incurs deterministic regression on JDK17 compared to JDK8

# Repro steps

1. checkout repo:
```shell
git clone git@github.com:alexjinghn/gradleJNI.git
```
2. Check JDK installation under /usr/lib/jvm
3. Run benchmark 
```shell
benchmark.sh <num of runs> <iteration per run>
```

# Repro walkthrough

This repro is inspired by Rocksdb logging use case (https://github.com/facebook/rocksdb/blob/main/java/rocksjni/loggerjnicallback.h)
 where there is a background native thread trying to log to JVM context. In doing so, the native background thread has to repeatedly attach and detach from the JVM.

In this repro, we have a worker and a logger:

* The worker drives the execution of a method (`attach_then_detach`) from logger in a loop and calculate the execution stats
* To simulate the rocksdb behavior, the workload from worker is executed on a native thread (not the JNI calling thread)
* The logger, instead of doing any actual logging, just attaches and detaches itself to the JVM from the native thread.


# Benchmarking

The script hardcodes the installation path for JDK8 and JDK11 as:
```shell
JAVA_HOME_8=/usr/lib/jvm/java-8-openjdk-amd64
JAVA_HOME_17=/usr/lib/jvm/java-17-openjdk-amd64
```


```shell
benchmark.sh <num of runs> <iteration per run>
```

sample output:
```shell
$ ./benchmark.sh 5 10000
-----------------------------------------------------------------
Ubuntu version:
-----------------------------------------------------------------
Linux ip-10-110-25-144 5.4.0-1045-aws #47~18.04.1-Ubuntu SMP Tue Apr 13 15:58:14 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
-----------------------------------------------------------------
JDK8 version:
-----------------------------------------------------------------
openjdk version "1.8.0_362"
OpenJDK Runtime Environment (build 1.8.0_362-8u372-ga~us1-0ubuntu1~18.04-b09)
OpenJDK 64-Bit Server VM (build 25.362-b09, mixed mode)
-----------------------------------------------------------------
JDK17 version:
-----------------------------------------------------------------
openjdk version "17.0.7" 2023-04-18
OpenJDK Runtime Environment (build 17.0.7+7-Ubuntu-0ubuntu118.04)
OpenJDK 64-Bit Server VM (build 17.0.7+7-Ubuntu-0ubuntu118.04, mixed mode, sharing)
-----------------------------------------------------------------
building libraries.....
-----------------------------------------------------------------

Deprecated Gradle features were used in this build, making it incompatible with Gradle 7.0.
Use '--warning-mode all' to show the individual deprecation warnings.
See https://docs.gradle.org/6.4/userguide/command_line_interface.html#sec:command_line_warnings

BUILD SUCCESSFUL in 381ms
9 actionable tasks: 9 up-to-date
-----------------------------------------------------------------
start benchmarking....
-----------------------------------------------------------------
iteration 1
iteration 2
iteration 3
iteration 4
iteration 5
Time Taken | Mean            | Standard Deviation | p999            | p99             | p95             | p90            
----------------------------------------
jdk8  110039 μs | 10966.776800 ns | 56177.341432 ns | 532334 ns       | 178610 ns       | 9317 ns         | 7873 ns        
jdk17 179558 μs | 17924.003600 ns | 54217.940476 ns | 321488 ns       | 122924 ns       | 18141 ns        | 15983 ns       
----------------------------------------
jdk8  110509 μs | 11013.906400 ns | 55116.644885 ns | 513406 ns       | 97419 ns        | 9828 ns         | 7960 ns        
jdk17 177801 μs | 17749.037200 ns | 55293.117182 ns | 330321 ns       | 111809 ns       | 18062 ns        | 16026 ns       
----------------------------------------
jdk8  109543 μs | 10919.695700 ns | 56184.273630 ns | 543077 ns       | 106345 ns       | 9569 ns         | 7974 ns        
jdk17 179328 μs | 17901.148800 ns | 54683.063365 ns | 346205 ns       | 112247 ns       | 18124 ns        | 16025 ns       
----------------------------------------
jdk8  112088 μs | 11166.931300 ns | 55597.324850 ns | 529521 ns       | 112062 ns       | 10241 ns        | 8825 ns        
jdk17 178398 μs | 17808.946700 ns | 54630.243726 ns | 296359 ns       | 116179 ns       | 18323 ns        | 16121 ns       
----------------------------------------
jdk8  110469 μs | 11013.433300 ns | 54701.167789 ns | 598978 ns       | 96847 ns        | 10273 ns        | 8487 ns        
jdk17 175880 μs | 17555.650300 ns | 53842.205624 ns | 305101 ns       | 114811 ns       | 18063 ns        | 15962 ns       
----------------------------------------
-----------------------------------------------------------------
DONE!
-----------------------------------------------------------------
```