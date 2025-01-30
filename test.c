#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    if (!glfwInit()) {
        printf("GLFW initialization failed!\n");
        return -1;
    }
    printf("GLFW initialized successfully!\n");
    glfwTerminate();
    return 0;
}
