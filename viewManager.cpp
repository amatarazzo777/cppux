/// <file>viewManagement.cpp</file>
/// <author>Anthony Matarazzo</author>
/// <date>6/16/18</date>
/// <version>1.0</version>
///
/// <summary>class that implements that main creation interface.
/// The file contains initialization, termination.</summary>
///
#include "viewManager.hpp"
#include <sys/types.h>

using namespace std;
using namespace viewManager;

/**********
These namespace global lists contain the objects as a system ownership.
********/
std::vector<std::unique_ptr<Element>> viewManager::elements;
std::unordered_map<std::string, std::reference_wrapper<Element>>
    viewManager::indexedElements;
std::vector<std::unique_ptr<StyleClass>> viewManager::styles;

/*

The objectFactoryMap provides an easy to maintain table of document
entities. The syntax, for consilidation, uses the macros CREATE_OBJECT
and CREATE_OBJECT_ALIAS. These macros expand to a string and a lambda
function which calls the createElement document api. The function
returns the newly created element. The table is used by the
parser to instianiate document elements.

*/
const factoryMap viewManager::objectFactoryMap = {
    CREATE_OBJECT(BR),        CREATE_OBJECT(H1),
    CREATE_OBJECT(H2),        CREATE_OBJECT(H3),
    CREATE_OBJECT(PARAGRAPH), CREATE_OBJECT_ALIAS(P, PARAGRAPH),
    CREATE_OBJECT(DIV),       CREATE_OBJECT(SPAN),
    CREATE_OBJECT(UL),        CREATE_OBJECT(OL),
    CREATE_OBJECT(LI),        CREATE_OBJECT(MENU),
    CREATE_OBJECT(UX),        CREATE_OBJECT(IMAGE)};

// clang-format off

/*
The attribtueStringMap provides a lookup table for
lower case attributes and aliases of an attribute.
The second map storage is a lambda function which
sets the specific attribute. The lambda accepts to parameters,
the base element for which to set the attribute on and
the string value of the setting. It should be noted that the
attribute objects themselves parse the input parameter where needed.
*/
const attributeStringMap
    viewManager::attributeFactory = {
    {"id",
        [](Element &e, string s) {
            e.setAttribute(indexBy{s});
        }
    },

    {"indexby",
        [](Element &e, string s) {
            e.setAttribute(indexBy{s});
        }
    },

    {"block",
        [](Element &e, string s) {
            e.setAttribute(display::block);
        }
    },

    {"inline",
        [](Element &e, string s) {
            e.setAttribute(display::in_line);
        }
    },

    {"hidden",
        [](Element &e, string s) {
            e.setAttribute(display::none);
        }
    },

    {"display",
        [](Element &e, string s) {
            e.setAttribute(display{s});
        }
    },

    {"absolute",
        [](Element &e, string s) {
            e.setAttribute(position::absolute);
        }
    },

    {"relative",
        [](Element &e, string s) {
            e.setAttribute(position::relative);
        }
    },

    {"position",
        [](Element &e, string s) {
            e.setAttribute(position{s});
        }
    },

    {"objecttop",
        [](Element &e, string s) {
            e.setAttribute(objectTop{doubleNF(s)});
        }
    },

    {"top",
        [](Element &e, string s) {
            e.setAttribute(objectTop{doubleNF(s)});
        }
    },

    {"objectleft",
        [](Element &e, string s) {
            e.setAttribute(objectLeft{doubleNF(s)});
        }
    },

    {"left",
        [](Element &e, string s) {
            e.setAttribute(objectLeft{doubleNF(s)});
        }
    },

    {"objectheight",
        [](Element &e, string s) {
            e.setAttribute(objectHeight{doubleNF(s)});
        }
    },

    {"height",
        [](Element &e, string s) {
            e.setAttribute(objectHeight{doubleNF(s)});
        }
    },

    {"objectwidth",
        [](Element &e, string s) {
            e.setAttribute(objectWidth{doubleNF(s)});
        }
    },

    {"width",
        [](Element &e, string s) {
            e.setAttribute(objectWidth{doubleNF(s)});
        }
    },

    {"coordinates",
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(objectTop{std::get<0>(coords)});
            e.setAttribute(objectLeft{std::get<1>(coords)});
            e.setAttribute(objectHeight{std::get<2>(coords)});
            e.setAttribute(objectWidth{std::get<3>(coords)});
        }
    },


    {"scrolltop",
        [](Element &e, string s) {
            e.setAttribute(scrollTop{doubleNF(s)});
        }
    },

    {"scrollleft",
        [](Element &e, string s) {
            e.setAttribute(scrollLeft{doubleNF(s)});
        }
    },

    {"background",
        [](Element &e, string s) {
            e.setAttribute(background{colorNF(s)});
        }
    },

    {"opacity",
        [](Element &e, string s) {
            e.setAttribute(opacity{s});
        }
    },

    {"textface",
        [](Element &e, string s) {
            e.setAttribute(textFace{s});
        }
    },

    {"textsize",
        [](Element &e, string s) {
            e.setAttribute(textSize{doubleNF(s)});
        }
    },

    {"textweight",
        [](Element &e, string s) {
            e.setAttribute(textWeight{s});
        }
    },

    {"textcolor",
        [](Element &e, string s) {
            e.setAttribute(textColor{colorNF(s)});
        }
    },

    {"textalignment",
        [](Element &e, string s) {
            e.setAttribute(textAlignment{s});
        }
    },

    {"left",
        [](Element &e, string s) {
            e.setAttribute(textAlignment::left);
        }
    },
    {"center",
        [](Element &e, string s) {
            e.setAttribute(textAlignment::center);
        }
    },
    {"right",
        [](Element &e, string s) {
            e.setAttribute(textAlignment::right);
        }
    },
    {"justified",
        [](Element &e, string s) {
            e.setAttribute(textAlignment::justified);
        }
    },


    {"textindent",
        [](Element &e, string s) {
            e.setAttribute(textIndent{doubleNF(s)});
        }
    },


    {"tabsize",
        [](Element &e, string s) {
            e.setAttribute(tabSize{doubleNF(s)});
        }
    },

    {"lineheight",
        [](Element &e, string s) {
            e.setAttribute(lineHeight{s});
        }
    },

    {"normal",
        [](Element &e, string s) {
            e.setAttribute(lineHeight::normal);
        }
    },

    {"numeric",
        [](Element &e, string s) {
            e.setAttribute(lineHeight::numeric);
        }
    },


    {"margintop",
        [](Element &e, string s) {
            e.setAttribute(marginTop{doubleNF(s)});
        }
    },

    {"marginleft",
        [](Element &e, string s) {
            e.setAttribute(marginLeft{doubleNF(s)});
        }
    },

    {"marginbottom",
        [](Element &e, string s) {
            e.setAttribute(marginBottom{doubleNF(s)});
        }
    },

    {"marginright",
        [](Element &e, string s) {
            e.setAttribute(marginRight{doubleNF(s)});
        }
    },

    {"margin",
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(marginTop{std::get<0>(coords)});
            e.setAttribute(marginLeft{std::get<1>(coords)});
            e.setAttribute(marginBottom{std::get<2>(coords)});
            e.setAttribute(marginRight{std::get<3>(coords)});
        }
    },

    {"paddingtop",
        [](Element &e, string s) {
            e.setAttribute(paddingTop{doubleNF(s)});
        }
    },

    {"paddingleft",
        [](Element &e, string s) {
            e.setAttribute(paddingLeft{doubleNF(s)});
        }
    },

    {"paddingbottom",
        [](Element &e, string s) {
            e.setAttribute(paddingBottom{doubleNF(s)});
        }
    },

    {"paddingright",
        [](Element &e, string s) {
            e.setAttribute(paddingRight{doubleNF(s)});
        }
    },

    {"padding",
        [](Element &e, string s) {
            auto coords=parseQuadCoordinates(s);

            e.setAttribute(paddingTop{std::get<0>(coords)});
            e.setAttribute(paddingLeft{std::get<1>(coords)});
            e.setAttribute(paddingBottom{std::get<2>(coords)});
            e.setAttribute(paddingRight{std::get<3>(coords)});
        }
    },

    {"borderstyle",
        [](Element &e, string s) {
            e.setAttribute(borderStyle{s});
        }
    },

    {"borderwidth",
        [](Element &e, string s) {
            e.setAttribute(borderWidth{doubleNF(s)});
        }
    },

    {"bordercolor",
        [](Element &e, string s) {
            e.setAttribute(borderColor{colorNF(s)});
        }
    },

    {"borderradius",
        [](Element &e, string s) {
            e.setAttribute(borderRadius{s});
        }
    },

    {"focusindex",
        [](Element &e, string s) {
            e.setAttribute(focusIndex{s});
        }
    },

    {"zindex",
        [](Element &e, string s) {
            e.setAttribute(zIndex{s});
        }
    },

    {"liststyletype",
        [](Element &e, string s) {
            e.setAttribute(listStyleType{s});
        }
    }};

// color names from https://www.w3schools.com/colors/colors_names.asp
const colorMap colorNF::colorFactory = {
    { "aliceblue", 0xF0F8FF },      { "antiquewhite", 0xFAEBD7 },   { "aqua", 0x00FFFF },
    { "aquamarine", 0x7FFFD4 },     { "azure", 0xF0FFFF },          { "beige", 0xF5F5DC },
    { "bisque", 0xFFE4C4 },         { "black", 0x000000 },          { "blanchedalmond", 0xFFEBCD },
    { "blue", 0x0000FF },           { "blueviolet", 0x8A2BE2 },     { "brown", 0xA52A2A },
    { "burlyWood", 0xDEB887 },      { "cadetblue", 0x5F9EA0 },      { "chartreuse", 0x7FFF00 },
    { "chocolate", 0xD2691E },      { "coral", 0xFF7F50 },          { "cornflowerblue", 0x6495ED },
    { "cornsilk", 0xFFF8DC },       { "crimson", 0xDC143C },        { "cyan", 0x00FFFF },
    { "darkblue", 0x00008B },       { "darkcyan", 0x008B8B },       { "darkgoldenrod", 0xB8860B },
    { "darkgray", 0xA9A9A9 },       { "darkgrey", 0xA9A9A9 },       { "darkgreen", 0x006400 },
    { "darkkhaki", 0xBDB76B },      { "darkmagenta", 0x8B008B },    { "darkolivegreen", 0x556B2F },
    { "darkorange", 0xFF8C00 },     { "darkorchid", 0x9932CC },     { "darkred", 0x8B0000 },
    { "darksalmon", 0xE9967A },     { "darkseagreen", 0x8FBC8F },   { "darkslateblue", 0x483D8B },
    { "darkslategray", 0x2F4F4F },  { "darkslategrey", 0x2F4F4F },  { "darkturquoise", 0x00CED1 },
    { "darkviolet", 0x9400D3 },     { "deeppink", 0xFF1493 },       { "deepskyblue", 0x00BFFF },
    { "dimgray", 0x696969 },        { "dimgrey", 0x696969 },        { "dodgerblue", 0x1E90FF },
    { "firebrick", 0xB22222 },      { "floralwhite", 0xFFFAF0 },    { "forestgreen", 0x228B22 },
    { "fuchsia", 0xFF00FF },        { "gainsboro", 0xDCDCDC },      { "ghostwhite", 0xF8F8FF },
    { "gold", 0xFFD700 },           { "goldenrod", 0xDAA520 },      { "gray", 0x808080 },
    { "grey", 0x808080 },           { "green", 0x008000 },          { "greenyellow", 0xADFF2F },
    { "honeydew", 0xF0FFF0 },       { "hotpink", 0xFF69B4 },        { "indianred", 0xCD5C5C },
    { "indigo", 0x4B0082 },         { "ivory", 0xFFFFF0 },          { "khaki", 0xF0E68C },
    { "lavender", 0xE6E6FA },       { "lavenderblush", 0xFFF0F5 },  { "lawngreen", 0x7CFC00 },
    { "lemonchiffon", 0xFFFACD },   { "lightblue", 0xADD8E6 },      { "lightcoral", 0xF08080 },
    { "lightcyan", 0xE0FFFF },      { "lightgoldenrodyellow", 0xFAFAD2 },
    { "lightgray", 0xD3D3D3 },      { "lightgrey", 0xD3D3D3 },      { "lightgreen", 0x90EE90 },
    { "lightpink", 0xFFB6C1 },      { "lightdalmon", 0xFFA07A },    { "lightseagreen", 0x20B2AA },
    { "lightskyblue", 0x87CEFA },   { "lightslategray", 0x778899 }, { "lightslategrey", 0x778899 },
    { "lightsteelblue", 0xB0C4DE }, { "lightyellow", 0xFFFFE0 },    { "lime", 0x00FF00 },
    { "limegreen", 0x32CD32 },      { "linen", 0xFAF0E6 },          { "magenta", 0xFF00FF },
    { "maroon", 0x800000 },         { "mediumaquamarine", 0x66CDAA },
    { "mediumblue", 0x0000CD },     { "mediumorchid", 0xBA55D3 },   { "mediumpurple", 0x9370DB },
    { "mediumseagreen", 0x3CB371 }, { "mediumslateblue", 0x7B68EE },{ "mediumspringgreen", 0x00FA9A },
    { "mediumturquoise", 0x48D1CC },{ "mediumvioletred", 0xC71585 },{ "midnightblue", 0x191970 },
    { "mintcream", 0xF5FFFA },      { "mistyrose", 0xFFE4E1 },      { "moccasin", 0xFFE4B5 },
    { "navajowhite", 0xFFDEAD },    { "navy", 0x000080 },           { "oldlace", 0xFDF5E6 },
    { "olive", 0x808000 },          { "olivedrab", 0x6B8E23 },      { "orange", 0xFFA500 },
    { "orangered", 0xFF4500 },      { "orchid", 0xDA70D6 },         { "palegoldenrod", 0xEEE8AA },
    { "palegreen", 0x98FB98 },      { "paleturquoise", 0xAFEEEE },  { "palevioletred", 0xDB7093 },
    { "papayawhip", 0xFFEFD5 },     { "peachpuff", 0xFFDAB9 },      { "peru", 0xCD853F },
    { "pink", 0xFFC0CB },           { "plum", 0xDDA0DD },           { "powderblue", 0xB0E0E6 },
    { "purple", 0x800080 },         { "rebeccapurple", 0x663399 },  { "red", 0xFF0000 },
    { "rosybrown", 0xBC8F8F },      { "royalblue", 0x4169E1 },      { "saddlebrown", 0x8B4513 },
    { "salmon", 0xFA8072 },         { "sandybrown", 0xF4A460 },     { "seagreen", 0x2E8B57 },
    { "seashell", 0xFFF5EE },       { "sienna", 0xA0522D },         { "silver", 0xC0C0C0 },
    { "skyblue", 0x87CEEB },        { "slateblue", 0x6A5ACD },      { "slategray", 0x708090 },
    { "slategrey", 0x708090 },      { "snow", 0xFFFAFA },           { "springgreen", 0x00FF7F },
    { "steelblue", 0x4682B4 },      { "tan", 0xD2B48C },            { "teal", 0x008080 },
    { "thistle", 0xD8BFD8 },        { "tomato", 0xFF6347 },         { "turquoise", 0x40E0D0 },
    { "violet", 0xEE82EE },         { "wheat", 0xF5DEB3 },          { "white", 0xFFFFFF },
    { "whitesmoke", 0xF5F5F5 },    { "yellow", 0xFFFF00 },          { "yellowgreen", 0x9ACD32 } };

// clang-format on

/* parsers for the string input of attribute settings. Each attribute object has
a string
version of the implementation. Simply the settings are applied from the string.
*/

// doubleNF(string _sOption)
// a constructor that takes a string and sets the options.
viewManager::doubleNF::doubleNF(const string &sOption) {
  static unordered_map<string, u_int8_t> annotationMap = {
      {"px", numericFormat::px},
      {"pt", numericFormat::pt},
      {"em", numericFormat::em},
      {"percent", numericFormat::percent},
      {"pct", numericFormat::percent},
      {"%", numericFormat::percent},
      {"autocalculate", numericFormat::autoCalculate},
      {"auto", numericFormat::autoCalculate}};
  // defualt to auto calculate
  option = numericFormat::autoCalculate;
  std::regex r("[\\s,_]+");
  std::string sTmp = std::regex_replace(sOption, r, "");

  u_int8_t opt;
  tie(value, opt) = strToNumericAndEnum("doubleNF", annotationMap, sOption);
  option = static_cast<numericFormat>(opt);
}

// parseQuadCoordinates(string _sOption)
// a function that returns a tuple of the four coordinates specified in a
// doubleNF object. this routine is used by the attributes that accept four at a
// time, that is the short hand versions of coordinates, margin and padding
tuple<doubleNF, doubleNF, doubleNF, doubleNF>
viewManager::parseQuadCoordinates(const string _sOptions) {
  regex re("^[\\s]*[\\{\\(]?([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)([\\+\\-]?[\\d]+[.,]?[\\d]*[\\%]?[\\w]{0,7})"
           "(?:[\\s]*[,]?[\\s]*)[\\s]*[\\}\\)]?");
  smatch coords;

  if (regex_search(_sOptions, coords, re)) {
    cout << "did match" << endl;

    cout << "matches = " << coords.size() << endl;
    for (int i = 0; i < coords.size(); i++)
      cout << "   ---> " << coords.str(i) << endl;

    if (coords.size() == 5) {
      cout << "is five items" << endl;
      auto ret =
          std::make_tuple(doubleNF(coords.str(1)), doubleNF(coords.str(2)),
                          doubleNF(coords.str(3)), doubleNF(coords.str(4)));
      return ret;
    }
  }

  std::string info = "Could not parse attribute string option : ";
  info += _sOptions;

  throw std::invalid_argument(info);
}

/* colorNF::colorIndex(const std::string &_colorName)
 The function accepts a name that may have spaces and can have camel case
 within the color name spelling. the function transforms the name and removes
 the spaces. It returns an iterator to the colorMap. This saves a find
 operation on the map when checking for the validity of a color name within
 the colormap.
*/
colorMap::const_iterator colorNF::colorIndex(const std::string &_colorName) {
  std::regex r("\\s+");
  std::string sKey = std::regex_replace(_colorName, r, "");
  std::transform(sKey.begin(), sKey.end(), sKey.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  auto it = colorNF::colorFactory.find(sKey);

  return it;
}

/*The constructor provides a string lookup of a passed color name.*/
viewManager::colorNF::colorNF(const string &_sOption) {
  option = colorFormat::name;
  auto it = colorIndex(_sOption);

  unsigned long color = 0;

  if (it != colorFactory.end())
    color = it->second;

  value[0] = static_cast<double>((color & 0xFF000000) >> 24);
  value[1] = static_cast<double>((color & 0x00FF0000) >> 16);
  value[2] = static_cast<double>((color & 0x0000FF00) >> 8);
  value[3] = 1.0;
}
// at times when the parser looks up a color name, this uses the iterator
// which came from the name
viewManager::colorNF::colorNF(colorMap::const_iterator it) {
  option = colorFormat::name;
  unsigned long color = it->second;

  value[0] = static_cast<double>((color & 0xFF000000) >> 24);
  value[1] = static_cast<double>((color & 0x00FF0000) >> 16);
  value[2] = static_cast<double>((color & 0x0000FF00) >> 8);
  value[3] = 1.0;
}

viewManager::colorNF::colorNF(const unsigned long &color) {
  value[0] = static_cast<double>((color & 0xFF000000) >> 24);
  value[1] = static_cast<double>((color & 0x00FF0000) >> 16);
  value[2] = static_cast<double>((color & 0x0000FF00) >> 8);
  value[3] = 1.0;
}

void viewManager::colorNF::lighter(const double &step) {}
void viewManager::colorNF::darker(const double &step) {}
void viewManager::colorNF::monochromatic(const double &step) {}
void viewManager::colorNF::triad(void) { /*hsl rotate 120*/
}
void viewManager::colorNF::neutralCooler(void) { /* hsl rotate -30 */
}
void viewManager::colorNF::neutralWarmer(void) { /* hsl rotate 30 */
}
void viewManager::colorNF::complementary(void) { /* hsl rotate 180*/
}
void viewManager::colorNF::splitComplements(void) { /*hsl rotate 150 */
}

// strToEnum(const string_view &sListName, const unordered_map<string, uint8_t>
// &optionMap) a function that accepts a unorder map of string and numeric
// values. the function removes invalid characters and applies a toLower case
// transform
uint8_t viewManager::strToEnum(const string_view &sListName,
                               const unordered_map<string, uint8_t> &optionMap,
                               const string &_sOption) {
  uint8_t ret = 0;

  std::regex r("\\s+");
  std::string sTmpKey = std::regex_replace(_sOption, r, "");
  std::transform(sTmpKey.begin(), sTmpKey.end(), sTmpKey.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  auto it = optionMap.find(sTmpKey);

  if (it != optionMap.end()) {
    ret = it->second;
  } else {
    std::string info(sListName);
    info += " attribute string option not found: ";
    info += _sOption;

    throw std::invalid_argument(info);
  }
}

/*
strToNumericAndEnum

returns: tuple<double, u_int8_t>

The routine provides a translation from a string format to a
c++ enumeration. The expected input type for the enumeration is a
uint8_t. The c++ compiler automatically translates the options
during the list initializer. However the output must be statically cast
back to the enumeration value.
*/
tuple<double, u_int8_t> viewManager::strToNumericAndEnum(
    const string_view &sListName,
    const unordered_map<string, uint8_t> &optionMap, const string &_sOption) {

  std::regex r("[\\s,_]+");
  std::string sTmp = std::regex_replace(_sOption, r, "");
  std::transform(sTmp.begin(), sTmp.end(), sTmp.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  char *pEnd;
  double dRet = 0;
  u_int8_t ui8Ret = 0;

  dRet = strtod(sTmp.data(), &pEnd);

  if (pEnd) {
    auto it = optionMap.find(string(pEnd));
    if (it != optionMap.end())
      ui8Ret = it->second;
  }

  return make_tuple(dRet, ui8Ret);
}

// display(string sOption)
// transforms the textual input into the display options
viewManager::display::display(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"inline", in_line}, {"block", block}, {"none", none}};
  value =
      static_cast<display::optionEnum>(strToEnum("display", enumMap, sOption));
}

// position(string sOption)
// transforms the textual input into the position options
viewManager::position::position(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"absolute", absolute},
                                                   {"relative", relative}};
  value = value = static_cast<position::optionEnum>(
      strToEnum("position", enumMap, sOption));
}

// textAlignment(string sOption)
// transforms the textual input into the textAlignment options
viewManager::textAlignment::textAlignment(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"left", left},
                                                   {"center", center},
                                                   {"right", right},
                                                   {"justified", justified}};
  value = static_cast<textAlignment::optionEnum>(
      strToEnum("textAlignment", enumMap, sOption));
}

// lineHeight(string sOption)
// transforms the textual input into the lineHeight options
viewManager::lineHeight::lineHeight(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {{"normal", normal},
                                                   {"numeric", numeric}};
  u_int8_t opt;
  tie(value, opt) = strToNumericAndEnum("lineHeight", enumMap, sOption);
  option = static_cast<lineHeight::optionEnum>(opt);
}

// lineHeight(string sOption)
// transforms the textual input into the lineHeight options
viewManager::borderStyle::borderStyle(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"none", none},   {"dotted", dotted},   {"dashed", dashed},
      {"solid", solid}, {"doubled", doubled}, {"groove", groove},
      {"ridge", ridge}, {"inset", inset},     {"outset", outset}};
  value = static_cast<borderStyle::optionEnum>(
      strToEnum("borderStyle", enumMap, sOption));
}

// listStyleType(const string &_sOption)
// transforms the string input to the list of options
viewManager::listStyleType::listStyleType(const string &sOption) {
  static unordered_map<string, uint8_t> enumMap = {
      {"none", none},     {"disc", disc},       {"circle", circle},
      {"square", square}, {"decimal", decimal}, {"alpha", alpha},
      {"greek", greek},   {"latin", latin},     {"roman", roman}};
  value = static_cast<listStyleType::optionEnum>(
      strToEnum("listStyleType", enumMap, sOption));
}

/*********************************************************************************/

/* the viewer constructor opens an window and establishes a root document object.
*/
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

  cout << iLevel << " " << e.softName << " ";

  std::string sID;

  try {
    sID = e.getAttribute<indexBy>().value;
  } catch (const std::exception &e) {
    sID = "-noID-";
  }

  cout << "(" << sID << ")" << endl;

  e.render();

  auto n = e.firstChild();

  while (n) {
    consoleRender(n->get(), iLevel + 1);
    n = n->get().nextSibling();
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

/*
The following user defined literals provide the consolidated syntax for ease of numeric
literal input.
*/
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
auto viewManager::query(const std::string &queryString) -> ElementList {
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

/*
This version of the query interface provides a
syntax whereby a lambda or a function may be used to provide matching.
The function is simply passed an element within the traversal.
The function is expected to return a true or false value.
*/
auto viewManager::query(const ElementQuery &queryFunction) -> ElementList {
  ElementList results;
  for (const auto &n : elements) {
    if (queryFunction(std::ref(*(n.get()))))
      results.push_back(std::ref(*(n.get())));
  }
  return results;
}

/*
hasElement
the hasElement function returns a true or false value if the index is found
within the index. This may be used to avoid possible exceptions.
*/
bool viewManager::hasElement(const std::string &key) {
  auto it = indexedElements.find(key);
  return it != indexedElements.end();
}

/******************************************************************************************
                    Element
*******************************************************************************************/
viewManager::Element::Element(const Element &other) {
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

viewManager::Element::Element(Element &&other) noexcept {
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

Element &viewManager::Element::operator=(const Element &other) {
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

Element &viewManager::Element::operator=(Element &&other) noexcept {
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

/**
 The function will parse the string as input searching for document tags.
 These elements are added as children of the element for which the function
 is invoked.

 @param sMarkup a std::string containing the markup.
 @return Element& returns the referenced element for continuation syntax.

*/
auto viewManager::Element::appendChild(const std::string &sMarkup)
    -> Element & {
  return (ingestMarkup(*this, sMarkup));
}

/**
 The function will append the given document element within the parameter as
 a child.

 @param newChild a new child element that was previously created.
 @return Element& returns the referenced element for continuation syntax.

*/
auto viewManager::Element::appendChild(Element &newChild) -> Element & {
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

/**
 The function will append the given document elements within the ElementList
 parameter as children.

 @param elementCollection an ElementList of new child element that was previously created.
 @return Element& returns the referenced element for continuation syntax.

*/
auto viewManager::Element::appendChild(const ElementList &elementCollection)
    -> Element & {
  for (auto e : elementCollection) {
    appendChild(e.get());
  }
  return (*this);
}

/**
 The function will append the given markup content as a sibling.

 @param elementCollection an ElementList of new child element that was previously created.
 @return Element& returns the referenced element for continuation syntax.

*/
auto viewManager::Element::append(const std::string &sMarkup) -> Element & {
  Element *base = this->m_parent;
  if (base == nullptr)
    base = this;
  return (ingestMarkup(*base, sMarkup));
}

auto viewManager::Element::append(Element &sibling) -> Element & {
  m_nextSibling = sibling.m_self;
  sibling.m_parent = this->m_parent;
  sibling.m_previousSibling = this;

  if (!this->m_parent->m_firstChild)
    this->m_parent->m_firstChild = sibling.m_self;

  this->m_parent->m_lastChild = sibling.m_self;

  this->m_parent->m_childCount++;
  return (sibling);
}

auto viewManager::Element::append(ElementList &elementCollection) -> Element & {
  for (auto &e : elementCollection)
    append(e);
  return (*this);
}

Element &viewManager::Element::setAttribute(const std::any &setting) {

  // filter list
  enum _enumTypeFilter {
    dt_char,
    dt_double,
    dt_float,
    dt_int,
    dt_std_string,
    dt_const_char,
    dt_vector_char,
    dt_vector_double,
    dt_vector_float,
    dt_vector_int,
    dt_vector_string,
    dt_vector_vector_string,
    dt_vector_pair_int_string,
    dt_indexBy,

    dt_nonFiltered
  };
  // filter map
  static std::unordered_map<size_t, _enumTypeFilter> _umapTypeFilter = {
      {std::type_index(typeid(char)).hash_code(), dt_char},
      {std::type_index(typeid(double)).hash_code(), dt_double},
      {std::type_index(typeid(float)).hash_code(), dt_float},
      {std::type_index(typeid(int)).hash_code(), dt_int},
      {std::type_index(typeid(std::string)).hash_code(), dt_std_string},
      {std::type_index(typeid(const char *)).hash_code(), dt_const_char},
      {std::type_index(typeid(std::vector<char>)).hash_code(), dt_vector_char},
      {std::type_index(typeid(std::vector<double>)).hash_code(),
       dt_vector_double},
      {std::type_index(typeid(std::vector<float>)).hash_code(),
       dt_vector_float},
      {std::type_index(typeid(std::vector<int>)).hash_code(), dt_vector_int},
      {std::type_index(typeid(std::vector<std::string>)).hash_code(),
       dt_vector_string},
      {std::type_index(typeid(std::vector<std::vector<std::string>>))
           .hash_code(),
       dt_vector_vector_string},
      {std::type_index(
           typeid(std::vector<std::vector<std::pair<int, std::string>>>))
           .hash_code(),
       dt_vector_pair_int_string},
      {std::type_index(typeid(indexBy)).hash_code(), dt_indexBy}};
  // set search result defaults for not found in filter
  _enumTypeFilter dtFilter = dt_nonFiltered;
  bool bSaveInMap = false;
  auto it = _umapTypeFilter.find(setting.type().hash_code());
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
    data<std::string>() = std::vector<std::string>{v};
  } break;
  case dt_std_string: {
    auto v = std::any_cast<std::string>(setting);
    data<std::string>() = std::vector<std::string>{v};
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
  case dt_vector_string: {
    auto v = std::any_cast<std::vector<std::string>>(setting);
    data<std::string>() = v;
  } break;
  case dt_vector_vector_string: {
    auto v = std::any_cast<std::vector<std::vector<std::string>>>(setting);
    data<std::vector<std::string>>() = v;
  } break;
  case dt_vector_pair_int_string: {
    auto v = std::any_cast<std::vector<std::pair<int, std::string>>>(setting);
    data<std::pair<int, std::string>>() = v;
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

Element &
viewManager::Element::setAttribute(const std::vector<std::any> &attribs) {
  for (auto n : attribs)
    setAttribute(n);
  return *this;
}

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
  std::string oldKey = "";
  const std::string &newKey = setting.value;
  auto it = attributes.find(std::type_index(typeid(indexBy)));

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
  auto it = eventTypeMap.find(evtType);
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
/// <summary>The function removes all children and data from the
/// the element.
/// </ summary>
///
auto viewManager::Element::clear(void) -> Element & { return *this; }

///
/// <summary>This is the main function which invokes drawing of the item and
/// its children. It is called recursively when painting needs to occur.
/// This function is used internally and is not necessary to invoke. That
/// is, system already invokes this as part of the processing stack. The
/// work performed by this routine is accomplished using the surface image.
/// </ summary>
///
void viewManager::Element::render(void) {
  std::string idName;
  try {
    idName = getAttribute<indexBy>().value;
  } catch (const std::exception &e) {
    idName = "noID";
  }

  std::cout << "indexBy " << idName << endl;
  std::cout << "children " << m_childCount << std::endl;

  // print information in the default string vector buffer
  auto vdata = data();
  for (auto s : vdata)
    std::cout << s << endl;
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

  // if stream ingestion is on, interprest the markup as it arrives.
  if (ingestStream)
    ingestMarkup(*this, buffer);
  else
    data().push_back(buffer);

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

  // if stream ingestion is on, interprest the markup as it arrives.
  if (ingestStream)
    ingestMarkup(*this, buffer);
  else
    data().push_back(buffer);

  free(buffer);
  va_end(ap);
#endif
}

/***************************************************************************
ingestMarkup

The routine is called by the functions that apply a string markup for parsing.
This routine uses the object factrory and color map to query the
contents of the maps. The parser applied is a simplified parser for
speed in that complete tags must exist within the given text. That does not
apply to beginning and ending tags however. Attribtues may also be captured.
The text within the enclosed portion is applied as a data item within the
element.

Comment blocks are supported as with the html notation <!-- and -->
Several aliases exist to shorten the attribute list as well as quad versions
of attributes such as coordinates(a,b,c,d) or margin(a,b,c,d). Options exist for
the formatting of the string as it uses regular expressions to capture four
parameters. You can use () {} [] for labling the group and separate the items
with a space or a comma.

In some regards, the parser is more strict in what can be applied to create
elements, verses recoginitions of color markup. In general, these rules mark the
implementation less code. Errors within the markup as implemented by the
developer will be shown at runtime. There is a program that can generate c++
code from this markup.

Notation is supported on numeric parameters with a format:
  coordinates {10% 10% 80% 80%}


      <!-- This is a comment block -->

       <h1>The title is</h1>
       <h2>The information</h3> <!-- not an element -->

      <div id=divtest background=blue>
         This is the text inside the block.
         <ul>
           <li>This is the first item</li>
           <li>This is the second item</li>
         </ul>
      </div>


      <blue>When the text is set this way, the color continues until another
color is selected. <green>This changes the color of the foreground and creates
textNodes within the current element context.



***************************************************************************/
Element &viewManager::Element::ingestMarkup(Element &node,
                                            const std::string &markup) {

  /* the parser context applies memory to successive calls to the function.
    This is important for functions like printf or the stream insertion
    operators so that markup gets interpreted correctly. Since there is one of
    these contexts per element, each element operates independently. For ease of
    implementation, the structure and typedef is located at the function level.

    The parser acts in a two phase operation, first locating each of the tags as
    markup and those that appears as tags but are not markup elements. The
    second phase builds the elements and applies the attributes to the elements.
    Since document fragments can be nested, the parser function maintains a
    stack of created elements.
  */
  enum itemType {
    element,
    elementTerminal,
    attribute,
    attributeValue,
    color,
    stringData
  };

  // the varaint holds the payload from the parser
  typedef variant<string, factoryLambda, attributeLambda, colorNF>
      parserOperator;

  typedef struct {
    bool bCapture = false;
    bool bSkip = false;
    bool bSignal = false;
    bool bTerminal = false;
    bool bAttributeList = false;
    bool bAttributeListValue = false;

    bool bQuery = false;
    string sCaptureString;
    string sBackflow;
    vector<pair<itemType, parserOperator>> parsedData;
    vector<reference_wrapper<Element>> elementStack;
    bool bFoundAttributeSet = false;
  } parserContext;

  static parserContext pc;

  pc.elementStack.push_back(node);

  // pointer to the input buffer.
  const char *p = markup.data();
  string sTmp;

  // tokenize the markup string
  while (*p) {

    switch (*p) {
    // when the markup < character is found, start capturing
    case '<':
      // if the capture signal is found, and items exist in the capture string,
      // store it.
      if (pc.sBackflow.length() != 0) {
        pc.parsedData.emplace_back(stringData, pc.sBackflow);
        pc.sBackflow = "";
      }

      cout << "< signal found" << endl;
      pc.bSignal = true;
      pc.bSkip = true;
      break;

    // when the space is found, if capturing is occurring, find out if the item
    // is a markup tag
    case ' ':
      if (pc.bSignal) {
        cout << "(space) signal found" << endl;
        pc.bQuery = true;
        pc.bSkip = true;
      }
      break;
    case '=':
      if (pc.bSignal && pc.bAttributeList) {
        pc.bQuery = true;
        pc.bSkip = true;
      }
      break;
    case '>':
      cout << "> signal found" << endl;
      // has a signal been established with the capture turned on?
      if (pc.bSignal && pc.bTerminal) {
        pc.bSignal = false;
        pc.bTerminal = false;
        pc.bCapture = false;
        pc.bQuery = false;
        pc.bSkip = true;
        pc.bAttributeList = false;
        pc.bAttributeListValue = false;

      } else if (pc.bSignal) {

        pc.bQuery = true;
        pc.bSkip = true;
        pc.bSignal = false;
      }
      break;

    case '/':
      cout << "/ signal found" << endl;
      if (pc.bSignal) {
        pc.bQuery = true;
        pc.bTerminal = true;
        pc.bSkip = true;
      }

      break;
    }

    // if a query has been requested by a parser condition, do this now.
    // This is established once within the loop function so that code within
    // the switch case block is not duplicated.
    if (pc.bQuery) {
      cout << "query start " << endl;

      // check the state of scanning for attribtues but not the attribute value.
      // this acts as a flip flop state between the attribute name and the
      // attribute value.
      if (pc.bAttributeList && !pc.bAttributeListValue) {
        cout << "check for attribute " << endl;

        // convert to lower case, the attribute list is keyed on lower case
        // names.
        string sKey = pc.sCaptureString;
        std::transform(sKey.begin(), sKey.end(), sKey.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        // store iterator to the function
        auto it = attributeFactory.find(sKey);
        if (attributeFactory.find(sKey) != attributeFactory.end()) {
          cout << "-----> is attribtue " << endl;
          pc.parsedData.emplace_back(attribute, it->second);
          pc.bAttributeListValue = true;
          pc.sCaptureString = "";
        }

      } else if (pc.bAttributeList && pc.bAttributeListValue) {
        cout << "attribute value " << endl;
        pc.parsedData.emplace_back(attributeValue, pc.sCaptureString);
        pc.bAttributeListValue = false;
        pc.sCaptureString = "";

      } else {
        string sKey = pc.sCaptureString;
        std::transform(sKey.begin(), sKey.end(), sKey.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        cout << "check is object element (" << sKey << ")" << endl;

        auto it = objectFactoryMap.find(sKey);
        if (it != objectFactoryMap.end()) {
          cout << "----->  is element " << endl;

          if (pc.bTerminal) {
            cout << "pc.bTerminal " << endl;

            pc.parsedData.emplace_back(elementTerminal, "");
            pc.bTerminal = false;
            pc.bAttributeList = false;
            pc.bAttributeListValue = false;

            pc.sCaptureString = "";
          } else {
            // store lambda for the element factory
            pc.parsedData.emplace_back(element, it->second);
            pc.bAttributeList = true;
            pc.bAttributeListValue = false;
            pc.sCaptureString = "";
          }

        } else {
          cout << "check to see if it is a color  " << sKey << endl;
          // store the color object within the parser payload
          auto it = colorNF::colorIndex(pc.sCaptureString);
          if (it != colorNF::colorFactory.end()) {
            cout << "----->  is color " << endl;
            pc.parsedData.emplace_back(color, colorNF(it));
            pc.sCaptureString = "";
          }
        }
      }

      pc.bQuery = false;
    }

    if (!pc.bSignal && !pc.bSkip)
      pc.sBackflow += *p;

    if (pc.bSignal && !pc.bSkip) {
      pc.sCaptureString += *p;
      cout << "pc.sCaptureString " << pc.sCaptureString << endl;

    } else {

      pc.bSkip = false;
    }

    // goto next character
    p++;
  }

  cout << "==============================" << endl;
  auto itemdbg = pc.parsedData.begin();
  while (itemdbg != pc.parsedData.end()) {
    switch (itemdbg->first) {
    case element: {
      cout << "element" << endl;
    } break;

    case elementTerminal: {
      cout << "element terminate" << endl;
    } break;

    // the attribute and value are handled here together
    case attribute: {
      cout << "attribute" << endl;

    } break;
    case attributeValue: {
      cout << "attributeValue" << get<string>(itemdbg->second) << endl;
    } break;

    case color: {
      cout << "color" << endl;
    } break;

    case stringData:
      cout << "stringData" << get<string>(itemdbg->second) << endl;
      break;
    }

    itemdbg++;
  }
  cout << "==============================" << endl;

  // second phase, iterate over the parsed context and develop the elements,
  // color text nodes, and set attributes for the items on the stack. once items
  // are processed, they are removed from the stack using the delete range
  // operator, For a complet etag to exist, the end tab must also exist.
  auto item = pc.parsedData.begin();
  while (item != pc.parsedData.end()) {
    switch (item->first) {
    case element: {
      Element &e = get<factoryLambda>(item->second)({});
      pc.elementStack.back().get().appendChild(e);
      pc.elementStack.push_back(e);
    } break;

    case elementTerminal: {
      pc.elementStack.pop_back();
    } break;

    // the attribute and value are handled here together
    case attribute: {
      auto itAttributeValue = std::next(item, 1);
      if (itAttributeValue != pc.parsedData.end() &&
          itAttributeValue->first == attributeValue) {
        get<attributeLambda>(item->second)(
            pc.elementStack.back(), get<string>(itAttributeValue->second));
        item++;
      }

    } break;

    case color: {
      auto &e = pc.elementStack.back().get().appendChild<textNode>(
          textColor{get<colorNF>(item->second)});
      pc.elementStack.push_back(e);
    } break;

    case stringData:
      pc.elementStack.back().get().data().push_back(get<string>(item->second));
      break;
    }

    // goto next item
    item++;
  }

  // return the the item on the stack appropiate
  Element &eRet = pc.elementStack.back().get();
  pc.elementStack.pop_back();

  return eRet;
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
