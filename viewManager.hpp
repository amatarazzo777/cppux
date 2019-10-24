//// <file>viewManager.hpp</file>
/// <author>Anthony Matarazzo</author>
/// <date>1/13/19</date>
/// <version>1.0</version<
///
/// <summary>Cross platfrom GUI DOM model with c++ 17 templates. </summary>
#ifndef VIEW_MANAGER_HPP_INCLUDED
#define VIEW_MANAGER_HPP_INCLUDED
#include <algorithm>
#include <any>
#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>
//#include <charconv>
#include <cstdarg>
#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

#define CONSOLE

/*************************************
OS SPECIFIC HEADERS
**************************************/
#if defined(CONSOLE)
#include <iostream>

#elif defined(__linux__)
#include <X11/keysymdef.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#elif defined(_WIN64)
// Windows Header Files:
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <windows.h>
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
#endif
namespace viewManager {
// forward declaration
class Element;
class StyleClass;
class event;
// interface specific communication types
typedef std::function<void(const event &)> eventHandler;
typedef std::function<bool(const Element &)> ElementQuery;
typedef std::vector<std::reference_wrapper<Element>> ElementList;
using tableData = std::vector<std::vector<std::string_view>>;
template <std::size_t I, typename T>
using dataTransformMap =
    std::unordered_map<const typename std::tuple_element<I, T>::type &,
                       std::function<Element &(T &)>>;
/**
These namespace global lists contain the objects as a system ownership.
**/
extern std::vector<std::unique_ptr<Element>> elements;
extern std::unordered_map<std::string_view, std::reference_wrapper<Element>>
    indexedElements;
extern std::vector<std::unique_ptr<StyleClass>> styles;
/*******************************************************
Events
*******************************************************/
enum class eventType : uint8_t {
  paint,
  focus,
  blur,
  resize,
  keydown,
  keyup,
  keypress,
  mouseenter,
  mousemove,
  mousedown,
  mouseup,
  click,
  dblclick,
  contextmenu,
  wheel,
  mouseleave
};
using event = class event {
public:
  event(const eventType &et) {
    evtType = et;
    bUnicodeEvent = false;
  }
  event(const eventType &et, const char &k) {
    evtType = et;
    key = k;
    bUnicodeEvent = false;
  }
  event(const eventType &et, const std::wstring &uniK) {
    evtType = et;
    unicodeKeys = uniK;
    bUnicodeEvent = true;
  }
  event(const eventType &et, const short &mx, const short &my,
        const short &mb_dis) {
    evtType = et;
    mousex = mx;
    mousey = my;
    if (et == eventType::wheel)
      wheelDistance = mb_dis;
    else
      mouseButton = mb_dis;
    bUnicodeEvent = false;
  }
  event(const eventType &et, const short &w, const short &h) {
    evtType = et;
    width = w;
    height = h;
    bUnicodeEvent = false;
  }
  event(const eventType &et, const short &distance) {
    evtType = et;
    wheelDistance = distance;
    bUnicodeEvent = false;
  }
  ~event(){};

public:
  eventType evtType;
  bool bUnicodeEvent;
  char key;
  std::wstring unicodeKeys;
  short mousex;
  short mousey;
  char mouseButton;
  short width;
  short height;
  short wheelDistance;
};

/* communication enum options.
these are provided as public, and used as a type
on the input of the class constructor.*/
using numericFormat = enum option { px, pt, em, percent, autoCalculate };
using colorFormat = enum colorFormat { rgb, hsl, name };
/*
Classes used by complex attributes.
*/
class doubleNF {
public:
  double value;
  numericFormat option;
  doubleNF(const doubleNF &_val) : value(_val.value), option(_val.option) {}
  doubleNF(const double &_val, const numericFormat &_nf)
      : value(_val), option(_nf) {}
};
class colorNF {
public:
  std::array<double, 4> value;
  colorFormat option;
  colorNF(const colorFormat &_opt, const std::array<double, 4> &_val)
      : option(_opt), value(_val) {}
  colorNF(const std::string_view &_colorName) { option = colorFormat::name; }
  void lighter(const double &step = 0.1) {}
  void darker(const double &step = 0.1) {}
  void monochromatic(const double &step = 0.1) {}
  void triad(void) { /*hsl rotate 120*/
  }
  void neutralCooler(void) { /* hsl rotate -30 */
  }
  void neutralWarmer(void) { /* hsl rotate 30 */
  }
  void complementary(void) { /* hsl rotate 180*/
  }
  void splitComplements(void) { /*hsl rotate 150 */
  }
};
/*
INTERNEL MACROS to reduce code needed for these attribute storage
implementations. These macros develop the storage class or
inheiritance to implement a complex attribute. Within the system, the
"using" provides an alias to name a specific type. Therefore, all classes
declared using these macros will establish their storage space securely at
its position within the attribute storage container. When a getAttribute
with a specific attribute is requested, the reference to this class is
returned. Therefore, values and such can be read or edited using only the
memory. getAttribute is templated so that the most modified values attain
their own specific function. Therefore, newer or specific interfaces can be
developed.
*/
#define _NUMERIC_ATTRIBUTE(NAME)                                               \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    double value;                                                              \
    NAME(const double &_val) : value(_val) {}                                  \
    NAME(const NAME &_val) : value(_val.value) {}                              \
  }
#define _STRING_ATTRIBUTE(NAME)                                                \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    std::string_view value;                                                    \
    NAME(const std::string_view &_val) : value(_val) {}                        \
    NAME(const NAME &_val) : value(_val.value) {}                              \
  }
#define _NUMERIC_WITH_FORMAT_ATTRIBUTE(NAME)                                   \
  using NAME = class NAME : public doubleNF {                                  \
  public:                                                                      \
    NAME(const double &_val, const numericFormat &_nf)                         \
        : doubleNF(_val, _nf) {}                                               \
    NAME(const doubleNF &_val) : doubleNF(_val) {}                             \
    NAME(const NAME &_val) : doubleNF(_val) {}                                 \
  }
#define _ENUMERATED_ATTRIBUTE(NAME, ...)                                       \
  using NAME = enum class NAME : uint8_t { __VA_ARGS__ }
#define _NUMERIC_WITH_ENUMERATED_ATTRIBUTE(NAME, ...)                          \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    enum optionEnum : uint8_t { __VA_ARGS__ };                                 \
    double value;                                                              \
    optionEnum option;                                                         \
    NAME(const double &_val, const optionEnum &_opt)                           \
        : value(_val), option(_opt) {}                                         \
    NAME(const NAME &_val) : value(_val.value), option(_val.option) {}         \
  }
#define _COLOR_ATTRIBUTE(NAME)                                                 \
  using NAME = class NAME : public colorNF {                                   \
  public:                                                                      \
    NAME(const double &_v1, const double &_v2, const double &_v3)              \
        : colorNF(colorFormat::rgb, {_v1, _v2, _v3, 0}) {}                     \
    NAME(const std::string_view &_colorName) : colorNF(_colorName) {}          \
    NAME(const colorFormat &_opt, const std::array<double, 4> &_val)           \
        : colorNF(_opt, _val) {}                                               \
    NAME(const colorFormat _opt, const double &_v1, const double &_v2,         \
         const double &_v3)                                                    \
        : colorNF(_opt, {_v1, _v2, _v3, 0}) {}                                 \
    NAME(const colorFormat &_opt, const double &_v1, const double &_v2,        \
         const double &_v3, const double &_v4)                                 \
        : colorNF(_opt, {_v1, _v2, _v3, _v4}) {}                               \
  }
#define _VECTOR_ATTRIBUTE(NAME)                                                \
  using NAME = class NAME {                                                    \
  public:                                                                      \
    std::vector<std::string_view> value;                                       \
    NAME(std::vector<std::string_view> _val) : value(std::move(_val)) {}       \
  }
// namespace viewManager
/*
Attributes are classes with registered name aliases. The underlying
architecture reduces the use of templates but promotes the passing of data.
The attributes are contained within the internel structure, within the
Element base class. The attribute storage is indexed and stored within an
unordered map. References are returned so that callee communication is
minimal.
*/
_STRING_ATTRIBUTE(indexBy);
_ENUMERATED_ATTRIBUTE(display, in_line, block, none);
_ENUMERATED_ATTRIBUTE(position, absolute, relative);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectTop);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectLeft);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectHeight);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(objectWidth);
_COLOR_ATTRIBUTE(background);
_NUMERIC_ATTRIBUTE(opacity);
_STRING_ATTRIBUTE(textFace);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(textSize);
_NUMERIC_ATTRIBUTE(textWeight);
_COLOR_ATTRIBUTE(textColor);
_ENUMERATED_ATTRIBUTE(textAlignment, left, center, right, justified);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(textIndent);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(tabSize);
_NUMERIC_WITH_ENUMERATED_ATTRIBUTE(lineHeight, normal, numeric);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginTop);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginLeft);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginBottom);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(marginRight);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingTop);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingLeft);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingBottom);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(paddingRight);
_NUMERIC_WITH_ENUMERATED_ATTRIBUTE(borderStyle, none, dotted, dashed, solid,
                                   doubled, groove, ridge, inset, outset);
_NUMERIC_WITH_FORMAT_ATTRIBUTE(borderWidth);
_COLOR_ATTRIBUTE(borderColor);
_NUMERIC_ATTRIBUTE(borderRadius);
_NUMERIC_ATTRIBUTE(focusIndex);
_NUMERIC_ATTRIBUTE(zIndex);
_ENUMERATED_ATTRIBUTE(listStyleType, none, disc, circle, square, decimal, alpha,
                      greek, latin, roman);
/*******************************************************
StyleClass
*******************************************************/
class StyleClass {
public:
  std::unordered_map<std::type_index, std::any> attributes;
  StyleClass *self;

public:
  template <typename... Args> StyleClass(const Args &... args) : self(this) {
    //((void)setValue(std::forward<Args>(args)), ...);
  }
  template <typename T> void setValue(const T &attr) {
    std::type_index ti = std::type_index(typeid(attr));
    attributes[ti] = attr;
  }
};
/*******************************************************
Visualizer
********************************************************/
namespace Visualizer {

typedef struct {
  double t;
  double l;
  double w;
  double h;
} rectangle;
extern std::vector<rectangle> items;
std::size_t allocate(Element &e);
void deallocate(const std::size_t &token);
void openWindow(Element &e);
void closeWindow(Element &e);
/******************************
Platform object
*******************************/
class platform {
public:
  platform(eventHandler evtDispatcher, unsigned short width,
           unsigned short height);
  ~platform();
  void messageLoop(void);
  void flip(void);
#if defined(_WIN64)
  LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
                           LPARAM lParam);
#endif
public:
#if defined(CONSOLE)

#elif defined(__linux__)

  xcb_connection_t *m_connection;
  xcb_screen_t *m_screen;
  xcb_drawable_t m_window;
  xcb_pixmap_t m_offScreen;
  // xcb -- keyboard
  xcb_key_symbols_t *m_syms;

#elif defined(_WIN64)
  HWND m_hwnd;
  ID2D1Factory *m_pDirect2dFactory;
  ID2D1HwndRenderTarget *m_pRenderTarget;
  ID2D1BitmapRenderTarget *m_pOffscreen;
  ID2D1Bitmap *m_offScreenBitmap;
#endif
private:
  eventHandler dispatchEvent;
}; // class platform
}; // namespace Visualizer
template <typename TYPE>
auto&  _createElement(const std::vector<std::any> &attr);
/*******************************************************
Element
********************************************************/
class Element {
public:
  std::string_view softName;

public:
  Element(std::string_view _softName, const std::vector<std::any> &attribs = {})
      : softName(_softName), m_self(this), m_parent(nullptr),
        m_firstChild(nullptr), m_lastChild(nullptr), m_nextChild(nullptr),
        m_previousChild(nullptr), m_nextSibling(nullptr),
        m_previousSibling(nullptr), m_childCount(0) {
    setAttribute(attribs);
  }
  ~Element() { Visualizer::deallocate(surface); }
  Element(const Element &other) {
    std::cout << "Element(const Element& other)" << std::endl;

    m_self = other.m_self;
    m_parent = other.m_parent;
    m_firstChild = other.m_firstChild;
    m_lastChild = other.m_lastChild;
    m_nextChild = other.m_nextChild;
    m_previousChild = other.m_previousChild;
    m_nextSibling = other.m_nextSibling;
    m_previousSibling = other.m_previousSibling;
    m_childCount = other.m_childCount;
    attributes = other.attributes;
    styles = other.styles;
  }
  Element(Element &&other) noexcept {
    std::cout << "Element(Element&& other) noexcept" << std::endl;

    m_self = other.m_self;
    m_parent = other.m_parent;
    m_firstChild = other.m_firstChild;
    m_lastChild = other.m_lastChild;
    m_nextChild = other.m_nextChild;
    m_previousChild = other.m_previousChild;
    m_nextSibling = other.m_nextSibling;
    m_previousSibling = other.m_previousSibling;
    m_childCount = other.m_childCount;
    attributes = std::move(other.attributes);
    styles = std::move(other.styles);
  }
  Element &operator=(const Element &other) {
    std::cout << "Element& operator=(const Element& other)" << std::endl;

    // Self-assignment detection
    if (&other == this)
      return *this;
    m_self = other.m_self;
    m_parent = other.m_parent;
    m_firstChild = other.m_firstChild;
    m_lastChild = other.m_lastChild;
    m_nextChild = other.m_nextChild;
    m_previousChild = other.m_previousChild;
    m_nextSibling = other.m_nextSibling;
    m_previousSibling = other.m_previousSibling;
    m_childCount = other.m_childCount;
    attributes = other.attributes;
    styles = other.styles;
    return *this;
  }
  Element &operator=(Element &&other) noexcept {
    std::cout << "Element& operator=(Element&& other) noexcept" << std::endl;

    if (&other == this)
      return *this;
    m_self = other.m_self;
    m_parent = other.m_parent;
    m_firstChild = other.m_firstChild;
    m_lastChild = other.m_lastChild;
    m_nextChild = other.m_nextChild;
    m_previousChild = other.m_previousChild;
    m_nextSibling = other.m_nextSibling;
    m_previousSibling = other.m_previousSibling;
    m_childCount = other.m_childCount;
    attributes = std::move(other.attributes);
    styles = std::move(other.styles);
    return *this;
  }

  /*
Data interface.
The data<> templated function provides a standard interface for data
projection and building for ease of interface communication.
*/
private:
  typedef struct _usageAdaptorState {
    std::size_t _size;
    std::size_t _visibleBegin;
    std::size_t _visibleEnd;
    std::size_t _lastWorkLoad;
  } usageAdaptorState;
  /*
usageAdaptor<> - INTERNAL a templated class used only internally,
holds the data of a templated type within a vector.
Noted that vectors have sequential memory for all of their elements.
This property is used by the hinting system to deduce set inclusion.
They can be established just by the type leaveing
data and fnTransform empty.
When just the data is passed, and a default transform function
does not exist, the data is saved leaving the fnTransform as a default
formatter according to the type.
*/
private:
  template <typename T> class usageAdaptor {
  public:
    usageAdaptor(void) {}
    usageAdaptor(std::vector<T> &_d) : _data(_d) { saveState(); }
    usageAdaptor(std::function<Element &(T &)> &_fn) : fnTransform(_fn) {
      saveState();
    }
    usageAdaptor(std::vector<T> _d, std::function<Element &(T &)> _fn)
        : _data(_d), fnTransform(_fn) {
      saveState();
    }
    auto data(void) -> std::vector<T> & {
      saveState();
      return _data;
    }
    auto data(std::vector<T> &_input) -> std::vector<T> & {
      _data = std::move(_input);
      saveState();
      return _data;
    }
    std::function<Element &(T &)> &transform(void) { return fnTransform; }
    // analyze hint data and deduce states
    void hint(void *hint1, std::size_t hint2, std::size_t hint3) {}

  private:
    std::vector<T> _data;
    std::function<Element &(T &)> fnTransform;
    usageAdaptorState state;

  private:
    void saveState(void) { state._size = _data.size(); }
  };
  /* three templated functions provide the data interface,
dataTransform<>(), data<>(), and dataHint<>(). All of these
templated functions work with the internal data storage mechnism.
*/
public:
  template <typename R, typename T>
  void dataTransform(const std::string_view &txtFn) {}
  template <typename R, typename T>
  void dataTransform(const std::string_view &txtFn,
                     const std::function<bool(T &)> &_fn) {}
  template <typename R, typename T>
  void dataTransform(const std::function<R &(T &)> &_fn) {
    std::function<R &(T &)> fn = _fn;
    std::type_index tIndex = std::type_index(typeid(std::vector<T>));
    auto it = m_usageAdaptorMap.find(tIndex);
    // if the requested data adaptor does not exist,
    // create its position within the adaptor member vector
    // return this to the caller.
    if (it == m_usageAdaptorMap.end()) {
      // create a default data display for the type here.
      std::function<Element &(T &)> fnDefault;
      m_usageAdaptorMap[tIndex] = usageAdaptor<T>(fnDefault);
    } else {
      const usageAdaptor<T> &adaptor =
          std::any_cast<usageAdaptor<T> &>(m_usageAdaptorMap[tIndex]);
    }
  }
  /*
This data transform uses the named value of the numerical column.
While being a constant, this reliance is that of an itm within a tuple
column. This tuple column is used as a index into the natural long list
of vector data. AS well, the parameter essential is an unordered map
reference. Simply that the match index as the key and a std::function
as the found item. THe item is used to process a requested data element
based upon this match. So, in effect this allows the unordered may to change,
over time, and selectively modify traites or visual composition in
a strict binary fashion rather than css conteplated sheets. While both are
often necessary, this type of solid work code really becomes the marking
of complexity and specific layouts that may be dynamically loaded.
And also provide effective space for description. I find that simple
and complex may go together, yet for usage one must create the sceneros
that elvolve in delicate use of competent technology.
*/
  template <std::size_t I, typename T>
  void dataTransform(
      const std::unordered_map<const typename std::tuple_element<I, T>::type &,
                               std::function<Element &(T &)>> &_transformList) {
  }
  /************** data access ***************/
  template <typename T = std::string_view> auto &data(void) {
    std::type_index tIndex = std::type_index(typeid(std::vector<T>));
    // if the requested data adaptor does not exist,
    // create its position within the adaptor member vector
    // return this to the caller.
    auto it = m_usageAdaptorMap.find(tIndex);
    if (it == m_usageAdaptorMap.end()) {
      // create a default data display for the type here.
      std::function<Element &(T &)> fnDefault;
      m_usageAdaptorMap[tIndex] = usageAdaptor<T>(fnDefault);
      return std::any_cast<usageAdaptor<T> &>(m_usageAdaptorMap[tIndex]).data();
    } else {
      return std::any_cast<usageAdaptor<T> &>(it->second).data();
    }
  }
  template <typename T>
  void dataHint(const T &hint1, std::size_t hint2 = 0, std::size_t hint3 = 0) {}
  template <typename T>
  void dataHint(int hint1 = 0, std::size_t hint2 = 0, std::size_t hint3 = 0) {
    auto it = m_usageAdaptorMap.find(std::type_index(typeid(std::vector<T>)));
    // save input signal ? valid ?
    // check saved state from getAdaptor.
    if (it != m_usageAdaptorMap.end()) {
      const usageAdaptor<T> &adaptor =
          std::any_cast<const usageAdaptor<T> &>(it->second);
      // adaptor.hint(hint1, hint2, hint3);
    }
  }

  // move assignment
  /// <summary> overload of the stream insertion operator.
  /// Simply puts the data into the stream. It should be
  /// noted that flush should be called.
  /// </summary>
  template <typename T> Element &operator<<(const T &data) {
    std::ostringstream s;
    s << data;

    // append the information to the end of the data vector.
    auto &vdata = this->data<std::string>();
    vdata.push_back(s.str());

    return *this;
  }

  /* query at this level must allow traversal of types, and direction.
siblings, parent, children...
*/
  auto query(const std::string_view &queryString) -> ElementList{};
  auto query(const ElementQuery &queryFunction) -> ElementList{};
  // private data menbers to hold the information of the class
private:
  Element *m_self;
  Element *m_parent;
  Element *m_firstChild;
  Element *m_lastChild;
  Element *m_nextChild;
  Element *m_previousChild;
  Element *m_nextSibling;
  Element *m_previousSibling;
  std::size_t m_childCount;
  // interface access ponits for the interface
public:
#define _REF_INTERFACE(NAME, xNAME)                                            \
  std::optional<std::reference_wrapper<Element>> NAME(void) {                  \
    return (xNAME ? std::optional<std::reference_wrapper<Element>>{*xNAME}     \
                  : std::nullopt);                                             \
  }
  _REF_INTERFACE(parent, m_parent);
  _REF_INTERFACE(firstChild, m_firstChild);
  _REF_INTERFACE(lastChild, m_lastChild);
  _REF_INTERFACE(nextChild, m_nextChild);
  _REF_INTERFACE(previousChild, m_previousChild);
  _REF_INTERFACE(nextSibling, m_nextSibling);
  _REF_INTERFACE(previousSibling, m_previousSibling);
  inline std::size_t &childCount(void) { return m_childCount; }
  std::vector<std::reference_wrapper<StyleClass>> styles;

private:
  std::unordered_map<std::type_index, std::any> attributes;
  std::unordered_map<std::type_index, std::any> m_usageAdaptorMap;
  std::size_t surface;

public:
  auto appendChild(const std::string_view &sMarkup) -> Element & {
    return (ingestMarkup(*this, sMarkup));
  }
  auto appendChild(Element &newChild) -> Element & {
    newChild.m_parent = this;
    newChild.m_previousSibling = m_lastChild;

    if (!m_firstChild)
      m_firstChild = newChild.m_self;

    if (m_lastChild)
      m_lastChild->m_nextSibling = newChild.m_self;

    m_lastChild = newChild.m_self;
    m_childCount++;
    return (newChild);
  }

  auto appendChild(const ElementList &elementCollection)
      -> std::add_lvalue_reference<Element>::type {
    for (auto e : elementCollection) {
      appendChild(e.get());
    }
    return (*this);
  }
  template <typename TYPE, typename... ATTRS>
  auto appendChild(const ATTRS &... attrs) -> Element & {
    TYPE &e = _createElement<TYPE>({attrs...});
    appendChild(e);
    return (e);
  }

public:
  auto append(const std::string_view &sMarkup) -> Element & {
    Element *base = this->m_parent;
    if (base == nullptr)
      base = this;
    return (ingestMarkup(*base, sMarkup));
  }
  auto append(Element &sibling) -> Element & {
    m_nextSibling = sibling.m_self;
    sibling.m_parent = this->m_parent;
    sibling.m_previousSibling = this;

    if (!this->m_parent->m_firstChild)
      this->m_parent->m_firstChild = sibling.m_self;

    this->m_parent->m_lastChild = sibling.m_self;

    this->m_parent->m_childCount++;
    return (sibling);
  }
  template <typename TYPE, typename... ATTRS>
  auto append(const ATTRS &... attrs) -> Element & {
    TYPE &e = _createElement<TYPE>({attrs...});
    append(e);
    return (e);
  }
  auto append(ElementList &elementCollection) -> Element & {
    for (auto &e : elementCollection)
      append(e);
    return (*this);
  }

public:
  /* setAttribute
The set attribute accepts an std::any, typesafe and convertable.
There are several predetermined types that are recoginized through
the type stored with the std::any parameter.
The filter allows compact input for vector and simple c++ based
types direction from the creation functions (createElement<>, append<>, and
appendChild<> which there are
typically few entries. */
  Element &setAttribute(const std::any &setting) {

    // filter list
    enum _enumTypeFilter {
      dt_char,
      dt_double,
      dt_float,
      dt_int,
      dt_std_string_view,
      dt_const_char,
      dt_vector_char,
      dt_vector_double,
      dt_vector_float,
      dt_vector_int,
      dt_vector_string_view,
      dt_vector_vector_string_view,
      dt_vector_pair_int_string_view,
      dt_indexBy,

      dt_nonFiltered
    };
    // filter map
    static std::unordered_map<size_t, _enumTypeFilter> _umapTypeFilter = {
        {std::type_index(typeid(char)).hash_code(), dt_char},
        {std::type_index(typeid(double)).hash_code(), dt_double},
        {std::type_index(typeid(float)).hash_code(), dt_float},
        {std::type_index(typeid(int)).hash_code(), dt_int},
        {std::type_index(typeid(std::string_view)).hash_code(),
         dt_std_string_view},
        {std::type_index(typeid(const char *)).hash_code(), dt_const_char},
        {std::type_index(typeid(std::vector<char>)).hash_code(),
         dt_vector_char},
        {std::type_index(typeid(std::vector<double>)).hash_code(),
         dt_vector_double},
        {std::type_index(typeid(std::vector<float>)).hash_code(),
         dt_vector_float},
        {std::type_index(typeid(std::vector<int>)).hash_code(), dt_vector_int},
        {std::type_index(typeid(std::vector<std::string_view>)).hash_code(),
         dt_vector_string_view},
        {std::type_index(typeid(std::vector<std::vector<std::string_view>>))
             .hash_code(),
         dt_vector_vector_string_view},
        {std::type_index(
             typeid(std::vector<std::vector<std::pair<int, std::string_view>>>))
             .hash_code(),
         dt_vector_pair_int_string_view},
        {std::type_index(typeid(indexBy)).hash_code(), dt_indexBy}};
    // set search result defaults for not found in filter
    _enumTypeFilter dtFilter = dt_nonFiltered;
    bool bSaveInMap = false;
    std::unordered_map<size_t, _enumTypeFilter>::iterator it =
        _umapTypeFilter.find(setting.type().hash_code());
    if (it != _umapTypeFilter.end())
      dtFilter = it->second;

    /* filter these types specifically and do not store them in the map.
these items change the dataAdaptor. This creates a more usable
syntax for population of large and small data within the
simple initializer list format given within the attribute list.*/
    switch (dtFilter) {
    case dt_char: {
      auto v = std::any_cast<char>(setting);
      data<char>() = std::vector<char>{v};
    } break;
    case dt_double: {
      auto v = std::any_cast<double>(setting);
      data<double>() = std::vector<double>{v};
    } break;
    case dt_float: {
      auto v = std::any_cast<float>(setting);
      data<float>() = std::vector<float>{v};
    } break;
    case dt_int: {
      auto v = std::any_cast<int>(setting);
      data<int>() = std::vector<int>{v};
    } break;
    case dt_const_char: {
      auto v = std::any_cast<const char *>(setting);
      data<std::string_view>() = std::vector<std::string_view>{v};
    } break;
    case dt_std_string_view: {
      auto v = std::any_cast<std::string_view>(setting);
      data<std::string_view>() = std::vector<std::string_view>{v};
    } break;
    case dt_vector_char: {
      auto v = std::any_cast<std::vector<char>>(setting);
      data<char>() = v;
    } break;
    case dt_vector_double: {
      auto v = std::any_cast<std::vector<double>>(setting);
      data<double>() = v;
    } break;
    case dt_vector_float: {
      auto v = std::any_cast<std::vector<float>>(setting);
      data<float>() = v;
    } break;
    case dt_vector_int: {
      auto v = std::any_cast<std::vector<int>>(setting);
      data<int>() = v;
    } break;
    case dt_vector_string_view: {
      auto v = std::any_cast<std::vector<std::string_view>>(setting);
      data<std::string_view>() = v;
    } break;
    case dt_vector_vector_string_view: {
      auto v =
          std::any_cast<std::vector<std::vector<std::string_view>>>(setting);
      data<std::vector<std::string_view>>() = v;
    } break;
    case dt_vector_pair_int_string_view: {
      auto v =
          std::any_cast<std::vector<std::pair<int, std::string_view>>>(setting);
      data<std::pair<int, std::string_view>>() = v;
    } break;
    // attributes stored in map but filtered for processing.
    case dt_indexBy: {
      updateIndexBy(std::any_cast<indexBy>(setting));
      bSaveInMap = true;
    } break;

    // other items are not filtered, so just pass through to storage.
    case dt_nonFiltered: {
      bSaveInMap = true;
    } break;
    }

    if (bSaveInMap)
      attributes[std::type_index(setting.type())] = setting;
    return *this;
  }
  template <typename... TYPES> Element &setAttribute(const TYPES... settings) {
    setAttribute(std::vector<std::any>{settings...});
    return *this;
  }
  Element &setAttribute(const std::vector<std::any> &attribs) {
    for (auto n : attribs)
      setAttribute(n);
    return *this;
  }

public:
  template <typename ATTR_TYPE> ATTR_TYPE &getAttribute(void) {
    ATTR_TYPE *ret = nullptr;
    std::unordered_map<std::type_index, std::any>::iterator it =
        attributes.find(std::type_index(typeid(ATTR_TYPE)));
    if (it != attributes.end()) {
      ret = &std::any_cast<ATTR_TYPE &>(it->second);
    } else {
      std::string info = typeid(ret).name();
      info += " attribute not found";

      throw std::invalid_argument(info);
    }
    return *ret;
  }

public:
  Element &clear(void) { return *this; }

public:
  std::vector<eventHandler> onfocus;
  std::vector<eventHandler> onblur;
  std::vector<eventHandler> onresize;
  std::vector<eventHandler> onkeydown;
  std::vector<eventHandler> onkeyup;
  std::vector<eventHandler> onkeypress;
  std::vector<eventHandler> onmouseenter;
  std::vector<eventHandler> onmouseleave;
  std::vector<eventHandler> onmousemove;
  std::vector<eventHandler> onmousedown;
  std::vector<eventHandler> onmouseup;
  std::vector<eventHandler> onclick;
  std::vector<eventHandler> ondblclick;
  std::vector<eventHandler> oncontextmenu;
  std::vector<eventHandler> onwheel;

private:
  std::vector<eventHandler> &getEventVector(eventType evtType);

public:
  auto move(const double t, const double l) -> Element &;
  auto resize(const double w, const double h) -> Element &;
  auto addListener(eventType evtType, eventHandler evtHandler) -> Element &;
  auto removeListener(eventType evtType, eventHandler evtHandler) -> Element &;
  void render(void);
  auto insertBefore(Element &newChild, Element &existingElement) -> Element &;
  auto insertAfter(Element &newChild, Element &existingElement) -> Element &;
  void remove(void);
  auto removeChild(Element &childElement) -> Element &;
  auto removeChildren(Element &e) -> Element &;
  auto replaceChild(Element &newChild, Element &oldChild) -> Element &;
#if defined(__clang__)
  void printf(const char *fmt, ...)
      __attribute__((__format__(__printf__, 2, 0)));
#else
  void printf(const char *fmt, ...);
#endif
  auto ingestMarkup(Element &node, const std::string_view &markup) -> Element &;

private:
  void updateIndexBy(const indexBy &setting);
}; // class Element
//
auto operator""_pt(unsigned long long int value) -> doubleNF;
auto operator""_pt(long double value) -> doubleNF;
auto operator""_em(unsigned long long int value) -> doubleNF;
auto operator""_em(long double value) -> doubleNF;
auto operator""_px(unsigned long long int value) -> doubleNF;
auto operator""_px(long double value) -> doubleNF;
auto operator""_percent(unsigned long long int value) -> doubleNF;
auto operator""_percent(long double value) -> doubleNF;
auto operator""_pct(unsigned long long int value) -> doubleNF;
auto operator""_pct(long double value) -> doubleNF;
auto operator""_normal(unsigned long long int value) -> lineHeight;
auto operator""_normal(long double value) -> lineHeight;
auto operator""_numeric(unsigned long long int value) -> lineHeight;
auto operator""_numeric(long double value) -> lineHeight;

using BR = class BR : public Element {
public:
  BR(const std::vector<std::any> &attribs) : Element("br") {
    setAttribute(attribs);
  }
};
using H1 = class H1 : public Element {
public:
  H1(const std::vector<std::any> &attribs)
      : Element("h1", {display::block, marginTop{.67_em}, marginLeft{.67_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{2_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
using H2 = class H2 : public Element {
public:
  H2(const std::vector<std::any> &attribs)
      : Element("h2", {display::block, marginTop{.83_em}, marginLeft{.83_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{1.5_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
using H3 = class H3 : public Element {
public:
  H3(const std::vector<std::any> &attribs)
      : Element("h3", {display::block, marginTop{1_em}, marginLeft{1_em},
                       marginBottom{0_em}, marginRight{0_em}, textSize{1.17_em},
                       textWeight{800}}) {
    setAttribute(attribs);
  }
};
using PARAGRAPH = class PARAGRAPH : public Element {
public:
  PARAGRAPH(const std::vector<std::any> &attribs)
      : Element("paragraph",
                {listStyleType::disc, marginTop{1_em}, marginLeft{1_em},
                 marginBottom{0_em}, marginRight{0_em}}) {
    setAttribute(attribs);
  }
};
using DIV = class DIV : public Element {
public:
  DIV(const std::vector<std::any> &attribs) : Element("div", {display::block}) {
    setAttribute(attribs);
  }
};
using SPAN = class SPAN : public Element {
public:
  SPAN(const std::vector<std::any> &attribs) : Element("span") {
    setAttribute(attribs);
  }
};
using UL = class UL : public Element {
public:
  UL(const std::vector<std::any> &attribs)
      : Element("ul", {listStyleType::disc, display::block, marginTop{1_em},
                       marginLeft{1_em}, marginBottom{0_em}, marginRight{0_em},
                       paddingLeft{40_px}}) {
    setAttribute(attribs);
  }
};
using OL = class OL : public Element {
public:
  OL(const std::vector<std::any> &attribs)
      : Element("ol", {listStyleType::decimal, display::block, marginTop{1_em},
                       marginLeft{1_em}, marginBottom{0_em}, marginRight{0_em},
                       paddingLeft{40_px}}) {
    setAttribute(attribs);
  }
};
using LI = class LI : public Element {
public:
  LI(const std::vector<std::any> &attribs) : Element("li") {
    setAttribute(attribs);
  }
};
// self understood attribute communication
_VECTOR_ATTRIBUTE(tableColumns);
using TABLE = class TABLE : public Element {
public:
  TABLE(const std::vector<std::any> &attribs) : Element("table") {
    setAttribute(attribs);
  }
};
using MENU = class MENU : public Element {
public:
  MENU(const std::vector<std::any> &attribs) : Element("menu") {
    setAttribute(attribs);
  }
};
using UX = class UX : public Element {
public:
  UX(const std::vector<std::any> &attribs) : Element("ux") {
    setAttribute(attribs);
  }
};
using IMAGE = class IMAGE : public Element {
public:
  IMAGE(const std::vector<std::any> &attribs) : Element("image") {
    setAttribute(attribs);
  }
};
class textNode : public Element {
public:
  std::string_view &value;
  textNode(std::string_view &s) : value(s), Element("textNode") {}
};
/// USE_LOWER_CASE_ENTITY_NAMES
/// <summary>Options for compiling that provide recognition of
/// lower case entity names.</summary>
#define USE_LOWER_CASE_ENTITY_NAMES
// map lower case terms as well for flexibility
#ifdef USE_LOWER_CASE_ENTITY_NAMES
using element = Element;
using paragraph = PARAGRAPH;
using br = BR;
using h1 = H1;
using h2 = H2;
using h3 = H3;
using dblock = DIV;
using span = SPAN;
using ul = UL;
using ol = OL;
using li = LI;
using menu = MENU;
using ux = UX;
using image = IMAGE;
using textnode = textNode;
#endif
/*********************************************************************************
Templated factory implementation for reference based callee and
viewManager ownership of the object. The vector deconstructor will cause
proper deallocation.
*********************************************************************************/

void consoleRender(Element &e, int iLevel);

template <typename TYPE>
auto& _createElement(const std::vector<std::any> &attrs) {
  std::unique_ptr<TYPE> e = std::make_unique<TYPE>(attrs);
  elements.push_back(std::move(e));
  TYPE &ret=static_cast<TYPE &>(*elements.back().get());
  return ret;
}

template <class TYPE, typename... ATTRS>
auto& createElement(const ATTRS &... attribs) {
  return _createElement<TYPE>({attribs...});;
}

template <typename... Types> auto createStyle(Types... args) -> StyleClass & {
  std::unique_ptr<StyleClass> newStyle = std::make_unique<StyleClass>(args...);
  styles.push_back(std::move(newStyle));
  return *styles.back().get();
}
auto query(const std::string_view &queryString) -> ElementList;
auto query(const ElementQuery &queryFunction) -> ElementList;

template <class T = Element &>
auto getElement(const std::string_view &key) -> T & {
  auto it = indexedElements.find(key);
  T ret = it->second.get();
  return ret;
}

bool hasElement(const std::string_view &key);
#define CREATE_OBJECT_ALIAS(OBJECT_TEXT, OBJECT_TYPE)                          \
  {                                                                            \
#OBJECT_TEXT,                                                              \
        [](const std::vector <std::any> &attrs)                                \
             -> Element & { return _createElement<OBJECT_TYPE>(attrs); }       \
  }

#define CREATE_OBJECT(OBJECT_TYPE) CREATE_OBJECT_ALIAS(OBJECT_TYPE, OBJECT_TYPE)
static std::unordered_map<
    std::string_view,
    std::function<Element &(const std::vector<std::any> &attr)>>
    objectFactoryMap = {
        CREATE_OBJECT(BR),   CREATE_OBJECT(H1),        CREATE_OBJECT(H2),
        CREATE_OBJECT(H3),   CREATE_OBJECT(PARAGRAPH), CREATE_OBJECT(DIV),
        CREATE_OBJECT(SPAN), CREATE_OBJECT(UL),        CREATE_OBJECT(OL),
        CREATE_OBJECT(LI),   CREATE_OBJECT(MENU),      CREATE_OBJECT(UX),
        CREATE_OBJECT(IMAGE)};
/****************************************************************
Viewer
*****************************************************************/
class Viewer : public Element {
public:
  Viewer(const std::vector<std::any> &attribs);
  ~Viewer();
  Viewer(const Viewer &) : Element("Viewer") {}
  Viewer &operator=(const Viewer &) {}
  Viewer &operator=(Viewer &&other) noexcept {} // move assignment
  void render(void);
  void processEvents(void);
  Viewer &clear(void) {}
  // event implementation
  void dispatchEvent(const event &e);

private:
  std::unique_ptr<Visualizer::platform> m_device;
};
/// <summary>returns a tag string for the pointer. The tag is a double
/// pointer so that it can be changed. These macros are useful when
/// element creation is being accomplished using parsing while the
/// software needs the pointer to the created object.</summary>
#define stringPointerTag(a) (symbolicPointer(&a))
/// <summary>useful for a parameter to printf which accepts a char
/// ///.</summary>
///
/// <remarks>
/// The macro returns a tag string for the pointer. The tag is a double
/// pointer so that it can be changed. These macros are useful when
/// element creation is being accomplished using parsing while the
/// software needs the pointer to the created object. The macro creates
/// readable printf statements.
/// </remarks>
#define charPointerTag(a) (symbolicPointer(&a).c_str())
/// <summary> The function returns a string identity of the point within
/// tags. This enables easy integration between textual markup build and c++
/// pointer facilities. Example symbolic pointer:</summary> <paragraphPtr
/// typeHash 0x11111 memoryLocation 0x3333adbc>
///
/// <param name="e">[in] e</param> should be a double pointer that has not
/// been populated yet. That is, it should be nullptr. The value is stored
/// within a tag.</param>
///
template <typename ElementType> std::string symbolicPointer(ElementType **e) {
  std::string elementName = std::type_index(typeid(e)).name();
/* build meaningful string representative of the object's name.
The namestring is built differently by the compier depending
upon the compiler.
*/
#if defined(__linux__)
  std::size_t found = elementName.find_first_of("_0123456789");
  if (found != std::string::npos) {
    elementName = elementName.substr(found + 1);
  }
#elif defined(_WIN64)
#define PREFIX_ID "class "
  std::size_t found = elementName.find_first_of(PREFIX_ID);
  if (found != std::string::npos) {
    elementName = elementName.substr(found + strlen(PREFIX_ID));
    found = elementName.find_first_of(" ");
    if (found != std::string::npos)
      elementName = elementName.substr(0, found);
  }
#endif
  std::transform(elementName.begin(), elementName.end(), elementName.begin(),
                 ::tolower);
  std::stringstream ss;
  ss << "<" << elementName << "Ptr typeHash " << std::uppercase
     << std::setfill('0') << std::hex << std::type_index(typeid(*e)).hash_code()
     << " memoryLocation " << (unsigned long long)e << ">";

  return ss.str();
}
};     // namespace viewManager
#endif // VIEW_MANAGER_HPP_INCLUDED
