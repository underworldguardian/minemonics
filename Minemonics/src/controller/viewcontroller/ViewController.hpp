#ifndef CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_
#define CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_

//# corresponding header
//# forward declarations
namespace CEGUI {
class OgreRenderer;
} /* namespace CEGUI */

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/Evaluation.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>

//## model headers
//## view headers
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/CEGUI/MovablePanel.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/visualization/CEGUI/MenuBar.hpp>
#include <view/visualization/CEGUI/infopanels/FPSPanel.hpp>
#include <view/visualization/CEGUI/infopanels/DetailsPanel.hpp>
#include <view/visualization/CEGUI/infopanels/graphpanels/MathGLPanel.hpp>

//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The view controller handles the information panels of the application and what is currently in view..
 * @details		Details
 * @date		2015-05-27
 * @author		Benjamin Ellenberger
 */
class ViewController {
public:
	ViewController();
	virtual ~ViewController();

	/**
	 * Initialize the view controller.
	 * @param renderTarget The render target.
	 * @param stateHandler The state handler of the simulation.
	 */
	void initialize(Ogre::RenderTarget* const renderTarget);

	/**
	 * Update the view controller.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void update(const double timeSinceLastFrame);

	/**
	 * Update the panels.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void updatePanels(const Ogre::Real timeSinceLastFrame);

	/**
	 * Notify CEGUI that the display size has changed.
	 * @param width The new width.
	 * @param height The new height.
	 */
	void notifyDisplaySizeChanged(const float width, const float height);

	/**
	 * Update the mouse position.
	 * @param mousePositionX The new mouse position X.
	 * @param mousePositionY The new mouse position Y.
	 */
	void updateMousePosition(const float mousePositionX,
		const float mousePositionY);

	void addPlanetToView(Planet* planet);

	void removePlanetFromView(Planet* const planet);

	// Accessor methods ##########################

	DetailsPanel* const getDetailsPanel() const {
		return mDetailsPanel;
	}

	FPSPanel* const getFpsPanel() const {
		return mFpsPanel;
	}

	const InfoOverlay& getInfoOverlay() const {
		return mInfoOverlay;
	}

	CEGUI::OgreRenderer* const getRenderer() const {
		return mRenderer;
	}

	Evaluation* const getEvaluationInView() const {
		return mEvaluationInView;
	}

	void setEvaluationInView(Evaluation* const evaluationInView) {
		mEvaluationInView = evaluationInView;
	}

	const std::vector<Planet*>& getPlanetsInView() const {
		return mPlanetsInView;
	}

	CameraHandler& getCameraHandler() {
		return mCameraHandler;
	}

	bool doesShowShadows() const {
		return mShowShadows;
	}

	void setShowShadows(bool showShadows) {
		mShowShadows = showShadows;
	}

	std::vector<MovablePanel*>& getMovablePanels() {
		return mMovablePanels;
	}

	void setNewPlanetWindowVisibility(bool visible) {
		if (visible) {
			mNewPlanetWindow->show();
		} else {
			mNewPlanetWindow->hide();
		}
	}

	void setEditPlanetWindowVisibility(bool visible) {
		if (visible) {
			mEditPlanetWindow->show();
		} else {
			mEditPlanetWindow->hide();
		}
	}

	void setLoadPlanetWindowVisibility(bool visible) {
		if (visible) {
			mLoadPlanetWindow->show();
		} else {
			mLoadPlanetWindow->hide();
		}
	}

	void setNewPopulationWindowVisibility(bool visible) {
		if (visible) {
			mNewPopulationWindow->show();
		} else {
			mNewPopulationWindow->hide();
		}
	}

	void setEditPopulationWindowVisibility(bool visible) {
		if (visible) {
			mEditPopulationWindow->show();
		} else {
			mEditPopulationWindow->hide();
		}
	}

	void setLoadPopulationWindowVisibility(bool visible) {
		if (visible) {
			mLoadPopulationWindow->show();
		} else {
			mLoadPopulationWindow->hide();
		}
	}

	MathGLPanel* getChaosControllerPanel() {
		return mChaosControllerPanel;
	}

	MathGLPanel* getJointDynamicsPanel() {
		return mJointDynamicsPanel;
	}

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"ViewController"));
		}
	} _initializer;

	//CEGUI windows
	//# planet windows
	MovablePanel* mNewPlanetWindow;
	MovablePanel* mEditPlanetWindow;
	MovablePanel* mLoadPlanetWindow;

	//# population windows
	MovablePanel* mNewPopulationWindow;
	MovablePanel* mEditPopulationWindow;
	MovablePanel* mLoadPopulationWindow;

	//SheetHandler
	GUISheetHandler mGUISheetHandler;

	//Camera Handler
	CameraHandler mCameraHandler;

	//CEGUI
	MenuBar* mMenuBar;
	FPSPanel* mFpsPanel;
	DetailsPanel* mDetailsPanel;
	MathGLPanel* mChaosControllerPanel;
	MathGLPanel* mJointDynamicsPanel;
	CEGUI::OgreRenderer* mRenderer;
	CEGUI::Window* mDragContainer;

	// Visualization components
	std::vector<MovablePanel*> mMovablePanels;
	InfoOverlay mInfoOverlay;

	std::vector<Planet*> mPlanetsInView;
	Evaluation* mEvaluationInView;
	bool mShowShadows;
};

#endif /* CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_ */
