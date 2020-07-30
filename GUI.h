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
    void createMb();
private:
    QLineEdit *bits = nullptr;
    QLineEdit *result = nullptr;

    QPushButton *convert = nullptr;
};
#endif // GUI_H
