#ifndef CONFIGURATION_EVOLUTIONCONFIGURATION_H_
#define CONFIGURATION_EVOLUTIONCONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration of the evolutionary algorithms.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class EvolutionConfiguration {
public:

	/**
	 * Number of elitists (the ones that get carried over to the next generation because they are so successful)
	 */
	static const unsigned EVOLUTION_SELECTION_ELITISTS_QTY;

	/**
	 * This is the number of times that a creature will be evaluated during a fitness
	 measurement. This value is set to one in all of the experimental
	 setups described in this work although it can be set higher to reduce noise.
	 The trade-off is one of noise reduction vs. computation time.
	 */
	static const unsigned EVOLUTION_EVALUATION_RUNS;

	/**
	 * Whenever a parent is needed, this setting dictates the number of individuals to choose
	 * at random from the previous generation. These individuals constitute a tournament.
	 * The creature with the highest fitness wins and becomes the selected parent. The
	 * higher this value is in relation to the population size, the higher the selection pressure
	 * will be and the more rapid the loss of diversity will be.
	 */
	static const unsigned EVOLUTION_TOURNAMENT_SIZE;

	/**
	 * This is the probability that a new creature, in any generation other than the first, will
	 be produced by the crossing of two parents from the previous generation.
	 */
	static const double EVOLUTION_CREATURE_CROSSOVER_RATE;

	/**
	 * This is the mutation rate used in mutation operators affecting the genome.
	 */
	static const double EVOLUTION_CREATURE_MUTATION_RATE;

	// Generation variables
	/**
	 * Ratios to which the reaper sows offspring as descendants from the best performing creatures.
	 * The best performing creature takes part in <ratio> of all cross-overs etc.
	 */
	static const double REAPER_SOW_OFFSPRING[]; // Initialization in EvolutionConfiguration.cpp

	static const double REAPER_REAP_PERCENTAGE; /**!< First the reaper reaps off a percentage */

	static const double REAPER_CROSSOVER_PERCENTAGE; /**!< Cross over percentage and sow fresh sum up to 1.0*/
	static const double REAPER_SOW_FRESH_PERCENTAGE; /** !< How many creatures should be sown randomly. */

	/** The percentage of the population to be affected. The following sum up to 1.0*/
	static const double REAPER_ELITIST_PERCENTAGE;
	static const double REAPER_GENE_MUTATION_PERCENTAGE;
	static const double REAPER_GENE_SPLIT_PERCENTAGE;
	static const double REAPER_LINK_MUTATION_PERCENTAGE;
	static const double REAPER_GENE_PURGE_PERCENTAGE;
	static const double REAPER_GROW_STUB_PERCENTAGE;
	static const double REAPER_GRAFT_PERCENTAGE;

	/** The probability of genome to be affected. The following DO NOT sum up to 1.0*/
	static const double REAPER_GENE_MUTATION_PROBABILITY;
	static const double REAPER_LINK_MUTATION_PROBABILITY;
	static const double REAPER_GENE_SPLIT_PROBABILITY;
	static const double REAPER_GENE_PURGE_PROBABILITY;
	static const double REAPER_GROW_STUB_PROBABILITY;
	static const int REAPER_GROW_STUB_BRANCHINESS;
	static const double REAPER_GRAFT_PROPABILITY;
};

#endif /* CONFIGURATION_EVOLUTIONCONFIGURATION_H_ */
