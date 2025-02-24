#ifndef MODEL_UNIVERSE_COLLISIONHANDLER_HPP_
#define MODEL_UNIVERSE_COLLISIONHANDLER_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The Collision handler processes collisions and distributes them to the relevant elements in the world.
 * @details		Details
 * @date		2015-08-14
 * @author		Benjamin Ellenberger
 */
bool processContactCallback(btManifoldPoint& cp, void* body0, void* body1) {
	LimbModel* limbModel1 = NULL;
	LimbModel* limbModel2 = NULL;
	btCollisionObject* o1 = static_cast<btCollisionObject*>(body0);
	btCollisionObject* o2 = static_cast<btCollisionObject*>(body1);

	//check if one is a limb and the other not (ground)
	if (o1->getUserPointer() != NULL && o2->getUserPointer() == NULL) {
		limbModel1 = static_cast<LimbModel*>(o1->getUserPointer());
		limbModel1->activateTactioceptors();
	}

	//check if one is a limb and the other not (ground)
	if (o2->getUserPointer() != NULL && o1->getUserPointer() == NULL) {
		limbModel2 = static_cast<LimbModel*>(o2->getUserPointer());
		limbModel2->activateTactioceptors();
	}

	// if both were limbs (not ground or anything else)
	if (limbModel1 != NULL && limbModel2 != NULL) {

//		float threshold = 50;
//		if (limbModel1->getVelocities().length() > threshold) {
//			std::cout << limbModel1->getVelocities().x
//				<< limbModel1->getVelocities().y
//				<< limbModel1->getVelocities().z << std::endl;
//		}
		if (cp.getDistance() < PhysicsConfiguration::PENETRATION_THRESHOLD) {
//			std::cout << "Interpenetration depth:" << cp.getDistance()
//				<< std::endl;
			limbModel1->setInterpenetrationDepth(
				limbModel1->getInterpenetrationDepth()
					+ cp.getDistance() / limbModel1->getDimensions().length());
			limbModel2->setInterpenetrationDepth(
				limbModel2->getInterpenetrationDepth()
					+ cp.getDistance() / limbModel2->getDimensions().length());
		}
	}

	return false; //ignore according to the documentation.
}

#endif /* MODEL_UNIVERSE_COLLISIONHANDLER_HPP_ */
