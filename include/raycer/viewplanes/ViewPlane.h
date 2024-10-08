#pragma once

#include "core/math/Matrix.h"
#include "core/math/Vector.h"
#include "core/math/Rect.h"
#include "core/InequalityOperator.h"

#include <vector>
#include <algorithm>
#include <memory>

namespace raycer {
  class Sampler;
  
  class ViewPlane {
  public:
    class IteratorBase : public InequalityOperator<IteratorBase> {
    public:
      explicit IteratorBase(const ViewPlane* plane, const Recti& rect);
      explicit IteratorBase(const ViewPlane* plane, const Recti& rect, bool end);
      virtual ~IteratorBase() {}

      Vector3d current() const;
      virtual void advance() = 0;

      inline bool operator==(const IteratorBase& other) const {
        return m_row == other.m_row && m_column == other.m_column;
      }

      inline int column() const {
        return m_rect.left() + m_column;
      }
      
      inline int row() const {
        return m_rect.top() + m_row;
      }
      
      inline int pixelSize() const {
        return m_pixelSize;
      }
      
    protected:
      const ViewPlane* m_plane;
      Recti m_rect;
      int m_column, m_row, m_pixelSize;
    };

    class RegularIterator : public IteratorBase {
    public:
      explicit RegularIterator(const ViewPlane* plane, const Recti& rect);
      explicit RegularIterator(const ViewPlane* plane, const Recti& rect, bool);

      virtual void advance();
    };

    class Iterator : public InequalityOperator<Iterator> {
    public:
      inline explicit Iterator(IteratorBase* iteratorImpl) {
        m_iteratorImpl = iteratorImpl;
      }

      inline ~Iterator() {
        delete m_iteratorImpl;
      }

      inline Vector3d operator*() const {
        return m_iteratorImpl->current();
      }

      inline Vector2d pixel() const {
        return Vector2d(column(), row());
      }

      inline virtual Iterator& operator++() {
        m_iteratorImpl->advance();
        return *this;
      }

      inline bool operator==(const Iterator& other) const {
        return *m_iteratorImpl == *(other.m_iteratorImpl);
      }

      inline int column() const {
        return m_iteratorImpl->column();
      }
      
      inline int row() const {
        return m_iteratorImpl->row();
      }
      
      inline int pixelSize() const {
        return m_iteratorImpl->pixelSize();
      }
      
    protected:
      IteratorBase* m_iteratorImpl;
    };

    ViewPlane();
    explicit ViewPlane(const Matrix4d& matrix, const Recti& window);
    
    virtual ~ViewPlane();

    inline void setup(const Matrix4d& matrix, const Recti& window) {
      m_matrix = matrix;
      m_window = window;
      setupVectors();
    }

    inline int width() const {
      return m_window.width();
    }
    
    inline int height() const {
      return m_window.height();
    }

    virtual Iterator begin(const Recti& rect) const;

    inline Iterator end(const Recti& rect) const {
      return Iterator(new RegularIterator(this, rect, true));
    }

    inline const Vector3d& topLeft() const {
      return m_topLeft;
    }
    
    inline const Vector3d& right() const {
      return m_right;
    }
    
    inline const Vector3d& down() const {
      return m_down;
    }
    
    inline double pixelSize() const {
      return m_pixelSize;
    }
    
    inline void setPixelSize(double pixelSize) {
      m_pixelSize = pixelSize;
    }
    
    inline Vector3d pixelAt(double x, double y) {
      return (m_topLeft + m_right * x + m_down * y) * m_pixelSize;
    }
    
    inline void setSampler(std::shared_ptr<Sampler> sampler) {
      m_sampler = sampler;
    }
    
    inline std::shared_ptr<Sampler> sampler() const {
      return m_sampler;
    }
    
  protected:
    void setupVectors();

    friend class Iterator;

    Matrix4d m_matrix;
    Recti m_window;
    Vector3d m_topLeft, m_right, m_down;
    float m_pixelSize;
    
    std::shared_ptr<Sampler> m_sampler;
  };
}
