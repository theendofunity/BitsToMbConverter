#include "GUI.h"

#include <QVBoxLayout>
#include <QLabel>

GUI::GUI(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addWidget(new QLabel("Enter bits with spacer separator (etc 2 3 4)"));
    mainLayout->addSpacing(5);

    auto fieldsLayout = new QHBoxLayout;
    mainLayout->addLayout(fieldsLayout);

    fieldsLayout->addWidget(new QLabel("Non zero bits (ICAO order)"));
    bits = new QLineEdit;
    bits->setMinimumWidth(200);
    fieldsLayout->addWidget(bits);

    fieldsLayout->addWidget(new QLabel("MB (hex)"));
    result = new QLineEdit;
    result->setMinimumWidth(200);
    fieldsLayout->addWidget(result);

    convert = new QPushButton("Convert");
    convert->setMinimumWidth(100);
    mainLayout->addWidget(convert, 0, Qt::AlignCenter);

    connect(convert, &QPushButton::clicked, this, &GUI::createMb);
}

GUI::~GUI()
{
}

uint64_t GUI::toReverseOrder(std::vector<uint> bitNums)
{
    uint64_t mb = 0;

    for (auto &bitNum : bitNums)
    {
        mb |= 1ULL << (56 - bitNum);
    }
    return mb;
}

void GUI::createMb()
{
    auto bitsString = bits->text();
    auto singleBits = bitsString.split(" ");

    if (singleBits.isEmpty())
        return;

    std::vector<uint> bitNums;

    for (auto bitNum : singleBits)
        bitNums.push_back(bitNum.toUInt());

    auto mb = toReverseOrder(bitNums);
    result->setText(QString::number(mb, 16));
}

