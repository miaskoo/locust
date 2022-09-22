#include "factoryBuffer.h"
#include "struct.h"
#include "glFunctional.h"

bufferIdx factoryBuffer::createTorusBuffer(int countSector) {
    // p1--p2
    // |    |
    // |    |
    // p4--p3
    unsigned int vboIdx = 0;
    unsigned int vaoIdx = 0;
    unsigned int eboIdx = 0;
    const float sectorStep = 2.f * 3.14159f / countSector;
    const float widthTriangles = 1;
    float xy = cosf(90.f);
    const int countDimension = 3;
    const int countDimensionTex = 2;
    const int cointVerticesForQuad = 4;
    const int countVerticesForQuads = countDimension * cointVerticesForQuad * countSector;
    const int countVecticesForTex = countDimensionTex * cointVerticesForQuad * countSector;
    
    
    const int countVertices = countVerticesForQuads + countVecticesForTex;
    const int countIndices = countSector * cointVerticesForQuad * countDimension;
    auto vertices = new float[countVertices];
    auto indices = new unsigned char[countIndices];
    
    const float z1 = widthTriangles / 2.f;
    const float z2 = -z1;
    
    
    int idxVertices = 0;
    int idxIndices = 0;
    auto setDataVertices = [&vertices, &idxVertices](vec3f pos, vec2f tex){
        for (size_t n = 0U; n < pos.size(); n++) {
            vertices[idxVertices] = pos[n];
            idxVertices++;
        }
        for (size_t n = 0U; n < tex.size(); n++) {
            vertices[idxVertices] = tex[n];
            idxVertices++;
        }
    };
    
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

        vec3f p1({x1,y1,z1});
        vec3f p2({x1,y1,z2});
        vec3f p3({x2,y2,z1});
        vec3f p4({x2,y2,z2});
        
        auto tIdx = (texIdx)%8;
        auto tIdx2 = (texIdx+1)%8;
        
        auto x1t = posTex[tIdx][0];
        auto y1t = posTex[tIdx][1];
        auto x2t = posTex[tIdx2][0];
        auto y2t = posTex[tIdx2][1];
        
        vec2f p1tex({x1t,y1t});
        vec2f p2tex({x1t,y2t});
        vec2f p3tex({x2t,y1t});
        vec2f p4tex({x2t,y2t});
        
        // p1--p2
        // |    |
        // |    |
        // p4--p3
        setDataVertices(p1, p1tex);
        setDataVertices(p2, p2tex);
        setDataVertices(p3, p3tex);
        setDataVertices(p4, p4tex);
    }
    
    auto setDataIndices = [&idxIndices, &indices, countSector = countSector](size_t idx, size_t numPoint){
        if (countSector * 2 <= idx + numPoint) {
            numPoint -= countSector * 2;
            
        }
        indices[idxIndices] = idx + numPoint;
        idxIndices++;
    };
    
    for (int i = 0, idxPoint = 0; i < countSector * 2; i++, idxPoint+=4) {
        setDataIndices(idxPoint, 0);
        setDataIndices(idxPoint, 2);
        setDataIndices(idxPoint, 1);
        
        setDataIndices(idxPoint, 2);
        setDataIndices(idxPoint, 3);
        setDataIndices(idxPoint, 1);
    }

    vaoIdx = glForwarder::genVertexArray();
    vboIdx = glForwarder::genBufferArray();
    eboIdx = glForwarder::genBufferArray();
    
    glForwarder::bindVertexArray(vaoIdx);
    
    glForwarder::copyBufferArrayToGlStatic(vboIdx, vertices, countVertices * sizeof(float));
    glForwarder::copyBufferElementArrayToGlStatic(eboIdx, indices, countIndices * sizeof(unsigned char));
    
    
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
