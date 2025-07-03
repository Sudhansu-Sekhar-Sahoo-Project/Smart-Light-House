# Use a lightweight OpenJDK image
FROM eclipse-temurin:17-jdk-alpine

# Set working directory
WORKDIR /app

# Copy all files into the container
COPY . .

# Build the project using Maven Wrapper
RUN ./mvnw clean package -DskipTests

# Expose port (change if needed)
EXPOSE 8080

# Run the JAR file
CMD ["java", "-jar", "target/esp8266-controller-0.0.1-SNAPSHOT.jar"]

