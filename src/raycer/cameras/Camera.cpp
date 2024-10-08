#include "raycer/cameras/Camera.h"
#include "core/math/Rect.h"
#include "raycer/viewplanes/ViewPlane.h"
#include "raycer/viewplanes/PointInterlacedViewPlane.h"
#include "raycer/samplers/Sampler.h"
#include "core/Buffer.h"
#include "raycer/Raycer.h"
#include "raycer/State.h"

using namespace raycer;

Camera::Camera()
  : m_cancelled(false),
    m_showProgressIndicators(false),
    m_viewPlane(std::make_shared<PointInterlacedViewPlane>())
{
}

Camera::Camera(const Vector3d& position, const Vector3d& target)
  : Camera()
{
  m_position = position;
  m_target = target;
}

Camera::~Camera() {
}

void Camera::setViewPlane(std::shared_ptr<ViewPlane> plane) {
  m_viewPlane = plane;
}

const Matrix4d& Camera::matrix() const {
  if (!m_matrix) {
    auto zAxis = (m_target - m_position).normalized();
    auto xAxis = Vector3d::up() ^ zAxis;
    auto yAxis = xAxis ^ -zAxis;

    m_matrix = Matrix4d(xAxis, yAxis, zAxis).inverted();
    m_matrix.value().setCell(0, 3, m_position[0]);
    m_matrix.value().setCell(1, 3, m_position[1]);
    m_matrix.value().setCell(2, 3, m_position[2]);
  }
  return m_matrix;
}

void Camera::render(std::shared_ptr<Raycer> raycer, Buffer<unsigned int>& buffer) const {
  render(raycer, buffer, Recti(0, 0, buffer.width(), buffer.height()));
}

void Camera::render(std::shared_ptr<Raycer> raycer, Buffer<unsigned int>& buffer, const Recti& rect) const {
  if (isCancelled())
    return;

  auto plane = viewPlane();

  for (ViewPlane::Iterator pixel = plane->begin(rect), end = plane->end(rect); pixel != end; ++pixel) {
    if (m_showProgressIndicators) {
      plotRGB(buffer, rect, pixel, 0xff0000);
    }

    Colord pixelColor;
    for (const auto& sample : plane->sampler()->sampleSet()) {
      Rayd ray = rayForPixel(pixel.pixel() + sample);
      if (ray.direction().isDefined()) {
        State state;
        pixelColor += raycer->rayColor(ray, state);
      }
    }

    plot(buffer, rect, pixel, pixelColor);

    if (isCancelled())
      break;
  }
}

void Camera::plot(Buffer<unsigned int>& buffer, const Recti& rect, const ViewPlane::Iterator& pixel, const Colord& color) const {
  auto avergageColor = color / viewPlane()->sampler()->numSamples();
  unsigned int rgb = avergageColor.rgb();
  plotRGB(buffer, rect, pixel, rgb);
}

void Camera::plotRGB(Buffer<unsigned int>& buffer, const Recti& rect, const ViewPlane::Iterator& pixel, unsigned int rgbColor) const {
  int size = pixel.pixelSize();
  if (size == 1) {
    buffer[pixel.row()][pixel.column()] = rgbColor;
  } else {
    for (int x = pixel.column(); x != pixel.column() + size && x < rect.right(); ++x)
      for (int y = pixel.row(); y != pixel.row() + size && y < rect.bottom(); ++y)
        buffer[y][x] = rgbColor;
  }
}
