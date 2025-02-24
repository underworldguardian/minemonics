#ifndef VIEW_UNIVERSE_ENVIRONMENTS_HILLSO3D_H_
#define VIEW_UNIVERSE_ENVIRONMENTS_HILLSO3D_H_

//# corresponding header
#include <view/universe/environments/EnvironmentO3D.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreLight.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The hills graphical representation in Ogre 3D.
 * @details		Details
 * @date		2015-02-12
 * @author		Benjamin Ellenberger
 */
class HillsO3D: public EnvironmentO3D {
public:
	HillsO3D();
	virtual ~HillsO3D();

	void initialize(Ogre::Light* l);
	void update();

	bool mTerrainsImported;
};

#endif /* VIEW_UNIVERSE_ENVIRONMENTS_HILLSO3D_H_ */
