/*
 * Copyright (C) 2015 ~ 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QResizeEvent>
#include <QHBoxLayout>
#include <QDebug>

#include "dspinbox.h"
#include "dthememanager.h"
#include "dlineedit.h"
#include "private/dspinbox_p.h"
#include "dimagebutton.h"

DWIDGET_BEGIN_NAMESPACE

DImageButton* DSpinBox_getButton(const QString &image_name)
{
    const QString str = ":/images/" + DThemeManager::instance()->theme() + "/images/" + image_name;

    DImageButton *button = new DImageButton(str + "_normal.png", str + "_hover.png", str + "_press.png");

    button->setObjectName("SpinBox_ImageButton");

    return button;
}

DSpinBoxPrivate::DSpinBoxPrivate(DSpinBox *parent) :
    DObjectPrivate(parent)
{

}

void DSpinBoxPrivate::init()
{
    D_Q(DSpinBox);

    insideFrame = new QFrame(q);
    insideFrame->setObjectName("SpinBoxInsideFrame");

    QHBoxLayout *h_layout = new QHBoxLayout(insideFrame);

    DImageButton *button_reset = DSpinBox_getButton("restore");
    DImageButton *button_add = DSpinBox_getButton("spinner_increase");
    DImageButton *button_sub = DSpinBox_getButton("spinner_decrease");

    h_layout->setMargin(0);
    h_layout->setSpacing(0);
    h_layout->addStretch();
    h_layout->addWidget(button_reset);
    h_layout->addWidget(button_add);
    h_layout->addWidget(button_sub);

    q->connect(button_reset, &DImageButton::clicked, q, [q, this] {
        if(defaultValue <= q->maximum() && defaultValue >= q->minimum())
            q->setValue(defaultValue);
        else
            q->setValue(q->minimum());
    });
    q->connect(button_add, &DImageButton::clicked, q, &DSpinBox::stepUp);
    q->connect(button_sub, &DImageButton::clicked, q, &DSpinBox::stepDown);
}

void DSpinBoxPrivate::_q_resizeInsideFrame(const QSize &size)
{
    insideFrame->setFixedWidth(size.width());
    insideFrame->setFixedHeight(size.height() - 1);
}

/*!
 * \class DSpinBox
 * \brief The DSpinBox class provides deepin style QSpinBox.
 *
 * Like DLineEdit, this widget can be set on alert to warn the user that the
 * input is not correct. In addition, there's a DSpinBox::defaultValue property
 * can be used to set a default value on the widget.
 */

/*!
 * \brief DSpinBox::DSpinBox constructs an instance of DSpinBox
 * \param parent is passed to QSpinBox constructor
 */
DSpinBox::DSpinBox(QWidget *parent) :
    QSpinBox(parent),
    DObject(*new DSpinBoxPrivate(this))
{
    D_THEME_INIT_WIDGET(DSpinBox, alert);

    d_func()->init();
}

/*!
 * \brief DSpinBox::lineEdit
 * \return the QLineEdit used by this spin box.
 */
QLineEdit *DSpinBox::lineEdit() const
{
    return QSpinBox::lineEdit();
}

/*!
 * \property DSpinBox::isAlert
 * \brief This property holds whether the widget on alert mode.
 */
bool DSpinBox::isAlert() const
{
    D_DC(DSpinBox);

    return d->alert;
}

/*!
 * \property DSpinBox::defaultValue
 * \brief This property holds the default value of this spin box.
 */
int DSpinBox::defaultValue() const
{
    return d_func()->defaultValue;
}

void DSpinBox::setAlert(bool alert)
{
    D_D(DSpinBox);

    if(alert == d->alert)
        return;

    d->alert = alert;

    Q_EMIT alertChanged(alert);
}

void DSpinBox::setDefaultValue(int defaultValue)
{
    D_D(DSpinBox);

    if (d->defaultValue == defaultValue)
        return;

    d->defaultValue = defaultValue;

    Q_EMIT defaultValueChanged(defaultValue);
}

void DSpinBox::resizeEvent(QResizeEvent *e)
{
    QSpinBox::resizeEvent(e);

    d_func()->_q_resizeInsideFrame(e->size());
}

DDoubleSpinBoxPrivate::DDoubleSpinBoxPrivate(DDoubleSpinBox *parent) :
    DObjectPrivate(parent)
{

}

void DDoubleSpinBoxPrivate::init()
{
    D_Q(DDoubleSpinBox);

    insideFrame = new QFrame(q);
    insideFrame->setObjectName("SpinBoxInsideFrame");

    QHBoxLayout *h_layout = new QHBoxLayout(insideFrame);

    DImageButton *button_reset = DSpinBox_getButton("restore");
    DImageButton *button_add = DSpinBox_getButton("spinner_increase");
    DImageButton *button_sub = DSpinBox_getButton("spinner_decrease");

    h_layout->setMargin(0);
    h_layout->setSpacing(0);
    h_layout->addStretch();
    h_layout->addWidget(button_reset);
    h_layout->addWidget(button_add);
    h_layout->addWidget(button_sub);

    q->connect(button_reset, &DImageButton::clicked, q, [q, this] {
        if(defaultValue < q->maximum() && defaultValue > q->minimum())
            q->setValue(defaultValue);
        else
            q->setValue(q->minimum());
    });
    q->connect(button_add, &DImageButton::clicked, q, &DSpinBox::stepUp);
    q->connect(button_sub, &DImageButton::clicked, q, &DSpinBox::stepDown);
}

void DDoubleSpinBoxPrivate::_q_resizeInsideFrame(const QSize &size)
{
    insideFrame->setFixedWidth(size.width());
    insideFrame->setFixedHeight(size.height() - 1);
}

DDoubleSpinBox::DDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent),
    DObject(*new DDoubleSpinBoxPrivate(this))
{
    D_THEME_INIT_WIDGET(DSpinBox, alert);

    d_func()->init();
}

bool DDoubleSpinBox::isAlert() const
{
    D_DC(DDoubleSpinBox);

    return d->alert;
}

double DDoubleSpinBox::defaultValue() const
{
    return d_func()->defaultValue;
}

void DDoubleSpinBox::setAlert(bool alert)
{
    D_D(DDoubleSpinBox);

    if(alert == d->alert)
        return;

    d->alert = alert;

    Q_EMIT alertChanged(alert);
}

void DDoubleSpinBox::setDefaultValue(double defaultValue)
{
    D_D(DDoubleSpinBox);

    if (d->defaultValue == defaultValue)
        return;

    d->defaultValue = defaultValue;

    Q_EMIT defaultValueChanged(defaultValue);
}

void DDoubleSpinBox::resizeEvent(QResizeEvent *e)
{
    QDoubleSpinBox::resizeEvent(e);

    d_func()->_q_resizeInsideFrame(e->size());
}

DWIDGET_END_NAMESPACE
