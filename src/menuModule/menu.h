#include <memory>
#include "guiModule/gui.h"
#include "consts.h"
namespace game {
	namespace menuModule {
		class menu {
		public:
			menu(const sf::Font& font);
			states run(GUI::window*);
		private:
			GUI::button play;
			GUI::button exit;
			GUI::mBackground bg;
		};
	}
}