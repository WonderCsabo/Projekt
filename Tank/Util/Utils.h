#pragma once

template<typename Container>
void clearPointerContainer(Container& cont) {
	while(!cont.empty()) {
		delete cont.back();
		cont.pop_back();
	}
}