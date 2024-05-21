
/**
* Name: Jephte Pierre
* Date: February 28, 2024
* Description: : n this assignment we will get familiar with generic 
* programming in C++ (abstract types, class
* hierarchies, templates, functors and lambdas) by creating a simple drawing program using OpenGL.
*/

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

template<typename T>
class Shape {
public:
    virtual void draw() const = 0;
    virtual void translate(float x, float y) const = 0;
    virtual void rotate(float angle) const = 0;
    virtual void scale(float factor) const = 0;
    virtual ~Shape() {} 
};

template<typename T>
class Circle : public Shape<T> {
public:
    void draw() const override {
        
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex2f(0.0f, 0.0f); 
        const float radius = 0.5f;
        const int numSegments = 100;
        for (int i = 0; i <= numSegments; ++i) {
            float angle = 2.0f * 3.14159f * float(i) / float(numSegments);
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    void translate(float x, float y) const override {
        // Translate the circle
        glTranslatef(x, y, 0.0f);
    }

    void rotate(float angle) const override {
        // Rotate the circle
        glRotatef(angle, 0.0f, 0.0f, 1.0f); 
    }

    void scale(float factor) const override {
        // Scale the circle
        glScalef(factor, factor, 1.0f); 
    }
};

// a square shape
template<typename T>
class Square : public Shape<T> {
public:
    void draw() const override {

        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f); 
        glVertex2f(0.5f, 0.5f); 
        glVertex2f(-0.5f, 0.5f); 
        glEnd();
    }

    void translate(float x, float y) const override {
        // Translate the square
        glTranslatef(x, y, 0.0f);
    }

    void rotate(float angle) const override {
        // Rotate the square
        glRotatef(angle, 0.0f, 0.0f, 1.0f); 
    }

    void scale(float factor) const override {
        // Scale the square
        glScalef(factor, factor, 1.0f); 
    }
};

template<typename T, typename Operation>
void renderShape(const T& shape, Operation operation) {
    glPushMatrix(); 
    shape.draw(); 
    operation(shape); 
    glPopMatrix();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    /* a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 780, "OpenGL Shapes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);

        // Render circle
        glLoadIdentity(); 
        Circle<float> circle;
        glColor3f(1.0f, 0.0f, 0.0f); 
        circle.translate(0.3f, 0.0f); 
        circle.rotate(45.0f);
        circle.scale(0.5f);
        circle.draw();

       
        glLoadIdentity(); 
        Square<float> square;
        glColor3f(0.0f, 0.0f, 1.0f); 
        square.translate(-0.3f, 0.0f);
        square.rotate(30.0f);
        square.scale(0.5f);
        square.draw();

        

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
