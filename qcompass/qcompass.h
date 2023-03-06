#ifndef QCOMPASS_H
#define QCOMPASS_H

#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

#define DEF_WEST_LABEL "W"
#define DEF_NORTH_LABEL "N"
#define DEF_EAST_LABEL "E"
#define DEF_SOUTH_LABEL "S"

class QDESIGNER_WIDGET_EXPORT QCompass : public QWidget {
  Q_OBJECT
public:
  explicit QCompass(QWidget *parent = nullptr);

  constexpr static const float DEF_RANGE = 180.0f;
  constexpr static const float DEF_BEARING = 0.0f;
  constexpr static const float DEF_HEADING = 0.0f;

  constexpr static const float MARKER_HEIGHT_FACTOR = 3.0f;
  constexpr static const float MARKER_WIDTH_RATIO = 0.06f;

  constexpr static const float INDICATOR_HEIGHT_RATIO = 0.75f;
  constexpr static const float INDICATOR_WIDTH_RATIO = 0.3f;

  constexpr static const int DEF_FONT_RATIO = 4;
  constexpr static const int ANGLE_STEPPING = 5;
  constexpr static const int UNIT_HEIGHT_RATIO = 4;
  constexpr static const int TEXT_OFFSET = 10;
  constexpr static const int MAX_RANGE = 360;
  constexpr static const int MIN_RANGE = 30;
  constexpr static const int MEASURE_WIDTH_FACTOR = 50;
  constexpr static const int MEASURE_HEIGHT_FACTOR = 30;
  constexpr static const int TERTIARY_LINE_HEIGHT = 10;
  constexpr static const int SECONDARY_LINE_HEIGHT = 8;
  constexpr static const int MAIN_LINE_HEIGHT = 6;

  constexpr static const float TERTIARY_LINE_THICKNESS = 1.0f;
  constexpr static const float SECONDARY_LINE_THICKNESS = 2.0f;
  constexpr static const float MAIN_LINE_THICKNESS = 3.0f;

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  QColor backgroundColor() const;
  void setBackgroundColor(const QColor &backgroundColor);

  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY
                 lineColorChanged)
  QColor lineColor() const;
  void setLineColor(const QColor &lineColor);

  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY
                 textColorChanged)
  QColor textColor() const;
  void setTextColor(const QColor &textColor);

  Q_PROPERTY(QColor headingColor READ headingColor WRITE setHeadingColor NOTIFY
                 headingColorChanged)
  QColor headingColor() const;
  void setHeadingColor(const QColor &headingColor);

  Q_PROPERTY(QColor bearingColor READ bearingColor WRITE setBearingColor NOTIFY
                 bearingColorChanged)
  QColor bearingColor() const;
  void setBearingColor(const QColor &bearingColor);

  Q_PROPERTY(QColor indicatorColor READ indicatorColor WRITE setIndicatorColor
                 NOTIFY indicatorColorChanged)
  QColor indicatorColor() const;
  void setIndicatorColor(const QColor &indicatorColor);

  Q_PROPERTY(bool showHeading READ showHeading WRITE setShowHeading NOTIFY
                 showHeadingChanged)
  bool showHeading() const;
  void setShowHeading(bool showHeading);

  Q_PROPERTY(bool showBearing READ showBearing WRITE setShowBearing NOTIFY
                 showBearingChanged)
  bool showBearing() const;
  void setShowBearing(bool showBearing);

  Q_PROPERTY(float heading READ heading WRITE setHeading NOTIFY headingChanged)
  float heading() const;
  void setHeading(float heading);

  Q_PROPERTY(float bearing READ bearing WRITE setBearing NOTIFY bearingChanged)
  float bearing() const;
  void setBearing(float bearing);

  Q_PROPERTY(float range READ range WRITE setRange NOTIFY rangeChanged)
  float range() const;
  void setRange(float range);

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  int borderWidth() const;
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY
                 borderColorChanged)
  QColor borderColor() const;
  void setBorderColor(const QColor &borderColor);

  Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
  float opacity() const;
  void setOpacity(float opacity);

protected:
  /**
   * @brief override of base class resizeEvent
   *
   * Invoked when widget area is resized.
   * Will update internal sub-areas size accordingly with defined ratios.
   *
   * @param event Event descriptor
   * @see resize
   */
  void resizeEvent(QResizeEvent *event);
  /**
   * @brief override of base class paintEvent.
   *
   * Invoked when widget area need to be repainted.
   * Forced by repaint() method calls.
   * Will depict widget current status.
   *
   * @param event Event descriptor
   */
  void paintEvent(QPaintEvent *event);

signals:
  void backgroundColorChanged();
  void lineColorChanged();
  void textColorChanged();
  void headingColorChanged();
  void bearingColorChanged();
  void indicatorColorChanged();
  void showHeadingChanged();
  void showBearingChanged();
  void headingChanged();
  void bearingChanged();
  void rangeChanged();
  void borderWidthChanged();
  void borderColorChanged();
  void opacityChanged();

private:
  // PROPERTIES
  QColor mBackgroundColor;
  QColor mLineColor;
  QColor mTextColor;
  QColor mHeadingColor;
  QColor mBearingColor;
  QColor mIndicatorColor;
  QColor mBorderColor;
  bool mShowHeading;
  bool mShowBearing;
  int mBorderWidth;
  float mHeading;
  float mBearing;
  float mRange;
  /**
   * @brief Opacity [property].
   * @see opacity, setOpacity
   */
  float mOpacity;
  /**
   * @brief Widget internal frame
   *
   * The widget frame is evaluated as the largest square area inside designed
   * widget area. The frame is centered in widget area.
   *
   */
  QRectF mFrame;
  /**
   * @brief Opacity effect.
   *
   */
  QGraphicsOpacityEffect mOpacityEffect;

  /**
   * @brief Evaluate internal widget frame.
   *
   * @return QRectF
   */
  QRectF getFrame();

  void resize();

  void drawMarker(QPainter &painter, int x, int y, int height, int width,
                  QColor color);

  void drawIndicator(QPainter &painter, int x, int y, int height, int width,
                     QColor color);

  void drawBackground(QPainter &painter);

  void drawBearing(QPainter &painter, float pixDeg, int unitHeight);

};

#endif // QCOMPASS_H
