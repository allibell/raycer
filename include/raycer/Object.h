#pragma once

#include <string>

namespace raycer {
  class Object {
  public:
    inline Object() {}
    virtual ~Object() {}

    inline void setName(const std::string& name) {
      m_name = name;
    }

    inline const std::string& name() const {
      return m_name;
    }

  private:
    std::string m_name;
  };
}
