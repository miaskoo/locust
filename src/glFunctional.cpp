#include "glFunctional.h"
#include <assert.h>

#ifdef MACOS
#include "GLUT/glut.h"
#else
#include "glew/glew.h"
#include "freeglut/freeglut.h"
#endif

unsigned int glForwarder::genBufferArray() {
    unsigned int result;
    glGenBuffers(1, &result);
    return result;
}

unsigned int glForwarder::genVertexArray() {
    unsigned int result;
#ifdef MACOS
    glGenVertexArraysAPPLE(1, &result);
#else
    glGenVertexArrays(1, &result);
#endif
    return result;
}

void glForwarder::bindVertexArray(unsigned int idArray) {
#ifdef MACOS
    glBindVertexArrayAPPLE(idArray);
#else
    glBindVertexArray(idArray);
#endif
}

void glForwarder::unbindVertexArray() {
#ifdef MACOS
    glBindVertexArrayAPPLE(0);
#else
    glBindVertexArray(0);
#endif
}

void glForwarder::copyBufferArrayToGlStatic(unsigned int idBuff, void* array, unsigned int sizeArray) {
    glBindBuffer(GL_ARRAY_BUFFER, idBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
}

void glForwarder::copyBufferElementArrayToGlStatic(unsigned int idBuff, void* array, unsigned int sizeArray) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idBuff);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeArray, array, GL_STATIC_DRAW);
}

void glForwarder::addVertexAttribPointerFloat(unsigned int idxAttrib, unsigned int countValueInAttrib, unsigned int stride, unsigned int offset) {
    const auto sizeFloat = sizeof(GLfloat);
    glVertexAttribPointer(idxAttrib, countValueInAttrib, GL_FLOAT, GL_FALSE, stride * sizeFloat, reinterpret_cast<GLvoid*>(offset * sizeFloat));
    glEnableVertexAttribArray(idxAttrib);
}

void glForwarder::drawTriangleElements(unsigned int countElements) {
    glDrawElements(GL_TRIANGLES, countElements, GL_UNSIGNED_BYTE, 0);
}

void glForwarder::setCullfaceMode(bool value) {
    if (value) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
}

void glForwarder::bind2DTexture(unsigned int idTex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTex);
}

void glForwarder::unbind2DTexture() {
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void glForwarder::bindShaderProgram(unsigned int idShaderProgram) {
    glUseProgram(idShaderProgram);
}

void glForwarder::unbindShaderProgram() {
    glUseProgram(0);
}

void glForwarder::drawQuad(unsigned int size) {
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1,0);
    glVertex2i(1,1);
    glVertex2i(0,1);
    glEnd();
}

void glForwarder::drawTextureQuad(unsigned int size) {
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex2i(0,0);
    glTexCoord2i(1,0);
    glVertex2i(size,0);
    glTexCoord2i(1,1);
    glVertex2i(size,size);
    glTexCoord2i(0,1);
    glVertex2i(0,size);
    glEnd();
}

void glForwarder::drawBitmapText(const char *text, unsigned int textSize, void* font) {
    int xChar = 0;
    for (unsigned int n = 0U; n < textSize; n++) {
        glRasterPos2f(xChar, 0);
        glutBitmapCharacter(font, text[n]);
        xChar = xChar + glutBitmapWidth(font, text[n]);
    }
}

void glForwarder::setAlphaMode(bool value) {
    if (value) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else {
        glDisable(GL_BLEND);
    }
}

void glForwarder::setColor4(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    glColor4ub(r, g, b, a);
}

void glForwarder::setColor3(unsigned char r, unsigned char g, unsigned char b) {
    glColor3ub(r, g, b);
}
