#pragma once

namespace glForwarder {
    unsigned int genBufferArray();
    unsigned int genVertexArray();
    void bindVertexArray(unsigned int idArray);
    void unbindVertexArray();
    void drawTriangleElements(unsigned int countElements);
    void copyBufferArrayToGlStatic(unsigned int idBuff, void* array, unsigned int sizeArray);
    void copyBufferElementArrayToGlStatic(unsigned int idBuff, void* array, unsigned int sizeArray);
    void addVertexAttribPointerFloat(unsigned int idxAttrib, unsigned int countValueInAttrib, unsigned int stride, unsigned int offset);
    void setCullfaceMode(bool value);
    void bind2DTexture(unsigned int idTex);
    void unbind2DTexture();
    void bindShaderProgram(unsigned int idShaderProgram);
    void unbindShaderProgram();
    void drawQuad(unsigned int size);
    void drawTextureQuad(unsigned int size);
    void drawBitmapText(const char* text, unsigned int textSize, void* font);
    void setAlphaMode(bool value);
    void setColor4(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void setColor3(unsigned char r, unsigned char g, unsigned char b);
}

