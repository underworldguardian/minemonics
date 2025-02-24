#ifndef VIEW_PICKING_MOUSEPICKER_HPP_
#define VIEW_PICKING_MOUSEPICKER_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
class btDynamicsWorld;
namespace Ogre {
class Ray;
} /* namespace Ogre */

//# system headers
//## controller headers
//## model headers
#include <model/universe/environments/physics/BulletPicker.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The mouse picker picks the objects on screen.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class MousePicker {
public:

	MousePicker();
	virtual ~MousePicker();

	void pickBody(btDynamicsWorld* world);
	void pickBody();

	void moveBody();

	void setPicking(const bool picking) {
		mBulletPicker.setPicking(picking);
	}

	const bool isPicking() const {
		return mBulletPicker.isPicking();
	}

	Ogre::Ray getMouseRay();

private:
	BulletPicker mBulletPicker; /**!< The bullet picker */
};

#endif /* VIEW_PICKING_MOUSEPICKER_HPP_ */
