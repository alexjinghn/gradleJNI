#!/bin/bash

arg1="$1"
arg2="$2"


#JAVA_HOME_8=/usr/lib/jvm/java-8-openjdk-amd64
#JAVA_HOME_17=/usr/lib/jvm/java-17-openjdk-amd64

JAVA_HOME_8=/usr/lib/jvm/zulu8-ca-amd64
JAVA_HOME_17=/usr/lib/jvm/zulu17-ca-amd64

echo "-----------------------------------------------------------------"
echo "JDK8 version:"
echo "-----------------------------------------------------------------"
$JAVA_HOME_8/bin/java -version


echo "-----------------------------------------------------------------"
echo "JDK17 version:"
echo "-----------------------------------------------------------------"
$JAVA_HOME_17/bin/java -version

echo "-----------------------------------------------------------------"
echo "building libraries....."
echo "-----------------------------------------------------------------"

JAVA_HOME=$JAVA_HOME_8 ./gradlew build

echo "-----------------------------------------------------------------"
echo "start benchmarking...."
echo "-----------------------------------------------------------------"

jdk8_time_taken_arr=()
jdk8_mean_arr=()
jdk8_sd_arr=()
jdk8_p999_arr=()
jdk8_p99_arr=()
jdk8_p95_arr=()
jdk8_p90_arr=()


jdk17_time_taken_arr=()
jdk17_mean_arr=()
jdk17_sd_arr=()
jdk17_p999_arr=()
jdk17_p99_arr=()
jdk17_p95_arr=()
jdk17_p90_arr=()

for ((i=1; i<=$arg1; i++)); do
  echo "iteration $i"

  output=$($JAVA_HOME_8/bin/java -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)

  time_taken=$(echo "$output" | grep -oP '(?<=time taken \(microseconds\): )\d+')
  mean=$(echo "$output" | grep -oP '(?<=mean \(nanoseconds\): )\d+\.\d+')
  sd=$(echo "$output" | grep -oP '(?<=sd \(nanoseconds\): )\d+\.\d+')
  p999=$(echo "$output" | grep -oP '(?<=p999 \(nanoseconds\): )\d+')
  p99=$(echo "$output" | grep -oP '(?<=p99 \(nanoseconds\): )\d+')
  p95=$(echo "$output" | grep -oP '(?<=p95 \(nanoseconds\): )\d+')
  p90=$(echo "$output" | grep -oP '(?<=p90 \(nanoseconds\): )\d+')

  jdk8_time_taken_arr+=("$time_taken")
  jdk8_mean_arr+=("$mean")
  jdk8_sd_arr+=("$sd")
  jdk8_p99_arr+=("$p99")
  jdk8_p95_arr+=("$p95")
  jdk8_p90_arr+=("$p90")
  jdk8_p999_arr+=("$p999")



  output=$($JAVA_HOME_17/bin/java -XX:+UseParallelGC -cp gradle-jni/build/libs/gradle-jni.jar com.test.Main $arg2 2>1)

  time_taken=$(echo "$output" | grep -oP '(?<=time taken \(microseconds\): )\d+')
  mean=$(echo "$output" | grep -oP '(?<=mean \(nanoseconds\): )\d+\.\d+')
  sd=$(echo "$output" | grep -oP '(?<=sd \(nanoseconds\): )\d+\.\d+')
  p999=$(echo "$output" | grep -oP '(?<=p999 \(nanoseconds\): )\d+')
  p99=$(echo "$output" | grep -oP '(?<=p99 \(nanoseconds\): )\d+')
  p95=$(echo "$output" | grep -oP '(?<=p95 \(nanoseconds\): )\d+')
  p90=$(echo "$output" | grep -oP '(?<=p90 \(nanoseconds\): )\d+')

  jdk17_time_taken_arr+=("$time_taken")
  jdk17_mean_arr+=("$mean")
  jdk17_sd_arr+=("$sd")
  jdk17_p99_arr+=("$p99")
  jdk17_p95_arr+=("$p95")
  jdk17_p90_arr+=("$p90")
  jdk17_p999_arr+=("$p999")
done


printf "%-10s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s\n" "Time Taken" "Mean" "Standard Deviation" "p999" "p99" "p95" "p90"
echo "----------------------------------------"
for ((i = 0; i < ${#jdk8_time_taken_arr[@]}; i++)); do
    printf "jdk8  %-10s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s\n" "${jdk8_time_taken_arr[i]} μs" "${jdk8_mean_arr[i]} ns" "${jdk8_sd_arr[i]} ns" "${jdk8_p999_arr[i]} ns" "${jdk8_p99_arr[i]} ns" "${jdk8_p95_arr[i]} ns" "${jdk8_p90_arr[i]} ns"
    printf "jdk17 %-10s | %-15s | %-15s | %-15s | %-15s | %-15s | %-15s\n" "${jdk17_time_taken_arr[i]} μs" "${jdk17_mean_arr[i]} ns" "${jdk17_sd_arr[i]} ns" "${jdk17_p999_arr[i]} ns"  "${jdk17_p99_arr[i]} ns" "${jdk17_p95_arr[i]} ns" "${jdk17_p90_arr[i]} ns"
    echo "----------------------------------------"
done


echo "-----------------------------------------------------------------"
echo "DONE!"
echo "-----------------------------------------------------------------"

