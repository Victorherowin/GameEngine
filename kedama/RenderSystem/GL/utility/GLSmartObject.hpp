//
// Created by moe on 2017-05-29.
//

#ifndef KEDAMA_GLSMARTOBJECT_HPP
#define KEDAMA_GLSMARTOBJECT_HPP

#include <functional>
#include <GL/glew.h>

namespace Kedama {
    namespace GL {
        using namespace std;

        class Counter {
        private:
            int m_num = 0;
        public:
            void operator++() { m_num++; }

            void operator--() { m_num--; }

            operator int() { return m_num; }
        };

        class GLSharedBuffer {
        private:
            GLuint m_obj = 0;
            Counter *m_counter = nullptr;
        public:
            GLSharedBuffer() {
                glCreateBuffers(1, &m_obj);
                m_counter = new Counter();
                ++(*m_counter);
            }

            GLSharedBuffer(GLuint obj) : m_obj(obj) {
                m_counter = new Counter();
                ++(*m_counter);
            }

            GLSharedBuffer(const GLSharedBuffer &buf) {
                if(m_obj!=0)glDeleteBuffers(1,&m_obj);

                m_counter = buf.m_counter;
                m_obj = buf.m_obj;
                ++(*m_counter);
            }

            GLSharedBuffer(GLSharedBuffer &&buf) {
                if(m_obj!=0)glDeleteBuffers(1,&m_obj);

                m_counter = buf.m_counter;
                m_obj = buf.m_obj;
                buf.m_counter = nullptr;
            }

            const GLSharedBuffer& operator==(const GLSharedBuffer &buf) {
                if(m_obj!=0)glDeleteBuffers(1,&m_obj);

                m_counter = buf.m_counter;
                m_obj = buf.m_obj;
                ++(*m_counter);
                return *this;
            }

            const GLSharedBuffer& operator==(GLSharedBuffer &&buf) {
                if(m_obj!=0)glDeleteBuffers(1,&m_obj);

                m_counter = buf.m_counter;
                m_obj = buf.m_obj;
                buf.m_counter = nullptr;
                return *this;
            }

            ~GLSharedBuffer() {
                if (m_counter != nullptr) {
                    if (*m_counter <= 1) {
                        glDeleteBuffers(1, &m_obj);
                        delete m_counter;
                    }
                }
            }

            operator GLuint() {
                return m_obj;
            }
        };
    }
}

#endif //KEDAMA_GLSMARTOBJECT_HPP
