#include "widgets/ViewPlaneTypeWidget.h"
#include "ViewPlaneTypeWidget.uic"
#include "raycer/viewplanes/ViewPlaneFactory.h"

#include <list>

using namespace std;
using namespace raycer;

struct ViewPlaneTypeWidget::Private {
  Ui::ViewPlaneTypeWidget ui;
};

ViewPlaneTypeWidget::ViewPlaneTypeWidget(QWidget* parent)
  : QWidget(parent),
    p(std::make_unique<Private>())
{
  p->ui.setupUi(this);
  list<string> types = ViewPlaneFactory::self().identifiers();
  for (const auto& type : types) {
    p->ui.viewPlaneTypeComboBox->addItem(QString::fromStdString(type));
  }
  connect(p->ui.viewPlaneTypeComboBox, SIGNAL(activated(int)), this, SLOT(typeChanged()));
}

ViewPlaneTypeWidget::~ViewPlaneTypeWidget() {
}

string ViewPlaneTypeWidget::type() const {
  return p->ui.viewPlaneTypeComboBox->currentText().toStdString();
}

void ViewPlaneTypeWidget::typeChanged() {
  emit changed();
}

#include "ViewPlaneTypeWidget.moc"
