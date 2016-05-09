/*
    Fast Batch.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef HX3D_GRAPHICS_FAST_BATCH
#define HX3D_GRAPHICS_FAST_BATCH

namespace hx3d {
namespace graphics {

/**
@brief Real batching using real-time VBO generation
*/
class FastBatch {
public:
    FastBatch(unsigned int size): size(size), vboId(0), vboIndicesId(0), current(0), currentIdx(0), maxIdx(0), drawing(false) {
        vertices.resize(size * 36);
        indices.resize(size * 6);

        // Buffers
        glGenBuffers(1, &vboId);
        glGenBuffers(1, &vboIndicesId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, size * 36 * sizeof(float), NULL, GL_STREAM_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * 6 * sizeof(GLushort), NULL, GL_STREAM_DRAW);
    }

    void setShader(const Ptr<Shader>& shader) {
        this->shader = shader;
    }

    void clear() {
        current = 0;
        currentIdx = 0;
        maxIdx = 0;
    }

    void begin() {
        if (shader == nullptr) {
            Log.Error("FastBatch: no shader.");
            return;
        }

        drawing = true;
        drawCalls = 0;
    }

    void end() {
        flush();

        drawing = false;
    }

    void draw(const Ptr<Sprite>& sprite) {

        if (!drawing) {
            Log.Error("FastBatch: not currently drawing !");
            return;
        }

        // Calcul des positions post-transform
        AttributeArrayBuffer& positions = sprite->getGeometry()->getAttribute("Position");
        unsigned int vertSize = positions.size() / 3;
        unsigned int prevMaxIdx = maxIdx;
        auto& ind = sprite->getGeometry()->getIndices();

        glm::mat4 model = sprite->transform.compute();
        std::vector<float> newPositions;
        newPositions.resize(vertSize * 3);

        if (current + vertSize * 3 > size * 36) {
            Log.Error("FastBatch too small: force flush.");
            flush();
        }

        if (maxIdx >= USHRT_MAX) {
            Log.Error("Too much indices ! (max: 65536): force flush.");
            flush();
        }

        for (unsigned int i = 0; i < vertSize*3; i += 3) {
            glm::vec4 pos = {
                positions.getValue(i),
                positions.getValue(i+1),
                positions.getValue(i+2),
                1
            };

            glm::vec4 npos = model * pos;

            newPositions[i] = npos.x;
            newPositions[i+1] = npos.y;
            newPositions[i+2] = npos.z;
        }

        for (unsigned int i = 0; i < vertSize; ++i) {
            for (unsigned int j = i * 3; j < (i+1) * 3; ++j) {
                vertices[current++] = newPositions[j];
            }
            for (unsigned int j = i * 4; j < (i+1) * 4; ++j) {
                vertices[current++] = sprite->getGeometry()->getAttribute("Color").getValue(j);
            }
            for (unsigned int j = i * 2; j < (i+1) * 2; ++j) {
                vertices[current++] = sprite->getGeometry()->getAttribute("Texture").getValue(j);
            }
        }

        for (unsigned int i = 0; i < ind.size(); ++i) {
            unsigned int val = ind.getValue(i) + prevMaxIdx;
            maxIdx = std::max(maxIdx, val);
            indices[currentIdx++] = val;
        }
        maxIdx += 1;
    }

    void flush() {
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesId);

        glBufferSubData(GL_ARRAY_BUFFER, 0, current * sizeof(float), vertices.data());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, currentIdx * sizeof(GLushort), indices.data());

        glEnableVertexAttribArray(shader->getAttribute("a_position"));
        glEnableVertexAttribArray(shader->getAttribute("a_color"));
        glEnableVertexAttribArray(shader->getAttribute("a_texture"));

        glVertexAttribPointer(shader->getAttribute("a_position"), 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), BUFFER_OFFSET(0));
        glVertexAttribPointer(shader->getAttribute("a_color"), 4, GL_FLOAT, GL_FALSE, 9*sizeof(float), BUFFER_OFFSET(3*sizeof(float)));
        glVertexAttribPointer(shader->getAttribute("a_texture"), 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), BUFFER_OFFSET(7*sizeof(float)));

        glDrawElements(GL_TRIANGLES, currentIdx, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

        glDisableVertexAttribArray(shader->getAttribute("a_position"));
        glDisableVertexAttribArray(shader->getAttribute("a_color"));
        glDisableVertexAttribArray(shader->getAttribute("a_texture"));

        ++drawCalls;

        clear();
    }

    unsigned int size;

    unsigned int vboId;
    unsigned int vboIndicesId;

    unsigned int current;
    unsigned int currentIdx;
    unsigned int maxIdx;

    unsigned int drawCalls;
    bool drawing;

    Ptr<Shader> shader;
    std::vector<float> vertices;
    std::vector<GLushort> indices;
};

} /* graphics */
} /* hx3d */

#endif /* HX3D_GRAPHICS_FAST_BATCH */
