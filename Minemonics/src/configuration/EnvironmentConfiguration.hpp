#ifndef CONFIGURATON_ENVIRONMENTCONFIGURATION_H_
#define CONFIGURATON_ENVIRONMENTCONFIGURATION_H_

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
#include <controller/universe/environments/Environment.hpp>

//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration of the environment.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentConfiguration {
public:
	static const float AMBIENT_R; /**!< Ambient light color */
	static const float AMBIENT_G;
	static const float AMBIENT_B;

	static const double GROUND_FRICTION;
};

#endif /* CONFIGURATON_ENVIRONMENTCONFIGURATION_H_ */
