//# corresponding header
#include <view/visualization/CEGUI/configpanels/LoadPlanetPanel.hpp>

//# system header
#include <stddef.h>
#include <string>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

LoadPlanetPanel::LoadPlanetPanel(const int left, const int top,
	const std::string name) :
	FileDialog(left, top, name, MovablePanel::LOAD_PANEL) {

}

LoadPlanetPanel::~LoadPlanetPanel(void) {
}

void LoadPlanetPanel::openFile(std::string filePath) {
	Planet* planet = new Planet();
	planet->setSerializationPath(filePath);
	planet->load();
	SimulationManager::getSingleton()->getUniverse().addPlanet(planet);

	//set planet selected because it was the last one loaded
	SimulationManager::getSingleton()->getStateHandler().setCurrentlySelectedPlanet(
		planet);
	this->hide();
}
