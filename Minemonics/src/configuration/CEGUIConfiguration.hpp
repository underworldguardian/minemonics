#ifndef CONFIGURATION_CEGUICONFIGURATION_H_
#define CONFIGURATION_CEGUICONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>

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

/**
 * @brief		The configuration of the CEGUI panels. It defines sizes of columns and text etc.
 * @details		The configuration of the CEGUI panels. It defines sizes of columns and text etc.
 * @date		2015-03-02
 * @author		Benjamin Ellenberger
 */
class CEGUIConfiguration {
public:

	static const std::string CEGUI_SCHEME;

	static const float NEW_PLANET_PANEL_LEFT_COL_WIDTH;
	static const float NEW_PLANET_PANEL_RIGHT_COL_WIDTH;

	static const float NEW_POPULATION_PANEL_LEFT_COL_WIDTH;
	static const float NEW_POPULATION_PANEL_RIGHT_COL_WIDTH;

	/**
	 * Information panel caption height
	 */
	static const float INFOPANEL_CAPTION;

	/**
	 * Information panel text height
	 */
	static const float INFOPANEL_TEXT_HEIGHT;

	/**
	 * Information panel border height
	 */
	static const float INFOPANEL_BORDER;

	/**
	 * Information panel column1 width
	 */
	static const float INFOPANEL_LEFT_COL_WIDTH;

	/**
	 * Information panel column2 width
	 */
	static const float INFOPANEL_RIGHT_COL_WIDTH;
};

#endif /* CONFIGURATION_CEGUICONFIGURATION_H_ */
