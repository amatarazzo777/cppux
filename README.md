# guidom

This is the new format in research for C++ 17 and above. The product is designed to be cross platform. 
Currently the macOS, iOS, and Android NDK library needs research. The template dom library works 
precisely with the standard library without adding new data types. It supports rapid development and 
incorporates a small set of memorable names within its model. it is a templated oriented coded 
implementation for higher performance than any of the preceding syntaxes. It offers the document 
object model integrated with C++ language as a natural syntax that appears like HTML because of the use of <>.
The product is designed to be a cross platform product line. The following development platforms and 
technologies are capable of use for development and distribution.

●Microsoft Windows
●Linux
●macOS
●iOS
●Android NDK (native development kit)

Supported C++ compilers
●Microsoft Visual Studio
●GCC
●clang
●Objective C

Rendering Engine
sThere are numerous possibilities for the model's occupancy within the developer’s toolbox. 
The system provides these capabilities through well documented preprocessor definitions. 
That is, compiling for each of these types of environments is established as simply turning 
a definition on or off. Some of these project types require third party libraries for linking.
Optionally linking can be static or runtime dynamic.

●Embedded internal
●Embedded external
●Embedded advanced image processing external
●Cross platform Desktop application model
●Cross platform application model with advanced image processing
●Qt client cross platform Dom
●GTK++ client cross platform Dom

●WxWidgets client cross platform Dom
●Chrome Embedded Framework
●Gecko Layout Engine
●Windows OS specific 
●XCB Linux Application
●X11 Linux Application
●X11 Linux Desktop
●Android OS specific

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
