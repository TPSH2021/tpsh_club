#include "gameSystem.h"
using namespace game;
using namespace gameModule;
int main()
{    // Program entry point.   
	Game game; 
	//game.m_window.setFramerateLimit(60);
	// Creating our game object.    
	while(!game.GetWindow()->IsDone()){
		// Game loop. 
		game.HandleInput();

		game.Update();  
		game.Render();
	}


}









//#ifdef _DEBUG
//#include "imgui.h"
//#include "imgui-SFML.h"
//#endif
//
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/System/Clock.hpp>
//#include <SFML/Window/Event.hpp>
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(640, 480), "");
//    window.setVerticalSyncEnabled(true);
//#ifdef _DEBUG
//    ImGui::SFML::Init(window);
//#endif
//
//    sf::Color bgColor;
//
//    float color[3] = { 0.f, 0.f, 0.f };
//
//    // let's use char array as buffer, see next part
//    // for instructions on using std::string with ImGui
//    char windowTitle[255] = "ImGui + SFML = <3";
//
//    window.setTitle(windowTitle);
//    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
//    sf::Clock deltaClock;
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//#ifdef _DEBUG
//            ImGui::SFML::ProcessEvent(event);
//#endif
//
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//#ifdef _DEBUG
//        ImGui::SFML::Update(window, deltaClock.restart());
//
//        ImGui::Begin("Sample window"); // begin window
//
//                                       // Background color edit
//        if (ImGui::ColorEdit3("Background color", color)) {
//            // this code gets called if color value changes, so
//            // the background color is upgraded automatically!
//            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
//            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
//            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
//        }
//
//        // Window title text edit
//        ImGui::InputText("Window title", windowTitle, 255);
//
//        if (ImGui::Button("Update window title")) {
//            // this code gets if user clicks on the button
//            // yes, you could have written if(ImGui::InputText(...))
//            // but I do this to show how buttons work :)
//            window.setTitle(windowTitle);
//        }
//        ImGui::End(); // end window
//#endif
//
//        window.clear(bgColor); // fill background with color
//#ifdef _DEBUG
//        ImGui::SFML::Render(window);
//#endif
//        window.display();
//    }
//#ifdef _DEBUG
//    ImGui::SFML::Shutdown();
//#endif
//}
