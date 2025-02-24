#ifndef VIEW_VISUALIZATION_CEGUI_BASEPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_BASEPANEL_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/widgets/FrameWindow.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		A baseclass panel for panels.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class BasePanel {
public:
	BasePanel(const std::string name);

	virtual ~BasePanel(void);

	void initialize(const int left, const int top, const int width,
		const int height, bool withTitleBar);

	void update(); /**!< Updates the immovable panel. */

	void show(); /**!< Show the immovable panel. */

	void hide(); /**!< Hides the immovable panel. */

	// Accessor methods ##########################

	void setPosition(const int left, const int top);

	int getWidth() {
		return (mFrameWindow != NULL) ? mFrameWindow->getWidth().d_offset : 0;
	}

	int getHeight() {
		return (mFrameWindow != NULL) ? mFrameWindow->getHeight().d_offset : 0;
	}

	bool isVisible() {
		return (mFrameWindow != NULL) ? mFrameWindow->isVisible() : false;
	}

	CEGUI::FrameWindow*& getWindow() {
		return mFrameWindow;
	}

protected:
	CEGUI::FrameWindow* mFrameWindow; /** The framed window of the panel. */
	std::string mName; /**!< The name of the base panel */
	int mWidth, mHeight; /**!< The dimensions of the base panel */
};

#endif /* VIEW_VISUALIZATION_CEGUI_BASEPANEL_HPP_ */
