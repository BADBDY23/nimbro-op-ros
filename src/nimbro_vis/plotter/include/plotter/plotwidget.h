// Plot widget
// Author: Max Schwarz <max.schwarz@uni-bonn.de>

#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

#include <ros/time.h>

namespace plotter
{

class Plot;

class PlotWidget : public QWidget
{
Q_OBJECT
public:
	explicit PlotWidget(QWidget* parent = 0);
	virtual ~PlotWidget();

	void addPlot(Plot* plot);

	ros::Time currentTime() const;

	inline ros::Time selectionStart() const
	{ return m_selectionStart; }

	inline ros::Time selectionEnd() const
	{ return m_selectionEnd; }
public Q_SLOTS:
	void setShowDots(bool enabled);
Q_SIGNALS:
	void timeChanged();
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void leaveEvent(QEvent *event);
	void resizeEvent(QResizeEvent *event);
private Q_SLOTS:
	void swipeFadeOut();
	void toggleDots();
private:
	QList<Plot*> m_plots;
	double m_screenScale_x;
	double m_screenScale_y;
	QPointF m_screenOffset;
	QTransform m_screenTransform;
	bool m_mousePresent; // Is the mouse on the widget or not.
	QPointF m_mouse; // current mouse location in pixel coordinates
	QPointF m_mappedMouse; // current mouse location in logical coordinates
	QPointF m_lastMouse; // last mouse location in pixel coordinates
	QPointF m_mouseDiff; // last mouse motion in pixel coordinates
	QPointF m_mappedMouseDiff; // last mouse motion in logical coordinates
	QPointF m_mouseVelocity; // estimated mouse velocity in pixels per second
	QPointF m_mappedMouseVelocity; // estimated mouse velocity in logical units per second
	QPointF m_mouseClick; // mouse click location in pixel coordinates
	QPointF m_mappedMouseClick;
	QElapsedTimer m_mouseClickElapsed;
	QPointF m_swipeFadeOutVelocity;
	QElapsedTimer m_swipeFadeOutElapsed;
	QTimer m_swipeFadeOutTimer;
	ros::Time m_currentTime;
	ros::Time m_fixedTime;

	ros::Time m_selectionStart;
	ros::Time m_selectionEnd;

	int m_currentLegendOffset;

	QFont m_font_default;
	QFont m_font_monospace;

	bool m_showDots;

	void updateMouse(QPointF mousePos);
	void updateScreenTransform();
	void drawLegend(QPainter* painter, const Plot* plot);
	QPointF scale(const QPointF& src);
	
};

}

#endif
