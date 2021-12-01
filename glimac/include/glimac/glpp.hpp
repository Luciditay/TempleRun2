#pragma once

#include <GL/glew.h>

class UniqueTexture {
public:
    UniqueTexture()
    {
        glGenTextures(1, &_id);
    }
    ~UniqueTexture()
    {
        glDeleteTextures(1, &_id);
    }
    UniqueTexture(const UniqueTexture&) = delete;
    UniqueTexture& operator=(const UniqueTexture&) = delete;
    UniqueTexture(UniqueTexture&& rhs) noexcept
        : _id{rhs._id}
    {
        rhs._id = 0;
    }
    UniqueTexture& operator=(UniqueTexture&& rhs) noexcept
    {
        if (this != &rhs) {
            glDeleteTextures(1, &_id);
            _id     = rhs._id;
            rhs._id = 0;
        }
        return *this;
    }

    GLuint operator*() const { return _id; }

private:
    GLuint _id;
};


class UniqueBuffer {
public:
    UniqueBuffer()
    {
        glGenBuffers(1, &_id);
    }
    ~UniqueBuffer()
    {
        glDeleteBuffers(1, &_id);
    }
    UniqueBuffer(const UniqueBuffer&) = delete;
    UniqueBuffer& operator=(const UniqueBuffer&) = delete;
    UniqueBuffer(UniqueBuffer&& rhs) noexcept
        : _id{rhs._id}
    {
        rhs._id = 0;
    }
    UniqueBuffer& operator=(UniqueBuffer&& rhs) noexcept
    {
        if (this != &rhs) {
            glDeleteBuffers(1, &_id);
            _id     = rhs._id;
            rhs._id = 0;
        }
        return *this;
    }

    GLuint operator*() const { return _id; }

private:
    GLuint _id;
};


class UniqueVAO {
public:
    UniqueVAO()
    {
        glGenVertexArrays(1, &_id);
    }
    ~UniqueVAO()
    {
        glDeleteVertexArrays(1, &_id);
    }
    UniqueVAO(const UniqueVAO&) = delete;
    UniqueVAO& operator=(const UniqueVAO&) = delete;
    UniqueVAO(UniqueVAO&& rhs) noexcept
        : _id{rhs._id}
    {
        rhs._id = 0;
    }
    UniqueVAO& operator=(UniqueVAO&& rhs) noexcept
    {
        if (this != &rhs) {
            glDeleteVertexArrays(1, &_id);
            _id     = rhs._id;
            rhs._id = 0;
        }
        return *this;
    }

    GLuint operator*() const { return _id; }

private:
    GLuint _id;
};
