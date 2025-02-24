#ifndef CONTROLLER_INPUT_OGREINPUTHANDLER_H_
#define CONTROLLER_INPUT_OGREINPUTHANDLER_H_

//# corresponding header
//# forward declarations

//# system headers
#include <string>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/ApplicationMousecode.hpp>
#include <controller/input/ApplicationKeycode.hpp>
#include <controller/input/KeyboardStateInputHandler.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The Ogre Input handler handles the input coming from the lower hardware input layer and handles it in the context of Ogre3D.
 * @details		Details
 * @date		2015-02-27
 * @author		Benjamin Ellenberger
 */
class OgreInputHandler: public KeyboardStateInputHandler {
public:
	OgreInputHandler();
	virtual ~OgreInputHandler();

protected:
	/**
	 * Initialize the Ogre input handler.
	 */
	void initialize();

	void update(double timeSinceLastUpdate);

	/**
	 * Key pressed event handler.
	 * @param key The key that was pressed.
	 * @return If the key press was consumed.
	 */
	bool keyPressed(ApplicationKeycode::Keycode key);

	/**
	 * Key release event handler.
	 * @param key The key that was released.
	 * @return If the key release was consumed.
	 */
	bool keyReleased(ApplicationKeycode::Keycode key);

	/**
	 * Mouse moved event handler.
	 * @param x The mouse X position.
	 * @param y The mouse Y position.
	 * @return If the mouse move was consumed.
	 */
	bool mouseMoved(float x, float y) const;

	/**
	 * Mouse wheel moved event handler.
	 * @param rel The relative position of the mouse wheel.
	 * @return If the mouse wheel move was consumed.
	 */
	bool mouseWheelMoved(float rel);

	/**
	 * Mouse pressed event handler.
	 * @param button The button of the mouse that was pressed.
	 * @return If the mouse button press was consumed.
	 */
	bool mousePressed(ApplicationMouseCode::MouseButton button);

	/**
	 * Mouse released event handler.
	 * @param button The button of the mouse that was pressed.
	 * @return If the mouse button release was consumed.
	 */
	bool mouseReleased(ApplicationMouseCode::MouseButton button);

	/**
	 * Quit the application.
	 */
	void quitApplication() const;

private:

	/**
	 * Stop the camera X dimension movement.
	 */
	void stopCameraXDimensionMovement();

	/**
	 * Stop the camera Y dimension movement.
	 */
	void stopCameraYDimensionMovement();

	/**
	 * Stop the camera Z dimension movement.
	 */
	void stopCameraZDimensionMovement();

	/**
	 * Move the camera left.
	 */
	void moveCameraLeft() const;

	/**
	 * Move the camera up.
	 */
	void moveCameraUp();

	/**
	 * Move the camera backward.
	 */
	void moveCameraBackward();

	/**
	 * Move the camera right.
	 */
	void moveCameraRight();

	/**
	 * Move the camera down.
	 */
	void moveCameraDown();

	/**
	 * Move the camera forward.
	 */
	void moveCameraForward();

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
					boost::log::attributes::constant<std::string>(
							"OgreInputHandler"));
		}
	} _initializer;
};

#endif /* CONTROLLER_INPUT_OGREINPUTHANDLER_H_ */
