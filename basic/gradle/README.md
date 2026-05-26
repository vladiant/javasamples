# basic-java-gradle

A simple Java application built with Gradle.

## Requirements

- Java 21+
- Gradle 8+ (or use the included Gradle wrapper)

## Project Structure

```
.
├── app/
│   ├── build.gradle          # App module build configuration
│   └── src/
│       ├── main/java/com/example/
│       │   └── App.java      # Application entry point
│       └── test/java/com/example/
│           └── AppTest.java  # Unit tests
├── gradle/
│   ├── libs.versions.toml    # Dependency version catalog
│   └── wrapper/              # Gradle wrapper files
├── settings.gradle           # Project settings
├── gradlew                   # Gradle wrapper (Unix)
└── gradlew.bat               # Gradle wrapper (Windows)
```

## Build

```bash
./gradlew build
```

## Run

```bash
./gradlew run
```

## Test

```bash
./gradlew test
```

## Clean

```bash
./gradlew clean
```
