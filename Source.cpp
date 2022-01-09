#include <GL/glut.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <time.h>   
#include <assert.h>

float VIEWPORT_WIDTH = 1000;
float VIEWPORT_HEIGHT = 500;

enum class ShapeType { RECTANGLE, TRIANGLE, CIRCLE, OCTOGAN };

struct Shape {
private:
    ShapeType shapeType;
    float centerX, centerY, width, height;
    std::vector<std::tuple<int, int, int>> colors;

public:
    Shape(ShapeType shapeType, float centerX, float centerY, float width, float height, std::vector<std::tuple<int, int, int>> colors) {
        this->shapeType = shapeType;
        this->centerX = centerX;
        this->centerY = centerY;
        this->width = width;
        this->height = height;
        this->colors = colors;
    }

    ShapeType getType() {
        return this->shapeType;
    }

    float getCenterX() {
        return this->centerX;
    }

    float getCenterY() {
        return this->centerY;
    }

    float getAbsoluteWidth() {
        return this->width;
    }

    float getScaledWidth() {
        return this->width * (glutGet(GLUT_WINDOW_WIDTH) / VIEWPORT_WIDTH);
    }

    float getAbsoluteHeight() {
        return this->height;
    }

    float getScaledHeight() {
        return this->height * (glutGet(GLUT_WINDOW_HEIGHT) / VIEWPORT_HEIGHT);
    }

    float getLeftBound() {
        return (this->centerX - (this->width / 2)) / glutGet(GLUT_WINDOW_WIDTH);
    }

    float getRightBound() {
        return (this->centerX + (this->width / 2)) / glutGet(GLUT_WINDOW_WIDTH);
    }

    float getUpperBound() {
        return (this->centerY + (this->height / 2)) / glutGet(GLUT_WINDOW_HEIGHT);
    }

    float getLowerBound() {
        return (this->centerY - (this->height / 2)) / glutGet(GLUT_WINDOW_HEIGHT);
    }

    std::vector<std::tuple<int, int, int>> getColors() {
        return this->colors;
    }

};


void createGeoFigures(float centerX, float centerY, float width, float height, std::string type) {

    width = width * (glutGet(GLUT_WINDOW_WIDTH) / VIEWPORT_WIDTH);
    height = height * (glutGet(GLUT_WINDOW_HEIGHT) / VIEWPORT_HEIGHT);

    float leftBound = (centerX - (width / 2)) / glutGet(GLUT_WINDOW_WIDTH);
    float rightBound = (centerX + (width / 2)) / glutGet(GLUT_WINDOW_WIDTH);
    float upperBound = (centerY + (height / 2)) / glutGet(GLUT_WINDOW_HEIGHT);
    float lowerBound = (centerY - (height / 2)) / glutGet(GLUT_WINDOW_HEIGHT);

    if (type == "rectangle") {
        glColor3ub(160, 168, 50);
        glRectf(leftBound, lowerBound, rightBound, upperBound);
    }
    else if (type == "triangle") {
        glColor3ub(90, 84, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(leftBound, upperBound);
        glColor3f(0.5, 5, 0);
        glVertex2f(leftBound + ((rightBound - leftBound) / 2), upperBound + ((height) / glutGet(GLUT_WINDOW_HEIGHT)));
        glColor3ub(60, 0, 255);
        glVertex2f(rightBound, upperBound);

        glEnd();
    }
    else if (type == "polygon") {

        glColor3f(1.0, 1.0, 0.6);

        glBegin(GL_POLYGON);
        glVertex2f(leftBound, lowerBound);
        glColor3ub(51, 142, 29);
        glVertex2f(rightBound, upperBound);
        glColor3ub(0, 56, 44);
        glVertex2f(leftBound + ((rightBound - leftBound) / 2), upperBound + ((height) / glutGet(GLUT_WINDOW_HEIGHT)));
        glColor3ub(39, 0, 21);
        glVertex2f(rightBound, upperBound);
        glColor3ub(90, 176, 0);
        glVertex2f(0.40, 0.20);
        glEnd();

    }

    else if (type == "opal") {
        float x1, y1, x2, y2;
        float angle;
        double radius = 0.1;

        x1 = 0.5, y1 = 0.6;
        glColor3f(0.5, 5, 0);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x1, y1);

        for (angle = 1.0f; angle < 361.0f; angle += 0.2)
        {
            x2 = x1 + sin(angle) * radius;
            y2 = y1 + cos(angle) * radius;
            glVertex2f(x2, y2);
        }

        glEnd();
    }

    glFlush();
}

void drawWithMask(Shape shape, GLubyte mask[]) {

    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(mask);

    std::tuple<int, int, int> primaryColor = shape.getColors().at(0);
    glColor3ub(std::get<0>(primaryColor), std::get<1>(primaryColor), std::get<2>(primaryColor));
    glRectf(shape.getLeftBound(), shape.getLowerBound(), shape.getRightBound(), shape.getUpperBound());

    glDisable(GL_POLYGON_STIPPLE);


    glEnd();
    glFlush();
}

void displayMe(void)
{
    float centerRectX = 100;
    float centerRectY = 100;
    float centerTriX = 200;
    float centerTriY = 200;
    float centerOpalX = 300;
    float centerOpalY = 300;
    float centerPolyX = -400;
    float centerPolyY = -400;
    GLubyte brickMask[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xF3, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0xFC
    };

    GLubyte fireMask[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0xf0,
    0x00, 0x00, 0x07, 0xf0, 0x0f, 0x00, 0x1f, 0xe0,
    0x1f, 0x80, 0x1f, 0xc0, 0x0f, 0xc0, 0x3f, 0x80,
    0x07, 0xe0, 0x7e, 0x00, 0x03, 0xf0, 0xff, 0x80,
    0x03, 0xf5, 0xff, 0xe0, 0x07, 0xfd, 0xff, 0xf8,
    0x1f, 0xfc, 0xff, 0xe8, 0xff, 0xe3, 0xbf, 0x70,
    0xde, 0x80, 0xb7, 0x00, 0x71, 0x10, 0x4a, 0x80,
    0x03, 0x10, 0x4e, 0x40, 0x02, 0x88, 0x8c, 0x20,
    0x05, 0x05, 0x04, 0x40, 0x02, 0x82, 0x14, 0x40,
    0x02, 0x40, 0x10, 0x80, 0x02, 0x64, 0x1a, 0x80,
    0x00, 0x92, 0x29, 0x00, 0x00, 0xb0, 0x48, 0x00,
    0x00, 0xc8, 0x90, 0x00, 0x00, 0x85, 0x10, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    };

    GLubyte flyMask[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
      0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
      0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
      0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
      0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
      0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
      0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
      0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
      0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
      0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
      0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
      0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
      0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
    };


    drawWithMask(Shape(ShapeType::RECTANGLE, -600, -400, 100, 100, std::vector<std::tuple<int, int, int>> {std::make_tuple(255, 255, 255)}), brickMask);
    drawWithMask(Shape(ShapeType::RECTANGLE, 600, -400, 100, 100, std::vector<std::tuple<int, int, int>> {std::make_tuple(255, 255, 255)}), fireMask);
    drawWithMask(Shape(ShapeType::RECTANGLE, -600, 400, 100, 100, std::vector<std::tuple<int, int, int>> {std::make_tuple(255, 255, 255)}), flyMask);
    std::string arr[4] = { "rectangle", "triangle", "opal", "polygon" };
    createGeoFigures(centerRectX, centerRectY, 500, 100, arr[0]);
    createGeoFigures(-100, -100, 100, 100, arr[0]);
    createGeoFigures(centerTriX, centerTriY, 200, 100, arr[1]);
    createGeoFigures(-400, -200, 200, 300, arr[1]);
    createGeoFigures(centerOpalX, centerOpalY, 100, 100, arr[2]);
    createGeoFigures(centerPolyX, centerPolyY, 100, 100, arr[3]);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("CSC 470 OpenGL Problem 1");

    glutDisplayFunc(displayMe);

    glutMainLoop();
    return 0;
}