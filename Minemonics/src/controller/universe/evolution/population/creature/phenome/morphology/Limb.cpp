//# corresponding headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbO3D.hpp>

//## utils headers

BoostLogger Limb::mBoostLogger; /*<! initialize the boost logger*/
Limb::_Init Limb::_initializer;
Limb::Limb() :
	mLimbGraphics(NULL), mCreature(NULL), mLimbModel(NULL) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Limb created.";
}

Limb::Limb(const Limb& limb) :
	mLimbModel(limb.mLimbModel) {
	mCreature = limb.mCreature;
	mLimbGraphics = limb.mLimbGraphics->clone();
}

Limb::Limb(Creature* const creature, LimbModel* const limbModel) {
	mLimbModel = limbModel;
	mCreature = creature;

	// Define the new component as a limb
	Component::initialize(limbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D(mLimbModel);

//	// Update the state of the limb.
	update(0);
}

Limb::~Limb() {
	delete mLimbGraphics;
	mLimbGraphics = NULL;

	mLimbModel = NULL;

	mCreature = NULL;
}

void Limb::initialize(Creature* const creature,
	const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const int ownIndex) {

	//initialize the model of the limb
	switch (creature->getPhysicsModelType()) {
	case PhysicsController::RigidbodyModel:
		mLimbModel =
			new SRBLimbModel(
				creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				creature->getCreatureModel(), type, position, orientation,
				initialRelativePosition, initialOrientation, dimensions, mass,
				restitution, friction, color, isIntraBodyColliding, ownIndex);
		break;
	case PhysicsController::FeatherstoneModel:
		mLimbModel =
			new FSLimbModel(
				creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				creature->getCreatureModel(), type, position, orientation,
				initialRelativePosition, initialOrientation, dimensions, mass,
				restitution, friction, color, isIntraBodyColliding, ownIndex);
		break;
	default:
		break;
	}

	mLimbModel->initialize();

	mCreature = creature;

	// Define the new component as a limb
	Component::initialize(mLimbModel);

	// initialize the graphics part of the limb
	mLimbGraphics = new LimbO3D(mLimbModel);

	// Update the state of the limb.
	update(0);
}

/**
 * Update the state of the limb.
 */
void Limb::update(double timeSinceLastTick) {
	//update the limb graphics
	mLimbModel->update(timeSinceLastTick);
	mLimbGraphics->update(timeSinceLastTick);
}

void Limb::reset(const Ogre::Vector3 position) {
	mLimbModel->reset(position);
}

void Limb::reposition(const Ogre::Vector3 position) {
	mLimbModel->reposition(position);
}

Limb* Limb::clone() {
	return new Limb(*this);
}

/**
 * Add the limb to the physics world.
 */
void Limb::addToPhysicsWorld() {

	if (!getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->addToWorld();
	}
}

/**
 * Add the limb to the world.
 */
void Limb::addToWorld() {
	if (!mLimbGraphics->isInWorld()) {
		mLimbGraphics->addToWorld();
	}

	if (!getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->addToWorld();
	}
}

/**
 * Remove the limb from the world.
 */
void Limb::removeFromWorld() {
	if (mLimbGraphics->isInWorld()) {
		mLimbGraphics->removeFromWorld();
	}

	if (getLimbPhysics()->isInWorld()) {
		getLimbPhysics()->removeFromWorld();
	}
}

const Ogre::Vector3 Limb::getPosition() const {
	return mLimbModel->getPosition();
}

const Ogre::Quaternion Limb::getOrientation() const {
	return mLimbModel->getOrientation();
}

/**
 * Get the Graphics part of the limb.
 */
LimbGraphics* const Limb::getLimbGraphics() const {
	return mLimbGraphics;
}

/**
 * Get the Physics part of the limb.
 */
LimbPhysics* const Limb::getLimbPhysics() const {
	return mLimbModel->getLimbPhysics();
}
