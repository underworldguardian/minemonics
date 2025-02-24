#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_
//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/Serializable.hpp>

//# forward declarations
class PopulationModel;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

//## controller headers
//## model headers
// include headers that implement a archive in xmlformat
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/juries/Jury.hpp>
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/Genome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
#include <model/universe/evolution/juries/AverageHeight.hpp>
#include <model/universe/evolution/juries/AverageVelocity.hpp>
#include <model/universe/evolution/juries/GroundContactRatio.hpp>
#include <model/universe/evolution/juries/GroundContactQty.hpp>
#include <model/universe/evolution/population/creature/phenome/SRBPhenomeModel.hpp>
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The model of the creature holds the important information about the creature.
 * @details		Details
 * @date		2014-12-02
 * @author		Benjamin Ellenberger
 */
class CreatureModel: public Serializable {
public:
	CreatureModel();
	CreatureModel(PopulationModel* const populationModel,
		const PhysicsController::PhysicsModelType physicsModelType,
		const Ogre::Vector3 position);
	CreatureModel(const CreatureModel& creatureModel);

	virtual ~CreatureModel();

	/**
	 * Initializes a creature with random values for its genome, name, total segments quantity and segments path limit.
	 * @param populationModel The population model of the population it belongs to.
	 * @param genome The creature's genome.
	 * @param phenomeModel The creature's phenome model.
	 * @param position The creature's position.
	 * @param branchiness The branchiness parameter defining whether the creature branches into many limbs.
	 */
	void initialize();

	/**
	 * Perform embryogenesis on all creatures that are not developed.
	 */
	void performEmbryogenesis();

	void perturbControllers();

	/**
	 * Give rebirth to the creature.
	 */
	void giveRebirth();

	/**
	 * Update the creature.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Provides a creature size to scale certain values in compensation for the overall size
	 * of a creature's body. We do this by summing all creature volumes of all cuboids and
	 * then we take the cube square of it (size(C) = sqrt^3{\sum\limits^{N(C)}_{i=1} v(c_i)}).
	 * @return The size of a creature.
	 */
	double getCreatureSize();

	/**
	 * Provides the total volume of the whole creature body.
	 * @return The total volume of the whole creature body.
	 */
	double getCreatureVolume() const;

	void calm();

	void createRandomGenome(const double branchiness) {
		mGenotype.createRandomGenome(branchiness); //generate random genome for the creature
	}

	/**
	 * Compare the creature model to another creature model.
	 * @param creature Another creature model.
	 * @return If the creature model is equal to the other creature model.
	 */
	bool equals(const CreatureModel& creature) const;

	/**
	 * Clone this creature model.
	 */
	CreatureModel* clone();

	// Accessor methods

	bool hasInterpenetrations() {
		return mPhenotypeModel->hasInterpenetrations();
	}

	double getMaxJointVelocity() {
		return mPhenotypeModel->getMaxJointVelocity();
	}

	double getMaxHeight() {
		return mPhenotypeModel->getMaxHeight();
	}

	MixedGenome& getGenotype() {
		return mGenotype;
	}

	bool isDeveloped() const {
		return mPhenotypeModel->isDeveloped();
	}

	void setDeveloped(const bool developed) {
		mPhenotypeModel->setDeveloped(developed);
	}

	const std::vector<Jury*>& getJuries() const {
		return mJuries;
	}

	void addJury(Jury* jury) {
		mJuries.push_back(jury);
	}

	void clearJuries() {
		mFitnessScoreCalculated = false;
		for (std::vector<Jury*>::iterator jit = mJuries.begin();
			jit != mJuries.end(); jit++) {
			delete *jit;
		}
		mJuries.clear();
	}

	void processJuries();

	double getFitnessScore();

	double getLastFitnessScore() {
		return mFitnessScore;
	}

	const std::string& getFirstName() const {
		return mFirstName;
	}

	const Ogre::Vector3 getPosition() const {
		return mPosition;
	}

	void setPosition(const Ogre::Vector3 position) {
		mPosition = position;
	}

	PopulationModel* const getPopulationModel() const {
		return mPopulationModel;
	}

	const Ogre::Vector3 getInitialPosition() const {
		return mInitialPosition;
	}

	PhenomeModel* getPhenotypeModel() {
		return mPhenotypeModel;
	}

	PhenomeModel* const getPhenotypeModel() const {
		return mPhenotypeModel;
	}

	bool isCulled() const {
		return mCulled;
	}

	void setCulled(bool culled) {
		mCulled = culled;
	}

	bool isNew() const {
		return mNew;
	}

	void setNew(bool _new) {
		mNew = _new;
	}

	btDynamicsWorld*& getWorld();

	void setWorld(btDynamicsWorld* world) {
		mWorld = world;
	}

	Ogre::Vector3 getLowestRelativePoint() {
		return mPhenotypeModel->getLowestRelativePoint();
	}

	PhysicsController::PhysicsModelType getPhysicsModelType() const {
		return mPhysicsModelType;
	}

	void setPopulationModel(PopulationModel* populationModel) {
		mPopulationModel = populationModel;
	}

	unsigned long int getDynasty() const {
		return mDynasty;
	}

	void setDynasty(unsigned long int dynasty) {
		mDynasty = dynasty;
	}

	bool isMutated() const {
		return mMutated;
	}

	void setMutated(bool mutated) {
		mMutated = mutated;
	}

	// Serialization

	virtual void save() {
		SaveController<CreatureModel> creatureModelSaver;
		creatureModelSaver.save(*this, mSerializationPath.c_str());
	}

	virtual void load() {
		SaveController<CreatureModel> creatureModelSaver;
		creatureModelSaver.restore(*this, mSerializationPath.c_str());
		mPhenotypeModel->setCreatureModel(this);
	}

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the creature model to a string.
	 * @param os The ostream.
	 * @param creature The creature we want to serialize.
	 * @return A string containing all information about the creature.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const CreatureModel &creature) {
		os
		/**The name of the creature*/
		<< "/CreatureModel: Name=" << creature.mFirstName

		/**The genome of the creature*/
		<< "\n/Genotype=" << creature.mGenotype

		<< "\n/Phenotype=" << creature.mPhenotypeModel;

		/**The juries of the creature model*/
		for (std::vector<Jury*>::const_iterator it = creature.mJuries.begin();
			it != creature.mJuries.end(); it++) {
			os << (**it);
			os << "||";
		}

		/**The position of the creature model*/
		os << "/Position=(" << creature.mPosition.x << ","
			<< creature.mPosition.y << "," << creature.mPosition.z << ")";

		/**The initial position of the creature model*/
		os << "/InitialPosition=(" << creature.mInitialPosition.x << ","
			<< creature.mInitialPosition.y << "," << creature.mInitialPosition.z
			<< ")";

		os << "/isCulled=" << creature.mCulled;
		os << "/isNew=" << creature.mNew;
		return os;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<AverageVelocity*>(NULL));
		ar.register_type(static_cast<AverageHeight*>(NULL));
		ar.register_type(static_cast<GroundContactRatio*>(NULL));
		ar.register_type(static_cast<GroundContactQty*>(NULL));
		ar.register_type(static_cast<FSPhenomeModel*>(NULL));
		ar.register_type(static_cast<SRBPhenomeModel*>(NULL));
		ar
		/**The name of the creature*/
		& BOOST_SERIALIZATION_NVP(mFirstName)

		/**The genome of the creature model*/
		& BOOST_SERIALIZATION_NVP(mGenotype)
		& BOOST_SERIALIZATION_NVP(mPhysicsModelType)
		& BOOST_SERIALIZATION_NVP(mPhenotypeModel)

		/**The juries of the creature model*/
		& BOOST_SERIALIZATION_NVP(mJuries)

		/**The position of the creature model*/
		& BOOST_SERIALIZATION_NVP(mPosition.x)
		& BOOST_SERIALIZATION_NVP(mPosition.y)
		& BOOST_SERIALIZATION_NVP(mPosition.z)

		/**The initial position of the creature model*/
		& BOOST_SERIALIZATION_NVP(mInitialPosition.x)
		& BOOST_SERIALIZATION_NVP(mInitialPosition.y)
		& BOOST_SERIALIZATION_NVP(mInitialPosition.z)

		/**If the creature was culled or not*/
		& BOOST_SERIALIZATION_NVP(mCulled)

		/**If the creature is new*/
		& BOOST_SERIALIZATION_NVP(mNew)

		/**!< The dynasty this creature belongs to */
		& BOOST_SERIALIZATION_NVP(mDynasty);
	}
private:
	static BoostLogger mBoostLogger;/**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("CreatureModel"));
		}
	} _initializer;

	//PARENT
	PopulationModel* mPopulationModel; /**!< The population the creature lives in. */

	std::string mFirstName; /**!< The name of the creature. */

	MixedGenome mGenotype; /**!< The genotype (genomic individual) of the creature. */

	PhenomeModel* mPhenotypeModel; /**!< The phenotype (morphological individual) of the creature. */

	std::vector<Jury*> mJuries; /**!< The juries that rate the creature according to their fitness function. */

	Ogre::Vector3 mPosition; /**!< The position of the creature. */

	Ogre::Vector3 mInitialPosition; /**!< The initial position of the creature. */

	bool mCulled; /**!< If the creature was culled or not. */

	bool mNew; /**!< If the creature is new and does not have a controller element yet. */

	bool mMutated; /**!< If the creature is mutated and the controller element has to be rebuilt */

	PhysicsController::PhysicsModelType mPhysicsModelType; /**!< Physics model type */

	double mFitnessScore; /**!< The fitness score competitively eruated by the juries. */

	unsigned long int mDynasty; /**!<  The dynasty that creature belongs to. */

	btDynamicsWorld* mWorld; /**!< The world the creature is living in */

	bool mFitnessScoreCalculated; /**!< The last fitness score */

	double mLastCreatureLength; /**!< The last creature volume cube length */

};
BOOST_CLASS_VERSION(CreatureModel, 1)

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATUREM_H_ */
