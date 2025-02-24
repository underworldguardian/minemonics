//# corresponding headers
#include <model/Serializable.hpp>
#include <controller/universe/evolution/population/Population.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

BoostLogger Population::mBoostLogger; /*<! initialize the boost logger*/
Population::_Init Population::_initializer;
Population::Population() :
	mPlanet(NULL) {
	mPopulationModel = new PopulationModel();

}
Population::Population(Planet* const planet, const int creatureQty) :
	mPlanet(planet) {
	mPopulationModel = new PopulationModel(planet->getPlanetModel(),
		creatureQty);

	initialize();
}

Population::Population(Planet* const planet, const int creatureQty,
	const Ogre::Vector3 initialPosition) :
	mPlanet(planet) {
	mPopulationModel = new PopulationModel(planet->getPlanetModel(),
		creatureQty, initialPosition);

	initialize();
}

Population::Population(PopulationModel* const populationModel) :
	mPlanet(NULL), mPopulationModel(populationModel) {
}

Population::~Population() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		delete (*cit);
	}
	mCreatures.clear();

	delete mPopulationModel;
	mPopulationModel = NULL;

	mPlanet = NULL;
}

void Population::perturbCreatureControllers() {
	mPopulationModel->perturbCreatureControllers();
}

void Population::initialize() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup population...";
	//initialize the population model with zero creatures.
	mPopulationModel->initialize();
	resyncWithModel();
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup population...done.";
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(const double branchiness,
	const Ogre::Vector3 rootPosition) {
	//add new creature
	Creature* creature = new Creature(this, mPlanet->getPhysicsModelType(),
		rootPosition, branchiness);
	addMember(creature);
}

void Population::addMember(Creature* const creature) {
	mCreatures.push_back(creature);

	//hand model down to the population model
	mPopulationModel->addMember(creature->getCreatureModel());
}

void Population::update(double timeSinceLastTick) {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->update(timeSinceLastTick);
	}
}

void Population::reset() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->reset();
	}
}

int Population::addToPhysicsWorld() {
	int limbQty = 0;
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		limbQty = (*cit)->addToPhysicsWorld();
	}
	return limbQty;
}

int Population::addToWorld() {
	int limbQty = 0;
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		limbQty += (*cit)->addToWorld();
	}
	return limbQty;
}

void Population::removeFromWorld() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->removeFromWorld();
	}
}

void Population::resyncWithModel() {

	//remove the creatures that were culled
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end();) {
		if ((*cit)->isCulled()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature culled.";

			delete *cit; // deletes creature model, it is already removed from mPopulationModel->getCreatureModels()
			cit = mCreatures.erase(cit);
		} else {
			cit++;
		}
	}

	// resync mutated creatures
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end();) {
		if ((*cit)->isMutated()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature mutated.";

			CreatureModel* creatureModel = (*cit)->getCreatureModel(); // keep the creature model to be put into a new controller
			(*cit)->unlinkCreatureModel(); // unlink and delete the old controller
			delete *cit;
			cit = mCreatures.erase(cit);

			Creature* creature = new Creature(creatureModel); // generate a new controller for the mutated creature
			creature->setMutated(false);
			mCreatures.push_back(creature);
		} else {
			cit++;
		}
	}

	// add creatures that were newly born.
	for (std::vector<CreatureModel*>::const_iterator cit =
		mPopulationModel->getCreatureModels().begin();
		cit != mPopulationModel->getCreatureModels().end(); cit++) {
		if ((*cit)->isNew()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Creature added.";
			Creature* creature = new Creature(*cit);
			mCreatures.push_back(creature);
			(*cit)->setNew(false);
		}
	}

	mPopulationModel->setOutOfSync(false);
}

void Population::process() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->processJuries();
	}
}

bool Population::hasInterpenetrations() {
	return mPopulationModel->hasInterpenetrations();
}

double Population::maxJointVelocity() {
	return mPopulationModel->getMaxJointVelocity();
}

double Population::maxHeight(){
	return mPopulationModel->getMaxHeight();
}

void Population::markCull() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->setCulled(true);
	}
}

void Population::calm() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
		cit != mCreatures.end(); cit++) {
		(*cit)->calm();
	}
}

bool Population::isOutOfSync() const {
	return mPopulationModel->isOutOfSync();
}

void Population::setOutOfSync(const bool outOfSync) {
	mPopulationModel->setOutOfSync(outOfSync);
}

void Population::setSerializationPath(std::string path) {
	mPopulationModel->setSerializationPath(path);
}

const std::string Population::getSerializationPath() const {
	return mPopulationModel->getSerializationPath();
}

const int Population::getCurrentGeneration() const {
	return mPopulationModel->getCurrentGeneration();
}

void Population::save() {
	mPopulationModel->save();
}

void Population::load() {
	mPopulationModel->load();
	initialize();
}

const std::string Population::getGenerationSerializationPath() {
	return mPopulationModel->getGenerationSerializationPath();
}

void Population::clearJuries() {
	mPopulationModel->clearJuries();
}
