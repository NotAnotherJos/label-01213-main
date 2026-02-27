# Dockerfile for C++ Student Management System
# Multi-platform support: AMD64 and ARM64

# Use multi-arch base image that supports both amd64 and arm64
FROM gcc:12-bookworm

WORKDIR /app

# Copy source files
COPY Student.h .
COPY Student.cpp .
COPY main.cpp .

# Compile the program with static linking for better portability
RUN g++ -o student_system main.cpp Student.cpp -std=c++17 -static-libgcc -static-libstdc++

# Set executable permission
RUN chmod +x student_system

# Run the program
CMD ["./student_system"]
