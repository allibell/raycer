#pragma once

#include <QWidget>
#include <memory>

class Element;

class AbstractParameterWidget : public QWidget {
  Q_OBJECT
  
public:
  explicit AbstractParameterWidget(QWidget* parent = nullptr);
  ~AbstractParameterWidget();
  
  void setElement(Element* element);
  const QString& parameterName() const;
  virtual void setParameterName(const QString& name);
  
  virtual const QVariant value() const = 0;
  virtual void setValue(const QVariant& value) = 0;
  
signals:
  void changed(const QString&, const QVariant&);

protected slots:
  void parameterChanged();
  QVariant lastValue() const;

private:
  struct Private;
  std::unique_ptr<Private> p;
};
