#include <glm/glm.hpp>

inline glm::vec4 add(const glm::vec4& a, const glm::vec4& b) {
  return glm::vec4(a.x + b.x, a.y + b.y, a.z + b.z, 1.0);
}

inline glm::vec4 subtract(const glm::vec4& a, const glm::vec4& b) {
  return glm::vec4(a.x - b.x, a.y - b.y, a.z - b.z, 1.0);
}

inline bool compare(const glm::vec4& a, const glm::vec4& b, float epsilon = 1e-9) {
  return std::abs(a.x - b.x) < epsilon && std::abs(a.y - b.y) < epsilon && std::abs(a.z - b.z) < epsilon && std::abs(a.w - b.w) < epsilon;
}

inline glm::vec4 divide(const glm::vec4& a, float b) {
  return glm::vec4(a.x / b, a.y / b, a.z / b, 1.0);
}