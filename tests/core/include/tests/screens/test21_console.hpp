#include "./base_test_screen.hpp"

#include <string>

using namespace hx3d;

class GUIWidget: public std::enable_shared_from_this<GUIWidget>, public InputHandler {
public:
  GUIWidget() {
    _sprite = Make<Sprite>();
    _sprite->setTexture(Core::Assets()->get<Texture>("box"));

    _visible = true;
    _activeChild = nullptr;
  }

  Pointer<Sprite> _sprite;
  std::vector<Pointer<GUIWidget>> _children;
  Pointer<GUIWidget> _parent;
  bool _visible;
  Pointer<GUIWidget> _activeChild;
  std::map<std::string, std::function<void(Pointer<GUIWidget>)>> _actions;

  virtual void onShow() {}
  virtual void onHide() {}
  virtual void onFocus() {}
  virtual void onExit() {}

  void setVisible(bool value) {
    this->_visible = value;
  }

  void registerAction(std::string action) {
    if (_actions.find(action) != _actions.end()) {
      Log.Error("GUIWidget: action %s already registered", action.c_str());
    } else {
      _actions[action] = nullptr;
    }
  }

  void send(std::string action) {
    if (_actions.find(action) == _actions.end()) {
      Log.Error("GUIWidget: action %s do not exist", action.c_str());
    } else {
      auto act = _actions[action];
      if (act != nullptr) {
        act(shared_from_this());
      }
    }
  }

  void on(std::string action, std::function<void(Pointer<GUIWidget>)> func) {
    if (_actions.find(action) == _actions.end()) {
      Log.Error("GUIWidget: action %s do not exist", action.c_str());
    } else {
      _actions[action] = func;
    }
  }

  template <class Type, class... Args>
  Pointer<Type> createChild(Args&&... args) {
    Pointer<Type> child = Make<Type>(args...);
    child->_parent = shared_from_this();
    _activeChild = child;
    _children.push_back(child);

    return child;
  }

  virtual void draw(const Pointer<Batch>& batch) {
    if (_visible) {
      batch->draw(_sprite);
    }

    for (auto& child: _children) {
      child->draw(batch);
    }
  }

  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {
    for (auto& child: _children) {
      if (child->checkBounds(mousePosition)) {

        if (_activeChild) {
          if (_activeChild != child) {
            child->onExit();
            _activeChild = child;
            child->onFocus();
          }
        } else {
          _activeChild = child;
          child->onFocus();
        }

        return;
      }
    }
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    for (auto& child: _children) {
      child->onKeyPressed(key);
    }
  }

  bool checkBounds(glm::vec2 position) {
    float lx = _sprite->transform.position.x - ((_sprite->transform.size.x / 2) * _sprite->transform.scale.x);
    float hx = _sprite->transform.position.x + ((_sprite->transform.size.x / 2) * _sprite->transform.scale.x);
    float ly = _sprite->transform.position.y - ((_sprite->transform.size.y / 2) * _sprite->transform.scale.y);
    float hy = _sprite->transform.position.y + ((_sprite->transform.size.y / 2) * _sprite->transform.scale.y);

    if (position.x >= lx && position.x <= hx && position.y >= ly && position.y <= hy) {
      return true;
    } else {
      return false;
    }
  }
};

class GUITextbox: public GUIWidget {
public:
  GUITextbox() {
    _sprite->setTexture(Core::Assets()->get<Texture>("box"));
    _sprite->transform.position.x = Core::App()->getWidth() / 2;
    _sprite->transform.position.y = Core::App()->getHeight() / 2;

    registerAction("validate");
  }

  virtual void onFocus() override {
    Log.Info("Focus !");
    Core::Events()->beginTextInput();
  }

  virtual void onExit() override {
    Log.Info("Exit !");
    Core::Events()->endTextInput();
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Return) {
      send("validate");
    }
  }

  std::string _enteredText;
};

class GUISystem {
public:
  GUISystem() {
    _root = Make<GUIWidget>();
    _root->setVisible(false);
    Core::Events()->registerHandler(_root.get());
  }

  ~GUISystem() {
    Core::Events()->unregisterHandler(_root.get());
  }

  void draw(const Pointer<Batch>& batch) {
    _root->draw(batch);
  }

  const Pointer<GUIWidget>& getContent() {
    return _root;
  }

  Pointer<GUIWidget> _root;
};

class Test21: public BaseTestScreen {
public:
  Test21()
  {
    gui = Make<GUISystem>();
    batch->setCamera(camera);

    auto textbox = gui->getContent()->createChild<GUITextbox>();
    textbox->on("validate", [](Pointer<GUIWidget> widget) {
      Log.Info("Executing script...");
    });
  }

  virtual void dispose() {
  }

  virtual void update(float delta) override {
    camera->update();
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    gui->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch::Ref batch;
  Pointer<GUISystem> gui;
};
