#include "./base_test_screen.hpp"
#include "hx3d/scripting/scripter.hpp"
#include "hx3d/scripting/repl.hpp"

#include <string>

using namespace hx3d;
using namespace hx3d::scripting;

/*******************
  GUI
********************/

class NWidget: public std::enable_shared_from_this<NWidget>, public InputHandler {
public:
  class FocusHandler: public InputHandler {
  public:
    FocusHandler(NWidget* widget): _widget(widget) {}

    virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) override {
      if (_widget->_propagateEvent) {
        Log.Info("CLIC");
        if (_widget->_activeChild) {
          _widget->_activeChild->_focusHandler->onMouseClicked(button, mousePosition);
        }
      }
    }

    virtual void onKeyPressed(KeyEvent::Key key) override {

    }

    virtual void onTextInput(std::string text) override {

    }

    NWidget* _widget;
  };

  NWidget(Pointer<NWidget> parent = nullptr) {
    _focusHandler = Make<FocusHandler>(this);
    _parent = parent;
    _activeChild = nullptr;

    _visible = true;
    _propagateEvent = true;
    _conserveFocus = true;
  }

  virtual void updateTransform() {}
  virtual void draw(const Pointer<Batch>& batch) {}

  Transform _transform;
  std::vector<Pointer<NWidget>> _children;
  Pointer<NWidget> _parent;
  Pointer<FocusHandler> _focusHandler;

  bool _visible;
  bool _propagateEvent;
  bool _conserveFocus;

  Pointer<NWidget> _activeChild;
  std::map<std::string, std::function<void(Pointer<NWidget>)>> _actions;
};

class GUIWidget: public std::enable_shared_from_this<GUIWidget>, public InputHandler {
public:
  class Placement {
  public:
    enum class Type {
      Fill = 0,
      Relative,
      Absolute
    };

    Placement() {
      _coords = {0, 0, 0, 0};
    }

    static Placement Fill() {
      Placement p;
      p._type = Type::Absolute;
      return p;
    }

    static Placement Relative(float min_x, float min_y, float max_x, float max_y) {
      Placement p;
      p._type = Type::Relative;
      p._coords = {min_x, min_y, max_x, max_y};
      return p;
    }

    static Placement Absolute() {
      Placement p;
      p._type = Type::Absolute;
      return p;
    }

    glm::vec4 _coords;
    Type _type;
  };

  GUIWidget() {
    _sprite = Make<Sprite>();

    _visible = true;
    _propagate = true;
    _activeChild = nullptr;
  }

  Pointer<Sprite> _sprite;
  std::vector<Pointer<GUIWidget>> _children;
  Pointer<GUIWidget> _parent;
  bool _visible;
  bool _propagate;
  Pointer<GUIWidget> _activeChild;
  std::map<std::string, std::function<void(Pointer<GUIWidget>)>> _actions;

  virtual void onShow() {}
  virtual void onHide() {}
  virtual void onFocus() {}
  virtual void onExit() {}

  void setVisible(bool value) {
    if (value != _visible) {
      if (value) this->onShow();
      else this->onHide();
    }

    _visible = value;
  }

  void setActive() {
    if (_parent) {
      auto parent_active = _parent->_activeChild;
      auto self = shared_from_this();

      if (parent_active && parent_active != self) {
        parent_active->onExit();
      }

      if (parent_active != self) {
        self->onFocus();
        _parent->_activeChild = self;
      }
    }
  }

  void setInactive() {
    if (_parent) {
      auto self = shared_from_this();
      auto parent_active = _parent->_activeChild;
      if (parent_active == self) {
        _parent->_activeChild = nullptr;
        self->onExit();
      }
    }
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

  virtual bool setFocus(glm::vec2 position) {
    for (auto& child: _children) {
      if (child->setFocus(position)) {
        if (_activeChild && _activeChild != child) {
          _activeChild->onExit();
        }

        if (_activeChild != child) {
          _activeChild = child;
          _activeChild->onFocus();
        }

        return true;
      }
    }

    if (_activeChild) {
      _activeChild->onExit();
      _activeChild = nullptr;
    }

    return checkBounds(position);
  }

  template <class Type, class... Args>
  Pointer<Type> createChild(Placement placement, Args&&... args) {
    Pointer<Type> child = Make<Type>(args...);
    child->_parent = shared_from_this();
    _children.push_back(child);

    if (placement._type == Placement::Type::Fill) {
      child->_sprite->transform.position.x = this->_sprite->transform.position.x;
      child->_sprite->transform.position.y = this->_sprite->transform.position.y;
      child->_sprite->transform.size.x = this->_sprite->transform.size.x;
      child->_sprite->transform.size.y = this->_sprite->transform.size.y;
    } else if (placement._type == Placement::Type::Absolute) {
      // Do nothing
    } else if (placement._type == Placement::Type::Relative) {
      // Calcul
    }

    return child;
  }

  template <class Type, class... Args>
  Pointer<Type> createHiddenChild(Placement placement, Args&&... args) {
    Pointer<Type> child = createChild<Type>(placement, args...);
    child->_visible = false;

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
    if (_propagate) {
      if (_activeChild) {
        _activeChild->onMouseClicked(button, mousePosition);
      }
    }
  }

  virtual void onTextInput(std::string text) {
    if (_propagate) {
      if (_activeChild) {
        _activeChild->onTextInput(text);
      }
    }
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    if (_propagate) {
      if (_activeChild) {
        _activeChild->onKeyPressed(key);
      }
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

class ConsolePanel: public GUIWidget {
public:
  ConsolePanel(float x, float y, float w, float h) {
    _sprite->transform.position.x = x;
    _sprite->transform.position.y = y;
    _sprite->transform.position.z = 0.01;
    _sprite->transform.size.x = w;
    _sprite->transform.size.y = h;

    _scrollback->transform.position.x = x;
    _scrollback->transform.position.y = y - 25;
    _scrollback->transform.position.z = 0.08;

    _sprite->setTint(Color(127, 127, 127, 127));

    registerAction("show");
    registerAction("hide");
  }

  virtual void onFocus() override {
    Log.Info("Console Panel active");
  }

  virtual void onExit() override {
    Log.Info("Console Panel inactive");
  }

  virtual void onShow() override {
    Core::Events()->endTextInput();

    Log.Info("Tweening Down");
    send("show");
  }

  virtual void onHide() override {
    Log.Info("Tweening Up");
    send("hide");
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::ConsoleKey) {
      Log.Info("Console !");

      setVisible(!_visible);
    }

    GUIWidget::onKeyPressed(key);
  }

  void addText(std::string text) {
    _scrollback->setContent(text);
  }

  virtual void draw(const Pointer<Batch>& batch) override {
    if (_visible) {
      batch->draw(_sprite);
      batch->draw(_scrollback);
    }

    for (auto& child: _children) {
      child->draw(batch);
    }
  }

  PrivateReference<gui::Text> _scrollback;
};

class GUITextbox: public GUIWidget {
public:
  GUITextbox() {
    _sprite->transform.position.x = Core::App()->getWidth() / 2;
    _sprite->transform.position.y = Core::App()->getHeight() - Core::App()->getHeight() / 8;
    _sprite->transform.position.z = 0.02;
    _sprite->transform.size.x = 256;
    _sprite->transform.size.y = 48;
    _sprite->transform.scale = glm::vec3(0.25);

    _display = Make<gui::Text>();
    _display->transform.position.x = _sprite->transform.position.x;
    _display->transform.position.y = _sprite->transform.position.y;
    _display->transform.position.z = _sprite->transform.position.z + 0.01;

    registerAction("validate");
  }

  virtual void onFocus() override {
    Log.Info("Focus !");
    _sprite->setTint(Color(127, 0, 127));
    Core::Events()->beginTextInput();
  }

  virtual void onExit() override {
    Log.Info("Exit !");
    _sprite->setTint(Color(127, 127, 127));
    Core::Events()->endTextInput();
  }

  virtual void onKeyPressed(KeyEvent::Key key) override {
    if (key == KeyEvent::Key::Return) {
      send("validate");
    }

    else if (key == KeyEvent::Key::Backspace) {
      if (_enteredText.size() > 0) {
        _enteredText.pop_back();
      }

      _updateText();
    }
  }

  virtual void onTextInput(std::string text) override {
    _enteredText += text;
    _updateText();
  }

  std::string getText() const {
    return _enteredText;
  }

  void setText(std::string txt) {
    _enteredText = txt;
    _updateText();
  }

  void _updateText() {
    _display->setContent(_enteredText);
  }

  virtual void draw(const Pointer<Batch>& batch) {
    if (_visible) {
      batch->draw(_sprite);
      batch->draw(_display);
    }
  }

  std::string _enteredText;
  Pointer<gui::Text> _display;
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
    glDisable(GL_DEPTH_TEST);
    _root->draw(batch);
    glEnable(GL_DEPTH_TEST);
  }

  const Pointer<GUIWidget>& getContent() {
    return _root;
  }

  Pointer<GUIWidget> _root;
};

/*******************
  Test
********************/

class Test21: public BaseTestScreen {
public:
  Test21()
  {
    batch->setCamera(camera);

    REPL::Config config;
    config.scripter = &scripter;
    repl = Make<REPL>(config);
    repl->begin();

    widg = Make<NWidget>();
    Core::Events()->registerHandler(widg->_focusHandler.get());

    // gui = Make<GUISystem>();
    //
    // auto top_center = glm::vec2(Core::App()->getWidth() / 2, Core::App()->getHeight() - Core::App()->getHeight() / 8);
    // auto consolepanel = gui->getContent()->createHiddenChild<ConsolePanel>(GUIWidget::Placement::Fill(), top_center.x, top_center.y, Core::App()->getWidth(), Core::App()->getHeight() / 4);
    // consolepanel->setActive();
    //
    // auto textbox = consolepanel->createHiddenChild<GUITextbox>(GUIWidget::Placement::Absolute());
    // textbox->on("validate", [this,consolepanel,textbox](Pointer<GUIWidget> widget) {
    //   auto txt = textbox->getText();
    //   if (txt.size() > 0) {
    //     std::string ret = repl->execute_line(txt);
    //
    //     consolepanel->addText(ret);
    //     textbox->setText("");
    //   }
    // });
    //
    // consolepanel->on("show", [textbox](Pointer<GUIWidget> widget) {
    //   textbox->setVisible(true);
    //   textbox->setActive();
    // });
    //
    // consolepanel->on("hide", [textbox](Pointer<GUIWidget> widget) {
    //   textbox->setVisible(false);
    //   textbox->setInactive();
    // });
  }

  virtual void dispose() {
    Core::Events()->unregisterHandler(widg->_focusHandler.get());
    repl->end();
  }

  virtual void update(float delta) override {
    camera->update();
  }

  virtual void render() override {
    Framebuffer::clear(Color::Black);

    batch->begin();
    // gui->draw(batch);
    batch->end();
  }

private:
  OrthographicCamera::Ref camera;
  Sprite::Ref sprite;
  SimpleBatch::Ref batch;
  Scripter scripter;
  Pointer<REPL> repl;
  Pointer<GUISystem> gui;

  Pointer<NWidget> widg;
};
