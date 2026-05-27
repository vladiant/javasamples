# Maven Basic Java Project

A simple Java project built with Apache Maven.

## Requirements

- Java 17+
- Maven 3.6+

## Project Structure

```
maven/
├── pom.xml
├── README.md
├── .gitignore
└── src/
    ├── main/
    │   └── java/
    │       └── com/
    │           └── example/
    │               └── App.java
    └── test/
        └── java/
            └── com/
                └── example/
                    └── AppTest.java
```

## Build

```bash
mvn compile
```

## Run Tests

```bash
mvn test
```

## Package

```bash
mvn package
```

The resulting JAR will be located at `target/maven-basic-1.0-SNAPSHOT.jar`.
