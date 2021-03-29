#include <memory>
#include "guiModule/gui.h"
#include "consts.h"
namespace game {
	namespace menuModule {
		class menu {
		public:
			menu();
			states run(std::shared_ptr<GUI::window>);
		private:
			GUI::button play;
			GUI::button exit;
			GUI::label title;
			GUI::mBackground bg;
		};
	}
}