#!/bin/bash

arg1="$1"
arg2="$2"

JAVA_HOME=/usr/lib/jvm/zulu8-ca-amd64/ ./gradlew build

for ((i=1; i<=$arg1; i++)); do
  echo "jdk8"
  /usr/lib/jvm/zulu8-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 | grep "Workload time"
  echo "jdk17"
  /usr/lib/jvm/zulu17-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 | grep "Workload time"
done