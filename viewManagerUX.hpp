/**
\author Anthony Matarazzo
\file viewManagerUX.hpp
\date 11/19/19
\version 1.0
\brief This header file contains the entirety of the base UX namespace.

*/
#pragma once

#if defined(__linux__)
#define XK_MISCELLANY
#include <X11/keysymdef.h>

#endif

/**

*/
#if defined(__linux__)
#define UX_LEFT XK_Left
#define UX_RIGHT XK_Right
#define UX_BACK XK_BackSpace
#define UX_RETURN XK_Return
#define UX_HOME XK_Home
#define UX_END XK_End

#elif defined(_WIN64)
#define UX_LEFT VK_LEFT
#define UX_RIGHT VK_RIGHT
#define UX_BACK VK_BACK
#define UX_RETURN VK_RETURN
#define UX_HOME VK_HOME
#define UX_END VK_END

#endif

/**
\namespace UX
\brief The UX namespace encapsulates the base user interface objects.
\details The UX namespace provides a library of user interface controls.
Each of the user interface components derives from the Element base class.
The creation and invocation of them is exactly the same as creating
other types of document entities. For example, to create a
textbox, it is:

\snippet examples.cpp ux_text
*/
using namespace viewManager;

namespace UX {

/**
\addtogroup UXcontrols UX Interface Controls

The UX Interface Controls provides a library of standard
editing components. Common controls that are available to the w3c
web browser are supported in addition to a few more advanced
controls such as accordion and menu.

@{
*/

/**
\class text
\extends viewManaager::Element
\brief user interface element for a text control.
\details The text user interface control is a textual editing component.
The user may edit a single line of text. This is useful for fields on a
dialog.

Example
-------
\snippet examples.cpp ux_text
*/
using text = class text : public viewManager::Element {
public:
  int position;

public:
  void render(Visualizer::platform &device) {
    Element::render(device);
    device.drawCaret(position * 10, data().size() * 20 +400, 20);
  }

  text(const std::vector<std::any> &attribs) : Element("ux::text") {
    setAttribute(attribs);
    position = 0;

    if (data().size() == 0)
      data().push_back("");

    eventHandler fnPress = [&](const event &e) {
      // the data string vector is used for base communication
      std::string &buffer = data().back();

      if (this->position < buffer.size())
        buffer[this->position] = e.key;
      else
        buffer += e.key;

      this->position++;
    };

    addListener(eventType::keypress, fnPress);

    eventHandler fnDn = [&](const event &e) {
      // the data string vector is used for base communication
      if (e.bVirtualKey) {
        switch (e.virtualKey) {
        case UX_LEFT:
          this->position--;
          break;
        case UX_RIGHT:
          this->position++;
          break;
        case UX_HOME:
          this->position = 0;
          break;
        case UX_BACK:
          if(this->position>0) {
            data().back().erase(this->position-1);
            this->position--;
          }
          break;

        case UX_END:
          this->position = data().back().size();
          break;
        case UX_RETURN:
          data().push_back("");
          this->position = 0;
          break;
        }
      }
    };
    addListener(eventType::keydown, fnDn);

    // set up the document state.
    auto &state = getElement("_root").getAttribute<documentState>();
    state.focusField = this;
  }
};

/**
\class password
\extends viewManager::Element
\brief user interface element for a password control.
\details The password control provides a non copy-able password
entry. When the user enters a password '*' appear instead of the
key pressed. This maintains the secrecy of the password.

Example
-------
\snippet examples.cpp ux_password
*/
using password = class password : public viewManager::Element {
public:
  password(const std::vector<std::any> &attribs) : Element("ux::password") {
    setAttribute(attribs);
  }
};

/**
\class multiline
\extends viewManager::Element
\brief The multiline interface control provides a field whereby the user
may edit multiple lines of text.

\details The multiline edit control provides editing of multiple lines of
text. The information is set using the data attribute.

Example
-------
\snippet examples.cpp ux_multiline
*/
using multiline = class multiline : public viewManager::Element {
public:
  multiline(const std::vector<std::any> &attribs) : Element("ux::multiline") {
    setAttribute(attribs);
  }
};

/**
\class number
\extends viewManager::Element
\brief editing component for entry of numerical data.
\details The number control provides the entry and editing of numerical
information. The data<short>(), data<unsigned short>(), data<int>(),
data<unsigned int>(), data<float>(), or data<double>() may be used to input
values into the control. The attribute numericalFormat is used to set the
edit mode. The attribute numericalBound is used to set the lower and upper
range of the allowed information.

Example
-------
\snippet examples.cpp ux_number
*/
using number = class number : public viewManager::Element {
public:
  number(const std::vector<std::any> &attribs) : Element("ux::number") {
    setAttribute(attribs);
  }
};

/**
\class masked
\extends viewManager::Element
\brief A control where masked characters may be used to format the
input.
\details  The masked edit control provides the ability to enter
a field whereby a masked is overlapped.

Example
-------
\snippet examples.cpp ux_masked
*/
using masked = class masked : public viewManager::Element {
public:
  masked(const std::vector<std::any> &attribs) : Element("ux::masked") {
    setAttribute(attribs);
  }
};

/**
\class pushButton
\extends viewManager::Element
\brief provides a button control.
\details The pushButton user interface control provides a button
element whereby the caption held within the data() property is shown.
The onclick event may be programmed to respond to the user when they
press the button.

Example
-------
\snippet examples.cpp ux_pushButton
*/
using pushButton = class pushButton : public viewManager::Element {
public:
  pushButton(const std::vector<std::any> &attribs) : Element("ux::pushButton") {
    setAttribute(attribs);
  }
};

/**
\class radioButton
\extends viewManager::Element
\brief provides a selection from a grouped collection of radioButtons.
\details The radioButton user interface control provides a selection of
one radioButton element from a grouped collection of radioButtons. When one
radio button is selected all others revert to non selected.

Example
-------
\snippet examples.cpp ux_radioButton
*/
using radioButton = class radioButton : public viewManager::Element {
public:
  radioButton(const std::vector<std::any> &attribs)
      : Element("ux::radioButton") {
    setAttribute(attribs);
  }
};
/**
\class hotImage
\extends viewManager::Element
\brief provides inline raytraced images.
\details The hotImage control provides a method of ray tracing images for
near real time display. The scene file must be specified within the
data() property.

Example
-------
\snippet examples.cpp ux_hotImage
*/
using hotImage = class hotImage : public viewManager::Element {
public:
  hotImage(const std::vector<std::any> &attribs) : Element("ux::hotImage") {
    setAttribute(attribs);
  }
};
/**
\class group
\extends viewManager::Element
\brief provides grouping of elements such as radioButtons.
\details The group control provides a framed border typically
surrounding a number of radioButtons. When multiple radioButtons
exists within the frame group, only one may be selected.

Example
-------
\snippet examples.cpp ux_group
*/
using group = class group : public viewManager::Element {
public:
  group(const std::vector<std::any> &attribs) : Element("ux::group") {
    setAttribute(attribs);
  }
};
/**
\class checkBox
\extends viewManager::Element
\brief  provides a check on or off switch for the selection.
\details The checkBox control provides an on/off switch or toggle.
The attribute checked provides a Boolean value that when true means
that the checkBox is selected.

Example
-------
\snippet examples.cpp ux_checkBox
*/
using checkBox = class checkBox : public viewManager::Element {
public:
  checkBox(const std::vector<std::any> &attribs) : Element("ux::checkBox") {
    setAttribute(attribs);
  }
};
/**
\class date
\extends viewManager::Element
\brief  provides entry of a standard date.
\details The date control provides entry of a standard date.
Information into the control can be placed within the data<std::cdate>()
or data<string>().

Example
-------
\snippet examples.cpp ux_date
*/
using date = class date : public viewManager::Element {
public:
  date(const std::vector<std::any> &attribs) : Element("ux::date") {
    setAttribute(attribs);
  }
};
/**
\class dateTime
\extends viewManager::Element
\brief  The dateTime control provides the entry mechanism of a valid date.
\details The control provides the ability for a user to enter or select
from a calendar view a date.

Example
-------
\snippet examples.cpp ux_dateTime
*/
using dateTime = class dateTime : public viewManager::Element {
public:
  dateTime(const std::vector<std::any> &attribs) : Element("ux::dateTime") {
    setAttribute(attribs);
  }
};
/**
\class week
\extends viewManager::Element
\brief The control provides the ability to select from a valid list of a week
number from a year.
\details The week control provides the ability to enter or select from a list
a valid week number for a particular year.

Example
-------
\snippet examples.cpp ux_week
*/
using week = class week : public viewManager::Element {
public:
  week(const std::vector<std::any> &attribs) : Element("ux::week") {
    setAttribute(attribs);
  }
};
/**
\class time
\extends viewManager::Element
\brief provides entry of a numerical time.
\details The time entry component allows the user to edit
a time based value.

Example
-------
\snippet examples.cpp ux_time
*/
using time = class time : public viewManager::Element {
public:
  time(const std::vector<std::any> &attribs) : Element("ux::time") {
    setAttribute(attribs);
  }
};
/**
\class file
\extends viewManager::Element
\brief  selection of a file from a local directory.
\details The file selection list displays when the user clicks
on the file button.

Example
-------
\snippet examples.cpp ux_file
*/
using file = class file : public viewManager::Element {
public:
  file(const std::vector<std::any> &attribs) : Element("ux::file") {
    setAttribute(attribs);
  }
};
/**
\class verticalScrollbar
\extends viewManager::Element
\brief a scroll bar.
\details Provides the vertical scroll component of the user
interface library. Users may move the position of the graph to
typically scroll the contents of an inner frame. The onchange
event occurs when the user interacts with the control.

Example
-------
\snippet examples.cpp ux_verticalScrollbar
*/
using verticalScrollbar =
    class verticalScrollbar : public viewManager::Element {
public:
  verticalScrollbar(const std::vector<std::any> &attribs)
      : Element("ux::verticalScrollbar") {
    setAttribute(attribs);
  }
};
/**
\class horizontalScrollbar
\extends viewManager::Element
\brief scroll bar for horizontal.
\details The horizontalScrollbar provides a horizontal scrolling aparatus
for user interface interaction.

Example
-------
\snippet examples.cpp ux_horizontalScrollbar
*/
using horizontalScrollbar =
    class horizontalScrollbar : public viewManager::Element {
public:
  horizontalScrollbar(const std::vector<std::any> &attribs)
      : Element("ux::horizontalScrollbar") {
    setAttribute(attribs);
  }
};
/**
\class resizerVertical
\extends viewManager::Element
\brief  provides a resizing control for the vertical position.
\details The resizerVertical allows a user to extend or shrink an area
which it is attached to. The modification and repainting of the contents
are automatically updated as the user drags the handle bars.

Example
-------
\snippet examples.cpp ux_resizerVertical
*/
using resizerVertical = class resizerVertical : public viewManager::Element {
public:
  resizerVertical(const std::vector<std::any> &attribs)
      : Element("ux::resizerVertical") {
    setAttribute(attribs);
  }
};
/**
\class resizerHorizontal
\extends viewManager::Element
\brief
\brief  Provides a resizing control for the horizontal position.
\details The resizerHorizontal allows a user to extend or shrink an area
which it is attached to. The modification and repainting of the contents
are automatically updated as the user drags the handle bars.

Example
-------
\snippet examples.cpp ux_resizerHorizontal
*/
using resizerHorizontal =
    class resizerHorizontal : public viewManager::Element {
public:
  resizerHorizontal(const std::vector<std::any> &attribs)
      : Element("ux::resizerHorizontal") {
    setAttribute(attribs);
  }
};
/**
\class listSelector
\extends viewManager::Element
\brief provides a dropdown combo for the selection of an item. When
the listSize attribute is set, the list may be configured to show more than
one option at a time.
\details The listSelector control provides a dual capability control for the
user to select from a list of items. The control can be configured as a drop
down combo or as a list box. Setting the listSize property to more than one
provides the capability for it to display as a listbox.

Example
-------
\snippet examples.cpp ux_listSelector
*/
using listSelector = class listSelector : public viewManager::Element {
public:
  listSelector(const std::vector<std::any> &attribs)
      : Element("ux::listSelector") {
    setAttribute(attribs);
  }
};
/**
\class menu
\extends viewManager::Element
\brief The menu control provides a drop down menu or a contextual
menu.
\details The menu control allows the developer to attach a drop
down menu to a particular element. Normally for an application level
menu, the menu should be attached to the Viewer object. However,
it can be attached to any element.

Example
-------
\snippet examples.cpp ux_menu
*/
using menu = class menu : public viewManager::Element {
public:
  menu(const std::vector<std::any> &attribs) : Element("ux::menu") {
    setAttribute(attribs);
  }
};
/**
\class gridEdit
\extends viewManager::Element
\brief The gridEdit control provides the ability to edit information
in a spread sheet like fashion.
\details The gridEdit control provides an advanced editing feature much
like the JavaScript variations found within the jQuery library. The control
provides the ability to define the type of editing component on
a columnar basis.

Example
-------
\snippet examples.cpp ux_gridEdit
*/
using gridEdit = class gridEdit : public viewManager::Element {
public:
  gridEdit(const std::vector<std::any> &attribs) : Element("ux::gridEdit") {
    setAttribute(attribs);
  }
};
/**
\class tabbedPanel
\extends viewManager::Element
\brief The tabbedPanel control provides the ability to show a note book style
interface.
\details The tabbedPanel control allows the developer to show a note book
style interface whereby the user may select from a thumb titled display from
the top, bottom, left or right side of the panel. Each of the views are hidden
from view until activated. The control provides the ability to consolidate
many settings and details within one view. The user simply chooses the tab to
show, and that particular notebook entry is shown within the view.

Example
-------
\snippet examples.cpp ux_tabbedPanel
*/
using tabbedPanel = class tabbedPanel : public viewManager::Element {
public:
  tabbedPanel(const std::vector<std::any> &attribs)
      : Element("ux::tabbedPanel") {
    setAttribute(attribs);
  }
};

/**
\class sliderRange
\extends viewManager::Element
\brief  Provides a selection of a number from a valid range.
\details The sliderRange control provides the ability to set
numerical values as a range. The control features a movable
handle which changes the value when moved from the left or right.
Alternatively, the control can be configured to show
a vertical style range.

Example
-------
\snippet examples.cpp ux_sliderRange
*/
using sliderRange = class sliderRange : public viewManager::Element {
public:
  sliderRange(const std::vector<std::any> &attribs)
      : Element("ux::sliderRange") {
    setAttribute(attribs);
  }
};
/**
\class knobRange
\extends viewManager::Element
\brief Provides the setting of a numerical value based upon the position
of a simulated knob within the view. The know appears similar to that
of a volume control common on electronic equipment.

\details The knobRange control provides the ability to select a numerical
value based upon its position. Within the view, the know has a pointing
setting which notes the value from the range. The knob is limited to
approximately 300 degrees of revolution.

Example
-------
\snippet examples.cpp ux_knobRange
*/
using knobRange = class knobRange : public viewManager::Element {
public:
  knobRange(const std::vector<std::any> &attribs) : Element("ux::knobRange") {
    setAttribute(attribs);
  }
};
/**
\class accordion
\extends viewManager::Element
\brief  The accordion control provides a similar operation of a notebook
interface but appears more as its jQuery counterpart.

\details The accordion control provides the ability to consolidate
and group document elements that are contained within a DIV. The default
view for the accordion is the tabs appear on the left.

Example
-------
\snippet examples.cpp ux_accordion
*/
using accordion = class accordion : public viewManager::Element {
public:
  accordion(const std::vector<std::any> &attribs) : Element("ux::accordion") {
    setAttribute(attribs);
  }
};
/**
\class progress
\extends viewManager::Element
\brief The progress control provides the summary of a graph to show
completness of an operation.

\details The progress user interface control provides the visual queue of a
graph to show an operation's completeness. These types of graphs are typically
shown for long processing items such as a downloading file or a lengthy
calculation.

Example
-------
\snippet examples.cpp ux_progress
*/
using progress = class progress : public viewManager::Element {
public:
  progress(const std::vector<std::any> &attribs) : Element("ux::progress") {
    setAttribute(attribs);
  }
};
/**
\class dialog
\extends viewManager::Element
\brief The dialog control provides an inner frame window that can be
moved and re-positioned by the user.

\details The dialog user interface element provides a popup interface
window whereby a form may be displayed that is independent of the main
window that it obscures. This window may be moved by the user to
show information that might be hidden by it. The window has a title
bar at the top which notes the developer set title. The contents
is directly controlled by the children and operates as any other
Element does.

Example
-------
\snippet examples.cpp ux_dialog
*/
using dialog = class dialog : public viewManager::Element {
public:
  dialog(const std::vector<std::any> &attribs) : Element("ux::dialog") {
    setAttribute(attribs);
  }
};
/** @}*/

}; // namespace UX
