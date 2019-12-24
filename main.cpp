#include "viewManager.hpp"

using namespace std;
using namespace viewManager;

void test0(Viewer &vm);
void test0b(Viewer &vm);
void test0c(Viewer &vm);
void test0d(Viewer &vm);
void testUX(Viewer &vm);
void testUXmarkup(Viewer &vm);

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
#elif defined(_WIN64)

#endif
}

/****************************************************************************************************
***************************************************************************************************/
#if defined(__linux__)
int main(int argc, char **argv) {
  // handle command line here...
#elif defined(_WIN64)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /* hPrevInstance */,
                   LPSTR lpCmdLine, int /* nCmdShow */) {
  // command line
#endif

  // create the main window area. This may this is called a Viewer object.
  // The main browsing window. It is an element as well.
  auto &vm = createElement<Viewer>(
      windowTitle{"Examples"}, objectTop{10_pct}, objectLeft{10_pct},
      objectHeight{640_px}, objectWidth{800_px}, textFace{"arial"},
      textSize{16_pt}, textWeight{400}, textIndent{2_em}, lineHeight::normal,
      textAlignment::left, position::relative, paddingTop{5_pt},
      paddingLeft{5_pt}, paddingBottom{5_pt}, paddingRight{5_pt},
      marginTop{5_pt}, marginLeft{5_pt}, marginBottom{5_pt}, marginRight{5_pt});
#if 0
  test0(vm);
  test0c(vm);
#endif
  //test0(vm);
  //test0c(vm);
  //test0b(vm);
  test0d(vm);
#if 0
  testUX(vm);
  testUXmarkup(vm);
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
#endif
  /*
  test7d(vm);
  test7e(vm);
  test7f(vm);
  test7g(vm);
  test7h(vm);
  test7i(vm);
  */

#if 0
  test8(vm);
  test8a(vm);
  test10(vm);
#endif

  vm.processEvents();
}

string randomString(int nChars);
double randomDouble(double a, double b);
int randomInt(int a);
void randomAttributeSettings(Element &e);

/************************************************************************
************************************************************************/
void test0(Viewer &vm) {
  vm.ingestStream = true;
  vm << "<h1 textFace=arial textsize=30pt color=hotpink>Hello World, high "
        "yags</h1>";
  vm << "<h2 textFace=britannic color=darkgrey >Subearth low jumps</h2>";
  vm << "<p textcolor=orange>Got to be a pretty day upside and underneath.</p>";
  vm << "<p textcolor=blue>Yet sometimes when evil lerks, days may be more "
        "creative than usual.</p>";
  vm << "<p color=green>green</p><p color=lime>lime</p><p "
        "color=crimson>crimson</p>";
}

/************************************************************************
************************************************************************/
//! [test0]
void test0b(Viewer &vm) {
  testStart(__FUNCTION__);
  auto o = vm.getAttribute<objectWidth>();
  auto &e = createElement<DIV>(indexBy{"divTTT"}, textColor{"red"}, "test",
                               vector<float>{.3f, .6f, .3f, .777f, 10.33f});

  auto &appTitle =
      createElement<H1>(indexBy{"title"}, objectTop{10_px},
                        textAlignment::center, textColor{"orange"}, "Type XCB");

  e.appendChild(appTitle);
  e.appendChild<H2>(indexBy{"subTitle"}, textColor("midnightblue"),
                    display::in_line, textAlignment::center,
                    "An application for entering text");

  vm.appendChild(e);
  vm.appendChild<PARAGRAPH>(indexBy{"content"},
                            "The information must add two children");
  e.data() = {"This is replaced as a data node"};

  vm.appendChild("<div id=testAdd></div>");

  getElement("testAdd").appendChild("<ul>"
                                    "<li>test item 1</li>"
                                    "<li>test item 2</li>"
                                    "<li>test item 3</li>"
                                    "<li>test item 4</li>"
                                    "<li>test item 5</li></ul>");
  vm.appendChild<UX::text>();
}
/************************************************************************
************************************************************************/
//! [test0]
void test0c(Viewer &vm) {
  testStart(__FUNCTION__);

  vm.appendChild("<div id=testAdd>Test information inside</div>");
  vm.appendChild("<div id=markupSecond>The drive to complete is the sincere "
                 "satisfaction of a working system. While a solution is a "
                 "compromise, value is found within the description.</div>");

  getElement("testAdd").ingestStream = true;
  getElement("testAdd").appendChild("<ul>"
                                    "<li>test item 1</li>"
                                    "<li>test item 2</li>"
                                    "<li>test item 3</li>"
                                    "<li>test item 4</li>"
                                    "<li>test item 5</li></ul>");

  getElement("testAdd") << "This is information that is appended.";
}
//! [test0]
void test0d(Viewer &vm) {
  vm.ingestStream = true;

  vm.appendChild("<h1 color=orange>Layout Manager</h1>");
  
  vm.appendChild("<div inline width=250px id=markupSecond>The drive to complete is the sincere "
                 "satisfaction of a working system. While a solution is a "
                 "compromise, value is found within the description.</div>");


  vm << "<p>Does mixing the objects still calculate appropiately. I "
        "believe the logic would work since they are separate elements."
        "Yet information is trampled upon. It is like the y pen position"
        " is not being incremented at the appropiate positions."
        "Perhaps this is true since the appearance is that way."
        "Ahh to discover the options, and the breakages."
        "The other problem with the layout is that the "
        "resizing to a small tollerance beyond the size of the smallest wrap"
        " object causes a freeze. The previous problem described has been fixed.</p>";
  vm << "<p>Second block of information might appear where?</p>";
  #if 0
  vm << "<div width=50%><h2 color=midnightblue>Quality Description</h2>";
  vm << "<p textsize=16pt color=darkgreen>Several bugs still exist and new feature "
        "logic will have to be "
        "added. Such as the calculation of spacing of the left side being greater."
        "When the left side height is greater than the right, the layout manager "
        "should move the rendering down to the next layer. This may involve "
        " searching. However the best way to solve the issue is to remember "
        " the value. Then when changing between inline to block again, the "
        "block level element should be set to the greatest y2 value thus "
        "developed.</p></div>";
  vm << "<div width=50% inline><h2 color=red>Bugs</h2>";
  vm << "<ul>"
        "<li></li>"
        "<li>The font height is incorrect somehow. FIXED</li>"
        "<li>Adding inline to the paragraph produces incorrect results. Meaning that the height is not gathered. </li>"
        "<li>Many layout features to debug.</li>"
        "<li>The dots do not draw yet...</li>"
        "<li>It locks up when the resizing. FIXED</li>"
        "<li>mixing data nodes and other elements seems quirky.</li></ul></div>";
  vm.appendChild<ul>().appendChild<li>("one").append<li>("two").append<li>("three");
  #endif

}

/************************************************************************
************************************************************************/
//! [testUX]
void testUX(Viewer &vm) {
  testStart(__FUNCTION__);

  vm.appendChild<UX::text>(indexBy{"idName"}, "Anthony");

  vm.appendChild<UX::password>(indexBy{"idPassword"}, "password");

  vm.appendChild<UX::multiline>(indexBy{"idMultiline"},
                                "Paragraph of informtion");

  vm.appendChild<UX::number>(indexBy{"idNumber"}, 3);

  vm.appendChild<UX::masked>(indexBy{"idMasked"}, "###.##");

  vm.appendChild<UX::pushButton>(indexBy{"idpushButton"}, "OK");

  vm.appendChild<UX::radioButton>(indexBy{"idradioButton"}, true);

  vm.appendChild<UX::hotImage>(indexBy{"idHotImage"}, "rays.scn");

  vm.appendChild<UX::group>(indexBy{"idGroup"}, "Title");

  vm.appendChild<UX::checkBox>(indexBy{"idCheckBox"}, true);

  vm.appendChild<UX::date>(indexBy{"idDate"}, "12/1/98");

  vm.appendChild<UX::dateTime>(indexBy{"idDateTime"}, "12/1/98 12:00:12am");

  vm.appendChild<UX::week>(indexBy{"idWeek"}, 23);

  vm.appendChild<UX::time>(indexBy{"idTime"}, "12:00:12am");

  vm.appendChild<UX::file>(indexBy{"idFile"}, "c:\\test.txt");

  vm.appendChild<UX::verticalScrollbar>(indexBy{"idVerticalScrollbar"}, 10);

  vm.appendChild<UX::horizontalScrollbar>(indexBy{"idHorizontalScrollbar"}, 10);

  vm.appendChild<UX::resizerVertical>(indexBy{"idResizerVertical"}, 10);

  vm.appendChild<UX::resizerHorizontal>(indexBy{"idResizerHorizontal"}, 10);

  vm.appendChild<UX::listSelector>(indexBy{"idListSelector"}).data() = {
      "option a", "option b", "option c"};

  vm.appendChild<UX::menu>(indexBy{"idMenu"}, "&File");

  vm.appendChild<UX::gridEdit>(indexBy{"idGridEdit"})
      .data<tuple<int, int, int>>() = {{10, 4, 5}, {5, 3, 2}};

  vm.appendChild<UX::tabbedPanel>(indexBy{"idTabbedPanel"}).data() = {
      "tab a", "tab b", "tab c"};

  vm.appendChild<UX::sliderRange>(indexBy{"idSliderRange"}).data<int>() = {0,
                                                                           100};

  vm.appendChild<UX::knobRange>(indexBy{"idKnobRange"}).data<int>() = {0, 100};

  vm.appendChild<UX::accordion>(indexBy{"idAccordion"}).data() = {
      "tab a", "tab b", "tab c"};

  vm.appendChild<UX::progress>(indexBy{"idProgress"}, .5);

  vm.appendChild<UX::dialog>(indexBy{"idDialog"}, "Dialog Window");
}
//! [testUX]

//! [testUXmarkup]
void testUXmarkup(Viewer &vm) {
  testStart(__FUNCTION__);
  vm.appendChild("<text id=txtFname>Anthony</text>"

                 "<password>guest</password>"

                 "<multiline>Pragraph of information</multiline>"

                 "<number>10.4</number>"

                 "<masked></masked>"

                 "<pushButton>OK</pushButton>"

                 "<group>"
                 "<radioButton>option a</radioButton>"
                 "<radioButton>option b</radioButton>"
                 "<radioButton>option c</radioButton>"
                 "<radioButton>option d</radioButton>"
                 "</group>"

                 "<hotImage>raytrace01.scene</hotImage>"

                 "<checkBox>Option a</checkBox>"

                 "<date>12/1/19</date>"

                 "<dateTime>12-1-19 12.30:10am </dateTime>"
                 "<week>52</week>"
                 "<time>12:30am</time>"
                 "<file>c:\\test.txt</file>"
                 "<verticalScrollbar>20</verticalScrollbar>"
                 "<horizontalScrollbar>20</horizontalScrollbar>"
                 "<resizerVertical>10</resizerVertical>"
                 "<resizerHorizontal>10</resizerHorizontal>"

                 "<listSelector></listSelector>"
                 "<menu></menu>"
                 "<gridEdit></gridEdit>"
                 "<tabbedPanel></tabbedPanel>"
                 "<sliderRange></sliderRange>"
                 "<knobRange></knobRange>"
                 "<accordion></accordion>"
                 "<progress></progress>"
                 "<dialog></dialog>");
}
//! [testUXmarkup]

/************************************************************************
************************************************************************/
//! [test1]
void test1(Viewer &vm) {
  testStart(__FUNCTION__);
  auto &mainArea = createElement<DIV>(
      indexBy{"mainArea"}, objectTop{10_pct}, objectLeft{10_pct},
      objectWidth{90_pct}, objectHeight{90_pct}, textColor{50, 50, 50},
      background{100, 200, 200}, textFace{"FiraMono-Regular"}, textSize{20_pt},
      textWeight{400});
  auto &appTitle = createElement<H1>(indexBy{"title"}, objectTop{10_px},
                                     textAlignment::center, "Type XCB");
  auto &appSubTitle =
      createElement<H2>(indexBy{"subtitle"}, objectTop{10_px},
                        textAlignment::center, "A starter testing Application");
  appTitle.setAttribute(objectTop{20_percent});

  // setting the data property directly.
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

  for (auto n : query("*")) {
  }
  getElement("title").data() = {
      "It uses the reference to the created object createElement."};

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

  getElement("mainArea").setAttribute(textColor{70, 70, 70});
  getElement("mainArea").setAttribute(objectLeft{100_px});
  getElement("title")
      .setAttribute(objectLeft{100_px}, "The Visualizer")
      .data() = {"Mini App Title"};
  getElement("bodyText").setAttribute(indexBy{"bodyInformation"}).data() = {
      "The new text information is not quite as long"};

  auto &statusText =
      createElement<H3>(indexBy{"statusText"}, "Status Line Updated:");
  mainArea.insertBefore(statusText, getElement("bodyInformation"));

  mainArea.insertAfter(
      createElement<H1>(indexBy{"titleText2"}, "A app built with gui tags."),
      getElement("bodyInformation"));
  mainArea.removeChild(getElement("bodyInformation"));

  getElement("mainArea")
      .appendChild<PARAGRAPH>(indexBy{"bodyText"}, textColor{"orange"},
                              "Re added and updated. Scatered coverered "
                              "diced and smashed.");
  mainArea.replaceChild(
      createElement<paragraph>(indexBy{"bodyTextNew"}, textColor{"green"},
                               "And now, for a limited time. the all new ... "),
      getElement("bodyText"));
  mainArea.insertAfter(
      createElement<paragraph>(indexBy{"afterInsert"}, textColor{"red"},
                               "new item added after the child"),
      getElement("bodyTextNew"));

  if (mainArea.parent())
    mainArea.data() = {"Hey attached to another container."};

  // walk children
  auto n = mainArea.firstChild();
  while (n) {
    n = n->get().nextSibling();
  }

  for (auto n = mainArea.firstChild(); n; n = n->get().nextSibling()) {
  }

  for (auto &n : mainArea.children()) {
  }

  /**
  Attributes and References
  -------------------------

  to quickly change attribute values wihin the dom
  you can get a reference to the actual value stored within the tree. this is
  accomplished using the getAttribute function. You must specify the reference
  operator. The first parameter is the attribute name you wish to get. The
  second is the format of the characteristic. At most time, the first one is the
  one that is commonly used. However, most attributes contain a format specifier
  or other characteristics associated with the attribute. To provide efficient
  usage, the second parameter is the type of the characteristic. The type is is
  defaulted to double. That is, the common characteristic type is a double
  storage type. IE, objectLeft, marginTop

  */

  // must use set to invoke indexing of elementById
  auto &[idRefText] = mainArea.getAttribute<indexBy>();
  idRefText = "mainAreaidView";
  mainArea.setAttribute(indexBy{idRefText});

  // get the actual reference of the memory
  auto &[d, opt] = mainArea.getAttribute<objectLeft>();
  d = 900;

  auto &d2 = mainArea.getAttribute<objectLeft>();
  d2.option = numericFormat::percent;
  d2.value = 50;

  // styles and CSS
  auto &boldTexts = createStyle(
      indexBy{"boldText"}, textColor{"green"}, background{100, 200, 200},
      textFace{"FiraMono-Regular"}, textSize{20_pt}, textWeight{800});

  mainArea.styles.push_back(boldTexts);
  appSubTitle.styles.push_back(boldTexts);
}
//! [test1]
//! [test1a]
void test1a(Viewer &vm) {
  testStart(__FUNCTION__);
  ElementList chapter;
  int m = randomInt(5);
  // notice here that the createElement is not chained because a reference
  // is being attained to the element. Because of the way chaining works,
  // this must be a single function so that the correct reference is
  // computed.
  for (int i = 0; i < m; i++) {
    auto &info = createElement<paragraph>(
        indexBy{"rndTEST3BookletParagraph_" + to_string(i)},
        vector<string>{randomString(200), randomString(200),
                       randomString(200)});
    info.appendChild<ul>(
        indexBy{"idbikes"},
        vector<string>{"Huffy", "Schwinn", "Giant", "Road Master"});
    chapter.push_back(info);
  }
  auto &booklet = createElement<dblock>(indexBy{"booklet3"});
  vm.appendChild(booklet);
  booklet.appendChild(chapter);
}
//! [test1a]
/************************************************************************
************************************************************************/
//! [test2]
void test2(Viewer &vm) {
  testStart(__FUNCTION__);
  for (int i = 0; i < randomInt(5); i++) {
    auto &information = createElement<DIV>(indexBy{"rndDIV_" + to_string(i)});
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
}
//! [test2]
/************************************************************************
************************************************************************/
//! [test3]
void test3(Viewer &vm) {
  testStart(__FUNCTION__);

  ElementList chapter;
  int m = randomInt(5);
  for (int i = 0; i < m; i++) {
    chapter.push_back(createElement<PARAGRAPH>(
        indexBy{"rndTEST3BookletParagraph_" + to_string(i)},
        randomString(200)));
  }
  auto &booklet = createElement<DIV>(indexBy{"booklet3"});
  vm.appendChild(booklet);
  booklet.appendChild(chapter);
}
//! [test3]
//! [test4]
void test4(Viewer &vm) {
  testStart(__FUNCTION__);

  int m = randomInt(5);
  Element &eBooklet = vm.appendChild<DIV>(indexBy{"booklet4"});
  for (int i = 0; i < m; i++)
    eBooklet.appendChild<PARAGRAPH>(
        indexBy{"rndTEST4BookletParagraph_" + to_string(i)}, randomString(200));
}
//! [test4]
//! [test5]
void test5(Viewer &vm) {
  testStart(__FUNCTION__);

  ElementList chapter;
  int m = randomInt(5);
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
  vm.appendChild<DIV>(indexBy{"booklet5"}).appendChild(chapter);
}
//! [test5]
/************************************************************************
************************************************************************/
//! [test6]
void test6(Viewer &vm) {
  testStart(__FUNCTION__);

  ElementList chapter;
  int m = randomInt(5);
  for (int i = 0; i < m; i++) {
    auto &e = createElement<PARAGRAPH>(
        indexBy{"rndTEST5BookletParagraph_" + to_string(i)});

    e << "Hello "
      << "anthony"
      << "can you do the []";

    e.appendChild<UL>(
         indexBy{"bookletNotes_" + to_string(i)},
         vector<string>{"Endurance training", "Biking", "Meals", "Schedule"})
        .append<UL>(indexBy{"guestCompanies_" + to_string(i)},
                    vector<pair<int, string>>{{0, "Gyms"},
                                              {1, "Gold's Gym"},
                                              {1, "Core Fitness"},
                                              {1, "Tommy Doright's"},
                                              {0, "Tools"},
                                              {1, "Huffy"},
                                              {1, "Scwitchers"},
                                              {1, "Clock Down Industrials"}})
        .append<UL>(indexBy{"bookletReferences_" + to_string(i)},
                    vector<string>{"The 26inch Road", "Flatters Chain",
                                   "Wheelers and Handlebars",
                                   "Rim's n Chains"});
    chapter.push_back(e);
  }

  vm.appendChild<DIV>(indexBy{"booklet5"}).appendChild(chapter);
}
//! [test6]
/************************************************************************
************************************************************************/
//! [test7]
void test7(Viewer &vm) {
  testStart(__FUNCTION__);

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
}
//! [test7]
//! [test7a]
void test7a(Viewer &vm) {
  testStart(__FUNCTION__);

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
      .append("<li indexBy=ttt></li>");
}
//! [test7a]
//! [test7b]
void test7b(Viewer &vm) {
  testStart(__FUNCTION__);

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
  divTest.appendChild("<ul></ul>")
      .appendChild("<li>test1</li>")
      .append("<li>test2</li>")
      .append("<li>test3</li>")
      .append("<li>test4</li>");
}
//! [test7b]
//! [test7c]
void test7c(Viewer &vm) {
  testStart(__FUNCTION__);

  auto &divTest = vm.appendChild<DIV>(indexBy{"testAnother"});
  // the append and appendChild with texts.
  divTest.appendChild("<ul></ul>")
      .appendChild("<li>test1</li>")
      .append("<li>test2</li>")
      .append("<li>test3</li>")
      .append("<li>test4</li>");
  divTest.append("<ul><li>Hello added to the end</li></ul>");
  divTest.appendChild("<p>Just adhoc dom building.</p>");
}
//! [test7d]
void test7d(Viewer &vm) {
  testStart(__FUNCTION__);

  auto &divTest = vm.appendChild<DIV>(indexBy{"testAnother"});
  // the append and appendChild with texts.
  divTest.appendChild("<ul></ul>").data() = {"2222", "3333", "444", "6.66",
                                             "7"};
  divTest.appendChild<ul>().data<double>() = {1, 4, 5, 3, 4, 4, 4, 33, 4, 5};
  divTest.appendChild<ul>().data<pair<int, string>>() = {
      {0, "AC/DC"},
      {1, "Hell's Bells"},
      {1, "You Shook Me All Night Long"},
      {1, "Have a Drink on Me"},
      {1, "Squeeler"},
      {0, "Books"},
      {1, "Yada yada yada"}};
  divTest.appendChild("<list></list>").data() = {
      "option a", "option b", "option c", "option d", "option e"};
  divTest.append("<ul><li>Hello added to the end</li></ul>");
  divTest.appendChild<paragraph>().data() = {"fdff", "fdfdfdf", "Yttyty",
                                             "ghhhht"};
}

void test7e(Viewer &view) {
  auto &tblCost = createElement<TABLE>(
      objectLeft{10_pct}, objectTop{10_pct}, objectWidth{80_pct},
      objectHeight{80_pct},
      tableColumns{
          {"Name", "Employment Start", "Salary", "Sales", "Cost Ratio"}},
      tableData{{"Anthony", "1/1/15", "10.75", "34.16", "4.5 +"},
                {"Candy", "4/16/12", "12.75", "4464.76", "35017.2 +"},
                {"Alvin", "1/1/65", "4.75", "125.16", "2634.9 +"}});
  /// tblCost.edit(1,4);
}
void test7f(Viewer &view) {
  // build a fancy <ul> list with <li> children consisting
  // of varying details...
  static array<string, 3> sIconNames = {"base.raw", "contentIcon.raw",
                                        "normal.raw"};
  // dataAdaptor
  using tagInfo = tuple<int, string, float>;
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
  auto &urecords = getElement(idRecords);
  auto &recordPlex = urecords.data<tagInfo>();
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

  // formatting lambda
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
  auto &ulRecords = getElement(idRecords);
  auto &recordPlex2 = ulRecords.data<tagInfo>();
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
    uniRecord(const string &broadName) {}
    uniRecord(const string &fname, const string &lname, const string &phone,
              const string &email) {
      schema = contact;
    };
    uniRecord(const string &_fileName, const size_t &fileSizeKiloByte,
              const size_t &indexPreviewKey) {
      schema = filelist;
    };
    uniRecord(const string &fname, const string &format, const int &depth,
              const tuple<double, double, double> gps,
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

  auto &ulItems = getElement("uniRec");

  ulItems.dataTransform<li, uniRecord>(
      [](auto &o) -> auto & { return o.build(); });

  vector<uniRecord> vegetables = {{"Broccoli"},        {"Broccoli Rabe "},
                                  {"Brussel Sprouts"}, {"Cabbage, Green"},
                                  {"Cabbage, Red"},    {"Carrot"},
                                  {"Cassava"},         {"Cauliflower"}};
  auto &vecItems = ulItems.data<uniRecord>();
  vecItems.insert(vecItems.end(), vegetables.begin(), vegetables.end());
  // takes info and induces the change.
  ulItems.dataHint<uniRecord>(vegetables.size());
}

void test7h(Viewer &view) {
  /* a record type such as this, containing dynamic children
can be described in the form :*/
  using tagInfo = std::tuple<int, std::string, float, std::string,
                             std::vector<std::pair<std::string, float>>>;
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

  view.appendChild<ul>().data<tagInfo>() = {{0,
                                             "Anthony",
                                             134.5,
                                             "Horror films, science fiction",
                                             {{"Planet Crack Core", 7.0},
                                              {"Nachzehrer Fires PG", 43.4},
                                              {"Alien Spacecraft R+", 97.1},
                                              {"Jupiter Time Shift R", 64.3}}}};
}

void test7i(Viewer &view) {
  using processList = std::tuple<int, std::string, float, std::string>;
  view.appendChild<ul>(indexBy{"corp"}).data<processList>() = {
      {0, "favorites", 4.5, "Umbrella Corporation"},
      {1, "less", 7.5, "Sky blink jinks"},
      {2, "grand", 4.5, "No touch, no voice, giant fingers"},
      {3, "flavor", 5.5, "360 flyers"},
      {0, "color", 2.9, "unknown not found error"},
      {2, "magnetism", 8.3, "perhaps but much after quantium decays"},
      {1, "alertness", 3.7, "can monitor laughter pinches"}};
  auto &o = getElement("corp");

  o.dataTransform<0, processList>(
      {{0,
        [](processList &r) -> Element & {
          stringstream ss;
          ss << get<1>(r) << " " << get<2>(r) << " " << get<3>(r);
          return createElement<li>(textColor{"red"}, ss.str());
        }},
       {1,
        [](processList &r) -> Element & {
          stringstream ss;
          ss << get<1>(r) << " " << get<2>(r) << " " << get<3>(r);
          return createElement<li>(textColor{"green"}, ss.str());
        }},
       {2,
        [](processList &r) -> Element & {
          stringstream ss;
          ss << get<1>(r) << " " << get<2>(r) << " " << get<3>(r);
          return createElement<li>(textColor{"blue"}, ss.str());
        }},
       {3, [](processList &r) -> Element & {
          stringstream ss;
          ss << get<1>(r) << " " << get<2>(r) << " " << get<3>(r);
          return createElement<li>(textColor{"plum"}, ss.str());
        }}});
}

//! [test8a]
void test8a(Viewer &vm) {
  testStart(__FUNCTION__);

  auto &dBook = vm.appendChild<DIV>(indexBy{"booklet5_t8a"});
  PARAGRAPH *pBooklet = nullptr;
  // a warning is issued which is what is required.
  // main.cpp:XXXXX: warning: format string is not a string
  // literal
  // [-Wformat-nonliteral]
  string s = "not literal";
  dBook.ingestStream = true;
  dBook.printf(s.c_str());
  dBook.printf("<div id=BookletParagraph_8a>");
  dBook.printf("The paragraph content is here.");
  // dBook.printf("<img id=imgData/>");
  dBook.printf("<ul id=chapterList_t8a>");
  for (int i = 0; i < 10; i++)
    dBook.printf("<li>Chapter List %i</li>", i);
  dBook.printf("</ul>");
  dBook.printf("</div>");
}
//! [test8a]
/*******************************************************************
*******************************************************************/
//! [test8]
void test8(Viewer &vm) {
  testStart(__FUNCTION__);

  int m = randomInt(5);
  auto &dBook = vm.appendChild<DIV>(indexBy{"booklet5_t8"});
  dBook.ingestStream = true;

  for (int i = 0; i < m; i++) {
    string sID = "BookletParagraph_t8_" + to_string(i);
    dBook.printf("<p id=%s>", sID.data());
    dBook.printf("The paragraph content is here.");
    dBook.printf(" <ul id=notes_t8_%i>%s", i, "text content ul");
    dBook.printf(" <ul id=guestSpeaker_t8_%i>%s</ul>", i,
                 "guest speaker information ... ");
    dBook.printf(" <ul id=references_t8_%i>%s</ul>", i,
                 " reference information: ... ");
    dBook.printf(" </ul>");
    dBook.printf("</p>");
    getElement(sID).setAttribute(textColor{"red"});
  }
}
//! [test8]
//! [test10]
void test10(Viewer &vm) {
  testStart(__FUNCTION__);

  int m = randomInt(5);
  auto &dBook = vm.appendChild<DIV>(indexBy{"booklet5_t10"});
  dBook.ingestStream = true;

  for (int i = 0; i < m; i++) {
    string sID = "BookletParagraph_t10_" + to_string(i);
    dBook << "<p id=" << sID << ">"
          << "The paragraph content is here."
          << " <ul id=notes_t10_" << i << ">text content ul"
          << "<ul id=guestSpeaker_t10_" << i << ">"
          << "guest speaker information ... "
          << "</ul>"
          << "<ul id=references_t10_" << i << ">"
          << "reference information: ... "
          << "</ul>"
          << "</ul>"
          << "</p>";
    getElement(sID).setAttribute(textColor{"plum"});
  }
}
//! [test10]
/************************************************************************
************************************************************************/
string randomString(int nChars) {
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

  string str(s1);
  std::generate_n(std::back_inserter(str), numChars, randchar);
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
    // std::cout << " Exception: " << e.what() << "\n";
  }
}
