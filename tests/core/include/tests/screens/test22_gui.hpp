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
  HX3D_ONLY_PTR(NWidget)

public:
  NWidget(Pointer<NWidget> parent = nullptr) {
    _parent = parent;
    _visible = true;

    _sprite->setTexture(Texture::Blank);
    _sprite->setTint(Color(127, 127, 127));
  }

  virtual void update(float delta) {
    _sprite->transform.position.x = _transform.position.x;
    _sprite->transform.position.y = _transform.position.y;
    _sprite->transform.size.x = _transform.size.x;
    _sprite->transform.size.y = _transform.size.y;
  }

  virtual void draw(const Pointer<Batch>& batch) {
    batch->draw(_sprite);
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

  Transform _transform;
  Sprite::Ref _sprite;
  Pointer<NWidget> _parent;

  bool _visible;

  std::map<std::string, std::function<void(Pointer<NWidget>)>> _actions;

  bool checkBounds(glm::vec2 position) {
    float lx = _transform.position.x - ((_transform.size.x / 2) * _transform.scale.x);
    float hx = _transform.position.x + ((_transform.size.x / 2) * _transform.scale.x);
    float ly = _transform.position.y - ((_transform.size.y / 2) * _transform.scale.y);
    float hy = _transform.position.y + ((_transform.size.y / 2) * _transform.scale.y);

    if (position.x >= lx && position.x <= hx && position.y >= ly && position.y <= hy) {
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

class NContainer: public NWidget {
  HX3D_ONLY_PTR(NContainer)

public:
  bool _propagateEvent;
  NWidget::Ptr _activeChild;
  std::vector<NWidget::Ptr> _children;

  NContainer(const NWidget::Ptr& parent = nullptr): NWidget(parent) {
    _propagateEvent = true;
    _activeChild = nullptr;
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
            break;
          }
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
};

class NLabel: public NWidget {
  HX3D_ONLY_PTR(NLabel)

public:
  gui::Text::Ptr _text;

  NLabel(const NWidget::Ptr& parent = nullptr): NWidget(parent) {
    _text = Make<gui::Text>();
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
};

class NPanel: public NContainer {
  HX3D_ONLY_PTR(NPanel)

};

// class GUIWidget: public std::enable_shared_from_this<GUIWidget>, public InputHandler {
// public:
//   class Placement {
//   public:
//     enum class Type {
//       Fill = 0,
//       Relative,
//       Absolute
//     };
//
//     Placement() {
//       _coords = {0, 0, 0, 0};
//     }
//
//     static Placement Fill() {
//       Placement p;
//       p._type = Type::Absolute;
//       return p;
//     }
//
//     static Placement Relative(float min_x, float min_y, float max_x, float max_y) {
//       Placement p;
//       p._type = Type::Relative;
//       p._coords = {min_x, min_y, max_x, max_y};
//       return p;
//     }
//
//     static Placement Absolute() {
//       Placement p;
//       p._type = Type::Absolute;
//       return p;
//     }
//
//     glm::vec4 _coords;
//     Type _type;
//   };
//
//   GUIWidget() {
//     _sprite = Make<Sprite>();
//
//     _visible = true;
//     _propagate = true;
//     _activeChild = nullptr;
//   }
//
//   Pointer<Sprite> _sprite;
//   std::vector<Pointer<GUIWidget>> _children;
//   Pointer<GUIWidget> _parent;
//   bool _visible;
//   bool _propagate;
//   Pointer<GUIWidget> _activeChild;
//   std::map<std::string, std::function<void(Pointer<GUIWidget>)>> _actions;
//
//   virtual void onShow() {}
//   virtual void onHide() {}
//   virtual void onFocus() {}
//   virtual void onExit() {}
//
//   void setVisible(bool value) {
//     if (value != _visible) {
//       if (value) this->onShow();
//       else this->onHide();
//     }
//
//     _visible = value;
//   }
//
//   void setActive() {
//     if (_parent) {
//       auto parent_active = _parent->_activeChild;
//       auto self = shared_from_this();
//
//       if (parent_active && parent_active != self) {
//         parent_active->onExit();
//       }
//
//       if (parent_active != self) {
//         self->onFocus();
//         _parent->_activeChild = self;
//       }
//     }
//   }
//
//   void setInactive() {
//     if (_parent) {
//       auto self = shared_from_this();
//       auto parent_active = _parent->_activeChild;
//       if (parent_active == self) {
//         _parent->_activeChild = nullptr;
//         self->onExit();
//       }
//     }
//   }
//
//   void registerAction(std::string action) {
//     if (_actions.find(action) != _actions.end()) {
//       Log.Error("GUIWidget: action %s already registered", action.c_str());
//     } else {
//       _actions[action] = nullptr;
//     }
//   }
//
//   void send(std::string action) {
//     if (_actions.find(action) == _actions.end()) {
//       Log.Error("GUIWidget: action %s do not exist", action.c_str());
//     } else {
//       auto act = _actions[action];
//       if (act != nullptr) {
//         act(shared_from_this());
//       }
//     }
//   }
//
//   void on(std::string action, std::function<void(Pointer<GUIWidget>)> func) {
//     if (_actions.find(action) == _actions.end()) {
//       Log.Error("GUIWidget: action %s do not exist", action.c_str());
//     } else {
//       _actions[action] = func;
//     }
//   }
//
//   virtual bool setFocus(glm::vec2 position) {
//     for (auto& child: _children) {
//       if (child->setFocus(position)) {
//         if (_activeChild && _activeChild != child) {
//           _activeChild->onExit();
//         }
//
//         if (_activeChild != child) {
//           _activeChild = child;
//           _activeChild->onFocus();
//         }
//
//         return true;
//       }
//     }
//
//     if (_activeChild) {
//       _activeChild->onExit();
//       _activeChild = nullptr;
//     }
//
//     return checkBounds(position);
//   }
//
//   template <class Type, class... Args>
//   Pointer<Type> createChild(Placement placement, Args&&... args) {
//     Pointer<Type> child = Make<Type>(args...);
//     child->_parent = shared_from_this();
//     _children.push_back(child);
//
//     if (placement._type == Placement::Type::Fill) {
//       child->_sprite->transform.position.x = this->_sprite->transform.position.x;
//       child->_sprite->transform.position.y = this->_sprite->transform.position.y;
//       child->_sprite->transform.size.x = this->_sprite->transform.size.x;
//       child->_sprite->transform.size.y = this->_sprite->transform.size.y;
//     } else if (placement._type == Placement::Type::Absolute) {
//       // Do nothing
//     } else if (placement._type == Placement::Type::Relative) {
//       // Calcul
//     }
//
//     return child;
//   }
//
//   template <class Type, class... Args>
//   Pointer<Type> createHiddenChild(Placement placement, Args&&... args) {
//     Pointer<Type> child = createChild<Type>(placement, args...);
//     child->_visible = false;
//
//     return child;
//   }
//
//   virtual void draw(const Pointer<Batch>& batch) {
//     if (_visible) {
//       batch->draw(_sprite);
//     }
//
//     for (auto& child: _children) {
//       child->draw(batch);
//     }
//   }
//
//   virtual void onMouseClicked(MouseButtonEvent::Button button, glm::vec2 mousePosition) {
//     if (_propagate) {
//       if (_activeChild) {
//         _activeChild->onMouseClicked(button, mousePosition);
//       }
//     }
//   }
//
//   virtual void onTextInput(std::string text) {
//     if (_propagate) {
//       if (_activeChild) {
//         _activeChild->onTextInput(text);
//       }
//     }
//   }
//
//   virtual void onKeyPressed(KeyEvent::Key key) override {
//     if (_propagate) {
//       if (_activeChild) {
//         _activeChild->onKeyPressed(key);
//       }
//     }
//   }
//
//   bool checkBounds(glm::vec2 position) {
//     float lx = _sprite->transform.position.x - ((_sprite->transform.size.x / 2) * _sprite->transform.scale.x);
//     float hx = _sprite->transform.position.x + ((_sprite->transform.size.x / 2) * _sprite->transform.scale.x);
//     float ly = _sprite->transform.position.y - ((_sprite->transform.size.y / 2) * _sprite->transform.scale.y);
//     float hy = _sprite->transform.position.y + ((_sprite->transform.size.y / 2) * _sprite->transform.scale.y);
//
//     if (position.x >= lx && position.x <= hx && position.y >= ly && position.y <= hy) {
//       return true;
//     } else {
//       return false;
//     }
//   }
// };
//
// class ConsolePanel: public GUIWidget {
// public:
//   ConsolePanel(float x, float y, float w, float h) {
//     _sprite->transform.position.x = x;
//     _sprite->transform.position.y = y;
//     _sprite->transform.position.z = 0.01;
//     _sprite->transform.size.x = w;
//     _sprite->transform.size.y = h;
//
//     _scrollback->transform.position.x = x;
//     _scrollback->transform.position.y = y - 25;
//     _scrollback->transform.position.z = 0.08;
//
//     _sprite->setTint(Color(127, 127, 127, 127));
//
//     registerAction("show");
//     registerAction("hide");
//   }
//
//   virtual void onFocus() override {
//     Log.Info("Console Panel active");
//   }
//
//   virtual void onExit() override {
//     Log.Info("Console Panel inactive");
//   }
//
//   virtual void onShow() override {
//     Core::Events()->endTextInput();
//
//     Log.Info("Tweening Down");
//     send("show");
//   }
//
//   virtual void onHide() override {
//     Log.Info("Tweening Up");
//     send("hide");
//   }
//
//   virtual void onKeyPressed(KeyEvent::Key key) override {
//     if (key == KeyEvent::Key::ConsoleKey) {
//       Log.Info("Console !");
//
//       setVisible(!_visible);
//     }
//
//     GUIWidget::onKeyPressed(key);
//   }
//
//   void addText(std::string text) {
//     _scrollback->setContent(text);
//   }
//
//   virtual void draw(const Pointer<Batch>& batch) override {
//     if (_visible) {
//       batch->draw(_sprite);
//       batch->draw(_scrollback);
//     }
//
//     for (auto& child: _children) {
//       child->draw(batch);
//     }
//   }
//
//   PrivateReference<gui::Text> _scrollback;
// };
//
// class GUITextbox: public GUIWidget {
// public:
//   GUITextbox() {
//     _sprite->transform.position.x = Core::App()->getWidth() / 2;
//     _sprite->transform.position.y = Core::App()->getHeight() - Core::App()->getHeight() / 8;
//     _sprite->transform.position.z = 0.02;
//     _sprite->transform.size.x = 256;
//     _sprite->transform.size.y = 48;
//     _sprite->transform.scale = glm::vec3(0.25);
//
//     _display = Make<gui::Text>();
//     _display->transform.position.x = _sprite->transform.position.x;
//     _display->transform.position.y = _sprite->transform.position.y;
//     _display->transform.position.z = _sprite->transform.position.z + 0.01;
//
//     registerAction("validate");
//   }
//
//   virtual void onFocus() override {
//     Log.Info("Focus !");
//     _sprite->setTint(Color(127, 0, 127));
//     Core::Events()->beginTextInput();
//   }
//
//   virtual void onExit() override {
//     Log.Info("Exit !");
//     _sprite->setTint(Color(127, 127, 127));
//     Core::Events()->endTextInput();
//   }
//
//   virtual void onKeyPressed(KeyEvent::Key key) override {
//     if (key == KeyEvent::Key::Return) {
//       send("validate");
//     }
//
//     else if (key == KeyEvent::Key::Backspace) {
//       if (_enteredText.size() > 0) {
//         _enteredText.pop_back();
//       }
//
//       _updateText();
//     }
//   }
//
//   virtual void onTextInput(std::string text) override {
//     _enteredText += text;
//     _updateText();
//   }
//
//   std::string getText() const {
//     return _enteredText;
//   }
//
//   void setText(std::string txt) {
//     _enteredText = txt;
//     _updateText();
//   }
//
//   void _updateText() {
//     _display->setContent(_enteredText);
//   }
//
//   virtual void draw(const Pointer<Batch>& batch) {
//     if (_visible) {
//       batch->draw(_sprite);
//       batch->draw(_display);
//     }
//   }
//
//   std::string _enteredText;
//   Pointer<gui::Text> _display;
// };

// class GUISystem {
// public:
//   GUISystem() {
//     _root = Make<GUIWidget>();
//     _root->setVisible(false);
//     Core::Events()->registerHandler(_root.get());
//   }
//
//   ~GUISystem() {
//     Core::Events()->unregisterHandler(_root.get());
//   }
//
//   void draw(const Pointer<Batch>& batch) {
//     glDisable(GL_DEPTH_TEST);
//     _root->draw(batch);
//     glEnable(GL_DEPTH_TEST);
//   }
//
//   const Pointer<GUIWidget>& getContent() {
//     return _root;
//   }
//
//   Pointer<GUIWidget> _root;
// };

class NSystem {
  HX3D_ONLY_PTR(NSystem)

public:
  NSystem(const NWidget::Ptr& content = nullptr) {
    setContent(content);
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
      glDisable(GL_DEPTH_TEST);
      _content->draw(batch);
      glEnable(GL_DEPTH_TEST);
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

    auto label = Make<NLabel>();
    label->_transform.position.x = Core::App()->getWidth() / 2;
    label->_transform.position.y = Core::App()->getHeight() / 2;
    label->_transform.size.x = 100;
    label->_transform.size.y = 100;
    label->_text->setContent("Hello");

    system = Make<NSystem>(label);
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
  SimpleBatch::Ref batch;
  NSystem::Ptr system;
};
