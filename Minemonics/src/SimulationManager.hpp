#ifndef __SimulationManager_h_
#define __SimulationManager_h_

//# corresponding header
#include <BaseApplication.hpp>

//# forward declarations
class Randomness;
struct SDL_Window;

//# system headers
//## controller headers
//## model headers
#include <OgreTimer.h>
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

//## view headers
#include <OgrePrerequisites.h>
#include <OgreRenderWindow.h>
#include <OgreTerrain.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/SDL2InputHandler.hpp>
#include <controller/StateHandler.hpp>
#include <controller/universe/Universe.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
//## view headers
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>
#include <view/picking/MousePicker.hpp>

//## utils headers
#include <utils/Debugger.hpp>
#include <utils/logging/Logger.hpp>

/**
 * @brief		The Simulation manager holds the whole application together.
 * @details		The Simulation manager holds the whole application together.
 * It helps to set up the evolutionary runs.
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class SimulationManager: public BaseApplication {
public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	virtual void setupView(void);

	/**
	 * Quit the simulation.
	 * @return If the simulation could be quit.
	 */
	bool quit();

	/**
	 * Event triggered when the window is resized.
	 * @param rw The renderwindow's details.
	 */
	virtual void windowResized(Ogre::RenderWindow* rw);

	// Accessor methods ##########################

	static SimulationManager* getSingleton() {
		return mSimulationManager;
	}

	SDL2InputHandler& getInputHandler() {
		return mInputHandler;
	}

	StateHandler& getStateHandler() {
		return mStateHandler;
	}

	Ogre::SceneManager* getSceneManager() {
		return mSceneMgr;
	}

	Ogre::Root* getRoot() {
		return mRoot;
	}

	Ogre3DFFMPEGVideoWriter& getVideoWriter() {
		return mVideoWriter;
	}

	unsigned long int getRuntime() {
		return mApplicationRuntime;
	}

	unsigned long int getNow() {
		return mThisModelIteration;
	}

	std::string getTimeStamp();

	OgreBtDebugDrawer& getDebugDrawer() {
		return mDebugDrawer;
	}

	Universe& getUniverse() {
		return mUniverse;
	}

	ViewController& getViewController() {
		return mViewController;
	}

	double getCurrentSimulationSpeed() const {
		return mCurrentSimulationSpeed;
	}

	void setCurrentSimulationSpeed(double currentSimulationSpeed) {
		mCurrentSimulationSpeed = currentSimulationSpeed;
	}

	const Debugger& getDebugger() const {
		return mDebugger;
	}

	MousePicker& getMousePicker() {
		return mMousePicker;
	}

	int getWindowHeight() const {
		return mWindow->getHeight();
	}

	int getWindowWidth() const {
		return mWindow->getWidth();
	}

	Ogre::Light*& getSun() {
		return mSun;
	}

	Ogre::TerrainGlobalOptions& getTerrainGlobals() {
		return mTerrainGlobals;
	}

	const std::string& getSerializationPath() const {
		return mSerializationPath;
	}

protected:
	bool configure(void);

	/**
	 * Create the scene in the simulation manager.
	 */
	virtual void createScene(void);

	/**
	 * Create the frame listener to react to frame trigger events.
	 */
	virtual void createFrameListener(void);

	/**
	 * Called after all render targets have had their rendering commands
	 * issued, but before render windows have been asked to flip their
	 * buffers over.
	 * @param evt
	 * 		Information about the frame rendering.
	 * @remarks
	 * 		The usefulness of this event comes from the fact that rendering
	 * commands are queued for the GPU to process. These can take a little
	 * while to finish, and so while that is happening the CPU can be doing
	 * useful things. Once the request to 'flip buffers' happens, the thread
	 * requesting it will block until the GPU is ready, which can waste CPU
	 * cycles. Therefore, it is often a good idea to use this callback to
	 * perform per-frame processing. Of course because the frame's rendering
	 * commands have already been issued, any changes you make will only
	 * take effect from the next frame, but in most cases that's not noticeable.
	 * @return
	 * 		True to continue rendering, false to drop out of the rendering loop.
	 */
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/**
	 * Destroy the scene on shutdown.
	 */
	virtual void destroyScene(void);

	/**
	 * Update the information panels.
	 * @param timeSinceLastFrame
	 */
	void updatePanels(Ogre::Real timeSinceLastFrame);

	/**
	 * If the window focus changes.
	 * @param rw Information about the render window.
	 */
	virtual void windowFocusChange(Ogre::RenderWindow* rw);

private:
	//## controller components ##################
	static SimulationManager* mSimulationManager; /**!< The simulation manager singleton handle */
	StateHandler mStateHandler; /**!< The application state handler */
	SDL2InputHandler mInputHandler; /**!< The input handler of the simulation */
	Universe mUniverse; /**!< The universe and everything */
	Ogre::Light* mSun; /**!< The sun of the universe */

	//## model components #######################
	int mCurrentSimulationSpeed; /**!< The speed of the currently runnig simulations */

	//## view components ########################
	Ogre::TerrainGlobalOptions mTerrainGlobals; /**!< This must be a singleton it seems */
	ViewController mViewController; /**!< The view controller of the simulation */
	MousePicker mMousePicker; /**!< The mouse picker to move 3D elements with the mouse */
	Ogre3DFFMPEGVideoWriter mVideoWriter; /**!< The video writer to produce videos from the scene */
	Randomness* mRandomness; /**!< The randomness generator singleton to be used in the simulator */

	// loop timing components ###################
	//# loop timestamps
	Ogre::Timer mOgreTimer; /**!< The ogre built-in timer to time the loop correctly */
	unsigned long int mApplicationStart; /**!< The time the application was started (absolute, in Milliseconds) */
	unsigned long int mPreviousModelIteration; /**!< The previous model iteration timestamp (absolute, in Milliseconds) */
	unsigned long int mThisModelIteration; /**!< This model iteration timestamp (absolute, in Milliseconds) */

	//# loop durations
	long int mModelAccumulator; /**!< The time to forward the model in this loop iteration (relative, in Milliseconds) */
	unsigned long int mFrameTime; /**!< The time to render a frame (relative, in Milliseconds) */
	unsigned long int mApplicationRuntime; /**!< The total application runtime (relative, in Milliseconds) */

	long int mInputDt; /**!< The time difference of input that has to be fed in */
	unsigned long int mInputClock;

	long int mLastGraphicsTick; /*!< The time it took the graphics rendering last time (relative, in Milliseconds) */
	unsigned long int mGraphicsStart;

	long int mLastInputTick; /**!< The time it took the input to process last time (relative, in Milliseconds) */
	unsigned long int mInputStart;

	long int mLastModelTick; /**!<  The time it took the model to update last time
	 This includes the bullet physics update */
	long int mModelStart; /**!< The timestamp the model started updating last (absolute, in Milliseconds)*/

	long int mPhysicsTick; /**!< The time remaining in the loop to update the physics (relative, in Milliseconds)*/
	long int mPhysicsStepStart; /**!< The physics start timestamp (absolute, in Milliseconds) */
	long int mPhysicsStepEnd; /**!< The last physics step end (absolute, in Milliseconds) */

	//## Debug components #######################
	OgreBtDebugDrawer mDebugDrawer; /**!< The debug drawer used by bullet physics to show debug information */
	Debugger mDebugger; /**!< Common simulator debug routines */
	static BoostLogger mBoostLogger; /**!< The logger instance of the simulation manager */
	std::string mSerializationPath; /**!< The serialization path of the simulator's components */

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string
					> ("SimulationManager"));
		}
	} _initializer;
};

#endif // #ifndef __SimulationManager_h_
