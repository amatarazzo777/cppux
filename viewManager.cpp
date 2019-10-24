/// <file>viewManagement.cpp</file>
/// <author>Anthony Matarazzo</author>
/// <date>6/16/18</date>
/// <version>1.0</version>
///
/// <summary>class that implements that main creation interface.
/// The file contains initialization, termination.</summary>
///
#include "viewManager.hpp"
using namespace std;
using namespace viewManager;
/**********
These namespace global lists contain the objects as a system ownership.
********/
std::vector<std::unique_ptr<Element>> viewManager::elements;
std::unordered_map<std::string_view, std::reference_wrapper<Element>>
    viewManager::indexedElements;
std::vector<std::unique_ptr<StyleClass>> viewManager::styles;
viewManager::Viewer::Viewer(const vector<any> &attrs)
    : Element("Viewer", attrs) {
  // setAttribute(indexBy{"_root"};
  Visualizer::openWindow(*this);
}
/// <summary>deconstructor for the view manager object.
/// </summary>
viewManager::Viewer::~Viewer() { Visualizer::closeWindow(*this); }
/// <summary>The main entry point for clients after their initial
/// buildup. The function simply calls the traversing function
/// with the main root as the starting point.
///
///
/// </summary>

void viewManager::consoleRender(Element &e, int iLevel) {
  int iWidth = iLevel * 4;

  cout.fill(' ');
  cout.width(iWidth);

  cout << e.softName << endl;

  e.render();

  auto n = e.firstChild();

  while (n) {
    consoleRender(n->get(), iLevel + 1);
    n = n->get().nextChild();
  }
}

void viewManager::Viewer::render(void) {

#if defined(CONSOLE)
  consoleRender(*this, 0);

#endif
}
/// <summary>
/// This is the only entry point from the platform for the event
/// dispatching system. The routine expects only certain types
/// of messages from the platform. The other events, that are computed,
/// are developed by this routine as needed. Each of these events, whether
/// passed through as the same message, or developed is placed into the
/// viewManager message queue. The background event dispatching fetches
/// messages from this queue, and calls the element's event processor
/// routines. The main thing to rememeber is that the information is
/// processed from a queue and using a background thread.
/// </summary>
void viewManager::Viewer::dispatchEvent(const event &evt) {
  switch (evt.evtType) {
  case eventType::resize:
    break;
  case eventType::keydown:
    break;
  case eventType::keyup:
    break;
  case eventType::keypress:
    break;
  case eventType::mousemove:
    break;
  case eventType::mousedown:
    break;
  case eventType::mouseup:
    break;
  case eventType::wheel:
    break;
  }
/* these events do not come from the platfrom. However,
they are spawned from conditions based upon the platform events.
*/
#if 0
eventType::focus
eventType::blur
eventType::mouseenter
eventType::click
eventType::dblclick
eventType::contextmenu
eventType::mouseleave
#endif
}
///< summary>The entry point that processes messages from the operating
/// system application level services. Typically on linux this is a
/// coupling of xcb and keysyms library for keyboard. Previous
/// incarnations of techology such as this typically used xserver.
/// However, XCB is the newer form. Primarily looking at the code of such
/// programs as vlc, the routine simply places pixels into the memory
/// buffer. while on windows the direct x library is used in combination
/// with windows message queue processing. </summary>
void viewManager::Viewer::processEvents(void) { m_device->messageLoop(); }

auto viewManager::operator""_pt(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::pt};
}
auto viewManager::operator""_pt(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::pt};
}
auto viewManager::operator""_em(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::em};
}
auto viewManager::operator""_em(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::em};
}
auto viewManager::operator""_px(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::px};
}
auto viewManager::operator""_px(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::px};
}
auto viewManager::operator""_percent(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}
auto viewManager::operator""_percent(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}
auto viewManager::operator""_pct(unsigned long long int value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}
auto viewManager::operator""_pct(long double value) -> doubleNF {
  return doubleNF{static_cast<double>(value), numericFormat::percent};
}
auto viewManager::operator""_normal(unsigned long long int value)
    -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::normal};
}
auto viewManager::operator""_normal(long double value) -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::normal};
}
auto viewManager::operator""_numeric(unsigned long long int value)
    -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::numeric};
}
auto viewManager::operator""_numeric(long double value) -> lineHeight {
  return lineHeight{static_cast<double>(value), lineHeight::numeric};
}

/// <summary>given the string id, the function returns
/// the element.
///
/// jquery shows that handling large document models can be
/// effectively managed using searching and iterators. Here,
/// elements or groups of elements can be accessed through query strings.
/// #, or *, or partial matches. Change attributes?
/// @ for style,
/// </summary>
auto viewManager::query(const std::string_view &queryString) -> ElementList {
  ElementList results;
  if (queryString == "*") {
    for (const auto &n : elements) {
      results.push_back(std::ref(*(n.get())));
    }
  } else {
    std::regex matchExpression(queryString.data(),
                               std::regex_constants::ECMAScript |
                                   std::regex_constants::icase);
    for (const auto &n : elements) {
      if (std::regex_match(n->getAttribute<indexBy>().value.data(),
                           matchExpression))
        results.push_back(std::ref(*(n.get())));
    }
  }
  return results;
}
auto viewManager::query(const ElementQuery &queryFunction) -> ElementList {
  ElementList results;
  for (const auto &n : elements) {
    if (queryFunction(std::ref(*(n.get()))))
      results.push_back(std::ref(*(n.get())));
  }
  return results;
}
bool viewManager::hasElement(const std::string_view &key) {
  auto it = indexedElements.find(key);
  return it != indexedElements.end();
}
/******************************************************************************************
Element
*******************************************************************************************/
/**
 * updateElementIdMap
 * updates the id within the
 * index if the item has
 * changed.
 *
 */
void viewManager::Element::updateIndexBy(const indexBy &setting) {
  // changing id just changes
  // the key in elementById
  // map
  std::string_view oldKey = "";
  const std::string_view &newKey = setting.value;
  std::unordered_map<std::type_index, std::any>::iterator it =
      attributes.find(std::type_index(typeid(indexBy)));
  // get the key of the old id
  if (it != attributes.end()) {
    oldKey = std::any_cast<indexBy>(it->second).value;
  }
  // case a. key is not blank,
  // yet it is the same value
  // as the old key therefore
  // there is no change.
  if (!oldKey.empty() && oldKey == newKey) {
    return;
    // case b. remap just the
    // key
  } else if (!oldKey.empty() && !newKey.empty()) {
    auto nodeHandler = indexedElements.extract(oldKey);
    nodeHandler.key() = newKey;
    indexedElements.insert(std::move(nodeHandler));
    // case c. remove key from
    // map
  } else if (!oldKey.empty() && newKey.empty()) {
    indexedElements.erase(oldKey);
    // case d. did not exist
    // before, add key to map
  } else if (!newKey.empty()) {
    indexedElements.insert({newKey, std::ref(*this)});
  }
  return;
}
auto viewManager::Element::insertBefore(Element &newChild,
                                        Element &existingElement) -> Element & {
  Element &child = newChild;
  // maintain tree structure
  child.m_parent = existingElement.m_parent;
  child.m_nextSibling = existingElement.m_self;
  child.m_previousSibling = existingElement.m_previousSibling;
  existingElement.m_previousSibling = child.m_self;
  // provide linkage
  if (child.m_previousSibling)
    child.m_previousSibling->m_nextSibling = child.m_self;
  if (child.m_nextSibling)
    child.m_nextSibling->m_previousSibling = child.m_self;
  // case where insert is at the first
  if (existingElement.m_self == m_firstChild) {
    m_firstChild = child.m_self;
  }
  m_childCount++;
  return child;
}
auto viewManager::Element::insertAfter(Element &newChild,
                                       Element &existingElement) -> Element & {
  return newChild;
}
auto viewManager::Element::removeChild(Element &oldChild) -> Element & {
  return *this;
}
auto viewManager::Element::replaceChild(Element &newChild, Element &oldChild)
    -> Element & {
  return *this;
}
auto viewManager::Element::move(const double t, const double l) -> Element & {
  getAttribute<objectTop>().value = t;
  getAttribute<objectLeft>().value = l;
  return *this;
}
auto viewManager::Element::resize(const double w, const double h) -> Element & {
  getAttribute<objectWidth>().value = w;
  getAttribute<objectHeight>().value = h;
  return *this;
}
void viewManager::Element::remove(void) { return; }
auto viewManager::Element::removeChildren(Element &e) -> Element & {
  return *this;
}
/// <summary>The function mapps the event id to the appropiate vector.
/// This is kept statically here for resource management.</summary>
///
vector<eventHandler> &viewManager::Element::getEventVector(eventType evtType) {
  static unordered_map<eventType, vector<eventHandler> &> eventTypeMap = {
      {eventType::focus, onfocus},
      {eventType::blur, onblur},
      {eventType::resize, onresize},
      {eventType::keydown, onkeydown},
      {eventType::keyup, onkeyup},
      {eventType::keypress, onkeypress},
      {eventType::mouseenter, onmouseenter},
      {eventType::mouseleave, onmouseleave},
      {eventType::mousemove, onmousemove},
      {eventType::mousedown, onmousedown},
      {eventType::mouseup, onmouseup},
      {eventType::click, onclick},
      {eventType::dblclick, ondblclick},
      {eventType::contextmenu, oncontextmenu},
      {eventType::wheel, onwheel}};
  unordered_map<eventType, vector<eventHandler> &>::iterator it;
  it = eventTypeMap.find(evtType);
  return it->second;
}
/// <summary>
/// The function will return the address of a std::function for the purposes
/// of equality testing. Function from
/// https://stackoverflow.com/questions/20833453/comparing-stdfunctions-for-equality
/// </summary>
template <typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
  typedef T(fnType)(U...);
  fnType **fnPointer = f.template target<fnType *>();
  return (size_t)*fnPointer;
}
auto viewManager::Element::addListener(eventType evtType,
                                       eventHandler evtHandler) -> Element & {
  getEventVector(evtType).push_back(evtHandler);
  return *this;
} /// <summary>The function will remove an event listener from the list of
/// events to receive messages.</summary>
///
/// <param name="evtType"> is the type of event to remove.</param>
/// <param name="evtHandler"> is the event to remove.?</param>
///
///
auto viewManager::Element::removeListener(eventType evtType,
                                          eventHandler evtHandler)
    -> Element & {
  auto eventList = getEventVector(evtType);
  auto it = eventList.begin();
  while (it != eventList.end()) {
    if (getAddress(*it) == getAddress(evtHandler))
      it = eventList.erase(it);
    else
      it++;
  }
  return *this;
}
///
/// <summary>This is the main function which invokes drawing of the item and
/// its children. It is called recursively when painting needs to occur.
/// This function is used internally and is not necessary to invoke. That
/// is, system already invokes this as part of the processing stack. The
/// work performed by this routine is accomplished using the surface image.
/// </ summary>
///
void viewManager::Element::render(void) {
#if 0
    std::string_view idName;
    try {
        idName = getAttribute<indexBy>().value;

    } catch (const std::exception& e) {
        idName = "noID";
    }

    std::cout << "indexBy " << idName << endl;
    std::cout << "children " << m_childCount << std::endl;

    // print information in the default string vector buffer
    auto vdata = data();
    for (auto s : vdata)
        std::cout << s << endl;
#endif
}
/// <summary>Uses the vasprint standard function to format the given
/// parameters with the format string. Inserts the named
/// elements within the markup into the document.</summary>
///
/// <param name="fmt"> is a printf format string. It should be a literal
/// string.</param> <param name="..."> is a variable argument parameter
/// passed to the standard printf function. </param>
///`
///
/// <code>
///
/// vector<string> movies={"The Hulk",
/// "Super Action Hero",
/// "Star Invader Eclipse"};
///
/// auto& e=createElement();
///
/// e.printf("The movie theatre is <blue>opened</blue> today for matinee.");
/// e.printf("Here is a list of movies: <ul>");
/// for(auto n : movies)
/// e.prinf("<li>%s</li>",n.c_str());
/// e.printf("</ul>");
///
/// </code>
///
/// <note>
/// <para>If a literal is not used for the first parameter, a warning will
/// be issued. This warning is effective because at times, it reminds the
/// developer that if the format string comes from a foreign source
/// and is not controlled, the stack may be violated.</para>
///
/// <para>To prevent this, the function has a static attribute type check
/// that is used during compile time. The actual parameter format
/// is associated with the 2 parameter. That is
/// this is actually in the 1 slot due to it being a
/// class member. So when a literal is not used for the first
/// parameter, a warning is issued.</para>
/// </note>
void viewManager::Element::printf(const char *fmt, ...) {
#if defined(__linux__)
  va_list ap;
  va_start(ap, fmt);
  char *buffer = nullptr;
/* These are checked with the __attribute__ setting on the function
 * declare above. Turning them off here makes it only report warnings to
 * calls of this member function and not the asprintf call. As well,
 * buffer is passed as a double pointer and is used to note the allocated
 * memory. It is also freed within this routine. */
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
  vasprintf(&buffer, fmt, ap);
#pragma clang diagnostic warning "-Wformat-security"
#pragma clang diagnostic warning "-Wformat-nonliteral"
  ingestMarkup(*this, buffer);
  free(buffer);
  va_end(ap);
#elif defined(__WIN64)
  va_list ap;
  va_start(ap, fmt);
  char *buffer = nullptr;
  int len;
  len = _vscprintf(fmt, ap) + 1;
  buffer = (char *)malloc(len * sizeof(char));
  vsprintf(buffer, fmt, ap);
  ingestMarkup(*this, buffer);
  free(buffer);
  va_end(ap);
#endif
}
Element &viewManager::Element::ingestMarkup(Element &node,
                                            const std::string_view &markup) {
  return *this;
}
/***************************************************************************
Visualizer module
***************************************************************************/
std::unordered_map<std::size_t, std::reference_wrapper<Element>> nodes;
std::size_t viewManager::Visualizer::allocate(Element &e) {
  static std::size_t token = 0;
  std::size_t ret = token;
  nodes.emplace(ret, std::ref<Element>(e));
  token++;
  return ret;
}
void viewManager::Visualizer::deallocate(const std::size_t &token) {}
void viewManager::Visualizer::openWindow(Element &e) {}
void viewManager::Visualizer::closeWindow(Element &e) {}
/***************************************************************************
Visualizer Platform module
***************************************************************************/
viewManager::Visualizer::platform::platform(eventHandler evtDispatcher,
                                            unsigned short width,
                                            unsigned short height) {
  dispatchEvent = evtDispatcher;

#if defined(CONSOLE)

#elif defined(__linux__)
  /* Open the connection to the X server */
  m_connection = xcb_connect(nullptr, nullptr);
  /* Get the first screen */
  m_screen = xcb_setup_roots_iterator(xcb_get_setup(m_connection)).data;
  m_syms = xcb_key_symbols_alloc(m_connection);
  /* Create black (foreground) graphic context */
  m_window = m_screen->root;
  m_foreground = xcb_generate_id(m_connection);
  uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
  uint32_t values[2] = {m_screen->black_pixel, 0};
  xcb_create_gc(m_connection, m_foreground, m_window, mask, values);
  /* Create a window */
  m_window = xcb_generate_id(m_connection);
  mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  values[0] = m_screen->white_pixel;
  values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
              XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
              XCB_EVENT_MASK_BUTTON_MOTION | XCB_EVENT_MASK_BUTTON_PRESS |
              XCB_EVENT_MASK_BUTTON_RELEASE;
  xcb_create_window(m_connection, XCB_COPY_FROM_PARENT, m_window,
                    m_screen->root, 0, 0, m_clientWidth, m_clientHeight, 10,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT, m_screen->root_visual, mask,
                    values);
  /* Map the window on the screen and flush*/
  xcb_map_window(m_connection, m_window);
  xcb_flush(m_connection);

  return;
#elif defined(_WIN64)
  HRESULT hr;
  // Create a Direct2D factory.
  hr =
      D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
  if (FAILED(hr))
    return;
  // Register the window class.
  WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  // ******** wcex.lpfnWndProc = &Visualizer::platform::WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = sizeof(LONG_PTR);
  wcex.hInstance = HINST_THISCOMPONENT;
  wcex.hbrBackground = NULL;
  wcex.lpszMenuName = NULL;
  wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
  wcex.lpszClassName = "viewManagerApp";
  RegisterClassEx(&wcex);
  // Create the window.
  m_hwnd = CreateWindow("viewManagerApp", "viewManager Application",
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                        static_cast<UINT>(width), static_cast<UINT>(height),
                        NULL, NULL, HINST_THISCOMPONENT, 0L);
  hr = m_hwnd ? S_OK : E_FAIL;
  if (FAILED(hr))
    return;
  SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (long long)this);
  ShowWindow(m_hwnd, SW_SHOWNORMAL);
  UpdateWindow(m_hwnd);
  RECT rc;
  GetClientRect(m_hwnd, &rc);
  // Create a Direct2D render target
  hr = m_pDirect2dFactory->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(
          m_hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
      &m_pRenderTarget);
  if (FAILED(hr))
    return;
#endif
}
#if defined(_WIN64)
///< summary>The default window message procesor for the application.
/// This is the version ofr the Microsoft Windows operating system.
///</summary>
LRESULT CALLBACK viewManager::Visualizer::platform::WndProc(HWND hwnd,
                                                            UINT message,
                                                            WPARAM wParam,
                                                            LPARAM lParam) {
  LRESULT result = 0;
  bool handled = false;
  LONG_PTR lpUserData = GetWindowLongPtr(hwnd, GWLP_USERDATA);
  platform *platformInstance = (platform *)lpUserData;
  switch (message) {
  case WM_SIZE:
    platformInstance->dispatchEvent(event{eventType::resize,
                                          static_cast<short>(LOWORD(lParam)),
                                          static_cast<short>(HIWORD(lParam))});
    result = 0;
    handled = true;
    break;
  case WM_KEYDOWN: {
    UINT scandCode = (lParam >> 8) & 0xFFFFFF00;
    WCHAR lBuffer[10];
    BYTE State[256];
    GetKeyboardState(State);
    ToUnicode(wParam, scandCode, State, lBuffer, wcslen(lBuffer), 0);
    platformInstance->dispatchEvent(
        event{eventType::keydown, wstring(lBuffer)});
  } break;
  case WM_KEYUP: {
    UINT scandCode = (lParam >> 8) & 0xFFFFFF00;
    WCHAR lBuffer[10];
    BYTE State[256];
    GetKeyboardState(State);
    ToUnicode(wParam, scandCode, State, lBuffer, wcslen(lBuffer), 0);
    platformInstance->dispatchEvent(event{eventType::keyup, wstring(lBuffer)});
  } break;
  case WM_CHAR: {
    WCHAR tmp[2];
    tmp[0] = wParam;
    tmp[1] = 0x00;
    platformInstance->dispatchEvent(event{eventType::keypress, wstring(tmp)});
  } break;
  case WM_LBUTTONDOWN:
    platformInstance->dispatchEvent(
        event{eventType::mousedown, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 1});
    break;
  case WM_LBUTTONUP:
    platformInstance->dispatchEvent(
        event{eventType::mouseup, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 1});
    break;
  case WM_MBUTTONDOWN:
    platformInstance->dispatchEvent(
        event{eventType::mousedown, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 2});
    break;
  case WM_MBUTTONUP:
    platformInstance->dispatchEvent(
        event{eventType::mouseup, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 2});
    break;
  case WM_RBUTTONDOWN:
    platformInstance->dispatchEvent(
        event{eventType::mousedown, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 3});
    break;
  case WM_RBUTTONUP:
    platformInstance->dispatchEvent(
        event{eventType::mouseup, static_cast<short>(LOWORD(lParam)),
              static_cast<short>(HIWORD(lParam)), 3});
    break;
  case WM_MOUSEMOVE:
    platformInstance->dispatchEvent(event{eventType::mousemove,
                                          static_cast<short>(LOWORD(lParam)),
                                          static_cast<short>(HIWORD(lParam))});
    result = 0;
    handled = true;
    break;
  case WM_MOUSEWHEEL:
    platformInstance->dispatchEvent(event{
        eventType::wheel, static_cast<short>(LOWORD(lParam)),
        static_cast<short>(HIWORD(lParam)), GET_WHEEL_DELTA_WPARAM(wParam)});
    break;
  case WM_DISPLAYCHANGE:
    InvalidateRect(hwnd, NULL, FALSE);
    result = 0;
    handled = true;
    break;
  case WM_PAINT:
    platformInstance->dispatchEvent(event{eventType::paint});
    ValidateRect(hwnd, NULL);
    result = 0;
    handled = true;
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    result = 1;
    handled = true;
    break;
  }
  if (!handled)
    result = DefWindowProc(hwnd, message, wParam, lParam);
  return result;
}
#endif
/// <summary>terminates the xserver connection
/// and frees resources.
/// </summary>
viewManager::Visualizer::platform::~platform() {
#if defined(CONSOLE)

#elif defined(__linux__)
  xcb_free_gc(m_connection, m_foreground);
  xcb_key_symbols_free(m_syms);
#elif defined(_WIN64)
  m_pDirect2dFactory->Release();
  m_pRenderTarget->Release();
  m_pOffscreen->Release();
  m_offScreenBitmap->Release();
#endif
}
void viewManager::Visualizer::platform::messageLoop(void) {
#if defined(CONSOLE)

#elif defined(__linux__)
  while ((event = xcb_wait_for_event(m_connection))) {
    switch (event->response_type & ~0x80) {
    case XCB_MOTION_NOTIFY: {
      xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;
      dispatchEvent(
          event{eventType::mousemove, motion->event_x, motion->event_y});
    } break;
    case XCB_BUTTON_PRESS: {
      xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;
      dispatchEvent(
          event{eventType::mousedown, bp->event_x, event_y, bp->detail});
    } break;
    case XCB_BUTTON_RELEASE: {
      xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
      dispatchEvent(
          event{eventType::mouseup, bp->event_x, event_y, bp->detail});
    } break;
    case XCB_KEY_PRESS: {
      xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
      xcb_keysym_t sym = xcb_key_press_lookup_keysym(m_syms, kp, 0);
      dispatchEvent(event{eventType::keydown, sym});
    } break;
    case XCB_KEY_RELEASE: {
      xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
      xcb_keysym_t sym = xcb_key_press_lookup_keysym(m_syms, kr, 0);
      dispatchEvent(event{eventType::keyup, sym});
    } break;
    }
    free(event);
  }
#elif defined(_WIN64)
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
#endif
}
void viewManager::Visualizer::platform::flip() {}
