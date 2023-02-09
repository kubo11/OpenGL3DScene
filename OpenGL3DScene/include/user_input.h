#ifndef OPENGL3DSCENE_USER_INPUT_H_
#define OPENGL3DSCENE_USER_INPUT_H_

#include <functional>
#include <string>
#include <unordered_map>

#include "window.h"

using ActionMap = std::unordered_map<GLenum, std::function<void(void)>>;
using BindingMap = std::unordered_map<GLenum, ActionMap>;
using ScopeMap = std::unordered_map<std::string, BindingMap>;

class UserInput {
 public:
  UserInput() = default;
  ~UserInput() = default;

  UserInput(const UserInput&) = delete;
  UserInput& operator = (const UserInput&) = delete;

  UserInput(UserInput&&) noexcept = default;
  UserInput& operator = (UserInput&&) noexcept = default;

  void AddScope(const std::string&);
  void RemoveScope(const std::string&);
  void AddBinding(const std::string&, const GLenum, const GLenum, std::function<void(void)>);
  void RemoveBinding(const std::string&, const GLenum, const GLenum);
  virtual void CaptureUserInput(std::shared_ptr<Window>) = 0;
  void ChangeScope(std::string);
  const ScopeMap& GetScopes();
  const BindingMap& GetCurrentScope();

  static const std::string DefaultScope;

  protected:
   ScopeMap scopes_ = { {DefaultScope, BindingMap()} };
   std::string current_scope_ = DefaultScope;
};

class KeyboardInput : public UserInput {
 public:
  KeyboardInput() = default;
  ~KeyboardInput() = default;

  KeyboardInput(const KeyboardInput&) = delete;
  KeyboardInput& operator = (const KeyboardInput&) = delete;

  KeyboardInput(KeyboardInput&&) noexcept = default;
  KeyboardInput& operator = (KeyboardInput&&) noexcept = default;

  void CaptureUserInput(std::shared_ptr<Window>) override;
};

class MouseInput : public UserInput {
 public:
  MouseInput() = default;
  ~MouseInput() = default;

  MouseInput(const MouseInput&) = delete;
  MouseInput& operator = (const MouseInput&) = delete;

  MouseInput(MouseInput&&) noexcept = default;
  MouseInput& operator = (MouseInput&&) noexcept = default;

  bool first_click = true;
  float sensitivity = 50.0f;

  void CaptureUserInput(std::shared_ptr<Window>) override;
};

#endif  // OPENGL3DSCENE_USER_INPUT_H_