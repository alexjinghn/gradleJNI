#!/bin/bash

JAVA_HOME=/usr/lib/jvm/zulu8-ca-amd64/ ./gradlew build

for ((i=1; i<=10; i++)); do
  echo "jdk8"
  /usr/lib/jvm/zulu8-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main 1000000 | grep "Workload time"
  echo "jdk17"
  /usr/lib/jvm/zulu17-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main 1000000 | grep "Workload time"
done