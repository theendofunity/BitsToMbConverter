#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    uint64_t toReverseOrder(std::vector<uint> bitNums);
    std::vector<uint> fromReverseOrder(uint64_t mb);
    void convertToMb();
    void convertToBits();

private:
    QLineEdit *bits = nullptr;
    QLineEdit *result = nullptr;

    QLineEdit *mb = nullptr;
    QLineEdit *bitsFromMb = nullptr;
};
#endif // GUI_H
