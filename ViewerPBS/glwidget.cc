// Author: Marc Comino 2018

#include <glwidget.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "./triangle_mesh.h"
#include "./mesh_io.h"

namespace {

const float kFieldOfView = 60;
const float kZNear = 0.0001;
const float kZFar = 10;
//REFLECTION
const char kReflectionVertexShaderFile[] = "../shaders/reflection.vert";
const char kReflectionFragmentShaderFile[] = "../shaders/reflection.frag";
//BRDF
const char kBRDFVertexShaderFile[] = "../shaders/brdf.vert";
const char kBRDFFragmentShaderFile[] = "../shaders/brdf.frag";
//SKY
const char kSkyVertexShaderFile[] = "../shaders/sky.vert";
const char kSkyFragmentShaderFile[] = "../shaders/sky.frag";
//PREFILTER
const char kPreFilterVertexShaderFile[] = "../shaders/prefilter.vert";
const char kPreFilterFragmentShaderFile[] = "../shaders/prefilter.frag";
//BRDF-LUT
const char kBRDFLUTVertexShaderFile[] = "../shaders/brdf_lut.vert";
const char kBRDFLUTFragmentShaderFile[] = "../shaders/brdf_lut.frag";

const int kVertexAttributeIdx = 0;
const int kNormalAttributeIdx = 1;

bool ReadFile(const std::string filename, std::string *shader_source) {
  std::ifstream infile(filename.c_str());

  if (!infile.is_open() || !infile.good()) {
    std::cerr << "Error " + filename + " not found." << std::endl;
    return false;
  }

  std::stringstream stream;
  stream << infile.rdbuf();
  infile.close();

  *shader_source = stream.str();
  return true;
}

bool LoadImage(const std::string &path, GLuint cube_map_pos) {
  QImage image;
  bool res = image.load(path.c_str());
  if (res) {
    QImage gl_image = image.mirrored();
    glTexImage2D(cube_map_pos, 0, GL_RGBA, image.width(), image.height(), 0,
                 GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
  }
  return res;
}

bool LoadCubeMap(const QString &dir) {
  std::string path = dir.toUtf8().constData();
  bool res = LoadImage(path + "/right.png", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
  res = res && LoadImage(path + "/left.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
  res = res && LoadImage(path + "/top.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
  res = res && LoadImage(path + "/bottom.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
  res = res && LoadImage(path + "/back.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
  res = res && LoadImage(path + "/front.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

  if (res) {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  }

  return res;
}

bool LoadProgram(const std::string &vertex, const std::string &fragment,
                 QOpenGLShaderProgram *program) {
  std::string vertex_shader, fragment_shader;
  bool res =
      ReadFile(vertex, &vertex_shader) && ReadFile(fragment, &fragment_shader);

  if (res) {
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                     vertex_shader.c_str());
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fragment_shader.c_str());
    program->bindAttributeLocation("vertex", kVertexAttributeIdx);
    program->bindAttributeLocation("normal", kNormalAttributeIdx);
    program->link();
  }

  return res;
}

}  // namespace

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent),
      initialized_(false),
      width_(0.0),
      height_(0.0),
      reflection_(true),
      fresnel_(0.2, 0.2, 0.2),
      LUT_rendered(false)
{
  setFocusPolicy(Qt::StrongFocus);

}

GLWidget::~GLWidget() {
  if (initialized_) {
    glDeleteTextures(1, &specular_map_);
    glDeleteTextures(1, &diffuse_map_);
  }
}


bool GLWidget::LoadModel(const QString &filename) {
  std::string file = filename.toUtf8().constData();
  uint pos = file.find_last_of(".");
  std::string type = file.substr(pos + 1);

  std::unique_ptr<data_representation::TriangleMesh> mesh =
      std::make_unique<data_representation::TriangleMesh>();

  bool res = false;
  if (type.compare("ply") == 0) {
    res = data_representation::ReadFromPly(file, mesh.get());
  }

  if (res) {
    mesh_.reset(mesh.release());
    camera_.UpdateModel(mesh_->min_, mesh_->max_);

    // TODO(students): Create / Initialize buffers.
    render.initializeBuffers(mesh_);
    // END.

    emit SetFaces(QString(std::to_string(mesh_->faces_.size() / 3).c_str()));
    emit SetVertices(
        QString(std::to_string(mesh_->vertices_.size() / 3).c_str()));
    return true;
  }

  return false;
}

bool GLWidget::LoadSpecularMap(const QString &dir) {
  glBindTexture(GL_TEXTURE_CUBE_MAP, specular_map_);
  bool res = LoadCubeMap(dir);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  render.computePrefilteredCubemap(prefilter_program_,camera_,specular_map_);
  render.compute2D_LUT(brdf_lut_program_);
  return res;
}

bool GLWidget::LoadDiffuseMap(const QString &dir) {
  glBindTexture(GL_TEXTURE_CUBE_MAP, diffuse_map_);
  bool res = LoadCubeMap(dir);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  return res;
}

void GLWidget::initializeGL() {
  render.glf.initializeOpenGLFunctions();

  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  glGenTextures(1, &specular_map_);
  glGenTextures(1, &diffuse_map_);

  reflection_program_ = std::make_unique<QOpenGLShaderProgram>();
  brdf_program_ = std::make_unique<QOpenGLShaderProgram>();
  sky_program_ = std::make_unique<QOpenGLShaderProgram>();
  prefilter_program_ = std::make_unique<QOpenGLShaderProgram>();
  brdf_lut_program_ = std::make_unique<QOpenGLShaderProgram>();

  bool res =
      LoadProgram(kReflectionVertexShaderFile, kReflectionFragmentShaderFile,
                  reflection_program_.get());
  res = res && LoadProgram(kBRDFVertexShaderFile, kBRDFFragmentShaderFile,
                           brdf_program_.get());
  res = res && LoadProgram(kSkyVertexShaderFile, kSkyFragmentShaderFile,
                           sky_program_.get());
  res = res && LoadProgram(kPreFilterVertexShaderFile, kPreFilterFragmentShaderFile,
                           prefilter_program_.get());
  res = res && LoadProgram(kBRDFLUTVertexShaderFile, kBRDFLUTFragmentShaderFile,
                           brdf_lut_program_.get());
  if (!res) exit(0);

  initialized_ = true;
}

void GLWidget::resizeGL(int w, int h) {
  if (h == 0) h = 1;
  width_ = w;
  height_ = h;

  camera_.SetViewport(0, 0, w, h);
  camera_.SetProjection(kFieldOfView, kZNear, kZFar);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    camera_.StartRotating(event->x(), event->y());
  }
  if (event->button() == Qt::RightButton) {
    camera_.StartZooming(event->x(), event->y());
  }
  updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  camera_.SetRotationX(event->y());
  camera_.SetRotationY(event->x());
  camera_.SafeZoom(event->y());
  updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    camera_.StopRotating(event->x(), event->y());
  }
  if (event->button() == Qt::RightButton) {
    camera_.StopZooming(event->x(), event->y());
  }
  updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Up) camera_.Zoom(-1);
  if (event->key() == Qt::Key_Down) camera_.Zoom(1);

  if (event->key() == Qt::Key_Left) camera_.Rotate(-1);
  if (event->key() == Qt::Key_Right) camera_.Rotate(1);

  if (event->key() == Qt::Key_W) camera_.Zoom(-1);
  if (event->key() == Qt::Key_S) camera_.Zoom(1);

  if (event->key() == Qt::Key_A) camera_.Rotate(-1);
  if (event->key() == Qt::Key_D) camera_.Rotate(1);

  if (event->key() == Qt::Key_R) {
    reflection_program_.reset();
    reflection_program_ = std::make_unique<QOpenGLShaderProgram>();
    LoadProgram(kReflectionVertexShaderFile, kReflectionFragmentShaderFile,
                reflection_program_.get());

    brdf_program_.reset();
    brdf_program_ = std::make_unique<QOpenGLShaderProgram>();
    LoadProgram(kBRDFVertexShaderFile, kBRDFFragmentShaderFile,
                brdf_program_.get());

    sky_program_.reset();
    sky_program_ = std::make_unique<QOpenGLShaderProgram>();
    LoadProgram(kSkyVertexShaderFile, kSkyFragmentShaderFile,
                sky_program_.get());

    prefilter_program_.reset();
    prefilter_program_ = std::make_unique<QOpenGLShaderProgram>();
    LoadProgram(kPreFilterVertexShaderFile, kPreFilterFragmentShaderFile,
                prefilter_program_.get());
  }

  updateGL();
}

void GLWidget::paintGL() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  QOpenGLTimerQuery timer;
  timer.create();
  timer.begin();



  if (initialized_) {
    camera_.SetViewport();

    Eigen::Matrix4f projection = camera_.SetProjection();
    Eigen::Matrix4f view = camera_.SetView();
    Eigen::Matrix4f model = camera_.SetModel();

    Eigen::Matrix4f view_inverse= view.inverse();
    Eigen::Matrix4f t = view * model;
    Eigen::Matrix3f normal;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) normal(i, j) = t(i, j);

    normal = normal.inverse().transpose();

    if (mesh_ != nullptr) {
      GLuint projection_location, view_location, model_location,
          normal_matrix_location, specular_map_location, diffuse_map_location,
          fresnel_location,brdf_lut_map_location;

      std::unique_ptr<QOpenGLShaderProgram> program_;

      if (reflection_) {
        reflection_program_->bind();
        projection_location = reflection_program_->uniformLocation("projection");
        view_location = reflection_program_->uniformLocation("view");
        model_location = reflection_program_->uniformLocation("model");
        normal_matrix_location =reflection_program_->uniformLocation("normal_matrix");
        specular_map_location = reflection_program_->uniformLocation("specular_map");
        diffuse_map_location =reflection_program_->uniformLocation("diffuse_map");
        brdf_lut_map_location = reflection_program_->uniformLocation("brdf_lut_map");
        fresnel_location = reflection_program_->uniformLocation("fresnel");

        render.glf.glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.data());
        render.glf.glUniformMatrix4fv(view_location, 1, GL_FALSE, view.data());
        render.glf.glUniformMatrix4fv(model_location, 1, GL_FALSE, model.data());
        render.glf.glUniformMatrix3fv(normal_matrix_location, 1, GL_FALSE, normal.data());
        render.glf.glUniformMatrix4fv(reflection_program_->uniformLocation("view_inverse"), 1, GL_FALSE, view_inverse.data());

        render.glf.glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, specular_map_);
        render.glf.glUniform1i(specular_map_location, 0);

        render.glf.glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, diffuse_map_);
        render.glf.glUniform1i(diffuse_map_location, 1);

        render.glf.glUniform3f(fresnel_location, fresnel_[0], fresnel_[1], fresnel_[2]);


        render.paintGL(reflection_program_, mesh_);

      } else {
          if(!LUT_rendered){
              render.compute2D_LUT(brdf_lut_program_);
              LUT_rendered=true;
          }

        brdf_program_->bind();
        projection_location = brdf_program_->uniformLocation("projection");
        view_location = brdf_program_->uniformLocation("view");
        model_location = brdf_program_->uniformLocation("model");
        normal_matrix_location =brdf_program_->uniformLocation("normal_matrix");
        specular_map_location = brdf_program_->uniformLocation("specular_map");
        diffuse_map_location = brdf_program_->uniformLocation("diffuse_map");
        brdf_lut_map_location = brdf_program_->uniformLocation("brdf_lut_map");
        fresnel_location = brdf_program_->uniformLocation("fresnel");

        render.glf.glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.data());
        render.glf.glUniformMatrix4fv(view_location, 1, GL_FALSE, view.data());
        render.glf.glUniformMatrix4fv(model_location, 1, GL_FALSE, model.data());
        render.glf.glUniformMatrix3fv(normal_matrix_location, 1, GL_FALSE, normal.data());
        render.glf.glUniformMatrix4fv(brdf_program_->uniformLocation("view_inverse"), 1, GL_FALSE, view_inverse.data());

        render.glf.glActiveTexture(GL_TEXTURE0);
        render.glf.glBindTexture(GL_TEXTURE_CUBE_MAP, render.prefilter_texture); //specular_map_
        render.glf.glUniform1i(specular_map_location, 0);

        render.glf.glActiveTexture(GL_TEXTURE1);
        render.glf.glBindTexture(GL_TEXTURE_CUBE_MAP, diffuse_map_);
        render.glf.glUniform1i(diffuse_map_location, 1);

        render.glf.glActiveTexture(GL_TEXTURE2);
        render.glf.glBindTexture(GL_TEXTURE_2D, render.brdfLUTTexture);
        render.glf.glUniform1i(brdf_lut_map_location,2);

        render.glf.glUniform3f(fresnel_location, fresnel_[0], fresnel_[1], fresnel_[2]);
        render.glf.glUniform1f( brdf_program_->uniformLocation("roughness"),roughness_);
        render.glf.glUniform1f( brdf_program_->uniformLocation("metallic"),metallic_);
        render.glf.glUniform3f( brdf_program_->uniformLocation("diffuseColor"),0,0,0);
        render.glf.glUniform3f( brdf_program_->uniformLocation("lightColor"),1,1,1);
        render.glf.glUniform3f( brdf_program_->uniformLocation("lightDir"),0,-1,-0.5);

        render.paintGL(brdf_program_, mesh_);
      }

    }

    model = camera_.SetIdentity();

    sky_program_->bind();
    GLuint projection_location = sky_program_->uniformLocation("projection");
    GLuint view_location = sky_program_->uniformLocation("view");
    GLuint model_location = sky_program_->uniformLocation("model");
    GLuint normal_matrix_location =
        sky_program_->uniformLocation("normal_matrix");
    GLuint specular_map_location =
        sky_program_->uniformLocation("specular_map");

    render.glf.glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.data());
    render.glf.glUniformMatrix4fv(view_location, 1, GL_FALSE, view.data());
    render.glf.glUniformMatrix4fv(model_location, 1, GL_FALSE, model.data());
    render.glf.glUniformMatrix3fv(normal_matrix_location, 1, GL_FALSE, normal.data());

    render.glf.glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, specular_map_);
    render.glf.glUniform1i(specular_map_location, 0);

    render.renderCube();

  }

  // TODO(students): Implement framerate displaying.
  timer.end();
  float frameRate = 1.0f/(timer.waitForResult()/1e9f);
  emit SetFramerate(QString::number(frameRate));
  // emit SetFramerate(...);

  // END.
}

void GLWidget::SetReflection(bool set) {
  reflection_ = set;
  updateGL();
}

void GLWidget::SetBRDF(bool set) {
  reflection_ = !set;
  updateGL();
}

void GLWidget::SetFresnelR(double r) {
  fresnel_[0] = r;
  updateGL();
}

void GLWidget::SetFresnelG(double g) {
  fresnel_[1] = g;
  updateGL();
}

void GLWidget::SetFresnelB(double b) {
  fresnel_[2] = b;
  updateGL();
}
void GLWidget::SetRoughness(double r) {
  roughness_ = r;
  updateGL();
}
void GLWidget::SetMetallic(double r) {
  metallic_ = r;
  updateGL();
}
