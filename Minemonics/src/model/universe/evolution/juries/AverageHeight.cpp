//# corresponding headers
#include <model/universe/evolution/juries/AverageHeight.hpp>

//# forward declarations
//## system headers
#include <math.h>
#include <cmath>
#include <vector>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers
#include <utils/MathUtils.hpp>

AverageHeight::AverageHeight() :
	Jury(Jury::AVG_HEIGHT, true, 1), mIsFirstTime(true), mAvgHeight(0), mSampleQty(
		0) {
}

AverageHeight::AverageHeight(const bool higherIsBetter, const double weight) :
	Jury(Jury::AVG_HEIGHT, higherIsBetter, weight), mIsFirstTime(true), mAvgHeight(
		0), mSampleQty(0) {

}

AverageHeight::~AverageHeight() {

}

void AverageHeight::calculateFitness(CreatureModel* creature,
	double timeSinceLastTick) {

	if (!mIsFirstTime) {
		int i = 0;
		double currentAvgHeight = 0;
		double totalVolume = 0;
		int segmentQty = 0;
		for (std::vector<LimbModel*>::iterator lit =
			creature->getPhenotypeModel()->getLimbModels().begin();
			lit != creature->getPhenotypeModel()->getLimbModels().end();
			lit++, i++) {
			if (MathUtils::isFinite((*lit)->getPosition())) {
				currentAvgHeight += (*lit)->getVolume()
					* ((*lit)->getPosition().y);
				totalVolume += (*lit)->getVolume();
				segmentQty++;
			}
		}
		if (totalVolume == 0 || segmentQty == 1) {

			mAvgHeight =
				(mHigherIsBetter) ? 0 : std::numeric_limits<double>::max();

		} else {
			mAvgHeight = ((mAvgHeight * mSampleQty)
				+ currentAvgHeight / totalVolume) / (mSampleQty + 1);
		}
	}

	mIsFirstTime = false;

	mSampleQty++;
}

void AverageHeight::evaluateFitness() {

	std::cout << "Average Height Fitness: " << mAvgHeight << std::endl;
	mFitness = mAvgHeight;
}

AverageHeight* AverageHeight::clone() {
	return new AverageHeight(*this);
}

std::string AverageHeight::getScoreString() {
	std::string scoreString = "Average Height Fitness : "
		+ boost::lexical_cast<std::string>(getFitness())
		+ ((isHigherBetter()) ?
			" (where higher is better)" : " (where lower is better)");
	return scoreString;
}
