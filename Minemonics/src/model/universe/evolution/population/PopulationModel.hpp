#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_

//# corresponding headers
#include <model/Serializable.hpp>

//# forward declarations
class PlanetModel;
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
#include <boost/lexical_cast.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/SerializationConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/Epoch.hpp>

//## view headers
//## utils headers

/**
 * @brief		The population model holds the information about a population of creatures.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class PopulationModel: public Serializable {
public:
	PopulationModel();
	PopulationModel(PlanetModel* const planetModel, const int creatureQty);
	PopulationModel(PlanetModel* const planetModel, const int creatureQty,
		const Ogre::Vector3 initialPosition);
	PopulationModel(const PopulationModel& populationModel);

	virtual ~PopulationModel();

	void perturbCreatureControllers();

	/**
	 * Initialize the population model
	 */
	void initialize();

	/**
	 * Adds a new creature to the population.
	 */
	void addNewMember(const double branchiness,
		const Ogre::Vector3 rootPosition);

	/**
	 * Adds a new creature to the population.
	 */
	void addMember(CreatureModel* const creatureModel);

	/**
	 * Tests if a population is equal to another population.
	 * @param population The population to test for equality.
	 * @return If this population and the other are equal.
	 */
	bool equals(const PopulationModel& population) const;

	/**
	 * Clone the population.
	 */
	PopulationModel* clone();

	bool hasInterpenetrations();

	double getMaxJointVelocity();

	double getMaxHeight();

	void clearJuries();

	// Accessor methods ##########################

	int getCreatureQty() const {
		return mCreatureQty;
	}

	void setCreatureQty(const int creatureQty) {
		mCreatureQty = creatureQty;
	}

	std::vector<CreatureModel*>& getCreatureModels() {
		return mCreatureModels;
	}

	const std::vector<CreatureModel*>& getCreatureModels() const {
		return mCreatureModels;
	}

	PlanetModel* getPlanetModel() const {
		return mPlanetModel;
	}

	void setPlanetModel(PlanetModel* const planetModel) {
		mPlanetModel = planetModel;
	}

	int getCurrentCreatureIndex() const {
		return mCurrentCreatureIndex;
	}

	bool isOutOfSync() const {
		return mOutOfSync;
	}

	void setOutOfSync(bool outOfSync) {
		mOutOfSync = outOfSync;
	}

	int getCurrentGeneration() const {
		return mCurrentGeneration;
	}

	void setCurrentGeneration(int currentGeneration) {
		mCurrentGeneration = currentGeneration;
	}

	int getDynastyQty() const {
		return mDynastyQty;
	}

	void setDynastyQty(int dynastyQty) {
		mDynastyQty = dynastyQty;
	}

	const std::string getGenerationSerializationPath() {
		//create folder for the generation
		std::string generationName = std::string("Generation-")
			+ boost::lexical_cast<std::string>(getCurrentGeneration());
		return getSerializationPath() + "/" + generationName;
	}

	// Serialization
	virtual void save();

	virtual void load();

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the population to a string.
	 * @param os The ostream.
	 * @param creature The population we want to serialize.
	 * @return A string containing all information about the population.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const PopulationModel &population) {
		os << population.mCreatureQty;
		for (std::vector<CreatureModel*>::const_iterator it =
			population.mCreatureModels.begin();
			it != population.mCreatureModels.end(); it++) {
			os << (**it);
		}
		return os;
	}

	/**
	 * Serializes the population to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
			& BOOST_SERIALIZATION_NVP(
				mCreatureQty) & BOOST_SERIALIZATION_NVP(mCurrentGeneration)
				& BOOST_SERIALIZATION_NVP(mDynastyQty); //TODO: Add this to the creatures
		if (!SerializationConfiguration::POPULATION_EXPANDED) {
			ar & BOOST_SERIALIZATION_NVP(mCreatureModels);
		}
	}

private:

	void saveCreatures();

	void loadCreatures();

	bool mOutOfSync; /**!< If the population model is out of sync with the controller. */

	std::vector<CreatureModel*> mCreatureModels; /**!< The creatures living in this population. All creatures in one population can mate together. */

	int mCurrentCreatureIndex; /**!< The index of the creature that is currently evaluated. */

	int mCreatureQty; /**!< The number of creatures that the population will consist of in every generation. */

	int mCurrentGeneration; /**!< The current generation */

	PlanetModel* mPlanetModel; /**!< The planet the population lives on. */

	std::vector<Epoch*> mEpochs; /**!< The epochs of the population. */

	int mDynastyQty; /**!< The number of dynasties that have been in the population */
};
BOOST_CLASS_VERSION(PopulationModel, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_POPULATIONMODEL_HPP_ */
