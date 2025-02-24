//# corresponding headers
#include <gtest/gtest.h>
#include <model/universe/evolution/population/creature/phenome/FSPhenomeModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>
#include <utils/Randomness.hpp>

class FSPhenomeModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new FSPhenomeModel();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete phenomeModel;
		phenomeModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSPhenomeModel* phenomeModel;

	Randomness* randomness;
};

class FSPhenomeModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new FSPhenomeModel();

		phenomeModel2 = new FSPhenomeModel();

		SaveController < FSPhenomeModel > saveController;

		saveController.save(*phenomeModel, "test/FSPhenomeModel.test");

		saveController.restore(*phenomeModel2, "test/FSPhenomeModel.test");
	}

	virtual void TearDown() {
		delete phenomeModel;
		phenomeModel = NULL;
		delete phenomeModel2;
		phenomeModel2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSPhenomeModel* phenomeModel;

	FSPhenomeModel* phenomeModel2;

	Randomness* randomness;
};

TEST_F(FSPhenomeModelTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(FSPhenomeModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(phenomeModel != phenomeModel2);
	ASSERT_TRUE(phenomeModel->equals(*phenomeModel2));
}
