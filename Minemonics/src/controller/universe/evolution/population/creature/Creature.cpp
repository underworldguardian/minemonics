//# corresponding header
#include <controller/universe/evolution/population/creature/Creature.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers

BoostLogger Creature::mBoostLogger; /*<! initialize the boost logger*/
Creature::_Init Creature::_initializer;
Creature::Creature(Population* const population,
	const PhysicsController::PhysicsModelType physicsModelType,
	const Ogre::Vector3 position, const double branchiness) :
	mMarked(false) {
	// set up the creature model
	mCreatureModel = new CreatureModel(population->getPopulationModel(),
		physicsModelType, position);
	mCreatureModel->createRandomGenome(branchiness);
	mCreatureModel->initialize();

	// set up the phenotype
	mPhenotype.initialize(this);
	mPhenotype.setPhenotypeModel(mCreatureModel->getPhenotypeModel());

}

Creature::Creature(CreatureModel* const creatureModel) :
	mCreatureModel(creatureModel), mMarked(false) {
	mPhenotype.setPhenotypeModel(mCreatureModel->getPhenotypeModel());

	// set up the phenotype
	mPhenotype.initialize(this);
}

Creature::~Creature() {
	if (mCreatureModel) {
		delete mCreatureModel;
	}
	mCreatureModel = NULL;
//	mPhenotype
}

int Creature::performEmbryogenesis() {
	return mPhenotype.performEmbryogenesis();
}

void Creature::reset(const Ogre::Vector3 position) {
	mCreatureModel->reset(position);
	mPhenotype.reset(position);
}

void Creature::reset() {
	// develop creature if it is not developed yet.
	if (!isDeveloped()) {
		performEmbryogenesis();
	}
	reset(mCreatureModel->getInitialPosition());
}

void Creature::reposition(const Ogre::Vector3 position) {
	// develop creature if it is not developed yet.
	if (!isDeveloped()) {
		performEmbryogenesis();
	}
	mCreatureModel->reposition(position);
	mPhenotype.reposition(position);
}

void Creature::update(double timeSinceLastTick) {
	mCreatureModel->update(timeSinceLastTick);
	// Update the phenotype of the creature if it is in the world.
	if (mPhenotype.isInWorld()) {
		mPhenotype.update(timeSinceLastTick);
	}
}

int Creature::addToPhysicsWorld() {
	int limbQty = 0;
	// develop creature if it is not developed yet.
	if (!isDeveloped()) {
		performEmbryogenesis();
	}

	// Add phenotype to world
	limbQty = mPhenotype.addToPhysicsWorld();
	return limbQty;
}

int Creature::addToWorld() {
	int limbQty = 0;
	// develop creature if it is not developed yet.
	if (!isDeveloped()) {
		performEmbryogenesis();
	}

	std::vector<const DataSink*> controllerDatasinks =
		mPhenotype.getPhenotypeModel()->getControllerDataSinks();
	for (std::vector<const DataSink*>::const_iterator dit =
		controllerDatasinks.begin(); dit != controllerDatasinks.end(); dit++) {
		SimulationManager::getSingleton()->getViewController().getChaosControllerPanel()->addDataset(
			&(*dit)->getDataset());
	}

	std::vector<const DataSink*> jointDatasinks =
		mPhenotype.getPhenotypeModel()->getJointDataSinks();
	for (std::vector<const DataSink*>::const_iterator dit =
		jointDatasinks.begin(); dit != jointDatasinks.end(); dit++) {
		SimulationManager::getSingleton()->getViewController().getJointDynamicsPanel()->addDataset(
			&(*dit)->getDataset());
	}

	// Add phenotype to world
	limbQty = mPhenotype.addToWorld();
	return limbQty;
}

void Creature::removeFromWorld() {
	// Remove phenotype from world
	mPhenotype.removeFromWorld();

	SimulationManager::getSingleton()->getViewController().getChaosControllerPanel()->clearDatasets();
	SimulationManager::getSingleton()->getViewController().getJointDynamicsPanel()->clearDatasets();
}

void Creature::processJuries() {
	mCreatureModel->processJuries();
}

void Creature::calm() {
	mCreatureModel->calm();
}

CreatureModel* Creature::getCreatureModel() {
	return mCreatureModel;
}

void Creature::unlinkCreatureModel() {
	mCreatureModel = NULL;
}

void Creature::save(std::string folderPath) {
	std::string creatureFilePath;
	creatureFilePath.append(folderPath);
	creatureFilePath.append("/Creature-");
	creatureFilePath.append(
		boost::lexical_cast<std::string>(
			mCreatureModel->getLastFitnessScore())); // returns the last score available
	creatureFilePath.append("-");
	creatureFilePath.append(SimulationManager::getSingleton()->getTimeStamp());
	if (mMarked) {
		creatureFilePath.append("-marked");
	}
	creatureFilePath.append(".cr");

	SaveController<CreatureModel> creatureSaver;
	creatureSaver.save(*(getCreatureModel()), creatureFilePath.c_str());
}

void Creature::setPosition(const Ogre::Vector3 position) {
	mCreatureModel->setPosition(position);
}

PlanetModel* Creature::getPlanet() {
	return mCreatureModel->getPopulationModel()->getPlanetModel();
}

void Creature::setPlanet(PlanetModel* planetModel) {
	mCreatureModel->getPopulationModel()->setPlanetModel(planetModel);
}

bool Creature::isDeveloped() {
	return mCreatureModel->isDeveloped();
}

void Creature::setDeveloped(bool developed) {
	mCreatureModel->setDeveloped(developed);
}

void Creature::setCulled(bool culled) {
	mCreatureModel->setCulled(culled);
}

bool Creature::isCulled() const {
	return mCreatureModel->isCulled();
}

bool Creature::isMutated() const {
	return mCreatureModel->isMutated();
}

PhysicsController::PhysicsModelType Creature::getPhysicsModelType() {
	return mCreatureModel->getPhysicsModelType();
}

void Creature::addJury(Jury* jury) {
	mCreatureModel->addJury(jury);
}

void Creature::clearJuries() {
	mCreatureModel->clearJuries();
}

void Creature::setMutated(bool mutated) {
	mCreatureModel->setMutated(mutated);
}

void Creature::hasInterpenetrations() {
	mCreatureModel->hasInterpenetrations();
}
