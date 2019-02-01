#include "render.h"

Render::Render()
{
cube_vao=0;
}

void Render::initializeBuffers(std::unique_ptr<data_representation::TriangleMesh>& mesh_){

    if( mesh_ == NULL) return;

    Render::initializeBuffers_VAO(mesh_);
    initialized_buffers_=true;
}

void Render::initializeBuffers_VAO(std::unique_ptr<data_representation::TriangleMesh>& mesh_) {


    long int size = mesh_->vertices_.size()*sizeof(float);

    // Fills the buffer with the vertices data.

    glf.glGenBuffers(1, &vbo_v_id);
    glf.glBindBuffer(GL_ARRAY_BUFFER, vbo_v_id);
    glf.glBufferData(GL_ARRAY_BUFFER, size, &mesh_->vertices_[0], GL_STATIC_DRAW);
    glf.glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Fills the buffer with the normals data.

    glf.glGenBuffers(1, &vbo_n_id);
    glf.glBindBuffer(GL_ARRAY_BUFFER, vbo_n_id);
    glf.glBufferData(GL_ARRAY_BUFFER, size, &mesh_->normals_[0], GL_STATIC_DRAW);
    glf.glBindBuffer(GL_ARRAY_BUFFER, 0);

    glf.glGenBuffers(1, &faces_id);
    glf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces_id);
    glf.glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_->faces_.size()*sizeof(int), &mesh_->faces_[0], GL_STATIC_DRAW);  // Initialization Time
    glf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    // Creates the VAO.
    glGenVertexArrays = (_glGenVertexArrays) QGLContext::currentContext()->getProcAddress("glGenVertexArrays");
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray = (_glBindVertexArray) QGLContext::currentContext()->getProcAddress("glBindVertexArray");
    glBindVertexArray(vao_id);

    //Tells where to find the positions and the normals.

    glf.glBindBuffer(GL_ARRAY_BUFFER, vbo_v_id);
    glf.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  0);
    glf.glEnableVertexAttribArray(0);
    glf.glBindBuffer(GL_ARRAY_BUFFER, 0);

    glf.glBindBuffer(GL_ARRAY_BUFFER, vbo_n_id);
    glf.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glf.glEnableVertexAttribArray(1);
    glf.glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}



void Render::paintGL(std::unique_ptr<QOpenGLShaderProgram>& program_,std::unique_ptr<data_representation::TriangleMesh>& mesh_) {

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (initialized_buffers_) {
        program_->bind();
        Render::paintGL_VAO(mesh_);
    }

}

void Render::paintGL_VAO(std::unique_ptr<data_representation::TriangleMesh>& mesh_) {

    glBindVertexArray(vao_id);
    glf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces_id);

    glDrawElements(GL_TRIANGLES, mesh_->faces_.size(), GL_UNSIGNED_INT, 0);

    glf.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
void Render::renderCube()
{
    if (cube_vao == 0)
    {
        float vertices[] = {
            2.0f,  -2.0f, -2.0f, //R0_0
            2.0f,  -2.0f,  2.0f, //R0_1
            2.0f,   2.0f,  2.0f, //R0_2
            2.0f,  -2.0f, -2.0f, //R1_0
            2.0f,   2.0f,  2.0f, //R1_1
            2.0f,   2.0f, -2.0f, //R1_2
           -2.0f,  -2.0f, -2.0f, //L0_0
           -2.0f,   2.0f,  2.0f, //L0_1
           -2.0f,  -2.0f,  2.0f, //L0_2
           -2.0f,  -2.0f, -2.0f, //L1_0
           -2.0f,   2.0f, -2.0f, //L1_1
           -2.0f,   2.0f,  2.0f, //L1_2
           -2.0f,  -2.0f,  2.0f, //FF0_0
           -2.0f,   2.0f,  2.0f, //FF0_1
            2.0f,   2.0f,  2.0f, //FF0_2
           -2.0f,  -2.0f,  2.0f, //FF1_0
            2.0f,   2.0f,  2.0f, //FF1_1
            2.0f,  -2.0f,  2.0f, //FF1_2
           -2.0f,  -2.0f, -2.0f, //BF0_0
            2.0f,   2.0f, -2.0f, //BF0_1
           -2.0f,   2.0f, -2.0f, //BF0_2
           -2.0f,  -2.0f, -2.0f, //BF1_0
            2.0f,  -2.0f, -2.0f, //BF1_1
            2.0f,   2.0f, -2.0f, //BF1_2
           -2.0f,   2.0f, -2.0f, //TF0_0
            2.0f,   2.0f, -2.0f, //TF0_1
            2.0f,   2.0f,  2.0f, //TF0_2
           -2.0f,   2.0f, -2.0f, //TF1_0
            2.0f,   2.0f,  2.0f, //TF1_1
           -2.0f,   2.0f,  2.0f, //TF1_2
           -2.0f,  -2.0f, -2.0f, //BF0_0
            2.0f,  -2.0f,  2.0f, //BF0_1
            2.0f,  -2.0f, -2.0f, //BF0_2
           -2.0f,  -2.0f, -2.0f, //BF1_0
           -2.0f,  -2.0f,  2.0f, //BF1_1
            2.0f,  -2.0f,  2.0f //BF1_2
        };
        glGenVertexArrays = (_glGenVertexArrays) QGLContext::currentContext()->getProcAddress("glGenVertexArrays");
        glBindVertexArray = (_glBindVertexArray) QGLContext::currentContext()->getProcAddress("glBindVertexArray");
        glGenVertexArrays(1, &cube_vao);
        glf.glGenBuffers(1, &cube_vbo);
        glBindVertexArray(cube_vao);
        glf.glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
        glf.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        glf.glEnableVertexAttribArray(0);
        glf.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }
    glGenVertexArrays = (_glGenVertexArrays) QGLContext::currentContext()->getProcAddress("glGenVertexArrays");
    glBindVertexArray = (_glBindVertexArray) QGLContext::currentContext()->getProcAddress("glBindVertexArray");
    glBindVertexArray(cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
void Render::renderQuad()
{
    if (quad_vao == 0)
    {
        float vertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays = (_glGenVertexArrays) QGLContext::currentContext()->getProcAddress("glGenVertexArrays");
        glBindVertexArray = (_glBindVertexArray) QGLContext::currentContext()->getProcAddress("glBindVertexArray");
        glGenVertexArrays(1, &quad_vao);
        glf.glGenBuffers(1, &quad_vbo);
        glBindVertexArray(quad_vao);
        glf.glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
        glf.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        glf.glEnableVertexAttribArray(0);
        glf.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glf.glEnableVertexAttribArray(1);
        glf.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glGenVertexArrays = (_glGenVertexArrays) QGLContext::currentContext()->getProcAddress("glGenVertexArrays");
    glBindVertexArray = (_glBindVertexArray) QGLContext::currentContext()->getProcAddress("glBindVertexArray");
    glBindVertexArray(quad_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Render::computePrefilteredCubemap(std::unique_ptr<QOpenGLShaderProgram>& prefilter_program_,data_visualization::Camera& camera_, unsigned int specular_texture ){


    glf.glGenFramebuffers(1, &captureFBO);
    glf.glGenRenderbuffers(1, &captureRBO);

    glf.glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glf.glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glf.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glf.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    glf.glGenTextures(1, &prefilter_texture);
    glf.glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter_texture);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glf.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glf.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glf.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glf.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glf.glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


    Eigen::Matrix4f captureProjection =  camera_.GetProjection(90.0f, 1.0f, 0.1f, 10.0f);
    Eigen::Matrix4f captureViews[] =
    {
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(1.0f,  0.0f,  0.0f), Eigen::Vector3f(0.0f, -1.0f,  0.0f)),
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(-1.0f,  0.0f,  0.0f), Eigen::Vector3f(0.0f, -1.0f,  0.0f)),
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f,  1.0f,  0.0f), Eigen::Vector3f(0.0f,  0.0f,  1.0f)),
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f, -1.0f,  0.0f), Eigen::Vector3f(0.0f,  0.0f, -1.0f)),
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f,  0.0f,  1.0f), Eigen::Vector3f(0.0f, -1.0f,  0.0f)),
        camera_.lookAt(Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f,  0.0f, -1.0f), Eigen::Vector3f(0.0f, -1.0f,  0.0f))
    };

    prefilter_program_->bind();
    glf.glUseProgram(prefilter_program_->programId());
    glf.glUniform1i(prefilter_program_->uniformLocation("specular_map"),0);
    //prefilter_program_->setInt("specular_map", 0);
    glf.glUniformMatrix4fv(prefilter_program_->uniformLocation("projection"),1,GL_FALSE,captureProjection.data());
    //prefilter_program_->setMat4("projection", captureProjection);
    glf.glActiveTexture(GL_TEXTURE0);
    glf.glBindTexture(GL_TEXTURE_CUBE_MAP, specular_texture);

    glf.glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth  = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        glf.glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glf.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);

        glf.glUniform1f(prefilter_program_->uniformLocation("roughness"), roughness);

        //prefilter_program_->setFloat("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            glf.glUniformMatrix4fv(prefilter_program_->uniformLocation("view"),1,GL_FALSE,captureViews[i].data());

            //prefilter_program_->setMat4("view", captureViews[i]);
            glf.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilter_texture, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            renderCube();
        }
    }
    glf.glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::compute2D_LUT(std::unique_ptr<QOpenGLShaderProgram>& brdf_lut_program_){

    glf.glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glf.glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
    glf.glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glf.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glf.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glf.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glf.glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glf.glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glf.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glf.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    //glViewport(0, 0, 512, 512);
    glf.glUseProgram(brdf_lut_program_->programId());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderQuad();

    glf.glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
