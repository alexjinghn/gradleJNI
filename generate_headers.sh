#!/bin/bash

echo "using $JAVA_HOME"

./gradlew build
JAR=./gradle-jni/build/libs/gradle-jni.jar
$JAVA_HOME/bin/javac -h -cp $JAR com.test.Main -d ./gradle-jni/src/main/jni