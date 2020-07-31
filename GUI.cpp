#include "GUI.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

GUI::GUI(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QGridLayout;
    setLayout(mainLayout);

    int row = 0;
    mainLayout->addWidget(new QLabel("Enter bits with spacer separator (etc 2 3 4)"), row, 0, 1, 3);
    row++;

    QString bitsLabelTitle("Non zero bits (ICAO order)");
    QLabel *bitsLabel = new QLabel(bitsLabelTitle);
    bitsLabel->setWordWrap(true);
    mainLayout->addWidget(bitsLabel, row, 0);
    bits = new QLineEdit;
    bits->setMinimumWidth(200);
    mainLayout->addWidget(bits, row, 1);

    QString mbLabelTitle("MB (hex)");
    mainLayout->addWidget(new QLabel(mbLabelTitle), row, 2);
    result = new QLineEdit;
    result->setMinimumWidth(200);
    mainLayout->addWidget(result, row, 3);
    row++;

    QPushButton *convertToMb = new QPushButton("Convert to MB");
    convertToMb->setMinimumWidth(100);
    mainLayout->addWidget(convertToMb, row, 1, 1, 2, Qt::AlignCenter);
    row++;

    connect(convertToMb, &QPushButton::clicked, this, &GUI::convertToMb);

    mainLayout->addWidget(new QLabel(mbLabelTitle), row, 0);
    mb = new QLineEdit;
    mb->setMinimumWidth(200);
    mainLayout->addWidget(mb, row, 1);

    bitsLabel = new QLabel(bitsLabelTitle);
    bitsLabel->setWordWrap(true);
    mainLayout->addWidget(bitsLabel, row, 2);
    bitsFromMb = new QLineEdit;
    bitsFromMb->setMinimumWidth(200);
    mainLayout->addWidget(bitsFromMb, row, 3);
    row++;

    QPushButton *convertToBits = new QPushButton("Convert from MB");
    convertToBits->setMinimumWidth(100);
    mainLayout->addWidget(convertToBits, row, 1, 1, 2, Qt::AlignCenter);

    connect(convertToBits, &QPushButton::clicked, this, &GUI::convertToBits);
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

std::vector<uint> GUI::fromReverseOrder(uint64_t mb)
{
    std::vector<uint> bits;
    QString binaryMb = QString::number(mb, 2);

    int i = 0;
    int coef = 56 - binaryMb.size() + 1;

    for (auto bit : binaryMb)
    {
        if (bit == "1")
            bits.push_back(i + coef);
        i++;
    }
    return bits;
}

void GUI::convertToMb()
{
    auto bitsString = bits->text();

    auto singleBits = bitsString.split(" ");

    if (singleBits.isEmpty())
        return;

    singleBits.removeAll("");

    std::vector<uint> bitNums;

    for (auto bitNum : singleBits)
        bitNums.push_back(bitNum.toUInt());

    auto mb = toReverseOrder(bitNums);
    result->setText(QString::number(mb, 16));
}

void GUI::convertToBits()
{
    auto bits = fromReverseOrder(mb->text().toULong(nullptr, 16));

    QString resultString;
    for (auto bit : bits)
    {
        resultString += QString::number(bit);
        if (bits.back() != bit)
            resultString += " ";
    }
    bitsFromMb->setText(resultString);
}

