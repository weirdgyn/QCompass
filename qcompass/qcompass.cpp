#include "qcompass.h"

QCompass::QCompass(QWidget *parent)
    : QWidget{parent}
    , mBackgroundColor(Qt::black)
    , mLineColor(Qt::lightGray)
    , mTextColor(Qt::lightGray)
    , mHeadingColor(Qt::red)
    , mBearingColor(Qt::cyan)
    , mIndicatorColor(Qt::yellow)
    , mBorderColor(Qt::black)
    , mShowHeading(true)
    , mShowBearing(false)
    , mBorderWidth(1)
    , mHeading(0)
    , mBearing(0)
    , mRange(DEF_RANGE)
    , mOpacity(1)
    /*, mOpacityEffect(new QGraphicsOpacityEffect(this))*/ {
//  mOpacityEffect.setOpacity((float)(mOpacity));
//  setAutoFillBackground(true);
//  setGraphicsEffect(&mOpacityEffect);
}

QColor QCompass::backgroundColor() const { return mBackgroundColor; }

void QCompass::setBackgroundColor(const QColor &backgroundColor) {
  if (mBackgroundColor == backgroundColor)
    return;

  mBackgroundColor = backgroundColor;

  repaint();
  emit backgroundColorChanged();
}

QColor QCompass::lineColor() const { return mLineColor; }

void QCompass::setLineColor(const QColor &lineColor) {
  if (mLineColor == lineColor)
    return;

  mLineColor = lineColor;

  repaint();
  emit lineColorChanged();
}

QColor QCompass::textColor() const { return mTextColor; }

void QCompass::setTextColor(const QColor &textColor) {
  if (mTextColor == textColor)
    return;
  mTextColor = textColor;

  repaint();
  emit textColorChanged();
}

QColor QCompass::headingColor() const { return mHeadingColor; }

void QCompass::setHeadingColor(const QColor &headingColor) {
  if (mHeadingColor == headingColor)
    return;
  mHeadingColor = headingColor;

  repaint();
  emit headingColorChanged();
}

QColor QCompass::bearingColor() const { return mBearingColor; }

void QCompass::setBearingColor(const QColor &bearingColor) {
  if (mBearingColor == bearingColor)
    return;
  mBearingColor = bearingColor;

  repaint();
  emit bearingColorChanged();
}

QColor QCompass::indicatorColor() const { return mIndicatorColor; }

void QCompass::setIndicatorColor(const QColor &indicatorColor) {
  if (mIndicatorColor == indicatorColor)
    return;
  mIndicatorColor = indicatorColor;

  repaint();
  emit indicatorColorChanged();
}

bool QCompass::showHeading() const { return mShowHeading; }

void QCompass::setShowHeading(bool showHeading) {
  if (mShowHeading == showHeading)
    return;
  mShowHeading = showHeading;

  repaint();
  emit showHeadingChanged();
}

bool QCompass::showBearing() const { return mShowBearing; }

void QCompass::setShowBearing(bool showBearing) {
  if (mShowBearing == showBearing)
    return;
  mShowBearing = showBearing;

  repaint();
  emit showBearingChanged();
}

float QCompass::heading() const { return mHeading; }

void QCompass::setHeading(float heading) {
  if (qFuzzyCompare(mHeading, heading))
    return;

  mHeading = heading;

  if (mHeading < 0)
    mHeading = 0;

  if (mHeading > MAX_RANGE)
    mHeading = MAX_RANGE;

  repaint();
  emit headingChanged();
}

float QCompass::bearing() const { return mBearing; }

void QCompass::setBearing(float bearing) {
  if (qFuzzyCompare(mBearing, bearing))
    return;

  mBearing = bearing;

  if (mBearing < 0)
    mBearing = 0;

  if (mBearing > MAX_RANGE)
    mBearing = MAX_RANGE;

  repaint();
  emit bearingChanged();
}

float QCompass::range() const { return mRange; }

void QCompass::setRange(float range) {
  if (qFuzzyCompare(mRange, range))
    return;

  mRange = range;

  if (mRange < 0)
    mRange = 0;

  if (mRange > MAX_RANGE)
    mRange = MAX_RANGE;

  repaint();
  emit rangeChanged();
}

QColor QCompass::borderColor() const { return mBorderColor; }

void QCompass::setBorderColor(const QColor &borderColor) {
  if (mBorderColor == borderColor)
    return;
  mBorderColor = borderColor;

  repaint();
  emit borderColorChanged();
}

int QCompass::borderWidth() const { return mBorderWidth; }

void QCompass::setBorderWidth(int borderWidth) {
  if (mBorderWidth == borderWidth)
    return;

  mBorderWidth = borderWidth;

  resize();
  repaint();

  emit borderWidthChanged();
}

void QCompass::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);

  resize();
}

void QCompass::resize() {
  mFrame = getFrame();

  mFont.setPixelSize((float)(mFrame.height()) * DEF_FONT_RATIO);
}

QRectF QCompass::getFrame() {
  QSizeF _widgetSize =
      QSizeF(this->width() - (mBorderWidth), this->height() - (mBorderWidth));

  QRectF _frame = QRectF();
  _frame.setSize(_widgetSize);

  float _xOffset = (this->width() - _widgetSize.width()) / 2;
  float _yOffset = (this->height() - _widgetSize.height()) / 2;

  QPointF _offsetPoint(_xOffset, _yOffset);
  _frame.moveTopLeft(_offsetPoint);

  return _frame;
}

void QCompass::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter _painter(this);

  _painter.setRenderHint(QPainter::Antialiasing, true);

  drawBackground(_painter);

  _painter.setFont(mFont);

  QFontMetricsF _metrics(mFont);

  const float _pixDeg = mFrame.width() / mRange;
  const int _minDeg = qRound(mHeading - (mRange / 2.0f));
  const int _maxDeg = qRound(mHeading + (mRange / 2.0f));

  for (int _i = -180; _i < 540; _i += ANGLE_STEPPING) {
    QPen _pen;
    _pen.setColor(mLineColor);

    if ((_i >= _minDeg) && (_i <= _maxDeg)) {
      // Draw a line every ANGLE_STEPPING

      int _x1, _y1, _x2, _y2;
      QString _label;

      _label = "";

      _x1 = _x2 = mFrame.left() + _pixDeg * (_i - _minDeg);
      _y1 = mFrame.top();
      _y2 = (L3_HEIGHT_RATIO * mFrame.height()) + mFrame.top();

      _pen.setWidth(L3_THICKNESS);

      if (_i % 45 == 0) {
        // Draw a thicker line on NE/NW/SE/SW
        _pen.setWidth(L2_THICKNESS);

        _y2 = (L2_HEIGHT_RATIO * mFrame.height()) + mFrame.top();
      }

      if (_i % 90 == 0) {
        // Draw an even thicker line on cardinal directions + label
        _pen.setWidth(L1_THICKNESS);

        _y2 = (L1_HEIGHT_RATIO * mFrame.height()) + mFrame.top();

        switch (_i) {
        case -90:
        case 270:
          _label = DEF_WEST_LABEL;
          break;

        case 0:
        case 360:
          _label = DEF_NORTH_LABEL;
          break;

        case 90:
        case 450:
          _label = DEF_EAST_LABEL;
          break;

        case -180:
        case 180:
          _label = DEF_SOUTH_LABEL;
          break;
        }
      }

      _painter.setPen(_pen);

      _painter.drawLine(_x1, _y1, _x2, _y2);

      if (!_label.isEmpty()) {
        float _text_off_x = _metrics.width(_label);
        float _text_off_y = 2 * _metrics.height();

        _y1 = _text_off_y + mFrame.top();
        _x1 -= (_text_off_x / 2.0f);

        QPen _text_pen(mTextColor);

        _painter.setPen(_text_pen);

        _painter.drawText(_x1, _y1, _label);
      }
    }
  }

  if (mShowHeading)
    drawMarker(_painter,
               mFrame.center().x(),
               mFrame.top(),
               mFrame.height() * MARKER_HEIGHT_RATIO,
               mFrame.width() * MARKER_WIDTH_RATIO,
               mHeadingColor);

  if (mShowBearing)
    drawBearing(_painter, _pixDeg);
}

float QCompass::opacity() const { return mOpacity; }

void QCompass::setOpacity(float opacity) {
  if (qFuzzyCompare(mOpacity, opacity))
    return;

  mOpacity = opacity;

  if (opacity > 1 || opacity < 0)
    return;

  //mOpacityEffect.setOpacity(opacity);

  this->setWindowOpacity(mOpacity);

  repaint();
  emit opacityChanged();
}

void QCompass::drawBackground(QPainter &painter) {
  QPen _pen(mBorderColor);
  QBrush _brush(mBackgroundColor);

  _pen.setWidth(mBorderWidth);
  painter.setPen(_pen);
  painter.setBrush(_brush);
  painter.drawRect(mFrame);
}

void QCompass::drawBearing(QPainter &painter, float pixDeg) {
  float _x = 0;
  float _y = mFrame.bottom();
  float _delta = (mBearing - mHeading);
  float _indicator_w;
  float _indicator_h = mFrame.height() * INDICATOR_HEIGHT_RATIO;
  bool _draw_marker = true;

  if (_delta < 0)
    _delta += 360;

  if (_delta >= 180) {
    if (_delta > (360 - (mRange / 2)) && (_delta <= 360))
      _x = mFrame.left() + pixDeg * (_delta - 360 + (mRange / 2));
    else {
      _draw_marker = false;
      _x = mFrame.right();
      _y = mFrame.center().y();
      _indicator_w = -mFrame.height() * INDICATOR_WIDTH_RATIO;
    }
  } else if (_delta < 180) {
    if ((_delta >= 0) && (_delta < (mRange / 2)))
      _x = mFrame.left() + pixDeg * (_delta + (mRange / 2));
    else {
      _draw_marker = false;
      _x = mFrame.left();
      _y = mFrame.center().y();
      _indicator_w = mFrame.height() * INDICATOR_WIDTH_RATIO;
    }
  }

  if (_draw_marker)
    drawMarker(painter,
               _x,
               _y,
               -(mFrame.height() * MARKER_HEIGHT_RATIO),
               mFrame.width() * MARKER_WIDTH_RATIO,
               mBearingColor);
  else
    drawIndicator(painter, _x, _y, _indicator_h, _indicator_w, mIndicatorColor);
}

void QCompass::drawMarker(QPainter &painter, int x, int y, int height,
                          int width, QColor color) {
  QPolygonF _polygon;

  _polygon << QPointF(x, height + y) << QPointF(x + (width / 2), y)
           << QPointF(x - (width / 2), y) << QPointF(x, height + y);

  QPen _pen(color);

  QBrush _brush(color);
  _brush.setStyle(Qt::SolidPattern);

  painter.setPen(_pen);
  painter.setBrush(_brush);

  painter.drawPolygon(_polygon);
}

void QCompass::drawIndicator(QPainter &painter, int x, int y, int height,
                             int width, QColor color) {
  QPolygonF _polygon;

  _polygon << QPointF(x, y) << QPointF(x + width, y - (height / 2))
           << QPointF(x + width, y + (height / 2)) << QPointF(x, y);

  QPen _pen(color);

  QBrush _brush(color);
  _brush.setStyle(Qt::SolidPattern);

  painter.setPen(_pen);
  painter.setBrush(_brush);

  painter.drawPolygon(_polygon);
}
