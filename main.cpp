#include "viewManager.hpp"

using namespace std;
using namespace viewManager;

void test0(Viewer &vm);
void test0b(Viewer &vm);
void test1(Viewer &vm);
void test1a(Viewer &vm);
void test2(Viewer &vm);
void test3(Viewer &vm);
void test4(Viewer &vm);
void test5(Viewer &vm);
void test6(Viewer &vm);
void test7(Viewer &vm);
void test7a(Viewer &vm);
void test7b(Viewer &vm);
void test7c(Viewer &vm);
void test7d(Viewer &vm);
void test7e(Viewer &vm);
void test7f(Viewer &vm);
void test7g(Viewer &vm);
void test7h(Viewer &vm);
void test7i(Viewer &view);
void test8a(Viewer &vm);
void test8(Viewer &vm);
void test10(Viewer &vm);

void testStart(string_view sFunc) {
#if defined(CONSOLE)
  cout << sFunc << endl;
#endif
}

/****************************************************************************************************

***************************************************************************************************/
#if defined(__linux__)
int main(int argc, char **argv) {
  // handle command line here...
#elif defined(_WIN64)
int WINAPI WinMain(HINSTANCE /* hInstance */, HINSTANCE /* hPrevInstance */,
                   LPSTR lpCmdLine, int /* nCmdShow */) {
  // command line
#endif

  // create the main window area. This may this is called a Viewer object.
  // The main browsing window. It is an element as well.
  cout << "start viewer create" << endl;
  auto vm = createElement<Viewer>(
      objectTop{10_pct}, objectLeft{10_pct}, objectHeight{80_pct},
      objectWidth{80_pct}, textFace{"arial"}, textSize{16_pt}, textWeight{400},
      textIndent{2_em}, lineHeight::normal, textAlignment::left,
      position::relative, paddingTop{5_pt}, paddingLeft{5_pt},
      paddingBottom{5_pt}, paddingRight{5_pt}, marginTop{5_pt},
      marginLeft{5_pt}, marginBottom{5_pt}, marginRight{5_pt});
  cout << "viewer created." << endl;
  test0b(vm);
#if 0
  test0(vm);
  test1(vm);
  test1a(vm);
  test2(vm);
  test3(vm);
  test4(vm);
  test5(vm);
  test6(vm);
  test7(vm);
  test7a(vm);
  test7b(vm);
  test7c(vm);
  test8(vm);
  test8a(vm);
  test10(vm);
#endif
}
string_view randomString(int nChars);
double randomDouble(double a, double b);
int randomInt(int a);
void randomAttributeSettings(Element &e);
/************************************************************************
************************************************************************/
void test0(Viewer &vm) {
  vm << "Hello World\n";
  vm.render();
  vm << "<h1>Hello World</h1>";
  vm << "<blue>Got to be a pretty day.</blue>";
  vm.render();
}
/************************************************************************
************************************************************************/
//! [test0]
void test0b(Viewer &vm) {
  testStart(__FUNCTION__);

  cout << "createElement DIV" << endl;
  auto e = createElement<DIV>(indexBy{"divTTT"}, "test",
                              vector<float>{.3, .6, .3, .777, 10.33});
  if (std::is_lvalue_reference<decltype(e)>::value)
    cout << "&";
  else if (std::is_rvalue_reference<decltype(e)>::value)
    cout << "&&";
  cout << typeid(e).name() << endl;

  cout << "createElement DIV END" << endl;

  cout << "createElement H1 BEGIN" << endl;
  auto &appTitle = createElement<H1>(indexBy{"title"}, objectTop{10_px},
                                     textAlignment::center, "Type XCB");
  if (std::is_lvalue_reference<decltype(appTitle)>::value)
    cout << "&";
  else if (std::is_rvalue_reference<decltype(appTitle)>::value)
    cout << "&&";
  cout << typeid(e).name() << endl;

  cout << "createElement H1 END" << endl;

  e.appendChild(appTitle);
  e.appendChild<H2>(indexBy{"subTitle"}, textAlignment::center,
                    "An application for entering text");

  vm.appendChild(e);
  vm.appendChild<PARAGRAPH>(indexBy{"content"},
                            "The information must add two children");
  e.data() = {"This is replace as a data node"};
  vm.appendChild("<div id=testAdd/>");
  vm.render();
}
//! [test0]
/************************************************************************
************************************************************************/
//! [test1]
void test1(Viewer &vm) {
  // testStart(__func__);
  auto mainArea = createElement<DIV>(
      indexBy{"mainArea"}, objectTop{10_pct}, objectLeft{10_pct},
      objectWidth{90_pct}, objectHeight{90_pct}, textColor{50, 50, 50},
      background{100, 200, 200}, textFace{"FiraMono-Regular"}, textSize{20_pt},
      textWeight{400});
  auto appTitle = createElement<H1>(indexBy{"title"}, objectTop{10_px},
                                    textAlignment::center, "Type XCB");
  auto appSubTitle =
      createElement<H2>(indexBy{"subtitle"}, objectTop{10_px},
                        textAlignment::center, "A starter testing Application");
  appTitle.setAttribute(objectTop{20_percent});
  appTitle.data() = {"New Text in there."};
  appTitle.data() = {"data(). New Text in there."};
  appTitle.data() = {"But after we add it to the dom."};
  mainArea.appendChild(appTitle);
  mainArea.appendChild(appSubTitle);
  vm.appendChild(mainArea);
  for (Element n : query("*")) {
  }
  getElement("title").clear().data() = {
      "A new copy is never created when appending happens., just std::move"};
  vm.render();
  for (auto n : query("*")) {
  }
  getElement("title").data() = {
      "It uses the reference to the created object createElement."};
  vm.render();
  getElement("title").appendChild<H2>(indexBy{"subtitle2"}, objectTop{20_px},
                                      textAlignment{textAlignment::center},
                                      "by Anthony Matarazzo");
  getElement("mainArea")
      .appendChild<PARAGRAPH>(
          indexBy{"bodyText"}, textColor{"blue"},
          "The information here is added to the document. Text is "
          "wrapped"
          "while other items remain. It is hoped that image and "
          "image "
          "processing will be fun. I think so. After I had learned "
          "that "
          "the ImageMagick library had been tuned, works with SSE "
          "in 64bit floating point format, I thought to myself, "
          "should be fast. ");
  vm.render();
  getElement("mainArea").setAttribute(textColor{70, 70, 70});
  getElement("mainArea").setAttribute(objectLeft{100_px});
  getElement("title")
      .setAttribute(objectLeft{100_px}, "The Visualizer")
      .data() = {"Mini App Title"};
  getElement("bodyText").setAttribute(indexBy{"bodyInformation"}).data() = {
      "The new text information is not quite as long"};
  vm.render();
  auto statusText =
      createElement<H3>(indexBy{"statusText"}, "Status Line Updated:");
  mainArea.insertBefore(statusText, getElement("bodyInformation"));
  vm.render();
  mainArea.insertAfter(
      createElement<H1>(indexBy{"titleText2"}, "A app built with gui tags."),
      getElement("bodyInformation"));
  mainArea.removeChild(getElement("bodyInformation"));
  vm.render();
  getElement("mainArea")
      .appendChild<PARAGRAPH>(indexBy{"bodyText"}, textColor{"orange"},
                              "Re added and updated. Scatered coverered "
                              "diced and smashed.");
  vm.render();
  mainArea.replaceChild(
      createElement<paragraph>(indexBy{"bodyTextNew"}, textColor{"green"},
                               "And now, for a limited time. the all new ... "),
      getElement("bodyText"));
  vm.render();
  // attributes and references
  /* to quickly change attribute values wihin the dom
you can
get a reference to the actual value stored within the tree. this is
accomplished using the getAttribute function. The first parameter is
the attribute name you wish to get. The second is the format of the
characteristic. At most time, the first one is the one that is
commonly used. However, most attributes contain a format specifier or
other characteristics associated with the attribute. To provide
efficient usage, the second parameter is the type of the
characteristic. The type is is defaulted to double. That is, the
common characteristic type is a double storage type. IE, objectLeft,
marginTop
...
*/
  if (mainArea.parent())
    mainArea.data() = {"Hey attached to another container."};
  // walk children
  auto n = mainArea.firstChild();
  while (n != std::nullopt) {
    n = mainArea.nextChild();
  }
  for (auto n = mainArea.firstChild(); n != std::nullopt;
       n = mainArea.nextChild()) {
  }
  auto [idRefText] = mainArea.getAttribute<indexBy>();
  idRefText = "idView";
  // must use set to invoke indexing of elementById
  mainArea.setAttribute(indexBy{idRefText});
  auto [d, opt] = mainArea.getAttribute<objectLeft>();
  d = 900;
  auto d2 = mainArea.getAttribute<objectLeft>();
  d2.option = numericFormat::percent;
  d2.value = 50;
  vm.render();
  // styles and CSS
  auto boldTexts = createStyle(
      indexBy{"boldText"}, textColor{"green"}, background{100, 200, 200},
      textFace{"FiraMono-Regular"}, textSize{20_pt}, textWeight{800});
  mainArea.styles.push_back(boldTexts);
  appSubTitle.styles.push_back(boldTexts);
  vm.render();
}
//! [test1]
//! [test1a]
/**
 * \brief The test shows that entry of lowercase names is valid as the names
 * are aliased by the 'using' feature. 'div' is reserved, so 'dblock' is used
 * instead. h1,h2,h3,h4
 *
 * \note A very important item to embrace is method chaining. Method chaining
 * provides a consolidated description of elements and their hierarchy of
 * children. Yet when setting a reference, to correctly receive the proper value
 * at most times you CANNOT chain the createElement method. This is so, because
 * the LAST return within the chain is the value that the reference is set to.
 *
 */
void test1a(Viewer &vm) {
  testStart(__FUNCTION__);
  // testStart(__func__);
  ElementList chapter;
  int m = randomInt(100);
  // notice here that the createElement is not chained because a reference
  // is being attained to the element. Because of the way chaining works,
  // this must be a single function so that the correct reference is
  // computed.
  for (int i = 0; i < m; i++) {
    auto info = createElement<paragraph>(
        indexBy{"rndTEST3BookletParagraph_" + to_string(i)},
        vector<string_view>{randomString(200), randomString(200),
                            randomString(200)});
    info.appendChild<ul>(
        indexBy{"idbikes"},
        vector<string_view>{"Huffy", "Schwinn", "Giant", "Road Master"});
    chapter.push_back(info);
  }
  auto booklet = createElement<dblock>(indexBy{"booklet3"});
  vm.appendChild(booklet);
  booklet.appendChild(chapter);
  vm.render();
}
//! [test1a]
/************************************************************************
************************************************************************/
//! [test2]
void test2(Viewer &vm) {
  testStart(__func__);
  for (int i = 0; i < randomInt(100); i++) {
    auto information = createElement<DIV>(indexBy{"rndDIV_" + to_string(i)});
    for (int j = 0; j < randomInt(100); j++) {
      information.appendChild<PARAGRAPH>(
          indexBy{"rndParagraph_" + to_string(j)}, randomString(200));
    }
    vm.appendChild(information);
  }

  // randomize attributes, usually the test would contain a larger number that 1
  // for testing the performance. hwoever with exceptions being caught, within
  // the terminal, one iteration is fine for the debug.
  for (int i = 0; i < 1; i++) {
    for (auto n : query("*"))
      randomAttributeSettings(n);
  }
  vm.render();
}
//! [test2]
/************************************************************************
************************************************************************/
//! [test3]
void test3(Viewer &vm) {
  testStart(__func__);
  ElementList chapter;
  int m = randomInt(100);
  for (int i = 0; i < m; i++) {
    chapter.push_back(createElement<PARAGRAPH>(
        indexBy{"rndTEST3BookletParagraph_" + to_string(i)},
        randomString(200)));
  }
  auto booklet = createElement<DIV>(indexBy{"booklet3"});
  vm.appendChild(booklet);
  booklet.appendChild(chapter);
  vm.render();
}
//! [test3]
//! [test4]
void test4(Viewer &vm) {
  testStart(__func__);
  int m = randomInt(100);
  Element eBooklet = vm.appendChild<DIV>(indexBy{"booklet4"});
  for (int i = 0; i < m; i++)
    eBooklet.appendChild<PARAGRAPH>(
        indexBy{"rndTEST4BookletParagraph_" + to_string(i)}, randomString(200));
  vm.render();
}
//! [test4]
//! [test5]
void test5(Viewer &vm) {
  testStart(__func__);
  ElementList chapter;
  int m = randomInt(100);
  for (int i = 0; i < m; i++) {
    auto &e = createElement<PARAGRAPH>(
        indexBy{"rndTEST5BookletParagraph_" + to_string(i)}, randomString(200));
    e.appendChild<PARAGRAPH>(indexBy{"rndTEST5BookletNotes_" + to_string(i)},
                             randomString(200))
        .appendChild<PARAGRAPH>(indexBy{"rndTEST5GuestSpeaker_" + to_string(i)},
                                randomString(200))
        .append<PARAGRAPH>(indexBy{"rndTEST5BookletReferences_" + to_string(i)},
                           randomString(200));
    chapter.push_back(e);
  }
  cout << "document building finished" << endl;
  vm.appendChild<DIV>(indexBy{"booklet5"}).appendChild(chapter);
  vm.render();
}
//! [test5]
/************************************************************************
************************************************************************/
//! [test6]
void test6(Viewer &vm) {
  testStart(__func__);
  ElementList chapter;
  int m = randomInt(5);
  for (int i = 0; i < m; i++) {
    auto &e = createElement<PARAGRAPH>(
        indexBy{"rndTEST5BookletParagraph_" + to_string(i)});

    e << "Hello "
      << "anthony"
      << "can you do the []";

    e.appendChild<UL>(indexBy{"bookletNotes_" + to_string(i)},
                      vector<string_view>{"Endurance training", "Biking",
                                          "Meals", "Schedule"})
        .append<UL>(
            indexBy{"guestCompanies_" + to_string(i)},
            vector<pair<int, string_view>>{{0, "Gyms"},
                                           {1, "Gold's Gym"},
                                           {1, "Core Fitness"},
                                           {1, "Tommy Doright's"},
                                           {0, "Tools"},
                                           {1, "Huffy"},
                                           {1, "Scwitchers"},
                                           {1, "Clock Down Industrials"}})
        .append<UL>(indexBy{"bookletReferences_" + to_string(i)},
                    vector<string_view>{"The 26inch Road", "Flatters Chain",
                                        "Wheelers and Handlebars",
                                        "Rim's n Chains"});
    chapter.push_back(e);
  }

  vm.appendChild<DIV>(indexBy{"booklet5"}).appendChild(chapter);

  vm.render();
}
//! [test6]
/************************************************************************
************************************************************************/
//! [test7]
void test7(Viewer &vm) {
  testStart(__func__);
  ElementList vParagraphs;
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara1"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara2"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara3"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara5"}));
  vm.appendChild<DIV>(indexBy{"test"});
  getElement("test").appendChild(vParagraphs);
  vm.appendChild<DIV>(indexBy{"mainArea"}, objectTop{10_pct},
                      objectLeft{10_pct}, objectWidth{90_pct},
                      objectHeight{90_pct}, textColor{50, 50, 50},
                      background{100, 200, 200}, textFace{"FiraMono-Regular"},
                      textSize{20_pt}, textWeight{400})
      .appendChild<H1>(indexBy{"title"}, textAlignment::center, "Type XCB")
      .append<H2>(indexBy{"subtitle"}, objectTop{40_pct}, textAlignment::center,
                  "A starter testing Application")
      .appendChild<SPAN>(indexBy{"idCompany"}, "research company name[].");
  // one part of the syntax that is error prone is snding the last item.
  // you have to have sure that the entire parameter is encapsolated inside
  // brackets... make several points about this in the documentation
  // since it is necessary....
  vm.appendChild<DIV>(indexBy{"footer"}, "Footer of Page")
      .appendChild<SPAN>(indexBy{"timeOfDay"})
      .append<SPAN>(indexBy{"currentDate"});
  vm.append("<ul><li>Hello added to the end</li></ul>");
  vm.render();
}
//! [test7]
//! [test7a]
void test7a(Viewer &vm) {
  testStart(__func__);
  ElementList vParagraphs;
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara1"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara2"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara3"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara4"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara5"}));
  auto divTest = vm.appendChild<DIV>(indexBy{"test"});
  divTest.appendChild(vParagraphs);
  divTest.append("<ul><li>Hello added to the end</li></ul>");
  divTest.appendChild("<p>Just adhoc dom building.</p>");
  // the append and appendChild with texts.
  divTest.appendChild("<ul></ul>")
      .appendChild("<li>test1</li>")
      .append("<li>test2</li>")
      .append("<li>test3</li>")
      .append("<li>test4</li>")
      .append("<li indexBy=ttt/>");
  vm.render();
}
//! [test7a]
//! [test7b]
void test7b(Viewer &vm) {
  testStart(__func__);
  ElementList vParagraphs;
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara1"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara2"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara3"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara4"}));
  vParagraphs.push_back(createElement<PARAGRAPH>(indexBy{"testpara5"}));
  auto divTest = vm.appendChild<DIV>(indexBy{"test"});
  divTest.appendChild(vParagraphs);
  divTest.append("<p>Appended after divtest as a sibling.</p>");
  divTest.appendChild("<p>Just adhoc dom building.</p>");
  // the append and appendChild with texts.
  // notice that you can appendChild to an element expressed by text.
  // The complete object and terminal must be given in one line.
  divTest.appendChild("<ul/>")
      .appendChild("<li>test1</li>")
      .append("<li>test2</li>")
      .append("<li>test3</li>")
      .append("<li>test4</li>");
  vm.render();
}
//! [test7b]
//! [test7c]
void test7c(Viewer &vm) {
  testStart(__func__);
  auto divTest = vm.appendChild<DIV>(indexBy{"testAnother"});
  // the append and appendChild with texts.
  divTest.appendChild("<ul></ul>")
      .appendChild("<li>test1</li>")
      .append("<li>test2</li>")
      .append("<li>test3</li>")
      .append("<li>test4</li>");
  divTest.append("<ul><li>Hello added to the end</li></ul>");
  divTest.appendChild("<p>Just adhoc dom building.</p>");
  vm.render();
}
//! [test7d]
void test7d(Viewer &vm) {
  testStart(__func__);
  auto divTest = vm.appendChild<DIV>(indexBy{"testAnother"});
  // the append and appendChild with texts.
  divTest.appendChild("<ul></ul>").data() = {"2222", "3333", "444", "6.66",
                                             "7"};
  divTest.appendChild<ul>().data<double>() = {1, 4, 5, 3, 4, 4, 4, 33, 4, 5};
  divTest.appendChild<ul>().data<pair<int, string_view>>() = {
      {0, "AC/DC"},
      {1, "Hell's Bells"},
      {1, "You Shook Me All Night Long"},
      {1, "Have a Drink on Me"},
      {1, "Squeeler"},
      {0, "Books"},
      {1, "Yada yada yada"}};
  divTest.appendChild("<Combo></Combo>").data() = {
      "option a", "option b", "option c", "option d", "option e"};
  divTest.append("<ul><li>Hello added to the end</li></ul>");
  divTest.appendChild<paragraph>().data() = {"fdff", "fdfdfdf", "Yttyty",
                                             "ghhhht"};
}
void test7e(Viewer &view) {
  auto tblCost = createElement<TABLE>(
      objectLeft{10_pct}, objectTop{10_pct}, objectWidth{80_pct},
      objectHeight{80_pct},
      tableColumns{
          {"Name", "Employment Start", "Salary", "Sales", "Cost Ratio"}},
      tableData{{"Anthony", "1/1/15", "10.75", "34.16", "4.5 +"},
                {"Candy", "4/16/12", "12.75", "4464.76", "35017.2 +"},
                {"Alvin", "1/1/65", "4.75", "125.16", "2634.9 +"}});
  /// tblCost.edit(1,4);
  view.render();
}
// complex form - most common in applications because of the layout and
// summary information used to visualize.
/* The 'using' statement below creates an alias of a type - the artificial
name used by a coder for their internal coding communication. This name
is used a template parameter and thus is used to store in
a vector container internally within the element object.
Therefore the data is stored as an efficient tuple whose members are
accessed by const expression which are offsets into the allocated memory.
When using the data<> function, also templated, as a parameter, the
using storage alias provides readible syntax easily. This is one
type of communication interface generation for specific binary data
formats may be attained. Others such as objects can be created for
more complex structures and object oriented large scale business architectures.
The data<> function is robust. As well as possessing a non-copied live
binary data input mechnism, the formatting and document building are
created by compiled lambda's using std::functions. The mechnism for
creating a dataAdaptor, which is a c++ std::tuple data structure in this
example, is simply accomplished by the alias declaration 'using NAME=tuple<...>;
The mechnism for creating a 'real world' formatter is also compile
time checked. It is stored within a std::function<> which is called
to summon the formatted document element when it is required for visualization.
The templated class dataTransform provides document building functionality
efficiently.
The design separates the data from the "objects". Another captivativing
purity is that each element object created is linked to the
storage container's memory index when it is created. The dataTransform stores
a std::function internally. The object created becomes internally related to
the data all through using type information. That is, it is expected that
a particular type have a unique formatter.
The dataTransform templated class accepts one parameter: storage type.
All items within the system are stored within a vector. This cannot be changed
and makes the interface easier. The actual transform is a std::function.
The function can be expressed as a lambda or std::function compatible object.
The function is called once in iteration for each item within the vector.
The system after calling the document creation function links the element
to it's index if it is on the screen. When elements are not on the display.
their relationship is no longer linked. The element is linked in two ways: by
unordered mapped key and direct data reference. The unordered map is useful when
data is edited, or rows inserted into the vector data structure using the data()
interface. This makes detailed interface creation simpler in syntax than a
parsing to memory structure does - less room.
The std::function option provides very easy syntax for binding to
class member functions and other types. Therefore, in particular
applications, or as a company architecture, formatting of this particular
sort may be accomplished as a business component. The architecture
supports these facets of modern design benefits.
*/
void test7f(Viewer &view) {
  // build a fancy <ul> list with <li> children consisting
  // of varying details...
  static array<string_view, 3> sIconNames = {"base.raw", "contentIcon.raw",
                                             "normal.raw"};
  // dataAdaptor
  using tagInfo = tuple<int, string_view, float>;
#define idRecords "id_records"
  // format detailed views easily ...
  view.appendChild<ul>(indexBy{idRecords}).data<tagInfo>() = {
      {0, "AC/DC", 9.9},
      {1, "Hell's Bells", 9.8},
      {1, "You Shook Me All Night Long", 7.2},
      {1, "Have a Drink on Me", 4.3},
      {1, "Squeeler", 9.1},
      {0, "Books", 10},
      {1, "The Button Bubble - Digital Economics By Anthony Matarazzo", 5.5}};
  auto urecords = getElement(idRecords);
  auto recordPlex = urecords.data<tagInfo>();
  recordPlex.push_back({0, "Variodic Blackhearts", .2});
  recordPlex.push_back({1, "Sympathetic Voting Machines", .001});
  recordPlex.push_back(
      {1, "Vectorized Signaling Auto Typed constexpr Candy", .101});
  recordPlex.push_back({1, "Ya Got To Write It All screamin interfaces", .22});
  recordPlex.push_back(
      {1, "Templated Desktops with INLINED ANIMATION MOTION _data", .667});
  recordPlex.push_back({1,
                        "a neutral index of finger motion path skeletal data "
                        "stored in reusable gesture rom",
                        .665});
  recordPlex.push_back({0, "The Stairsouppe Choordettes", .4});
  recordPlex.push_back(
      {1, "My Binary Blister Coniquebine <ani=greenGlow>megatron remix</ani>",
       .19});
  // allowing for very fast expansion for meta creations. Most likely,
  // the tags may mean somthing more preverse than numeric. So the balance is
  // in defintion
  // formatting lambda
  // passed T & - type, class or tuple
  auto fnTransform = [](tagInfo &tag) -> li & {
    textColor vip =
        std::get<2>(tag) < 5.0 ? textColor{"blue"} : textColor{"purple"};
    auto &o = createElement<li>(textColor{"blue"});
    // set icon of the li element
    auto n = std::get<0>(tag);
    o.appendChild<image>(sIconNames[n]);
    // set text
    o.appendChild<span>(std::get<1>(tag));
    return o;
  };
  urecords.dataTransform<li, tagInfo>(fnTransform);
  // Data insertion using the stdandard libary
  //
  // get reference to actual memory. std interface.
  auto ulRecords = getElement(idRecords);
  // tagFormatter is needed for hash map to get the structure.
  // templated for user defined storage and reflexion.
  // state information is saved when getAdaptor is invoked,
  // so senseing what changes according to screen rules is
  // the problem to solve for the system that will create
  // high performance "implementation error free" solution
  // exception raised from non created item from absorb.
  auto recordPlex2 = ulRecords.data<tagInfo>();
  for (int i = 1; i < 10; i++)
    recordPlex2.push_back({i, "STD::MOVE", randomDouble(0, 10)});
  // senses that 10 added to the end of a list of 1000 already/ - no display
  // change.
  ulRecords.dataHint<tagInfo>(10);
  for (auto &n : recordPlex2) {
    if (std::get<2>(n) > 5.5 && std::get<2>(n) < 6.9) {
      auto &sv = std::get<1>(n);
      sv = std::string(sv) + std::string(" Wowza");
      // takes info and induces the change.
      ulRecords.dataHint<tagInfo>(n);
    }
  }
  /* Using a hinted signaller will expose the versitility of the design
and standard library usage. As well define typical usage
intrinsic with data structure usage rather than reliance on
the neccessity of parsed structure definition as html must have. w3c
technology h1, h2, h3, div, and ^element. Meaning that these concepts
of visual layout technology are the intellectual property of the w3c.
So after it works, perhaps some working will have to be attained.
a) not all members of the data adaptor will have to be displayed. therefore
not all subsequent dom members need reflexition as a clipped viewport.
the .size() method and index access according to display rendering
position can show the information.
b) lighter memory mangement according to clipped cache prune methods
of dom tree reflection of templated typed data.
c) operating in an error free rate according to limitations of
vector standard interface conventions - that is no change. The actual
data is exposed. While scrollbar numberical values offer higher
memory performance than a browser . The display of large information
sets as these structures permits is inaccessible for screen resolutions.
That is typically less than 100k of text at a time.
Hint hashes about the location of the data are saved within the element
strcture. As well, within the onscreen datastructure, hashed information that
describe how the data is displayed on the screen. Such as text,color,etc which
summarizes the attribute data. When the gui programmer invokes the smart
adaptor signaler with the hint, the displayed cache is search for numerical
relationships that affect the rendering of the visualized or cached offscreen
clipped non visible element. This uery combined with the fact the the on
screen 'built' elements are kept to a minimal can be a design to research for
the rendering engine and big data performance. This makes the dirtiness of
textual attributes more efficient according to their necessity - displayed?.
*/
}
void test7g(Viewer &view) {
  // class based linkage for more complex formatters and
  // builders. This class and formatting logic would be in a separate file,
  // here for testing.
  using uniRecord = class uniRecord {
    enum uniRecordSchema {
      contact,
      filelist,
      pictureThumb,
      ratingVisual,
      videoThumb,
      audioThumb
    };

  public:
    size_t index;
    uniRecordSchema schema;
    uniRecord(const string_view &broadName) {}
    uniRecord(const string_view &fname, const string_view &lname,
              const string_view &phone, const string_view &email) {
      schema = contact;
    };
    uniRecord(const string_view &_fileName, const size_t &fileSizeKiloByte,
              const size_t &indexPreviewKey) {
      schema = filelist;
    };
    uniRecord(const string_view &fname, const string_view &format,
              const int &depth, const tuple<double, double, double> gps,
              const size_t summaryIndexKey) {
      schema = pictureThumb;
    };
    uniRecord(const float &stars) { schema = ratingVisual; };
    /*... for each record type */
    auto &build(void) {
      auto &o = createElement<li>();
      // build interface based on the schema selected from enumeration
      // as a simple example. so the data input would be a parameter to
      // some kind of specialized formatter, user preferences,
      // who knows - linked to shared memory, or some disk data.
      switch (schema) {
      case contact:
        o.appendChild("contact info");
        break;
      case filelist:
        break;
      case pictureThumb:
        break;
      case ratingVisual:
        break;
      case videoThumb:
        break;
      case audioThumb:
        break;
      }
      // link the element object to this one.
      o.setAttribute(*this);
      return o;
    }
  };
  /* format detailed views easily ...
now records within the vector template type,
combined with
the std::function creates the view through dynamic visualization.
Because the
record format is usertyped always, only defaulted for std::string vectors
adapted by constructor. ie:
fname, string_view lname, string_view phone,
string_view email
*/
  view.appendChild<ul>(indexBy{"uniRec"}).data<uniRecord>() = {
      {"anthony", "matarazzo", "(666) 123-4567", "simple@sss.com"},
      {"kevin", "styemark", "222 333 4444", "kevin.styemark@sss.com"},
      {"brenda", "rollerbank", "222 333 4444", "brenda.rollerbank@sss.com"},
      {"cindy", "trustinalo", "222 333 4444", "cindy.trustinalo@sss.com"},
      {"samantha", "skapity", "(123) 457-8906", "samantha.skapity@sss.com"},
      {"Tony", "Mowkar", "(777) 765-4321", "zitapps@sss.com"},
      {"mark", "maglich", "(800) 869-1234", "mark@sss.com"},
      {"cyclemount.jpg", 33234, 0x994834},
      {"greybirds.jpg", 8877394, 0x7564774},
      {"grapefruit.jpg", 47764, 0x95785777},
      {"cantelope.jpg", 997787, 0x645654},
      {"bannana.jpg", 12217767, 0x77667844},
      {"apple.jpg", 2344, 0x676778534},
      {"orange.jpg", 5545, 0x99887},
      {"pineapple.jpg", 1346, 0x454567}};
  auto ulItems = getElement("uniRec");
  // transform lambda
  ulItems.dataTransform<li, uniRecord>(
      [](auto &o) -> auto & { return o.build(); });
  vector<uniRecord> vegetables = {{"Broccoli"},        {"Broccoli Rabe "},
                                  {"Brussel Sprouts"}, {"Cabbage, Green"},
                                  {"Cabbage, Red"},    {"Carrot"},
                                  {"Cassava"},         {"Cauliflower"}};
  auto vecItems = ulItems.data<uniRecord>();
  vecItems.insert(vecItems.end(), vegetables.begin(), vegetables.end());
  // takes info and induces the change.
  ulItems.dataHint<uniRecord>(vegetables.size());
  /*
then building complex user interfaces is more objected oriented, separated
from the data, and the data interface is the standard library.
*/
}
/*
These series of tests all provide the easiest most concise
building factory methods however at the cost of more parsed data.
Specifically using the C++ binary string literal interface.
Within the string format, appearing and communicating with
a based initializer list,

View manager object notation is a parsed input function prvoding
the ability to generate very complex dataTransform function for
the standard input. That is, at times lambda's of this sort may be
difficult to implement. Yet the syntax provides a templated mechnism
for building tree and event patterns which format the information within
the data<>.
*/
void test7h(Viewer &view) {
  /* A dataTransform is required when using the direct data interface.
By default, for simple types input into the model, a default exists.
However, in most cases, overriding the default format is necessary.
To compensate in the complexity of building large document fragments,
the system offers a dataTransform that may be described using a string.
The form is very simple, integrated within the same type of html and c++
style. This is the most compact form to use as well, it can achieve high
performance due to the creation.
The parameter is given as a string. The significance of the
first value enclosed within the paranthesis notes what "name" the main input
type is reffereed to as. This must be a container that supports std::get<#>.
Ends with a colon. Next is the markup document mapped to the value input
column (a tuple in this case). There are some inclusion of format
descriptors in form borrowed from python. However this form uses the
standard form %s and expands it. A nice time performance about this function
is that the information is parsed only once. The internal mechnism creates a
deep cloneabled object that can also reflect vectorized expansion during
build. Notice the ... expansion for tuple column 4. Formatting and gathering
of values from the tuple are iterative based upon index. The
function returned will contain the logic to build the tree from vectors. The
vectors will also contain the formatter object calls themselves. This will
make visualization much quicker as creation of the object, tree structure,
attributes, etc will be purely binary. So, small price - parse
at transform creation. Yet still using and not interuppting data flow, nor
decreasing the volumne of data the transform may handle.
This creates multiple expansion using the data interface. As well,
advanced formatting.
** adding an evaluator to the internal storage can provide
selection of different templates based on the item. Thereform, multiple
forms are given as input. The second form of the text template, provides the
ability to have the system evaluate which "text template" to use based upon
the boolean return of the given lambda.
https://docs.python.org/3/library/string.html#string-formatting
https://docs.python.org/3/library/string.html#formatspec
- control alignment using standard attributes,
https://en.wikipedia.org/wiki/Polymer_(library)
*/
  /* a record type such as this, containing dynamic children
can be described in the form :*/
  using tagInfo = std::tuple<int, std::string, float, std::string,
                             std::vector<std::tuple<std::string, float>>>;
  auto o = view.appendChild<ul>(indexBy{"music"});
  o.dataTransform<li, tagInfo>(
      R"( (t) :
<li>{t[0],%0xd}
	<ul>
	<li>{t[1],:20}</li>
	<li>{t[2]}</li>
	<li>{t[3]}</li>
	<li><table>
		<{t[4]...v, odd-even} tr>
		<td>{v[0], titlecap}</td>
		<td>{v[1], Currency}</td>
		</tr>
		</table></li>
	</ul>
</li>
)");
#if 0
 view.appendChild<ul>().data<tagInfo>() = {{0,
 "Anthony",
 134.5,
 "Horror films, science fiction",
 {{"Planet Crack Core", 7.0},
 {"Nachzehrer Fires PG", 43.4},
 {"Alien Spacecraft R+", 97.1},
 {"Jupiter Time Shift R", 64.3}}}};
#endif
  view.render();
}
/*
 The string form of the transform may be expanded further to increase
 application production speed. decisions, plugin necessity. This is
 merely a considerable technique that can be differentated from the draft
 approach. However as always, the operation of a system at a binary level as
 complete as possible does reduce complexity once inside of an embedded device
 such as a video card. While one may jump to conclusions about the complexity
 of such devices, their operation to make selective slot choices are the very
 component that creates advances as well as facilitates that speed boost.
 To start with the std::unordered_map to be accepted as a function slot choice
 machine, creates a great communication device for c++ programmers.
 However, in this device, nothing is ever copied, merely described in syntax.
 My next techniques for building interfaces lies within the very
 necessity of those concepts. Abstraction of data and format. An
 interesting type of mid and large application layout formula takes place
 during the maintenance stage. Most forms of these presentation factors
 are coded in easily changed components of differnt formatting possibilities
 plus data system logic support. Labels, consildated and easily matched
 through a long list of options. However this can become the bottle neck at
 times. So, the balance at times is considered, yet is specific enough that
 langauge and its operation capacity are questioned for these types of
 products. In effect one may say that these are the concepts of a complete
 system.
 So my next capacity of interface building relies on the strict data
 input interface, however also uses a condensor for functional attributes
 of gui interfaces. So most complex, most used, most pro would like
 something like this following:
*/
void test7i(Viewer &view) {
  /* dynamic or static. dynamic most likely...
These processors are very short for effeciveness. Typically, many
other things can occur for these states. This format allows these states
to exist, be automatically instaniated, maintained on a separate basis,
reduced, and defaulted. So defaulted must be handled as a case as well.
And a very robust secret of this type is how c++ programmers can
abstract these again into other captured data sets for just
modifing specific summaries based upon data these routines
may share with internal and exteral communication.
*/
  using processList = std::tuple<int, std::string, float, std::string>;
  view.appendChild<ul>(indexBy{"corp"}).data<processList>() = {
      {0, "favorites", 4.5, "Umbrella Corporation"},
      {1, "less", 7.5, "Sky blink jinks"},
      {2, "grand", 4.5, "No touch, no voice, giant fingers"},
      {3, "flavor", 5.5, "360 flyers"},
      {0, "color", 2.9, "unknown not found error"},
      {2, "magnetism", 8.3, "perhaps but much after quantium decays"},
      {1, "alertness", 3.7, "can monitor laughter pinches"}};
  auto o = getElement("corp");
#if 0
 o.dataTransform<0, processList>(
 {{0,
 [](processList &r) {
 return createElement<li>(
 textColor{"red"}, get<1>(r), get<2>(r), get<3>(r));
 }},
 {1,
 [](processList &r) {
 return createElement<li>(
 textColor{"green"}, get<1>(r), get<2>(r), get<3>(r));
 }},
 {2,
 [](processList &r) {
 return createElement<li>(
 textColor{"blue"}, get<1>(r), get<2>(r), get<3>(r));
 }},
 {3, [](processList &r) {
 return createElement<li>(
 textColor{"plum"}, get<1>(r), get<2>(r), get<3>(r));
 }}});
#endif
}
/*******************************************************************
My next thoughtre of a very nice ordered approach to classical
naturalism of information presentation. That is need for styling and
sizing comes about not only to classify, but to order, and to provide
longevity, weight, and exposure of information into the view. I found a
discussion of color to be quite elegant according to some concepts of web
design standards. Such as that which leave anyone a nomad concepting a design
from mere tid bits of broken data structures within most document object
models. These tasks may be derrived from extensions of the tools used for
normlization of base platform. The concept of the "information system"
is present within most designs. By specifing a type of color schema and
perhaps direct methods for manulipting it by function may be too assumptive in
the approach to how the application can be built. So perhaps further definition
of these typese of traits can be refined with more investigation after
the base framework is assembled.

A style sheet that can apply itself to a document by classifying terms
of information system to that of information structure name within the
document heirarchy. This is typical of how style and the cascade works.
One method is to provide binary labeled build up routines that accept
a reduced parameter set of the explicit information to set. This would
be an extension that also provides base interaction of more advanced gui
elements such that defining elegant operating and interactive style is
accomplished as a utility function. here are numerious examples that
pop to mind, yet I would like to leave them out for later to understand
how this new extension should work. And perhaps in that provide an
efficient and flexible way these methods can be passed along. It is
interesting once tools are available how others use them. I have seen some
very pleaseing web designs, and therefore the ability to apply that content
and layout apprach is important. XML and XSL are some solutions which compete
and apply this in a grand parsed manner.
 a. naming for these forms are more strict and therefore more
 natural and pleasing
 1. the names are more specific
 2. information at times may have to be defaulted because it is
large set a. this information such as documentation, corporate id, etc. b.
personel c. software promoting license d. etc.
 3. some may required storage resources and
 processes that run in the background
 a. all processes should be promoted
 b. storage requirements and reasons
 I see this direction as an after approach to refining the
library for specific types of uses.
--- a type of style guide for std integration
*******************************************************************/
//! [test8a]
void test8a(Viewer &vm) {
  testStart(__func__);
  auto dBook = vm.appendChild<DIV>(indexBy{"booklet5"});
  PARAGRAPH *pBooklet = nullptr;
  // a warning is issued which is what is required.
  // main.cpp:XXXXX: warning: format string is not a string
  // literal
  // [-Wformat-nonliteral]
  string s = "not literal";
  dBook.printf(s.c_str());
  dBook.printf("<div id=BookletParagraph>");
  dBook.printf("The paragraph content is here.");
  dBook.printf("<img id=imgData/>");
  dBook.printf("<ul id=chapterList>");
  for (int i = 0; i < 10; i++)
    dBook.printf("<li>Chapter List %i</li>", i);
  dBook.printf("</ul>");
  dBook.printf("</div>");
  vm.render();
}
//! [test8a]
/*******************************************************************
*******************************************************************/
//! [test8]
void test8(Viewer &vm) {
  testStart(__func__);
  int m = randomInt(5);
  auto dBook = vm.appendChild<DIV>(indexBy{"booklet5"});
  vm.render();
  // std::reference_wrapper<PARAGRAPH> Booklet;
  for (int i = 0; i < m; i++) {
    // this line is like putting :
    // pBooklet=
    // in textual tag
    // dBook.printf("%s", referenceTag(Booklet));
    dBook.printf("<p id=BookletParagraph_%i>", i);
    dBook.printf("The paragraph content is here.");
    dBook.printf(" <ul id=notes_%i>%s", i, "text content ul");
    dBook.printf(" <ul id=guestSpeaker_%i>%s</ul>", i,
                 "<blue>guest speaker information <black>... ");
    dBook.printf(" <ul id=references_%i>%s</ul>", i,
                 " <green>reference information: <black>... ");
    dBook.printf(" </ul>");
    dBook.printf("</p>");
    // Booklet.setAttribute(textColor{"red"});
  }
  vm.render();
}
//! [test8]
//! [test10]
void test10(Viewer &vm) {
  testStart(__func__);
  int m = randomInt(5);
  auto dBook = vm.appendChild<DIV>(indexBy{"booklet5"});
  vm.render();

  for (int i = 0; i < m; i++) {

    dBook << "<p id=BookletParagraph_" << i << ">"
          << "The paragraph content is here."
          << " <ul id=notes_" << i << ">text content ul"
          << "<ul id=guestSpeaker_" << i << ">"
          << "<blue>guest speaker information <black>... "
          << "</ul>"
          << "<ul id=references_" << i << ">"
          << "<green>reference information: <black>... "
          << "</ul>"
          << "</ul>"
          << "</p>";
#if 0
       /* rather than mixing the use of pointer withi nthe syntax, the stringPointTag syntax might offer complexity.
         document for the user of the library a query facility that implements the functionality.
         */
    auto Booklet = query("id=

    ->setAttribute(textColor{"red"});
#endif
  }
  vm.render();
}
//! [test10]
/************************************************************************
************************************************************************/
string_view randomString(int nChars) {
  unsigned int numChars =
      1u +
      (std::rand() / ((RAND_MAX + 1u) / static_cast<unsigned int>(nChars)));
  auto randchar = []() -> char {
    const char charset[] = "0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };
  string s1(numChars, 0);
  ;
  string_view str(s1);
  // std::generate_n(str.begin(), numChars, randchar);
  return str;
}
/************************************************************************
************************************************************************/
double randomDouble(double a, double b) {
  double ret =
      a + 1 +
      ((unsigned int)std::rand() / ((RAND_MAX + 1u) / static_cast<int>(b - a)));
  return ret;
}
/************************************************************************
************************************************************************/
int randomInt(int a) {
  int ret =
      1 + ((unsigned int)std::rand() / ((RAND_MAX + 1u) / static_cast<int>(a)));
  return ret;
}
/************************************************************************
************************************************************************/
void randomAttributeSettings(Element &e) {
  try {
    e.getAttribute<textIndent>().value = randomDouble(0.0, 10.5);
    e.getAttribute<objectTop>().value = randomDouble(0.0, 300);
    e.setAttribute(objectTop{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectLeft>().value = randomDouble(0.0, 300);
    e.setAttribute(objectLeft{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectWidth>().value = randomDouble(0.0, 300);
    e.setAttribute(objectWidth{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<objectHeight>().value = randomDouble(0.0, 300);
    e.setAttribute(
        objectHeight{randomDouble(0.0, 300), numericFormat::percent});
    e.getAttribute<textFace>().value = randomString(10);
    e.getAttribute<textWeight>().value = randomDouble(0.0, 1000.0);
    e.getAttribute<tabSize>().value = randomDouble(0.0, 10.0);
    e.getAttribute<focusIndex>().value = randomDouble(0.0, 1000.0);
    e.getAttribute<lineHeight>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingTop>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingBottom>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingLeft>().value = randomDouble(0.0, 20.0);
    e.getAttribute<paddingRight>().value = randomDouble(0.0, 20.0);
    e.getAttribute<marginTop>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginBottom>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginLeft>().value = randomDouble(0.0, 50.0);
    e.getAttribute<marginRight>().value = randomDouble(0.0, 50.0);
    e.getAttribute<borderWidth>().value = randomDouble(0.0, 50.0);
    e.getAttribute<borderRadius>().value = randomDouble(0.0, 10.5);
  } catch (const std::exception &e) {
    std::cout << " Exception: " << e.what() << "\n";
  }
}
