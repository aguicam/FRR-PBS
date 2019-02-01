#ifndef RENDER_H
#define RENDER_H

#include "./triangle_mesh.h"
#include <memory>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <glm/glm.hpp>
#include <QtWidgets>
#include <QGLWidget>
#include <QGLFunctions>
#include <QGLShaderProgram>
#include <QGLContext>
#include "camera.h"

enum{VA, VBO, VAO};

class Render
{
public:
    Render();

    /**
     * @brief initialized_ Whether the widget has finished initializations.
     */
    bool initialized_;

    /**
     * @brief initialized_buffers_ Whether the widget has finished buffer initializations.
     */
    bool initialized_buffers_;

    /**
     * IDs of the buffers used in the communication with the gpu.
     */
    unsigned int vbo_v_id, vbo_n_id, faces_id;
    unsigned int vao_id, vbo_id;

    unsigned int quad_vao, quad_vbo;

    unsigned int cube_vao, cube_vbo;

    unsigned int captureFBO, captureRBO;
    unsigned int captureFBO2, captureRBO2;

    unsigned int prefilter_texture;
    unsigned int brdfLUTTexture;

    typedef void (APIENTRY *_glGenVertexArrays) (GLsizei, GLuint*);
    typedef void (APIENTRY *_glBindVertexArray) (GLuint);
    typedef void (APIENTRY *_glDrawBuffers) (GLuint,GLuint*);
    _glGenVertexArrays glGenVertexArrays;
    _glBindVertexArray glBindVertexArray;
    _glDrawBuffers glDrawBuffers;
    QOpenGLFunctions glf;
    /**
     * @brief initializeBuffers Initializes buffers for sending data to GPU.
     */
    virtual void initializeBuffers(std::unique_ptr<data_representation::TriangleMesh>& mesh_);

    /**
     * @brief initializeBuffers_VA Initializes the buffers for Vertex Array Objects.
     * @param mesh_
     */
    void initializeBuffers_VAO(std::unique_ptr<data_representation::TriangleMesh>& mesh_);

    /**
     * @brief paintGL Function that handles rendering the scene.
     */
    virtual void paintGL(std::unique_ptr<QOpenGLShaderProgram>& program_,std::unique_ptr<data_representation::TriangleMesh>& mesh_);


    /**
     * @brief paintGL_VAO Draws in the widget using Vertex Array Objects.
     * @param mesh_
     */
    void paintGL_VAO(std::unique_ptr<data_representation::TriangleMesh>& mesh_);
    void renderQuad();
    void renderCube();
    void computePrefilteredCubemap(std::unique_ptr<QOpenGLShaderProgram>& prefilter_program_,data_visualization::Camera& camera_, unsigned int specular_texture );
    void compute2D_LUT(std::unique_ptr<QOpenGLShaderProgram>& brdf_lut_program_);

};

#endif // RENDER_H
