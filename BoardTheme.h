#ifndef BOARDTHEME_H
#define BOARDTHEME_H

#include <QColor>
typedef class BoardTheme{

public:
    struct SquareColours {
        QColor normal;
        QColor legal;
        QColor selected;
        QColor moveFromHighlight;
        QColor moveToHighlight;
    };
    SquareColours lightSquares = { QColor("#e9d7b4"), QColor("#CA7F69"), QColor("#f4ea8a"), QColor("#f4ea8a"), QColor("#f4ea8a") };
    SquareColours darkSquares = { QColor("#b18967"), QColor("#C2705A"), QColor("#d8c363"), QColor("#d8c363"), QColor("#d8c363") };
}Theme;

//    QColor lightSquareCol = QColor("#F0D9B5"), darkSquareCol = QColor("#B58863"), lastFromCol = QColor("#1E90FF"), LastToCol = QColor("#FFA500");
//QColor SelectedSquareCol = QColor("#FFA500");

#endif // BOARDTHEME_H
