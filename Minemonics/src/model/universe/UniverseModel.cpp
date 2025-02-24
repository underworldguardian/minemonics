//# corresponding headers
#include <model/universe/UniverseModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

UniverseModel::UniverseModel() :
	mEvaluatingPlanetIndex(0) {
}

UniverseModel::~UniverseModel() {
//	mCurrentEvaluationPlanetIndex

	for (std::vector<EvaluationModel*>::iterator eit =
		mEvaluationModels.begin(); eit != mEvaluationModels.end(); eit++) {
		delete (*eit);
	}
	mEvaluationModels.clear();

	mPlanetModels.clear(); // planetmodels are deleted in the planet controllers
}

void UniverseModel::initialize() {
}

void UniverseModel::addPlanetModel(PlanetModel* const planetModel) {
	mPlanetModels.push_back(planetModel);
}

void UniverseModel::proceedEvaluation() {

}
