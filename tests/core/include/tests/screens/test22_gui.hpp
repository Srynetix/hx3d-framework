#include "./base_test_screen.hpp"
#include "hx3d/scripting/scripter.hpp"
#include "hx3d/scripting/repl.hpp"

#include <string>

using namespace hx3d;
using namespace hx3d::graphics;
using namespace hx3d::scripting;

/*******************
  GUI
********************/

using NData = void*;

class NWidget: public std::enable_shared_from_this<NWidget>, public InputHandler {
  HX3D_ONLY_PTR(NWidget)

public:
  NWidget(Pointer<NWidget> parent = nullptr) {
    _parent = parent;
    _visible = true;
    _shape->setTint(Color(127, 127, 127));
  }

  virtual ~NWidget() {
    onFocusExit();
    onHide();
  }

  virtual void update(float delta) {
    _shape->transform.position.x = _transform.position.x;
    _shape->transform.position.y = _transform.position.y;
    _shape->transform.size.x = _transform.size.x;
    _shape->transform.size.y = _transform.size.y;
  }

  virtual void draw(const Pointer<Batch>& batch) {
    batch->draw(_shape);
  }

  virtual void onFocusEnter() {
    Log.Info("NWidget Focus Enter");
  }

  virtual void onFocusExit() {
    Log.Info("NWidget Focus Exit");
  }

  virtual void onShow() {
    Log.Info("NWidget Show");
  }

  virtual void onHide() {
    Log.Info("NWidget Hide");
  }

  void registerAction(std::string action) {
    if (_actions.find(action) != _actions.end()) {
      Log.Error("action %s already registered", action.c_str());
    } else {
      _actions[action] = nullptr;
    }
  }

  void send(std::string action) {
    if (_actions.find(action) == _actions.end()) {
      Log.Error("action %s do not exist", action.c_str());
    } else {
      auto act = _actions[action];
      if (act != nullptr) {
        act();
      }
    }
  }

  void on(std::string action, std::function<void()> func) {
    if (_actions.find(action) == _actions.end()) {
      Log.Error("action %s do not exist", action.c_str());
    } else {
      _actions[action] = func;
    }
  }

  Transform _transform;
  Shape::Ref _shape;
  Pointer<NWidget> _parent;

  bool _visible;

  std::map<std::string, std::function<void()>> _actions;

  bool checkBounds(glm::vec2 position) {
    float lx = _transform.position.x - ((_transform.size.x / 2) * _transform.scale.x);
    float hx = _transform.position.x + ((_transform.size.x / 2) * _transform.scale.x);
    float ly = _transform.position.y - ((_transform.size.y / 2) * _transform.scale.y);
    float hy = _transform.position.y + ((_transform.size.y / 2) * _transform.scale.y);

    auto x_pos = position.x;
    auto y_pos = Core::App()->getHeight() - position.y;

    if (x_pos >= lx && x_pos <= hx && y_pos >= ly && y_pos <= hy) {
      return true;
    } else {
      return false;
    }
  }

  ///////////////////
  // Input handler

  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) override {
    mouseClicked(button, mousePosition);
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    keyPressed(key);
  }

  virtual void onTextInput(std::string text) override {
    textInput(text);
  }

  /////////////////////
  // Widget handlers

  virtual void mouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {

  }

  virtual void keyPressed(KeyEvent::Key key) {

  }

  virtual void textInput(std::string text) {

  }
};

class NPlacement {
public:
  NPlacement(const Pointer<NWidget>& widget) {
    _widget = widget;
  }

  template <class W>
  static Pointer<W> None(const Pointer<NWidget>& widget) {
    NPlacement pl(widget);
    pl.size = {widget->_transform.size.x, widget->_transform.size.y};
    pl.position = {widget->_transform.position.x, widget->_transform.position.y};

    return std::dynamic_pointer_cast<W>(pl.apply());
  }

  template <class W>
  static Pointer<W> Fill(const Pointer<NWidget>& widget) {
    NPlacement pl(widget);

    if (widget->_parent) {
      pl.size = {widget->_parent->_transform.size.x, widget->_parent->_transform.size.y};
      pl.position = {widget->_parent->_transform.position.x, widget->_parent->_transform.position.y};
    }

    else {
      pl.size = Core::App()->getSize();
      pl.position = Core::App()->getSize() / 2;
    }

    return std::dynamic_pointer_cast<W>(pl.apply());
  }

  template <class W>
  static Pointer<W> Relative(const Pointer<NWidget>& widget, glm::vec2 relativePos, glm::vec2 relativeSize) {
    NPlacement pl(widget);
    if (widget->_parent) {
      auto trans = widget->_parent->_transform;

      pl.position = {trans.size.x * relativePos.x, trans.size.y * relativePos.y};
      pl.size = {trans.size.x * relativeSize.x, trans.size.y * relativeSize.y};
    }

    else {
      pl.position = {Core::App()->getWidth() * relativePos.x, Core::App()->getHeight() * relativePos.y};
      pl.size = {Core::App()->getWidth() * relativeSize.x, Core::App()->getHeight() * relativeSize.y};
    }

    return std::dynamic_pointer_cast<W>(pl.apply());
  }

  Pointer<NWidget> apply() {
    _widget->_transform.position.x = position.x;
    _widget->_transform.position.y = position.y;
    _widget->_transform.size.x = size.x;
    _widget->_transform.size.y = size.y;

    return _widget;
  }

  Pointer<NWidget> _widget;
  glm::vec2 size;
  glm::vec2 position;
};

class NContainer: public NWidget {
  HX3D_ONLY_PTR(NContainer)

public:
  bool _propagateEvent;
  Pointer<NWidget> _activeChild;
  std::vector<Pointer<NWidget>> _children;

  NContainer(const Pointer<NWidget>& parent = nullptr): NWidget(parent) {
    _propagateEvent = true;
    _activeChild = nullptr;
  }

  void addChild(const NWidget::Ptr& widget) {
    widget->_parent = shared_from_this();
    _children.push_back(widget);
  }

  virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) override {
    mouseClicked(button, mousePosition);

    if (_propagateEvent) {
      if (_activeChild && _activeChild->checkBounds(mousePosition)) {
        _activeChild->onMouseClicked(button, mousePosition);
      } else {
        // New active child
        for (auto& child: _children) {
          if (child != _activeChild && child->checkBounds(mousePosition)) {
            if (_activeChild) _activeChild->onFocusExit();

            _activeChild = child;
            child->onFocusEnter();
            child->onMouseClicked(button, mousePosition);
            return;
          }
        }

        // No active child
        if (_activeChild) {
          _activeChild->onFocusExit();
          _activeChild = nullptr;
        }
      }
    }
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    keyPressed(key);

    if (_propagateEvent) {
      if (_activeChild) {
        _activeChild->onKeyPressed(key);
      }
    }
  }

  virtual void onTextInput(std::string text) override {
    textInput(text);

    if (_propagateEvent) {
      if (_activeChild) {
        _activeChild->onTextInput(text);
      }
    }
  }

  virtual void update(float delta) override {
    NWidget::update(delta);
    for (auto& child: _children) {
      child->update(delta);
    }
  }

  virtual void draw(const Pointer<Batch>& batch) override {
    NWidget::draw(batch);
    for (auto& child: _children) {
      child->draw(batch);
    }
  }
};

class NLabel: public NWidget {
  HX3D_ONLY_PTR(NLabel)

public:
  Text::Ptr _text;

  NLabel(const NWidget::Ptr& parent = nullptr): NWidget(parent) {
    _text = Make<Text>();
  }

  virtual void update(float delta) override {
    NWidget::update(delta);

    _text->transform.position.x = _transform.position.x;
    _text->transform.position.y = _transform.position.y;
  }

  virtual void draw(const Pointer<Batch>& batch) override {
    NWidget::draw(batch);

    batch->draw(_text);
  }

  void setText(const std::string& text) {
    _text->setContent(text);
  }

  const std::string& getText() {
    return _text->getContent();
  }
};

class NPanel: public NContainer {
  HX3D_ONLY_PTR(NPanel)

public:
  NPanel(const NWidget::Ptr& parent = nullptr): NContainer(parent) {
    _shape->setTint(Color(0, 127, 127));
  }
};

class NTextBox: public NLabel {
  HX3D_ONLY_PTR(NTextBox)

public:
  NTextBox(const NWidget::Ptr& parent = nullptr): NLabel(parent) {
    registerAction("validate");
    _text->setCenterAlignment(false);
  }

  virtual void onFocusEnter() {
    _shape->setTint(Color(127, 127, 0));

    Core::Events()->beginTextInput();
  }

  virtual void onFocusExit() {
    _shape->setTint(Color(127, 127, 127));

    Core::Events()->endTextInput();
  }

  virtual void update(float delta) override {
    NWidget::update(delta);

    _text->transform.position.x = _transform.position.x - _transform.size.x / 2;
    _text->transform.position.y = _transform.position.y;
  }

  virtual void keyPressed(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Return) {
      send("validate");
    }

    else if (key == KeyEvent::Key::Backspace) {
      if (_content.size() > 0) {
        _content.pop_back();
      }

      _updateText();
    }
  }

  virtual void textInput(std::string text) override {
    _content += text;
    _updateText();
  }

  std::string _content;

private:
  void _updateText() {
    _text->setContent(_content);
  }
};

class NSystem {
  HX3D_ONLY_PTR(NSystem)

public:
  NSystem(const NWidget::Ptr& content = nullptr) {
    setContent(content);
  }

  ~NSystem() {
    unregisterHandler();
  }

  void setContent(const NWidget::Ptr& content) {
    if (_content) unregisterHandler();
    _content = content;

    if (_content->_visible) {
      _content->onShow();
      _content->onFocusEnter();
    }

    registerHandler();
  }

  void registerHandler() {
    if (_content)
      Core::Events()->registerHandler(_content.get());
  }

  void unregisterHandler() {
    if (_content)
      Core::Events()->unregisterHandler(_content.get());
  }

  void update(float delta) {
    if (_content)
      _content->update(delta);
  }

  void draw(const Pointer<Batch>& batch) {
    if (_content) {
      _content->draw(batch);
    }
  }

  NWidget::Ptr _content;
};

/*******************
  Test
********************/

class Test22: public BaseTestScreen {
public:
  Test22()
  {
    batch->setCamera(camera);

    auto panel = Make<NPanel>();
    auto label = Make<NLabel>();
    auto textbox = Make<NTextBox>();

    label->setText("Hello");

    textbox->on("validate", [textbox,label]() {
      label->setText(textbox->getText());
    });

    system = Make<NSystem>(NPlacement::Fill<NPanel>(panel));
    panel->addChild(NPlacement::Relative<NLabel>(label, {0.75, 0.15}, {0.25, 0.15}));
    panel->addChild(NPlacement::Relative<NTextBox>(textbox, {0.5, 0.85}, {0.25, 0.05}));
  }

  virtual void update(float delta) override {
    camera->update();

    system->update(delta);
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    system->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch2D::Ref batch;
  NSystem::Ptr system;
};
