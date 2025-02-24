//# corresponding header
#include <view/visualization/CEGUI/configpanels/NewPlanetPanel.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <string>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Combobox.h>
#include <CEGUI/widgets/ListboxItem.h>
#include <CEGUI/widgets/ListboxTextItem.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/Planet.hpp>

//## model headers
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>

//## utils headers
#include <utils/serialization/FilesystemManipulator.hpp>

NewPlanetPanel::NewPlanetPanel(const int left, const int top,
	const std::string name) :
	MovablePanel(name, MovablePanel::NEW_PLANET_PANEL), mEnvironmentTypeLabel(
	NULL) {
	int width = 600;
	int height = 800;

	float verticalOffset = 0.02f;
	float verticalStep = 0.09f;
	float i = 0;

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	float leftColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_LEFT_COL_WIDTH;
	float rightColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_RIGHT_COL_WIDTH;

	{
		// physics controller type
		mPhysicsControllerTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mPhysicsControllerTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mPhysicsControllerTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);

		mPhysicsControllerTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalOffset, 0)));
		mPhysicsControllerTypeLabel->setText("Physics Controller Type: ");
		mBaseWidget->addChild(mPhysicsControllerTypeLabel);

		// Physics Controller type Combobox
		mPhysicsControllerTypeCb =
			static_cast<CEGUI::Combobox*>(wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mPhysicsControllerTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"RigidBody Dynamicsworld", PhysicsController::RigidbodyModel);
		mPhysicsControllerTypeCb->addItem(itemCombobox);

		itemCombobox = new CEGUI::ListboxTextItem(
			"Featherstone MultiBody Dynamicsworld",
			PhysicsController::FeatherstoneModel);
		mPhysicsControllerTypeCb->addItem(itemCombobox);
		mPhysicsControllerTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mPhysicsControllerTypeCb->setItemSelectState(itemCombobox, true);
		mPhysicsControllerTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mPhysicsControllerTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mPhysicsControllerTypeCb);
		i++;
	}

	{
		// Environment type
		mEnvironmentTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEnvironmentTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEnvironmentTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);

		mEnvironmentTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEnvironmentTypeLabel->setText("Environment type: ");
		mBaseWidget->addChild(mEnvironmentTypeLabel);

		// Environment type Combobox
		mEnvironmentTypeCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mEnvironmentTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Plane", EnvironmentModel::PLANE);
		mEnvironmentTypeCb->addItem(itemCombobox);
		mEnvironmentTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mEnvironmentTypeCb->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("Hills",
			EnvironmentModel::HILLS);
		mEnvironmentTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("Open Sea",
			EnvironmentModel::OPENSEA);
		mEnvironmentTypeCb->addItem(itemCombobox);

		mEnvironmentTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mEnvironmentTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mEnvironmentTypeCb);
		i++;
	}

	{
		// Evaluation time
		mEvaluationTimeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEvaluationTimeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEvaluationTimeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mEvaluationTimeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTimeLabel->setText("Evaluation time: ");
		mBaseWidget->addChild(mEvaluationTimeLabel);

		mEvaluationTimeBs = new BoxSlider("EvaluationTimeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mEvaluationTimeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mBaseWidget->addChild(mEvaluationTimeBs);
		i++;
	}

	{
		// Evaluation type
		mEvaluationTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEvaluationTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEvaluationTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mEvaluationTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTypeLabel->setText("Evaluation type: ");
		mBaseWidget->addChild(mEvaluationTypeLabel);

		// Evaluation type Combobox
		mEvaluationTypeCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mEvaluationTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Individual evaluation", EvolutionModel::INDIVIDUAL_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		mEvaluationTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mEvaluationTypeCb->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("N Individuals Tournament",
			EvolutionModel::N_INDIVIDUALS_TOURNAMENT_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("Whole Population Tournament",
			EvolutionModel::POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem(
			"N Individuals from each Population Tournament",
			EvolutionModel::N_POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("N Populations Tournament",
			EvolutionModel::N_POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("All Populations Tournament",
			EvolutionModel::POPULATIONS_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);

		mEvaluationTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mEvaluationTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTypeCb->subscribeEvent(
			CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber(&NewPlanetPanel::onValueChanged, this));
		mBaseWidget->addChild(mEvaluationTypeCb);
		i++;
	}

	{
		// Tournament size
		mTournamentSizeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mTournamentSizeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mTournamentSizeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mTournamentSizeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mTournamentSizeLabel->setText("Tournament size: ");
		mTournamentSizeLabel->hide();
		mBaseWidget->addChild(mTournamentSizeLabel);

		mTournamentSizeBs = new BoxSlider("TournamentSizeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mTournamentSizeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mTournamentSizeBs->hide();
		mBaseWidget->addChild(mTournamentSizeBs);
		i++;
	}

	{
		mEpochNumber = static_cast<CEGUI::Editbox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Editbox"));
		mEpochNumber->setText("1");
		mEpochNumber->setSize(
			CEGUI::USize(CEGUI::UDim(0, 30), CEGUI::UDim(0, 20)));
		mEpochNumber->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.1f, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mEpochNumber);
	}

	{
		mJuryWeight = static_cast<CEGUI::Editbox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Editbox"));
		mJuryWeight->setText("1");
		mJuryWeight->setSize(
			CEGUI::USize(CEGUI::UDim(0, 30), CEGUI::UDim(0, 20)));
		mJuryWeight->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.2f, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mJuryWeight);
	}

	{
		// jury type Combobox
		mJuryType = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mJuryType->setReadOnly(true);

		// Add new juries here

		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Velocity", Jury::AVG_VELOCITY);
		mJuryType->addItem(itemCombobox);
		mJuryType->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mJuryType->setItemSelectState(itemCombobox, true);

		itemCombobox = new CEGUI::ListboxTextItem("Height", Jury::AVG_HEIGHT);
		mJuryType->addItem(itemCombobox);

		itemCombobox = new CEGUI::ListboxTextItem("GroundContactRatio",Jury::GROUND_CONTACT_RATIO);
		mJuryType->addItem(itemCombobox);

		itemCombobox = new CEGUI::ListboxTextItem("GroundContactQty",Jury::GROUND_CONTACT_QTY);
		mJuryType->addItem(itemCombobox);

		mJuryType->setSize(
			CEGUI::USize(CEGUI::UDim(0.2, 0), CEGUI::UDim(0, 200)));
		mJuryType->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.4, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mBaseWidget->addChild(mJuryType);
	}

	{
		// jury sort direction Combobox
		mDirection = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mDirection->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem("Asc",
			1);
		mDirection->addItem(itemCombobox);
		mDirection->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mDirection->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("Dsc", 0);
		mDirection->addItem(itemCombobox);

		mDirection->setSize(
			CEGUI::USize(CEGUI::UDim(0.1, 0), CEGUI::UDim(0, 200)));
		mDirection->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.6, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mBaseWidget->addChild(mDirection);
	}

	{
		/* add jury Button */
		mAddJury = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mAddJury->setText("Add Jury");
		mAddJury->setSize(
			CEGUI::USize(CEGUI::UDim(0, 100), CEGUI::UDim(0, 20)));
		mAddJury->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.8, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mAddJury->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&NewPlanetPanel::onAddJury, this));
		mBaseWidget->addChild(mAddJury);
		i++;
	}

	float juryMcHeight = 0.2;
	{
		/* MultiColumnList */
		mJuryMcl = static_cast<CEGUI::MultiColumnList*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MultiColumnList"));
		mJuryMcl->addColumn("Epoch #", 0, CEGUI::UDim(0.248f, 0));
		mJuryMcl->addColumn("JuryWeight", 1, CEGUI::UDim(0.248f, 0));
		mJuryMcl->addColumn("JuryType", 2, CEGUI::UDim(0.248f, 0));
		mJuryMcl->addColumn("Asc/Dsc", 3, CEGUI::UDim(0.248f, 0));
		mJuryMcl->setSelectionMode(CEGUI::MultiColumnList::RowSingle); // MultiColumnList::RowMultiple

		mJuryMcl->setSize(
			CEGUI::USize(CEGUI::UDim(0.9f, 0), CEGUI::UDim(juryMcHeight, 0)));
		mJuryMcl->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.1, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mJuryMcl);

	}

	{
		/* Confirm Button */
		mConfirmButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mConfirmButton->setText("Create");
		mConfirmButton->setSize(
			CEGUI::USize(CEGUI::UDim(0, 150), CEGUI::UDim(0, 20)));
		mConfirmButton->setPosition(
			CEGUI::UVector2(
				CEGUI::UDim(leftColWidth + rightColWidth / 1.5f, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset + juryMcHeight,
					0.0f)));
		mConfirmButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&NewPlanetPanel::onConfirmClicked, this));
		mBaseWidget->addChild(mConfirmButton);
	}
}

NewPlanetPanel::~NewPlanetPanel(void) {

	//Cleanup according to
	// http://cegui.org.uk/wiki/CEGUI_In_Practice_-_Introduction
	// http://cegui.org.uk/forum/viewtopic.php?t=1535
//	if (mPhysicsControllerTypeLabel) {
//		mBaseWidget->removeChild(mPhysicsControllerTypeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mPhysicsControllerTypeLabel);
////		delete mPhysicsControllerTypeLabel;
//	}
//	mPhysicsControllerTypeLabel = NULL;
//
//	if (mEnvironmentTypeLabel) {
//		mBaseWidget->removeChild(mEnvironmentTypeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEnvironmentTypeLabel);
////		delete mEnvironmentTypeLabel;
//	}
//	mEnvironmentTypeLabel = NULL;
//
//	if (mEvaluationTimeLabel) {
//		mBaseWidget->removeChild(mEvaluationTimeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTimeLabel);
////		delete mEvaluationTimeLabel;
//	}
//	mEvaluationTimeLabel = NULL;
//
//	if (mEvaluationTypeLabel) {
//		mBaseWidget->removeChild(mEvaluationTypeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTypeLabel);
////		delete mEvaluationTypeLabel;
//	}
//	mEvaluationTypeLabel = NULL;
//
//	if (mTournamentSizeLabel) {
//		mBaseWidget->removeChild(mTournamentSizeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTournamentSizeLabel);
////		delete mTournamentSizeLabel;
//	}
//	mTournamentSizeLabel = NULL;
//
//	if (mEnvironmentTypeCb) {
//		mBaseWidget->removeChild(mEnvironmentTypeCb);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEnvironmentTypeCb);
////		delete mEnvironmentTypeCb;
//	}
//	mEnvironmentTypeCb = NULL;
//
//	if (mEvaluationTimeBs) {
//		mBaseWidget->removeChild(mEvaluationTimeBs);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTimeBs);
////		delete mEvaluationTimeBs;
//	}
//	mEvaluationTimeBs = NULL;
//
//	if (mEvaluationTypeCb) {
//		mBaseWidget->removeChild(mEvaluationTypeCb);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTypeCb);
////		delete mEvaluationTypeCb;
//	}
//	mEvaluationTypeCb = NULL;
//
//	if (mTournamentSizeBs) {
//		mBaseWidget->removeChild(mTournamentSizeBs);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTournamentSizeBs);
////		delete mTournamentSizeBs;
//	}
//	mTournamentSizeBs = NULL;
//
//	if (mConfirmButton) {
//		mBaseWidget->removeChild(mConfirmButton);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mConfirmButton);
////		delete mConfirmButton;
//	}
//	mConfirmButton = NULL;
//
//	if (mEpochNumber) {
//		mBaseWidget->removeChild(mEpochNumber);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEpochNumber);
////		delete mEpochNumber;
//	}
//	mEpochNumber = NULL;
//
//	if (mJuryWeight) {
//		mBaseWidget->removeChild(mJuryWeight);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mJuryWeight);
////		delete mJuryWeight;
//	}
//	mJuryWeight = NULL;
//
//	if (mJuryType) {
//		mBaseWidget->removeChild(mJuryType);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mJuryType);
////		delete mJuryType;
//	}
//	mJuryType = NULL;
//
//	if (mDirection) {
//		mBaseWidget->removeChild(mDirection);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mDirection);
////		delete mDirection;
//	}
//	mDirection = NULL;
//
//	if (mAddJury) {
//		mBaseWidget->removeChild(mAddJury);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mAddJury);
////		delete mAddJury;
//	}
//	mAddJury = NULL;
//
//	if (mJuryMcl) {
//		mBaseWidget->removeChild(mJuryMcl);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mJuryMcl);
////		delete mJuryMcl;
//	}
//	mJuryMcl = NULL;
}

void NewPlanetPanel::onValueChanged() {
	EvolutionModel::EvaluationType evaluationType =
		(EvolutionModel::EvaluationType) mEvaluationTypeCb->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item

	switch (evaluationType) {
	case EvolutionModel::INDIVIDUAL_EVALUATION:
	case EvolutionModel::POPULATION_EVALUATION:
	case EvolutionModel::POPULATIONS_EVALUATION:
		mTournamentSizeLabel->hide();
		mTournamentSizeBs->hide();
		break;
	default:
		mTournamentSizeLabel->show();
		mTournamentSizeBs->show();
		break;
	}
}

void NewPlanetPanel::onAddJury() {
	CEGUI::ListboxTextItem* itemMultiColumnList;
	mJuryMcl->addRow();

	itemMultiColumnList = new CEGUI::ListboxTextItem(mEpochNumber->getText(),
		1);
	mJuryMcl->setItem(itemMultiColumnList, 0, mJuryMcl->getRowCount() - 1); // ColumnID, RowID

	itemMultiColumnList = new CEGUI::ListboxTextItem(mJuryWeight->getText(), 1);
	mJuryMcl->setItem(itemMultiColumnList, 1, mJuryMcl->getRowCount() - 1); // ColumnID, RowID

	itemMultiColumnList = new CEGUI::ListboxTextItem(
		mJuryType->getSelectedItem()->getText(),
		mJuryType->getSelectedItem()->getID());
	mJuryMcl->setItem(itemMultiColumnList, 2, mJuryMcl->getRowCount() - 1); // ColumnID, RowID

	itemMultiColumnList = new CEGUI::ListboxTextItem(
		mDirection->getSelectedItem()->getText(),
		mDirection->getSelectedItem()->getID());
	mJuryMcl->setItem(itemMultiColumnList, 3, mJuryMcl->getRowCount() - 1); // ColumnID, RowID

	mEpochNumber->setText("1");
	mJuryWeight->setText("1");
	CEGUI::ListboxItem* itemCombobox = mJuryType->getListboxItemFromIndex(0);
	mJuryType->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
	mJuryType->setItemSelectState(itemCombobox, true);

	itemCombobox = mDirection->getListboxItemFromIndex(0);
	mDirection->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
	mDirection->setItemSelectState(itemCombobox, true);

}

void NewPlanetPanel::onConfirmClicked() {
	PhysicsController::PhysicsModelType modelType =
		(PhysicsController::PhysicsModelType) mPhysicsControllerTypeCb->getSelectedItem()->getID(); // Retrieve the model type

	EnvironmentModel::EnvironmentType environmentType =
		(EnvironmentModel::EnvironmentType) mEnvironmentTypeCb->getSelectedItem()->getID(); // Retrieve the environment type

	int evaluationTime = mEvaluationTimeBs->getCurrentValue();

	EvolutionModel::EvaluationType evaluationType =
		(EvolutionModel::EvaluationType) mEvaluationTypeCb->getSelectedItem()->getID(); // Retrieve the evaluation type

	//TODO: Changing tournament size does not have an effect
	int tournamentSize = mTournamentSizeBs->getCurrentValue(); // Retrieve the tournament size

	//create the planet and set its serialization path
	Planet* planet = new Planet(modelType, environmentType, evaluationTime,
		evaluationType, tournamentSize);

	std::vector<Epoch*> mEpochs;

	//TODO: Make adding epochs more userfriendly
	for (int i = 0; i < mJuryMcl->getRowCount(); i++) {
		CEGUI::ListboxItem* listboxItem = mJuryMcl->getItemAtGridReference(
			CEGUI::MCLGridRef(i, 0));
		uint epochNumber = boost::lexical_cast<int>(listboxItem->getText()); // Retrieve the value of the item

		listboxItem = mJuryMcl->getItemAtGridReference(CEGUI::MCLGridRef(i, 1));
		uint juryWeight = boost::lexical_cast<int>(listboxItem->getText()); // Retrieve the value of the item

		listboxItem = mJuryMcl->getItemAtGridReference(CEGUI::MCLGridRef(i, 2));
		uint juryType = listboxItem->getID(); // Retrieve the value of the item

		listboxItem = mJuryMcl->getItemAtGridReference(CEGUI::MCLGridRef(i, 3));
		uint jurySortDirection = listboxItem->getID(); // Retrieve the value of the item

		if (mEpochs.size() < epochNumber) {
			for (int i = epochNumber - mEpochs.size(); i > 0; i--) {
				Epoch* epoch = new Epoch();
				mEpochs.push_back(epoch);
			}
		}
		mEpochs[epochNumber - 1]->addJuryType((Jury::JuryType) juryType,
			juryWeight, jurySortDirection);
	}

	for (int i = 0; i < mEpochs.size(); i++) {
		planet->addEpoch(mEpochs[i]);
	}

	//create folder for the planet
	std::string planetFolderName = std::string("Planet-")
		+ boost::lexical_cast<std::string>(
			SimulationManager::getSingleton()->getTimeStamp());
	std::string folderPath = FilesystemManipulator::createFolder(
		SimulationManager::getSingleton()->getSerializationPath(),
		planetFolderName);

	std::string planetFilePath = folderPath + std::string("/planet.pl");

	planet->setSerializationPath(planetFilePath);
	planet->save();

	SimulationManager::getSingleton()->getUniverse().addPlanet(planet);

	//set planet selected because it was the last one added
	SimulationManager::getSingleton()->getStateHandler().setCurrentlySelectedPlanet(
		planet);
	this->hide();
}
