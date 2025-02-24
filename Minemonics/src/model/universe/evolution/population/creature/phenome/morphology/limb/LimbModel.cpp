//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger LimbModel::mBoostLogger; /*<! initialize the boost logger*/
LimbModel::_Init LimbModel::_initializer;
LimbModel::LimbModel() :
	mLimbPhysics(NULL), mCreatureModel(NULL), mParentJointIndex(0),mHadGroundContact(false) {
}

LimbModel::LimbModel(const LimbModel& limbModel) {
	mLimbPhysics = limbModel.mLimbPhysics->clone();
	mCreatureModel = limbModel.mCreatureModel;
	mParentJointIndex = limbModel.mParentJointIndex;
	mHadGroundContact = limbModel.mHadGroundContact;
}

LimbModel::~LimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;

	mCreatureModel = NULL;

	while (!mSensors.empty()) {
		delete mSensors.back();
		mSensors.pop_back();
	}

	mTactioceptors.clear();
}

void LimbModel::reset(Ogre::Vector3 position) {
	mLimbPhysics->reset(position);
	mHadGroundContact = false;
}

void LimbModel::reposition(Ogre::Vector3 position) {
	mLimbPhysics->reposition(position);
	mHadGroundContact = false;
}

bool LimbModel::equals(const LimbModel& limbModel) const {
	if (!ComponentModel::equals(limbModel)) {
		return false;
	}

	if (!mLimbPhysics->equals(*limbModel.mLimbPhysics)) {
		return false;
	}

	return true;
}

void LimbModel::activateTactioceptors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(true);
	}
	mHadGroundContact = true;
}

void LimbModel::resetSensors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(false);
	}
}

void LimbModel::update(double timeSinceLastTick) {

	for (std::vector<Sensor*>::iterator sit = mSensors.begin();
		sit != mSensors.end(); sit++) {
		(*sit)->update(timeSinceLastTick);
	}

//	std::cout << std::endl << "TactileSensors:";
//	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
//			tit != mTactioceptors.end(); tit++) {
//		std::cout << (*tit)->isTouched() << "|";
//	}
//	std::cout << std::endl;

// reset the sensors when they are processed
	resetSensors();
}

/**
 * The the limb physics model of the limb.
 * @return The limb physics model of the limb.
 */
LimbPhysics* LimbModel::getLimbPhysics() const {
	return mLimbPhysics;
}

/**
 * Get the position of the limb in the physical world.
 * @return The position of the limb in the physical world.
 */
const Ogre::Vector3 LimbModel::getPosition() const {
	return OgreBulletUtils::convert(mLimbPhysics->getPosition());
}

const double LimbModel::getVolume() const {
	return mLimbPhysics->getVolume();
}

/**
 * Get the orientation of the limb in the physical world.
 * @return The orientation of the limb in the physical world.
 */
const Ogre::Quaternion LimbModel::getOrientation() const {
	return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
}

void LimbModel::setInterpenetrationDepth(double interpenetrationDepth) {
	mLimbPhysics->setInterpenetrationDepth(interpenetrationDepth);
}

void LimbModel::calm() {
	mLimbPhysics->calm();
}

double LimbModel::getInterpenetrationDepth() {
	return mLimbPhysics->getInterpenetrationDepth();
}

const Ogre::ColourValue LimbModel::getColor() const {
	return mLimbPhysics->getColor();
}

const LimbPhysics::PrimitiveType LimbModel::getPrimitiveType() const {
	return mLimbPhysics->getType();
}

const Ogre::Vector3 LimbModel::getDimensions() const {
	return mLimbPhysics->getDimensions();
}

std::ostream & operator<<(std::ostream &os, const LimbModel &limbModel) {
	os << "LimbModel: LimbPhysics=" << (*limbModel.mLimbPhysics)
		<< "/ParentJointIndex=" << limbModel.mParentJointIndex;

	os << "/ChildJointIndices=[";
	for (std::vector<std::vector<JointModel*>::size_type>::const_iterator it =
		limbModel.mChildJointIndices.begin(); /**!< The vector of child joint indices.*/
	it != limbModel.mChildJointIndices.end(); it++) {
		os << (*it);
		os << "||";
	}
	os << "]/Sensors=[";

	for (std::vector<Tactioceptor*>::const_iterator it =
		limbModel.mTactioceptors.begin(); /**!< The vector of tactioceptors.*/
	it != limbModel.mTactioceptors.end(); it++) {
		os << (**it);
		os << "||";
	}
	os << "]";
	return os;
}

const Ogre::Vector3 LimbModel::getVelocities() const {
	return mLimbPhysics->getVelocities();
}

std::vector<ControlInput*> LimbModel::getControlInputs() {
	std::vector<ControlInput*> mControlInputs;

	return mControlInputs;
}

std::vector<ControlOutput*> LimbModel::getControlOutputs() {
	std::vector<ControlOutput*> mControlOutputs;

	mControlOutputs.insert(mControlOutputs.end(),mSensors.begin(),mSensors.end()); // Insert all sensor

	return mControlOutputs;
}

void LimbModel::setControlInputs(std::vector<ControlOutput*> controlInputs) {
	//TODO: Implement set control inputs as soon as it is needed
}

void LimbModel::setControlOutputs(std::vector<ControlInput*> controlOutputs) {
	//TODO: Implement set control inputs as soon as it is needed
}

void LimbModel::storeControlIndices() {
	//TODO: Implement store control indices as soon as it is needed
}
