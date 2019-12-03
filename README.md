# guidom

This project is a research API for the C++ 17 and above language to provide a document object model. 
The product is designed to be cross platform. 
Currently the macOS, iOS, and Android NDK library needs research. The template dom library works 
precisely with the standard library without adding new data types. It supports rapid development and 
incorporates a small set of memorable names within its model. It is a templated oriented 
implementation for higher performance and integrated syntax. It offers the document 
object model integrated with C++ language as a natural syntax that appears like HTML because of the use of <>.
The following development platforms and rendering
technologies are capable of use for development and distribution.

<ul>
<li>Microsoft Windows
<li>Linux
<li>macOS
<li>iOS
<li>Android NDK (native development kit)
</ul>

Supported C++ compilers
<ul>
<li>Microsoft Visual Studio
<li>GCC
<li>clang
<li>Objective C
</ul>

Rendering Engines

There are numerous possibilities for the model's occupancy within the developer’s toolbox. 
The system provides these capabilities through well documented preprocessor definitions. 
That is, compiling for each of these types of environments is established as simply turning 
a definition on or off. Some of these project types require third party libraries for linking.
Optionally linking can be static or runtime dynamic.

<ul>
<li>Embedded internal
<li>Embedded external
<li>Embedded advanced image processing external
<li>Cross platform Desktop application model
<li>Cross platform application model with advanced image processing
<li>Qt client cross platform Dom
<li>GTK++ client cross platform Dom
<li>WxWidgets client cross platform Dom
<li>Chrome Embedded Framework
<li>Gecko Layout Engine
<li>Windows OS specific 
<li>XCB Linux Application
<li>X11 Linux Application
<li>X11 Linux Desktop
<li>Android OS specific
</ul>

      #include "viewManager.hpp"
      using namespace std;
      using namespace ViewManager;

      #if defined(__linux__)int main(int argc, char **argv) {
      // handle command line here...
      #elif defined(_WIN64)int WINAPI WinMain(HINSTANCE /* hInstance */, HINSTANCE /* hPrevInstance */,                   
            LPSTR lpCmdLine, int /* nCmdShow */) {
            // command line
       #endif 

       auto &vm = createElement<Viewer>(
              objectTop{10_pct}, objectLeft{10_pct}, objectHeight{80_pct},      
              objectWidth{80_pct}, textFace{"arial"}, textSize{16_pt}, textWeight{400},      
              textIndent{2_em}, lineHeight::normal, textAlignment::left,      
              position::relative, paddingTop{5_pt}, paddingLeft{5_pt},      
              paddingBottom{5_pt}, paddingRight{5_pt}, marginTop{5_pt},      
              marginLeft{5_pt}, marginBottom{5_pt}, marginRight{5_pt});  

              vm << "Hello World\n";  
              vm.render();
        }
