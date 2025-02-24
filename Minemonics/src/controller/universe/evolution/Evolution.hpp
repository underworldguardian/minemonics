#ifndef CONTROLLER_UNIVERSE_EVOLUTION_EVOLUTION_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_EVOLUTION_HPP_

//# corresponding headers
//# forward declarations
class Planet;

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/EvaluationController.hpp>
#include <controller/universe/evolution/population/Population.hpp>

//## model headers
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The evolution runs evaluations depending on type.
 * @details		 A particular experimental setup is referred to as an "evolution".
 *      Evolutions consist of one or more independent GA runs, where each
 *      run is identical in terms of settings like population size,
 *      tournament size, mutation rates, and so on.
 *
 *      All creatures in the first generation of any run are produced from randomly-initialized genomes.
 *      Creatures in generations other than the first are produced either by mutation or
 *      crossover of parents selected by tournament from the previous generation. The sole
 *      exception is the first creature in such generations, which is always a copy of the best (or
 *      elite) creature from the previous generation. (Graham Lee Thesis)
 * @date		2015-04-28
 * @author		Benjamin Ellenberger
 */
class Evolution {
public:
	Evolution();
	Evolution(EvolutionModel* const evolutionModel);
	virtual ~Evolution();

	/**
	 * Initialize the evolution.
	 */
	void initialize(EvaluationController* const evaluationController,
		Planet* const planet, EvolutionModel* const evolutionModel);

	/**
	 * Perform embryogenesis on all creatures that are not developed.
	 */
	void performEmbryogenesis();

	/**
	 * Add a population to the evolution.
	 * @param population The population to be added.
	 */
	void addPopulation(Population* const population);

	/**
	 * Proceed with the next creature of the currently tested population or
	 * proceed with reaping and sowing. This method is called by the
	 * EvaluationTimer after the predefined evaluation interval.
	 */
	bool proceedEvaluation();

	/**
	 * Update the evolution.
	 */
	void update(double timeSinceLastTick);

	// Accessor methods ##########################

	EvolutionModel* getEvolutionModel() {
		return mEvolutionModel;
	}

	const std::vector<Population*>& getPopulations() const {
		return mPopulations;
	}

	int getTotalCreatureQty();
private:

	static BoostLogger mBoostLogger; /**!<  The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("Evolution"));
		}
	} _initializer;

	//PARENT
	Planet* mPlanet; /**!< The planet the evolution takes place on. */

	//PARENT
	EvaluationController* mEvaluationController; /**!< The evaluation controller of the universe. */

	std::vector<Population*> mPopulations; /**!< The population under the same evolution */

	EvolutionModel* mEvolutionModel; /**!< The model of the evolution */
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_EVOLUTION_HPP_ */
