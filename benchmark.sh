#!/bin/bash

arg1="$1"
arg2="$2"

JAVA_HOME=/usr/lib/jvm/zulu8-ca-amd64/ ./gradlew build
#JAVA_HOME=/Library/Java/JavaVirtualMachines/zulu-8.jdk/Contents/Home/ ./gradlew build

for ((i=1; i<=$arg1; i++)); do
  echo "jdk8"
#  output=$(/Library/Java/JavaVirtualMachines/zulu-8.jdk/Contents/Home/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)

  output=$(/usr/lib/jvm/zulu8-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)
  time_taken=$(echo "$output" | grep -oP '(?<=time taken \(microseconds\): )\d+')
  mean=$(echo "$output" | grep -oP '(?<=mean \(nanoseconds\): )\d+\.\d+')
  sd=$(echo "$output" | grep -oP '(?<=sd \(nanoseconds\): )\d+\.\d+')

  echo "Time taken: $time_taken microseconds"
  echo "Mean: $mean nanoseconds"
  echo "Standard Deviation: $sd nanoseconds"

  echo "jdk17"
#  output=$(/Library/Java/JavaVirtualMachines/zulu-17.jdk/Contents/Home/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)
  output=$(/usr/lib/jvm/zulu17-ca-amd64/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)
  time_taken=$(echo "$output" | grep -oP '(?<=time taken \(microseconds\): )\d+')
  mean=$(echo "$output" | grep -oP '(?<=mean \(nanoseconds\): )\d+\.\d+')
  sd=$(echo "$output" | grep -oP '(?<=sd \(nanoseconds\): )\d+\.\d+')

  echo "Time taken: $time_taken microseconds"
  echo "Mean: $mean nanoseconds"
  echo "Standard Deviation: $sd nanoseconds"
done