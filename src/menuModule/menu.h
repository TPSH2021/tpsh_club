#include <memory>
#include "guiModule/gui.h"
namespace game {
	namespace menuModule {
		class menu {
		public:
			menu(std::shared_ptr<GUI::window>);
		private:
			GUI::button start;
			GUI::button exit;
			GUI::label title;

		};
	}
}