Markup Input Format
===================

\page markupInputFormat Markup Input Format
There are several function that accept a markup
string. The appendChild, append, printf, << operator
and ingestMarkup functions provide interfaces 
for this functionality. 

The two stream functions, printf and << operator, only
invoke parsing of the string when the member variable
ingestStream is set to true. When elements are created,
the default is false. 

The parser applied is a simplified parser for
speed in that complete tags must exist within the given text. 
Attributes may also be captured and set. The text within the 
enclosed portion is applied as a data item within the
element.

Several aliases exist to shorten the entity, UX and attribute list. 
As well, quad versions of attributes such as 
coordinates(a,b,c,d) or margin(a,b,c,d) are provided
to shorten the descriptive syntax. Within the quad version of attributes,
the () {} [] pair may be used for labeling the group. The numeric parameters
should be delimited with a space or a comma.

Notation is supported on numeric parameters with a format. Allowable measurement
mode notations are %, pct, percent, px, and em. For example:

\code
  coordinates {10% 10% 80% 80%}
\endcode

A given markup may appear as follows: 

\code
<h1>The title is</h1>
<h2>The information</h2>

<div id=divtest background=blue center relative>
  This is the text inside the block.
  <ul>
    <li>This is the first item</li>
    <li>This is the second item</li>
  </ul>
</div>


<blue>When the text is set this way, the color continues until another
color is selected. <green>This changes the color of the foreground and creates
textNodes within the current element context.
\endcode

The following attributes and tags may be used within the markup. Markup
keys are matched by case insensitive logic. Tags should be within the 
&lt;TAG&gt; symbols. Document tags should be formed with a &lt;/TAG&gt;.

Tags
====

Document Entity       | Description
--------------------- | ---------------------------
br                    | BR
h1                    | H1
h2                    | H2
h3                    | H3
paragraph             | PARAGRAPH
p                     | PARAGRAPH
div                   | DIV
span                  | SPAN
ul                    | UL
ol                    | OL
li                    | LI
image                 | IMAGE

User Interface Controls
=======================
There are several base user interface controls provided for data entry.
The data portion should appear between the beginning and ending tag. 
As with other tags, user interface markup should be formed as 
&lt;UX_NAME&gt; &lt;/UX_NAME&gt;.  For example, to create two fields
that contain the first and last name John Doe ready for editing, the 
following markup may be used:

\code
<h1>Enter your Name</h1>
First Name:<text>John</text><br>
Last Name:<text>Doe</text><br>
<br>
<button>Continue</button>
\endcode

The following interface markup control names are supported.

UX Controls           | Description
--------------------- | ---------------------------
text                  | creates a UX::text element.
password              | UX::password
multiline             | UX::multiline
number                | UX::number
masked                | UX::masked
pushbutton            | UX::pushButton
button                | UX::pushButton
radiobutton           | UX::radioButton
radio                 | UX::radioButton
hotimage              | UX::hotImage
group                 | UX::group
checkbox              | UX::checkBox
date                  | UX::date
datetime              | UX::dateTime
week                  | UX::week
time                  | UX::time
file                  | UX::file
verticalscrollbar     | UX::verticalScrollbar
horizontalscrollbar   | UX::horizontalScrollbar
resizervertical       | UX::resizerVertical
resizerhorizontal     | UX::resizerHorizontal
listselector          | UX::listSelector
list                  | UX::listSelector
menu                  | UX::menu
gridedit              | UX::gridEdit
tabbedpanel           | UX::tabbedPanel
sliderrange           | UX::sliderRange
knobrange             | UX::knobRange
knob                  | UX::knobRange
accordion             | UX::accordion
progress              | UX::progress
dialog                | UX::dialog


Attributes
==========

Attributes appear within the tag before the &gt; Some of the items are offered 
as a shortened name. As well, specific attributes may be set using only the keyword
without using the =. The following attributes are supported:<br>

- id 
  - attribute sets the indexBy of the element.
  - should include the = for setting the attribute
  - Example:
    - <span id=idTest>Info Spanned</span>
  - \see indexBy
- indexby
  - attribute sets the indexBy of the element.
  - should include the = for setting the attribute
  - Example:
    - <span id=idTest>Info Spanned</span>
  - \see indexBy

- block 
  - can be by itself
  - \see display
- inline - false,
  - can be by itself
  - \see display
- hidden - false,
  - can be by itself
  - \see display
- display
  - should be followed by an =
  - use the words "block", "inline" or "hidden"
  - \see display
- absolute
  - used by itself
  - \see position
- relative
  - used by itself
  - \see position
- position
  - must be followed by an =
  - use the keywords "absolute" or "relative"
  - \see position
- objecttop
  - followed by an =
  - can use format mode specifiers as suffix
  - %, pct, percent, px, em
  - \see objectTop
- top
  - followed by an =
  - can use format mode specifiers as suffix
  - %, pct, percent, px, em
  - \see objectTop
- objectleft - true,
  - followed by an =
  - can use format mode specifiers as suffix
  - %, pct, percent, px, em
  - \see objectLeft
- left
  - followed by an =
  - %, pct, percent, px, em
  - \see objectLeft
- objectheight
  - followed by an =
  - %, pct, percent, px, em
  - \see objectHeight
- height
  - followed by an =
  - %, pct, percent, px, em
  - \see objectHeight
- objectwidth
  - followed by an =
  - %, pct, percent, px, em
  - \see objectWidth
- width - true,
  - followed by an =
  - %, pct, percent, px, em
  - \see objectWidth
- coordinates
  - specify all coordinates within {}
  - %, pct, percent, px, em
  - \see objectWidth
- scrolltop
  - %, pct, percent, px, em
  - \see scrollTop
- scrollleft
  - %, pct, percent, px, em
  - \see scrollLeft
- background
  - followed by an =
  - \see background
- opacity
  - should be followed by =
  - \see opacity
- textface
  - should be followed by =
  - \see textFace
- textsize
  - should be followed by =
  - \see textSize
- textweight
  - should be followed by =
  - \see textWeight
- weight
  - should be followed by =
  - \see textWeight
- textcolor
  - should be followed by =
  - \see textColor
- color
  - should be followed by =
  - \see textColor
- textalignment
  - should be followed by an =
  - The keywords "left","right","center" or "justified" should be used.
  - \see textAlignment
- left
  - can appear by itself
  - \see textAlignment
- center
  - can appear by itself
  - \see textAlignment
- right
  - can appear by itself
  - \see textAlignment
- justified
  - can appear by itself
  - \see textAlignment
- textindent
  - should be followed by an =
  - \see textIndent
- indent 
  - should be followed by an =
  - \see textIndent
- tabsize
  - use an =
  - \see tabSize
- tab
  - use an =
  - \see tabSize
- lineheight
  - use an =
  - the keywords "normal" or "numeric" should be used
  - \see lineHeight
- normal
  - can appear alone
  - \see lineHeight
- numeric
  - can appear alone
  - \see lineHeight
- margintop
  - %, pct, percent, px, em
  - include the =
  - \see marginTop
- marginleft
  - %, pct, percent, px, em
  - include the =
  - \see marginLeft
- marginbottom
  - %, pct, percent, px, em
  - include the =
  - \see marginBottom
- marginright
  - %, pct, percent, px, em
  - include the =
  - \see marginRight
- margin 
  - must include the =
  - provide all four items within the {}
  - Example:
    - <span margin={10px,10px,10px,10px}>Information within a span</span>
  - \see marginTop
- marginleft
  - %, pct, percent, px, em
  - include the =
  - \see marginLeft
    \see marginBottom
    \see marginRight
    \see marginBottom

- paddingtop - true,
  - %, pct, percent, px, em
  - include the =
  - \see paddingTop
- paddingleft - true,
  - %, pct, percent, px, em
  - include the =
  - \see paddingLeft
- paddingbottom - true,
  - %, pct, percent, px, em
  - include the =
  - \see paddingBottom
- paddingright - true,
  - %, pct, percent, px, em
  - include the =
  - \see paddingRight
- padding
  - should be followed by the =
  - provide all four items within the {}
  - Example:
    - <span padding={10px,10px,10px,10px}>Padding</span>
- borderstyle
  - use an =
  - \see borderStyle
  - Use one of the following keywords:
    - "none"
    - "dotted"
    - "dashed"
    - "solid"
    - "doubled"
    - "groove"
    - "ridge"
    - "inset"
    - "outset"
- borderwidth
  - use an =
  - \see borderWidth
- bordercolor
  - use an =
  - \see borderColor
- borderradius
  - use an =
  - \see borderRadius
- focusindex
  - use an =
  - \see focusIndex
- focus
  - use an =
  - \see focusIndex
- zindex
  - use an =
  - \see zIndex
- liststyletype - true,
  - use an =
  - \see listStyleType
  - Use the keywords
    - "none"
    - "disc"
    - "circle"
    - "square"
    - "decimal"
    - "alpha"
    - "greek"
    - "latin"
    - "roman"



Supported Colors
================

The following names may be used within any of the color attributes
when specify a color. Colors may also be described in rgb(r,g,b),
rgba(r,g,b,a), hsl(hue,saturation,luminescence) or
24bit unsigned long hexidecimal. For example:

\code
<span background=rgb(255,0,0)>The color is red</span>
<span background=rgba(0,0,255, .5)>The color is blue and translucent.</span>
<span background=hsl(30,30,40)>A color given in hsl format.</span>
<span background=0xF0FFFF>A color given in 24bit hex format.</span>

\endcode

<br><br>

\htmlonly
<table>
<tr style="background:black;color:white"><td>Color name</td><td>sample</td><td style="padding-right:65px">24bit</td>
<td>Color name</td><td>sample</td><td style="padding-right:65px">24bit</td>
<td>Color name</td><td>sample</td><td style="padding-right:65px">24bit</td>
</tr>
<tr><td>aliceblue             </td><td style="background:#F0F8FF;padding-right:65px"> </td><td>0xF0F8FF </td>
<td>antiquewhite          </td><td style="background:#FAEBD7;padding-right:65px"> </td><td>0xFAEBD7 </td>
<td>aqua                  </td><td style="background:#00FFFF;padding-right:65px"> </td><td>0x00FFFF </td></tr>
<tr><td>aquamarine            </td><td style="background:#7FFFD4;padding-right:65px"> </td><td>0x7FFFD4 </td>
<td>azure                 </td><td style="background:#F0FFFF;padding-right:65px"> </td><td>0xF0FFFF </td>
<td>beige                 </td><td style="background:#F5F5DC;padding-right:65px"> </td><td>0xF5F5DC </td></tr>
<tr><td>bisque                </td><td style="background:#FFE4C4;padding-right:65px"> </td><td>0xFFE4C4</td>
<td>black                 </td><td style="background:#000000;padding-right:65px"> </td><td>0x000000 </td>
<td>blanchedalmond        </td><td style="background:#FFEBCD;padding-right:65px"> </td><td>0xFFEBCD </td></tr>
<tr><td>blue                  </td><td style="background:#0000FF;padding-right:65px"> </td><td>0x0000FF</td>
<td>blueviolet            </td><td style="background:#8A2BE2;padding-right:65px"> </td><td>0x8A2BE2 </td>
<td>brown                 </td><td style="background:#A52A2A;padding-right:65px"> </td><td>0xA52A2A </td></tr>
<tr><td>burlyWood             </td><td style="background:#DEB887;padding-right:65px"> </td><td>0xDEB887</td>
<td>cadetblue             </td><td style="background:#5F9EA0;padding-right:65px"> </td><td>0x5F9EA0</td>
<td>chartreuse            </td><td style="background:#7FFF00;padding-right:65px"> </td><td>0x7FFF00 </td></tr>
<tr><td>chocolate             </td><td style="background:#D2691E;padding-right:65px"> </td><td>0xD2691E</td>
<td>coral                 </td><td style="background:#FF7F50;padding-right:65px"> </td><td>0xFF7F50 </td>
<td>cornflowerblue        </td><td style="background:#6495ED;padding-right:65px"> </td><td>0x6495ED </td></tr>
<tr><td>cornsilk              </td><td style="background:#FFF8DC;padding-right:65px"> </td><td>0xFFF8DC </td>
<td>crimson               </td><td style="background:#DC143C;padding-right:65px"> </td><td>0xDC143C</td>
<td>cyan                  </td><td style="background:#00FFFF;padding-right:65px"> </td><td>0x00FFFF </td></tr>
<tr><td>darkblue              </td><td style="background:#00008B;padding-right:65px"> </td><td>0x00008B</td>
<td>darkcyan              </td><td style="background:#008B8B;padding-right:65px"> </td><td>0x008B8B</td>
<td>darkgoldenrod         </td><td style="background:#B8860B;padding-right:65px"> </td><td>0xB8860B </td></tr>
<tr><td>darkgray              </td><td style="background:#A9A9A9;padding-right:65px"> </td><td>0xA9A9A9</td>
<td>darkgrey              </td><td style="background:#A9A9A9;padding-right:65px"> </td><td>0xA9A9A9</td>
<td>darkgreen             </td><td style="background:#006400;padding-right:65px"> </td><td>0x006400 </td></tr>
<tr><td>darkkhaki             </td><td style="background:#BDB76B;padding-right:65px"> </td><td>0xBDB76B </td>
<td>darkmagenta           </td><td style="background:#8B008B;padding-right:65px"> </td><td>0x8B008B</td>
<td>darkolivegreen        </td><td style="background:#556B2F;padding-right:65px"> </td><td>0x556B2F </td></tr>
<tr><td>darkorange            </td><td style="background:#FF8C00;padding-right:65px"> </td><td>0xFF8C00</td>
<td>darkorchid            </td><td style="background:#9932CC;padding-right:65px"> </td><td>0x9932CC</td>
<td>darkred               </td><td style="background:#8B0000;padding-right:65px"> </td><td>0x8B0000 </td></tr>
<tr><td>darksalmon            </td><td style="background:#E9967A;padding-right:65px"> </td><td>0xE9967A</td>
<td>darkseagreen          </td><td style="background:#8FBC8F;padding-right:65px"> </td><td>0x8FBC8F</td>
<td>darkslateblue         </td><td style="background:#483D8B;padding-right:65px"> </td><td>0x483D8B </td></tr>
<tr><td>darkslategray         </td><td style="background:#2F4F4F;padding-right:65px"> </td><td>0x2F4F4F</td>
<td>darkslategrey         </td><td style="background:#2F4F4F;padding-right:65px"> </td><td>0x2F4F4F</td>
<td>darkturquoise         </td><td style="background:#00CED1;padding-right:65px"> </td><td>0x00CED1 </td></tr>
<tr><td>darkviolet            </td><td style="background:#9400D3;padding-right:65px"> </td><td>0x9400D3</td>
<td>deeppink              </td><td style="background:#FF1493;padding-right:65px"> </td><td>0xFF1493</td>
<td>deepskyblue           </td><td style="background:#00BFFF;padding-right:65px"> </td><td>0x00BFFF </td></tr>
<tr><td>dimgray               </td><td style="background:#696969;padding-right:65px"> </td><td>0x696969</td>
<td>dimgrey               </td><td style="background:#696969;padding-right:65px"> </td><td>0x696969</td>
<td>dodgerblue            </td><td style="background:#1E90FF;padding-right:65px"> </td><td>0x1E90FF </td></tr>
<tr><td>firebrick             </td><td style="background:#B22222;padding-right:65px"> </td><td>0xB22222</td>
<td>floralwhite           </td><td style="background:#FFFAF0;padding-right:65px"> </td><td>0xFFFAF0</td>
<td>forestgreen           </td><td style="background:#228B22;padding-right:65px"> </td><td>0x228B22 </td></tr>
<tr><td>fuchsia               </td><td style="background:#FF00FF;padding-right:65px"> </td><td>0xFF00FF</td>
<td>gainsboro             </td><td style="background:#DCDCDC;padding-right:65px"> </td><td>0xDCDCDC</td>
<td>ghostwhite            </td><td style="background:#F8F8FF;padding-right:65px"> </td><td>0xF8F8FF </td></tr>
<tr><td>gold                  </td><td style="background:#FFD700;padding-right:65px"> </td><td>0xFFD700</td>
<td>goldenrod             </td><td style="background:#DAA520;padding-right:65px"> </td><td>0xDAA520</td>
<td>gray                  </td><td style="background:#808080;padding-right:65px"> </td><td>0x808080 </td></tr>
<tr><td>grey                  </td><td style="background:#808080;padding-right:65px"> </td><td>0x808080</td>
<td>green                 </td><td style="background:#008000;padding-right:65px"> </td><td>0x008000</td>
<td>greenyellow           </td><td style="background:#ADFF2F;padding-right:65px"> </td><td>0xADFF2F </td></tr>
<tr><td>honeydew              </td><td style="background:#F0FFF0;padding-right:65px"> </td><td>0xF0FFF0</td>
<td>hotpink               </td><td style="background:#FF69B4;padding-right:65px"> </td><td>0xFF69B4</td>
<td>indianred             </td><td style="background:#CD5C5C;padding-right:65px"> </td><td>0xCD5C5C </td></tr>
<tr><td>indigo                </td><td style="background:#4B0082;padding-right:65px"> </td><td>0x4B0082</td>
<td>ivory                 </td><td style="background:#FFFFF0;padding-right:65px"> </td><td>0xFFFFF0</td>
<td>khaki                 </td><td style="background:#F0E68C;padding-right:65px"> </td><td>0xF0E68C </td></tr>
<tr><td>lavender              </td><td style="background:#E6E6FA;padding-right:65px"> </td><td>0xE6E6FA</td>
<td>lavenderblush         </td><td style="background:#FFF0F5;padding-right:65px"> </td><td>0xFFF0F5</td>
<td>lawngreen             </td><td style="background:#7CFC00;padding-right:65px"> </td><td>0x7CFC00 </td></tr>
<tr><td>lemonchiffon          </td><td style="background:#FFFACD;padding-right:65px"> </td><td>0xFFFACD</td>
<td>lightblue             </td><td style="background:#ADD8E6;padding-right:65px"> </td><td>0xADD8E6</td>
<td>lightcoral            </td><td style="background:#F08080;padding-right:65px"> </td><td>0xF08080 </td></tr>
<tr><td>lightcyan             </td><td style="background:#E0FFFF;padding-right:65px"> </td><td>0xE0FFFF</td>
<td>lightgoldenrodyellow  </td><td style="background:#FAFAD2;padding-right:65px"> </td><td>0xFAFAD2 </td>
<td>lightgray             </td><td style="background:#D3D3D3;padding-right:65px"> </td><td>0xD3D3D3</td></tr>
<tr><td>lightgrey             </td><td style="background:#D3D3D3;padding-right:65px"> </td><td>0xD3D3D3</td>
<td>lightgreen            </td><td style="background:#90EE90;padding-right:65px"> </td><td>0x90EE90 </td>
<td>lightpink             </td><td style="background:#FFB6C1;padding-right:65px"> </td><td>0xFFB6C1</td></tr>
<tr><td>lightdalmon           </td><td style="background:#FFA07A;padding-right:65px"> </td><td>0xFFA07A</td>
<td>lightseagreen         </td><td style="background:#20B2AA;padding-right:65px"> </td><td>0x20B2AA </td>
<td>lightskyblue          </td><td style="background:#87CEFA;padding-right:65px"> </td><td>0x87CEFA</td></tr>
<tr><td>lightslategray        </td><td style="background:#778899;padding-right:65px"> </td><td>0x778899</td>
<td>lightslategrey        </td><td style="background:#778899;padding-right:65px"> </td><td>0x778899 </td>
<td>lightsteelblue        </td><td style="background:#B0C4DE;padding-right:65px"> </td><td>0xB0C4DE</td></tr>
<tr><td>lightyellow           </td><td style="background:#FFFFE0;padding-right:65px"> </td><td>0xFFFFE0</td>
<td>lime                  </td><td style="background:#00FF00;padding-right:65px"> </td><td>0x00FF00 </td>
<td>limegreen             </td><td style="background:#32CD32;padding-right:65px"> </td><td>0x32CD32</td></tr>
<tr><td>linen                 </td><td style="background:#FAF0E6;padding-right:65px"> </td><td>0xFAF0E6</td>
<td>magenta               </td><td style="background:#FF00FF;padding-right:65px"> </td><td>0xFF00FF </td>
<td>maroon                </td><td style="background:#800000;padding-right:65px"> </td><td>0x800000</td></tr>
<tr><td>mediumaquamarine      </td><td style="background:#66CDAA;padding-right:65px"> </td><td>0x66CDAA </td>
<td>mediumblue            </td><td style="background:#0000CD;padding-right:65px"> </td><td>0x0000CD</td>
<td>mediumorchid          </td><td style="background:#BA55D3;padding-right:65px"> </td><td>0xBA55D3</td></tr>
<tr><td>mediumpurple          </td><td style="background:#9370DB;padding-right:65px"> </td><td>0x9370DB </td>
<td>mediumseagreen        </td><td style="background:#3CB371;padding-right:65px"> </td><td>0x3CB371</td>
<td>mediumslateblue       </td><td style="background:#7B68EE;padding-right:65px"> </td><td>0x7B68EE</td></tr>
<tr><td>mediumspringgreen     </td><td style="background:#00FA9A;padding-right:65px"> </td><td>0x00FA9A </td>
<td>mediumturquoise       </td><td style="background:#48D1CC;padding-right:65px"> </td><td>0x48D1CC</td>
<td>mediumvioletred       </td><td style="background:#C71585;padding-right:65px"> </td><td>0xC71585</td></tr>
<tr><td>midnightblue          </td><td style="background:#191970;padding-right:65px"> </td><td>0x191970 </td>
<td>mintcream             </td><td style="background:#F5FFFA;padding-right:65px"> </td><td>0xF5FFFA</td>
<td>mistyrose             </td><td style="background:#FFE4E1;padding-right:65px"> </td><td>0xFFE4E1</td></tr>
<tr><td>moccasin              </td><td style="background:#FFE4B5;padding-right:65px"> </td><td>0xFFE4B5 </td>
<td>navajowhite           </td><td style="background:#FFDEAD;padding-right:65px"> </td><td>0xFFDEAD</td>
<td>navy                  </td><td style="background:#000080;padding-right:65px"> </td><td>0x000080</td></tr>
<tr><td>oldlace               </td><td style="background:#FDF5E6;padding-right:65px"> </td><td>0xFDF5E6 </td>
<td>olive                 </td><td style="background:#808000;padding-right:65px"> </td><td>0x808000</td>
<td>olivedrab             </td><td style="background:#6B8E23;padding-right:65px"> </td><td>0x6B8E23</td></tr>
<tr><td>orange                </td><td style="background:#FFA500;padding-right:65px"> </td><td>0xFFA500 </td>
<td>orangered             </td><td style="background:#FF4500;padding-right:65px"> </td><td>0xFF4500</td>
<td>orchid                </td><td style="background:#DA70D6;padding-right:65px"> </td><td>0xDA70D6</td></tr>
<tr><td>palegoldenrod         </td><td style="background:#EEE8AA;padding-right:65px"> </td><td>0xEEE8AA </td>
<td>palegreen             </td><td style="background:#98FB98;padding-right:65px"> </td><td>0x98FB98</td>
<td>paleturquoise         </td><td style="background:#AFEEEE;padding-right:65px"> </td><td>0xAFEEEE</td></tr>
<tr><td>palevioletred         </td><td style="background:#DB7093;padding-right:65px"> </td><td>0xDB7093 </td>
<td>papayawhip            </td><td style="background:#FFEFD5;padding-right:65px"> </td><td>0xFFEFD5</td>
<td>peachpuff             </td><td style="background:#FFDAB9;padding-right:65px"> </td><td>0xFFDAB9</td></tr>
<tr><td>peru                  </td><td style="background:#CD853F;padding-right:65px"> </td><td>0xCD853F </td>
<td>pink                  </td><td style="background:#FFC0CB;padding-right:65px"> </td><td>0xFFC0CB</td>
<td>plum                  </td><td style="background:#DDA0DD;padding-right:65px"> </td><td>0xDDA0DD</td></tr>
<tr><td>powderblue            </td><td style="background:#B0E0E6;padding-right:65px"> </td><td>0xB0E0E6 </td>
<td>purple                </td><td style="background:#800080;padding-right:65px"> </td><td>0x800080</td>
<td>rebeccapurple         </td><td style="background:#663399;padding-right:65px"> </td><td>0x663399</td></tr>
<tr><td>red                   </td><td style="background:#FF0000;padding-right:65px"> </td><td>0xFF0000 </td>
<td>rosybrown             </td><td style="background:#BC8F8F;padding-right:65px"> </td><td>0xBC8F8F</td>
<td>royalblue             </td><td style="background:#4169E1;padding-right:65px"> </td><td>0x4169E1</td></tr>
<tr><td>saddlebrown           </td><td style="background:#8B4513;padding-right:65px"> </td><td>0x8B4513 </td>
<td>salmon                </td><td style="background:#FA8072;padding-right:65px"> </td><td>0xFA8072</td>
<td>sandybrown            </td><td style="background:#F4A460;padding-right:65px"> </td><td>0xF4A460</td></tr>
<tr><td>seagreen              </td><td style="background:#2E8B57;padding-right:65px"> </td><td>0x2E8B57 </td>
<td>seashell              </td><td style="background:#FFF5EE;padding-right:65px"> </td><td>0xFFF5EE</td>
<td>sienna                </td><td style="background:#A0522D;padding-right:65px"> </td><td>0xA0522D</td></tr>
<tr><td>silver                </td><td style="background:#C0C0C0;padding-right:65px"> </td><td>0xC0C0C0 </td>
<td>skyblue               </td><td style="background:#87CEEB;padding-right:65px"> </td><td>0x87CEEB</td>
<td>slateblue             </td><td style="background:#6A5ACD;padding-right:65px"> </td><td>0x6A5ACD</td></tr>
<tr><td>slategray             </td><td style="background:#708090;padding-right:65px"> </td><td>0x708090 </td>
<td>slategrey             </td><td style="background:#708090;padding-right:65px"> </td><td>0x708090</td>
<td>snow                  </td><td style="background:#FFFAFA;padding-right:65px"> </td><td>0xFFFAFA</td></tr>
<tr><td>springgreen           </td><td style="background:#00FF7F;padding-right:65px"> </td><td>0x00FF7F </td>
<td>steelblue             </td><td style="background:#4682B4;padding-right:65px"> </td><td>0x4682B4</td>
<td>tan                   </td><td style="background:#D2B48C;padding-right:65px"> </td><td>0xD2B48C</td></tr>
<tr><td>teal                  </td><td style="background:#008080;padding-right:65px"> </td><td>0x008080 </td>
<td>thistle               </td><td style="background:#D8BFD8;padding-right:65px"> </td><td>0xD8BFD8</td>
<td>tomato                </td><td style="background:#FF6347;padding-right:65px"> </td><td>0xFF6347</td></tr>
<tr><td>turquoise             </td><td style="background:#40E0D0;padding-right:65px"> </td><td>0x40E0D0 </td>
<td>violet                </td><td style="background:#EE82EE;padding-right:65px"> </td><td>0xEE82EE</td>
<td>wheat                 </td><td style="background:#F5DEB3;padding-right:65px"> </td><td>0xF5DEB3</td></tr>
<td>white                 </td><td style="background:#FFFFFF;padding-right:65px"> </td><td>0xFFFFFF </td>
<td>whitesmoke            </td><td style="background:#F5F5F5;padding-right:65px"> </td><td>0xF5F5F5</td>
<td>yellow                </td><td style="background:#FFFF00;padding-right:65px"> </td><td>0xFFFF00</td></tr>
<tr><td>yellowgreen           </td><td style="background:#9ACD32;padding-right:65px"> </td><td>0x9ACD32 </td></tr>
</table>
\endhtmlonly
