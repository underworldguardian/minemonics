#ifndef CONTROLLER_INPUT_SDL2INPUTHANDLER_H_
#define CONTROLLER_INPUT_SDL2INPUTHANDLER_H_

//# corresponding headers
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
#include <controller/input/CEGUIInputHandler.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The SDL2 input handler handles the input coming directly from the hardware layer SDL2 manages and hands the inputs up to its connecting input handlers.
 * @details		Details
 * @date		2015-02-27
 * @author		Benjamin Ellenberger
 */
class SDL2InputHandler: public CEGUIInputHandler {
public:
	SDL2InputHandler();
	virtual ~SDL2InputHandler();

	/**
	 * Initialize the SDL2InputHandler.
	 */
	void initialize();

	/**
	 * Inject input into the other layered handlers.
	 */
	void injectInput();

	/**
	 * Inject a time pulse to give the handlers a notion of time passing.
	 */
	void injectTimePulse();

	void update(double timeSinceLastTick);

	// Accessor methods ##########################

	/**
	 * Get the mouse X position.
	 * @return The mouse X position.
	 */
	int getMousePositionX() const;

	/**
	 * Get the mouse Y position.
	 * @return The mouse Y position.
	 */
	int getMousePositionY() const;

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string
					> ("SDL2InputHandler"));
		}
	} _initializer;

	/**
	 * The last mouse X position.
	 */
	int mLastMouseX;

	/**
	 * The last mouse Y position.
	 */
	int mLastMouseY;

	int mIgnoreEvent;
};

#endif /* CONTROLLER_INPUT_SDL2INPUTHANDLER_H_ */
