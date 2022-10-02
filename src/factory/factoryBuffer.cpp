#include "factoryBuffer.h"
#include "struct.h"
#include "glFunctional.h"

bufferIdx factoryBuffer::createTorusBuffer(int countSector) {
    // p1--p2
    // |    |
    // |    |
    // p4--p3
    const float sectorStep = 2.f * 3.14159f / countSector;
    const float widthTriangles = 1;
    float xy = cosf(90.f);
    std::vector<vec3f> vertices;
    std::vector<vec2f> textureCoordinate;
    std::vector<unsigned int> indices;
    
    const float z1 = widthTriangles / 2.f;
    const float z2 = -z1;
    
    float whTex = 0.25f;
    vec2f posTex[8];
    for (int n =0, i = 0; n < 8; n+=2, i++) {
        posTex[n][0] = whTex * (n%2);
        posTex[n][1] = whTex * (n%2);
        posTex[n+1][0] = whTex + whTex * (n%2);
        posTex[n+1][1] = whTex +  whTex * (n%2);
        if ((i%2) == 1) {
            posTex[n][0] += whTex;
            posTex[n+1][0] += whTex;
        }
        if (n > 3) {
            posTex[n][1] += whTex;
            posTex[n+1][1] += whTex;
        }
    }
    std::swap(posTex[4], posTex[6]);
    std::swap(posTex[5], posTex[7]);
    
    for (int n = 0, texIdx = 0; n < countSector; n++, texIdx += 2) {
        
        float sectorAngle1 = n * sectorStep;
        float x1 = xy * cosf(sectorAngle1);
        float y1 = xy * sinf(sectorAngle1);
    
        n++;
        float sectorAngle2 = n * sectorStep;
        float x2 = xy * cosf(sectorAngle2);
        float y2 = xy * sinf(sectorAngle2);
        n--;

        vec3f p1(x1,y1,z1);
        vec3f p2(x1,y1,z2);
        vec3f p3(x2,y2,z1);
        vec3f p4(x2,y2,z2);
        
        auto tIdx = (texIdx)%8;
        auto tIdx2 = (texIdx+1)%8;
        
        auto x1t = posTex[tIdx][0];
        auto y1t = posTex[tIdx][1];
        auto x2t = posTex[tIdx2][0];
        auto y2t = posTex[tIdx2][1];
        
        vec2f p1tex(x1t,y1t);
        vec2f p2tex(x1t,y2t);
        vec2f p3tex(x2t,y1t);
        vec2f p4tex(x2t,y2t);
        
        // p1--p2
        // |    |
        // |    |
        // p4--p3
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);
        
        textureCoordinate.push_back(p1tex);
        textureCoordinate.push_back(p2tex);
        textureCoordinate.push_back(p3tex);
        textureCoordinate.push_back(p4tex);
    }

    for (auto i = 0U, idxPoint = 0U; i < countSector; i++, idxPoint+=4U) {
        indices.push_back(idxPoint);
        indices.push_back(idxPoint + 2U);
        indices.push_back(idxPoint + 1U);
        
        indices.push_back(idxPoint + 2U);
        indices.push_back(idxPoint + 3U);
        indices.push_back(idxPoint + 1U);
    }

    return generateBufferIdx(vertices, textureCoordinate, indices);
}


bufferIdx factoryBuffer::generateBufferIdx(const std::vector<vec3f>& verticesVector, const std::vector<vec2f>& textureCoordinateVector, const std::vector<unsigned int>& indicesVector) {
    if (verticesVector.size() != textureCoordinateVector.size()) {
        assert(false && "verticesVector and textureCoordinateVector size not the same");
    }
    
    const auto countVertices = verticesVector.size() * 3 + textureCoordinateVector.size() * 2;
    const auto countIndices = indicesVector.size();
    float* vertices = new float[countVertices];
    unsigned int* indices = new unsigned int[countIndices];
    
    for (auto n = 0U, idx = 0U; n < verticesVector.size(); n++, idx+=5) {
        for (auto i = 0U; i < verticesVector[n].size(); i++) {
            vertices[idx + i] = verticesVector[n][i];
        }
        for (auto i = 0U, offset = 3U; i < textureCoordinateVector[n].size(); i++) {
            vertices[idx + i + offset] = textureCoordinateVector[n][i];
        }
    }
    
    for (auto n = 0U; n < indicesVector.size(); n++) {
        auto value = indicesVector[n];
        indices[n] = value;
    }
    
    unsigned int vaoIdx = glForwarder::genVertexArray();
    unsigned int vboIdx = glForwarder::genBufferArray();
    unsigned int eboIdx = glForwarder::genBufferArray();
    
    glForwarder::bindVertexArray(vaoIdx);
    
    glForwarder::copyBufferArrayToGlStatic(vboIdx, vertices, countVertices * sizeof(float));
    glForwarder::copyBufferElementArrayToGlStatic(eboIdx, indices, countIndices * sizeof(unsigned int));
    
    
    glForwarder::addVertexAttribPointerFloat(0, 3, 5, 0);
    glForwarder::addVertexAttribPointerFloat(1, 2, 5, 3);

    glForwarder::unbindVertexArray();
    
    bufferIdx buff;
    buff.vbo = vboIdx;
    buff.vao = vaoIdx;
    buff.ebo = eboIdx;
    buff.countIdx = countIndices;
    

    delete[] vertices;
    delete[] indices;

    return buff;
}
