#pragma once

#include <memory>

namespace game {
	namespace dialogModule {
		class dialogDataInterface {
			//...
			// implement getters and setters for dialogData fields
			
		};
		class dialogSystemInterface {
			virtual ~dialogSystemInterface() = delete;
			virtual bool addDialog(std::unique_ptr<dialogDataInterface>) = 0;
			virtual std::weak_ptr<dialogDataInterface> getDialog() = 0;
		};
	}
}
