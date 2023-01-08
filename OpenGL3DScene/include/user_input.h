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
  UserInput(UserInput&) = delete;
  ~UserInput() = default;

  void AddScope(const std::string&);
  void RemoveScope(const std::string&);
  void AddBinding(const std::string&, const GLenum, const GLenum, std::function<void(void)>);
  void RemoveBinding(const std::string&, const GLenum, const GLenum);
  virtual void CaptureUserInput(std::shared_ptr<Window>) = 0;
  void ChangeScope(const std::string&);
  const ScopeMap& GetScopes();
  const BindingMap& GetCurrentScope();

  static const std::string DefaultScope;

  protected:
   ScopeMap scopes_ = { {DefaultScope, BindingMap()} };
   BindingMap& current_scope_ = scopes_[DefaultScope];
};

class KeyboardInput : public UserInput {
 public:
  KeyboardInput() = default;
  KeyboardInput(KeyboardInput&) = delete;
  ~KeyboardInput() = default;

  void CaptureUserInput(std::shared_ptr<Window>) override;
};

class MouseInput : public UserInput {
 public:
  MouseInput() = default;
  MouseInput(MouseInput&) = delete;
  ~MouseInput() = default;

  bool first_click = true;
  float sensitivity = 50.0f;

  void CaptureUserInput(std::shared_ptr<Window>) override;
};

#endif  // OPENGL3DSCENE_USER_INPUT_H_