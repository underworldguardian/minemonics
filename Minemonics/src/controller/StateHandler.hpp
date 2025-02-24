#ifndef CONTROLLER_STATEHANDLER_HPP_
#define CONTROLLER_STATEHANDLER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The state handler holds the application states.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class StateHandler {

public:

	/**
	 * Application states
	 */
	enum ApplicationState {
		STARTUP, //!< The application is starting up
		GUI, //!< The GUI is shown
		LOADING, //!< The simulation is loading
		CANCEL_LOADING, //!< The simulation loading is cancelled
		SIMULATION, //!< The simulation is running
		HEADLESS_SIMULATION, //!< The simulation is running headlessly
		SHUTDOWN, //!< The simulation is shutting down
		NUM_APPLICATION_STATES
	};

	StateHandler();
	virtual ~StateHandler();

public:
	/**
	 * Request a state change.
	 * @param state The state to switch to.
	 * @return If it switched to the requested state.
	 */
	bool requestStateChange(const ApplicationState state);

	/**
	 * Lock the current state.
	 * @return If the state has been locked.
	 */
	bool lockState();

	/**
	 * Unlock the current state.
	 * @return If the state has been unlocked.
	 */
	bool unlockState();

	// Accessor methods ##########################

	ApplicationState getCurrentState();

	void setFrameTime(const float ms);

	inline float getFrameTime() const {
		return mFrameTime;
	}

	Planet* getCurrentlySelectedPlanet() const {
		return mCurrentlySelectedPlanet;
	}

	void setCurrentlySelectedPlanet(Planet* currentlySelectedPlanet) {
		mCurrentlySelectedPlanet = currentlySelectedPlanet;
	}

protected:
	ApplicationState mState; /**!< The state of the application. */

	bool mLocked; /**!< If the state is locked or not. */

	float mFrameTime; /**!< The frame time of the application. */
private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>("StateHandler"));
		}
	} _initializer;

	Planet* mCurrentlySelectedPlanet; /**!< The currently selected planet */
};

#endif /* CONTROLLER_STATEHANDLER_HPP_ */
