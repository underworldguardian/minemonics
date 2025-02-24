//# corresponding header
#include <stddef.h>
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>
#include <view/visualization/CEGUI/configpanels/EditPopulationPanel.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

EditPopulationPanel::EditPopulationPanel(const int left, const int top,
	const std::string name) :
	MovablePanel(name, MovablePanel::NEW_POPULATION_PANEL), mTextBoxLabel(NULL), mTextBoxValues(
	NULL) {
	int width = 600;
	int height = 600;

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	// Items
	// + Names
	mTextBoxLabel = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Label", mName + "_Label");

	mTextBoxLabel->setSize(
		CEGUI::USize(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_LEFT_COL_WIDTH
					* (float) (width))),
			CEGUI::UDim(0, height - CEGUIConfiguration::INFOPANEL_CAPTION)));

	mTextBoxLabel->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
	mBaseWidget->addChild(mTextBoxLabel);

	// + Values
	mTextBoxValues = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Label", mName + "_Values");

	mTextBoxValues->setSize(
		CEGUI::USize(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_RIGHT_COL_WIDTH
					* (float) (width))),
			CEGUI::UDim(0, height - CEGUIConfiguration::INFOPANEL_CAPTION)));

	mTextBoxValues->setPosition(
		CEGUI::UVector2(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_LEFT_COL_WIDTH
					* (float) (width))), CEGUI::UDim(0, 0)));
	mBaseWidget->addChild(mTextBoxValues);

	std::string labelText = "Hello";
	std::string valuesText = "World";

	mTextBoxLabel->setText(labelText);
	mTextBoxValues->setText(valuesText);
}

EditPopulationPanel::~EditPopulationPanel(void) {
	//Cleanup according to
	// http://cegui.org.uk/wiki/CEGUI_In_Practice_-_Introduction
	// http://cegui.org.uk/forum/viewtopic.php?t=1535
//	if (mTextBoxLabel) {
//		mBaseWidget->removeChild(mTextBoxLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTextBoxLabel);
////		delete mTextBoxLabel;
//	}
//	mTextBoxLabel = NULL;
//
//	if (mTextBoxValues) {
//		mBaseWidget->removeChild(mTextBoxValues);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTextBoxValues);
////		delete mTextBoxValues;
//	}
//	mTextBoxValues = NULL;
}
