#include "user_input.h"

const std::string UserInput::DefaultScope = "default";

void UserInput::AddScope(const std::string& scope_name) {
  scopes_[scope_name] = BindingMap();
}

void UserInput::RemoveScope(const std::string& scope_name) {
  scopes_.erase(scope_name);
}

void UserInput::AddBinding(const std::string& scope_name, const GLenum key, const GLenum action, std::function<void(void)> func) {
  scopes_[scope_name][key][action] = func;
}

void UserInput::RemoveBinding(const std::string& scope_name, const GLenum key, const GLenum action) {
  scopes_.at(scope_name).at(key).erase(action);
}

void UserInput::ChangeScope(const std::string& scope_name) {
  current_scope_ = scopes_.at(scope_name);
}

const ScopeMap& UserInput::GetScopes() {
  return scopes_;
}

const BindingMap& UserInput::GetCurrentScope() {
  return current_scope_;
}

void KeyboardInput::CaptureUserInput(std::shared_ptr<Window> window) {
  for (const auto& binding : current_scope_) {
    for (const auto& action : binding.second) {
      if (window->GetKey(binding.first) == action.first) {
        action.second();
      }
    }
  }
}

void MouseInput::CaptureUserInput(std::shared_ptr<Window> window) {
  for (const auto& binding : current_scope_) {
    for (const auto& action : binding.second) {
      if (window->GetMouseButton(binding.first) == action.first) {
        action.second();
      }
    }
  }
}