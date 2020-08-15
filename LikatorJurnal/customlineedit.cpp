#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit(parent) {
    setInputMask("8(000)0000000");
}

void CustomLineEdit::mousePressEvent(QMouseEvent *event){
    QLineEdit::mousePressEvent(event);
    setCursorPosition(2);
}
